import awkward as ak
import numpy as np
from BTVNanoCommissioning.helpers.func import flatten
from .hist_helpers import get_hist_collections, get_axes_collections

def histogrammer(
    jet_fields=None,
    obj_list=[],
    hist_collections=["custom_analysis"],
    axes_collections=["common"],
    custom_axes=None,
    **kwargs,
):
    """
    Get a dictionary of histograms from the given histogram collections with the specified axes.

        histogrammer(events.Jet.fields, obj_list=["jet0"], hist_collections=["custom_analysis"])

    Parameters:
    jet_fields (list): List of jet fields, e.g. events.Jet.fields
    obj_list (list): List of objects to build per-object histograms for, e.g. ["jet0"]
    hist_collections (list): Names of histogram collections to include (see utils/histogramming/histograms)
    axes_collections (list): Names of axes collections to include (see utils/histogramming/axes)
    custom_axes (dict): Overrides axes_collections if given.
    **kwargs: Passed through to the histogram collection functions.

    Returns:
        dict: A dictionary containing the defined histograms.
    """
    if custom_axes:
        axes = custom_axes
    else:
        axes = get_axes_collections(axes_collections)

    _hist_dict = get_hist_collections(
        axes,
        hist_collections,
        obj_list=obj_list,
        jet_fields=jet_fields,
        **kwargs,
    )

    return _hist_dict


def histo_writer(pruned_ev, output, weights, systematics, isSyst, SF_map):
    return histo_writter(pruned_ev, output, weights, systematics, isSyst, SF_map)


def histo_writter(pruned_ev, output, weights, systematics, isSyst, SF_map):
    """
    Fill histograms produced by histogrammer() for the "custom_analysis" collection
    (Zee/Zmm, AK8 leading jet).

    is_zee and is_zmm are independent, NOT mutually exclusive: an event that
    passes both selections is filled into BOTH the "zee" and "zmm" bins of the
    channel axis, once per channel, via two separate masked fill passes below.

    Expects pruned_ev to already carry these fields (see the pruned_ev
    construction block added to process_shift):
        pruned_ev.is_zee, pruned_ev.is_zmm  -- independent per-event booleans
        pruned_ev.SelJet       -- flat (non-jagged) leading AK8 jet, one per event
        pruned_ev.njet         -- number of ID'd/cleaned AK8 jets, one per event
        pruned_ev.MET          -- present on raw events already, no construction needed

    Every fill is guarded so histograms absent from `output` (not requested via
    hist_collections/obj_list) are simply skipped.
    """

    for syst in systematics:
        if isSyst == False and syst != "nominal":
            break

        weight = (
            weights.weight()
            if syst == "nominal" or syst not in list(weights.variations)
            else weights.weight(modifier=syst)
        )

        # Each channel gets its own independent masked fill pass -- an event
        # passing both is_zee and is_zmm contributes to both passes below.
        channel_masks = (
            ("zee", pruned_ev.is_zee, pruned_ev.SelElectron, "ele"),
            ("zmm", pruned_ev.is_zmm, pruned_ev.SelMuon, "mu"),
        )

        for channel_name, mask, leptons_all, lep_prefix in channel_masks:
            w = weight[mask]

            # --- Event-level ---
            if "njet" in output:
                output["njet"].fill(
                    syst=syst, channel=channel_name, njet=pruned_ev.njet[mask], weight=w
                )

            # --- MET (flat, one per event) ---
            if "MET" in pruned_ev.fields:
                if "MET_pt" in output:
                    output["MET_pt"].fill(
                        syst=syst,
                        channel=channel_name,
                        pt=pruned_ev.MET.pt[mask],
                        weight=w,
                    )

            # --- Leading jet: kinematics + substructure ---
            jet0 = pruned_ev.SelJet[mask]
            for histname, h in output.items():
                if not (
                    histname.startswith("jet")
                    and len(histname) > 3
                    and histname[3].isdigit()
                ):
                    continue
                obj_part, var = histname.split("_", 1)
                i = int(obj_part.replace("jet", ""))
                if i != 0:
                    continue  # only the leading jet ("jet0") is supported here

                if var == "tau21":
                    value = jet0.tau2 / jet0.tau1
                elif var == "tau32":
                    value = jet0.tau3 / jet0.tau2
                elif var in jet0.fields:
                    value = jet0[var]
                else:
                    continue

                h.fill(syst=syst, channel=channel_name, **{var: value}, weight=w)

            # --- Subjets of the leading jet ---
            for subjet_name, subjet_field in (
                ("subjet0", "SelSubJet0"),
                ("subjet1", "SelSubJet1"),
            ):
                if subjet_field not in pruned_ev.fields:
                    continue
                subjet = pruned_ev[subjet_field][mask]
                for var in ("pt", "eta", "phi", "mass"):
                    histname = f"{subjet_name}_{var}"
                    if histname in output and var in subjet.fields:
                        output[histname].fill(
                            syst=syst,
                            channel=channel_name,
                            **{var: subjet[var]},
                            weight=w,
                        )
            # --- Leptons: leading (idx 0) and subleading (idx 1) filled separately ---
            # --- Leptons (ele for zee, mu for zmm) ---
            leptons = leptons_all[mask]
            for idx in (0, 1):
                lep = leptons[:, idx]
                for var in ("pt", "eta", "phi"):
                    histname = f"{lep_prefix}{idx}_{var}"
                    if histname in output and var in lep.fields:
                        output[histname].fill(
                            syst=syst,
                            channel=channel_name,
                            **{var: lep[var]},
                            weight=w,
                        )

            # --- Dilepton system (leading + subleading lepton of this channel) ---
            dilep = leptons[:, 0] + leptons[:, 1]
            for var in ("pt", "mass"):
                histname = f"dilep_{var}"
                if histname in output and var in dilep.fields:
                    output[histname].fill(
                        syst=syst,
                        channel=channel_name,
                        **{var: dilep[var]},
                        weight=w,
                    )

    return output

