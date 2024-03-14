//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Feb 14 16:02:21 2020 by ROOT version 6.14/09
// from TTree Events/Events
// found on file: 8F93A522-A364-BE4A-8A5D-26591CD081F1.root
//////////////////////////////////////////////////////////

#ifndef Reader_h
#define Reader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector


class Reader : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
#if defined(DATA_preVFP2016) || defined(DATA_postVFP2016) || defined(DATA_2017) || defined(DATA_2018)
   TTreeReaderValue<UInt_t> run = {fReader, "run"};
   TTreeReaderValue<UInt_t> luminosityBlock = {fReader, "luminosityBlock"};
#endif

#if defined(MC_preVFP2016) || defined(MC_postVFP2016) || defined(MC_2017)
   TTreeReaderValue<Float_t> L1PreFiringWeight_Dn = {fReader, "L1PreFiringWeight_Dn"};
   TTreeReaderValue<Float_t> L1PreFiringWeight_Nom = {fReader, "L1PreFiringWeight_Nom"};
   TTreeReaderValue<Float_t> L1PreFiringWeight_Up = {fReader, "L1PreFiringWeight_Up"};
#endif
   
   //reco electrons
   TTreeReaderValue<UInt_t> nElectron = {fReader, "nElectron"};
   TTreeReaderArray<Float_t> Electron_pt = {fReader, "Electron_pt"};
   TTreeReaderArray<Float_t> Electron_eta = {fReader, "Electron_eta"};
   TTreeReaderArray<Float_t> Electron_deltaEtaSC = {fReader, "Electron_deltaEtaSC"};
   TTreeReaderArray<Float_t> Electron_phi = {fReader, "Electron_phi"};
   TTreeReaderArray<Float_t> Electron_mass = {fReader, "Electron_mass"};
   TTreeReaderArray<Int_t> Electron_charge = {fReader, "Electron_charge"};
   TTreeReaderArray<Int_t> Electron_cutBased = {fReader, "Electron_cutBased"};
   TTreeReaderArray<Float_t> Electron_dxy = {fReader, "Electron_dxy"};
   TTreeReaderArray<Float_t> Electron_dz = {fReader, "Electron_dz"};
   
   //reco muons
   TTreeReaderValue<UInt_t> nMuon = {fReader, "nMuon"};
   TTreeReaderArray<Float_t> Muon_pt = {fReader, "Muon_pt"};
   TTreeReaderArray<Float_t> Muon_eta = {fReader, "Muon_eta"};
   TTreeReaderArray<Float_t> Muon_phi = {fReader, "Muon_phi"};
   TTreeReaderArray<Float_t> Muon_mass = {fReader, "Muon_mass"};
   TTreeReaderArray<Int_t> Muon_charge = {fReader, "Muon_charge"};
   TTreeReaderArray<Int_t> Muon_nTrackerLayers = {fReader, "Muon_nTrackerLayers"};
   TTreeReaderArray<Float_t> Muon_pfRelIso04_all = {fReader, "Muon_pfRelIso04_all"};
   TTreeReaderArray<Bool_t> Muon_looseId = {fReader, "Muon_looseId"};
   TTreeReaderArray<Bool_t> Muon_tightId = {fReader, "Muon_tightId"};
   TTreeReaderArray<Bool_t> Muon_mediumId = {fReader, "Muon_mediumId"};
#if defined(MC_preVFP2016) || defined(MC_postVFP2016) || defined(MC_2017) || defined(MC_2018)
   TTreeReaderArray<Int_t> Muon_genPartIdx = {fReader, "Muon_genPartIdx"};
#endif   

   //GenDressedLepton_pt
#if defined(MC_preVFP2016) || defined(MC_postVFP2016) || defined(MC_2017) || defined(MC_2018)
   TTreeReaderValue<UInt_t> nGenDressedLepton = {fReader, "nGenDressedLepton"};
   TTreeReaderArray<Float_t> GenDressedLepton_eta = {fReader, "GenDressedLepton_eta"};
   TTreeReaderArray<Float_t> GenDressedLepton_mass = {fReader, "GenDressedLepton_mass"};
   TTreeReaderArray<Float_t> GenDressedLepton_phi = {fReader, "GenDressedLepton_phi"};
   TTreeReaderArray<Float_t> GenDressedLepton_pt = {fReader, "GenDressedLepton_pt"};
   TTreeReaderArray<Int_t> GenDressedLepton_pdgId = {fReader, "GenDressedLepton_pdgId"};
   TTreeReaderArray<Float_t> GenPart_pt = {fReader, "GenPart_pt"};
  
   TTreeReaderValue<UInt_t> nGenJet = {fReader, "nGenJet"};
   TTreeReaderArray<Float_t> GenJet_eta = {fReader, "GenJet_eta"};
   TTreeReaderArray<Float_t> GenJet_mass = {fReader, "GenJet_mass"};
   TTreeReaderArray<Float_t> GenJet_phi = {fReader, "GenJet_phi"};
   TTreeReaderArray<Float_t> GenJet_pt = {fReader, "GenJet_pt"};
   TTreeReaderArray<UChar_t> GenJet_hadronFlavour = {fReader, "GenJet_hadronFlavour"};
   TTreeReaderArray<Int_t> FatJet_hadronFlavour = {fReader, "FatJet_hadronFlavour"};
   TTreeReaderArray<UChar_t> FatJet_nBHadrons = {fReader, "FatJet_nBHadrons"};
   TTreeReaderArray<UChar_t> FatJet_nCHadrons = {fReader, "FatJet_nCHadrons"};
#endif

   //reco SV
   TTreeReaderValue<UInt_t> nSV = {fReader, "nSV"};
   TTreeReaderArray<Float_t> SV_eta = {fReader, "SV_eta"};
   TTreeReaderArray<Float_t> SV_mass = {fReader, "SV_mass"};
   TTreeReaderArray<Float_t> SV_phi = {fReader, "SV_phi"};
   TTreeReaderArray<Float_t> SV_pt = {fReader, "SV_pt"};

   
   //reco jets
   TTreeReaderValue<UInt_t> nJet = {fReader, "nJet"};
   TTreeReaderArray<Float_t> Jet_pt = {fReader, "Jet_pt"};
   TTreeReaderArray<Float_t> Jet_eta = {fReader, "Jet_eta"};
   TTreeReaderArray<Float_t> Jet_phi = {fReader, "Jet_phi"};
   TTreeReaderArray<Float_t> Jet_mass = {fReader, "Jet_mass"};
   TTreeReaderArray<Float_t> Jet_btagDeepB = {fReader, "Jet_btagDeepB"};
   TTreeReaderArray<Float_t> Jet_btagDeepFlavB = {fReader, "Jet_btagDeepFlavB"};
   TTreeReaderArray<Int_t> Jet_jetId = {fReader, "Jet_jetId"};
   TTreeReaderArray<Float_t> Jet_puIdDisc = {fReader, "Jet_puIdDisc"};

   //reco fatjets

   TTreeReaderValue<UInt_t> nFatJet = {fReader, "nFatJet"};
   TTreeReaderArray<Float_t> FatJet_phi = {fReader, "FatJet_phi"};
   TTreeReaderArray<Float_t> FatJet_pt = {fReader, "FatJet_pt"};
   TTreeReaderArray<Float_t> FatJet_eta = {fReader, "FatJet_eta"};
   TTreeReaderArray<Float_t> FatJet_mass = {fReader, "FatJet_mass"};
   TTreeReaderArray<Float_t> FatJet_area = {fReader, "FatJet_area"};
   TTreeReaderArray<Float_t> FatJet_btagCSVV2 = {fReader, "FatJet_btagCSVV2"};
   TTreeReaderArray<Float_t> FatJet_btagDDBvLV2 = {fReader, "FatJet_btagDDBvLV2"};
   TTreeReaderArray<Float_t> FatJet_btagDDCvBV2 = {fReader, "FatJet_btagDDCvBV2"};
   TTreeReaderArray<Float_t> FatJet_btagDDCvLV2 = {fReader, "FatJet_btagDDCvLV2"};
   TTreeReaderArray<Float_t> FatJet_btagDeepB = {fReader, "FatJet_btagDeepB"};
   TTreeReaderArray<Float_t> FatJet_btagHbb = {fReader, "FatJet_btagHbb"};
   TTreeReaderArray<Float_t> FatJet_deepTagMD_H4qvsQCD = {fReader, "FatJet_deepTagMD_H4qvsQCD"};
   TTreeReaderArray<Float_t> FatJet_deepTagMD_HbbvsQCD = {fReader, "FatJet_deepTagMD_HbbvsQCD"};
   TTreeReaderArray<Float_t> FatJet_deepTagMD_TvsQCD = {fReader, "FatJet_deepTagMD_TvsQCD"};
   TTreeReaderArray<Float_t> FatJet_deepTagMD_WvsQCD = {fReader, "FatJet_deepTagMD_WvsQCD"};
   TTreeReaderArray<Float_t> FatJet_deepTagMD_ZHbbvsQCD = {fReader, "FatJet_deepTagMD_ZHbbvsQCD"};
   TTreeReaderArray<Float_t> FatJet_deepTagMD_ZHccvsQCD = {fReader, "FatJet_deepTagMD_ZHccvsQCD"};
   TTreeReaderArray<Float_t> FatJet_deepTagMD_ZbbvsQCD = {fReader, "FatJet_deepTagMD_ZbbvsQCD"};
   TTreeReaderArray<Float_t> FatJet_deepTagMD_ZvsQCD = {fReader, "FatJet_deepTagMD_ZvsQCD"};
   TTreeReaderArray<Float_t> FatJet_deepTagMD_bbvsLight = {fReader, "FatJet_deepTagMD_bbvsLight"};
   TTreeReaderArray<Float_t> FatJet_deepTagMD_ccvsLight = {fReader, "FatJet_deepTagMD_ccvsLight"};
   TTreeReaderArray<Float_t> FatJet_deepTag_H = {fReader, "FatJet_deepTag_H"};
   TTreeReaderArray<Float_t> FatJet_deepTag_QCD = {fReader, "FatJet_deepTag_QCD"};
   TTreeReaderArray<Float_t> FatJet_deepTag_QCDothers = {fReader, "FatJet_deepTag_QCDothers"};
   TTreeReaderArray<Float_t> FatJet_deepTag_TvsQCD = {fReader, "FatJet_deepTag_TvsQCD"};
   TTreeReaderArray<Float_t> FatJet_deepTag_WvsQCD = {fReader, "FatJet_deepTag_WvsQCD"};
   TTreeReaderArray<Float_t> FatJet_deepTag_ZvsQCD = {fReader, "FatJet_deepTag_ZvsQCD"};
   TTreeReaderArray<Float_t> FatJet_msoftdrop = {fReader, "FatJet_msoftdrop"};
   TTreeReaderArray<Float_t> FatJet_n2b1 = {fReader, "FatJet_n2b1"};
   TTreeReaderArray<Float_t> FatJet_n3b1 = {fReader, "FatJet_n3b1"};
   TTreeReaderArray<Float_t> FatJet_particleNetMD_QCD = {fReader, "FatJet_particleNetMD_QCD"};
   TTreeReaderArray<Float_t> FatJet_particleNetMD_Xbb = {fReader, "FatJet_particleNetMD_Xbb"};
   TTreeReaderArray<Float_t> FatJet_particleNetMD_Xcc = {fReader, "FatJet_particleNetMD_Xcc"};
   TTreeReaderArray<Float_t> FatJet_particleNetMD_Xqq = {fReader, "FatJet_particleNetMD_Xqq"};
   TTreeReaderArray<Float_t> FatJet_particleNet_H4qvsQCD = {fReader, "FatJet_particleNet_H4qvsQCD"};
   TTreeReaderArray<Float_t> FatJet_particleNet_HbbvsQCD = {fReader, "FatJet_particleNet_HbbvsQCD"};
   TTreeReaderArray<Float_t> FatJet_particleNet_HccvsQCD = {fReader, "FatJet_particleNet_HccvsQCD"};
   TTreeReaderArray<Float_t> FatJet_particleNet_QCD = {fReader, "FatJet_particleNet_QCD"};
   TTreeReaderArray<Float_t> FatJet_particleNet_TvsQCD = {fReader, "FatJet_particleNet_TvsQCD"};
   TTreeReaderArray<Float_t> FatJet_particleNet_WvsQCD = {fReader, "FatJet_particleNet_WvsQCD"};
   TTreeReaderArray<Float_t> FatJet_particleNet_ZvsQCD = {fReader, "FatJet_particleNet_ZvsQCD"};
   TTreeReaderArray<Float_t> FatJet_particleNet_mass = {fReader, "FatJet_particleNet_mass"};
   TTreeReaderArray<Float_t> FatJet_rawFactor = {fReader, "FatJet_rawFactor"};
   TTreeReaderArray<Float_t> FatJet_tau1 = {fReader, "FatJet_tau1"};
   TTreeReaderArray<Float_t> FatJet_tau2 = {fReader, "FatJet_tau2"};
   TTreeReaderArray<Float_t> FatJet_tau3 = {fReader, "FatJet_tau3"};
   TTreeReaderArray<Float_t> FatJet_tau4 = {fReader, "FatJet_tau4"};
   TTreeReaderArray<Float_t> FatJet_lsf3 = {fReader, "FatJet_lsf3"};
   TTreeReaderArray<Int_t> FatJet_jetId = {fReader, "FatJet_jetId"};
   TTreeReaderArray<Int_t> FatJet_subJetIdx1 = {fReader, "FatJet_subJetIdx1"};
   TTreeReaderArray<Int_t> FatJet_subJetIdx2 = {fReader, "FatJet_subJetIdx2"};
   TTreeReaderArray<Int_t> FatJet_electronIdx3SJ = {fReader, "FatJet_electronIdx3SJ"};
   TTreeReaderArray<Int_t> FatJet_muonIdx3SJ = {fReader, "FatJet_muonIdx3SJ"};
   

   //MET 
   TTreeReaderValue<Float_t> MET_pt = {fReader, "MET_pt"};
   TTreeReaderValue<Float_t> PuppiMET_pt = {fReader, "PuppiMET_pt"};
   TTreeReaderValue<Float_t> MET_significance = {fReader, "MET_significance"};

   //muon trigger
   TTreeReaderValue<Bool_t> HLT_IsoMu24 = {fReader, "HLT_IsoMu24"};
   TTreeReaderValue<Bool_t> HLT_IsoMu27 = {fReader, "HLT_IsoMu27"};
#if defined(MC_preVFP2016) || defined(MC_postVFP2016) || defined(DATA_preVFP2016) || defined(DATA_postVFP2016)
   TTreeReaderValue<Bool_t> HLT_IsoTkMu24 = {fReader, "HLT_IsoTkMu24"};
#endif
   //ele trigger
#if defined(MC_preVFP2016) || defined(MC_postVFP2016) || defined(DATA_preVFP2016) || defined(DATA_postVFP2016)
   TTreeReaderValue<Bool_t> HLT_Ele27_WPTight_Gsf = {fReader, "HLT_Ele27_WPTight_Gsf"};
#endif
#if defined(MC_2017) || defined(DATA_2017)
   TTreeReaderValue<Bool_t> HLT_Ele32_WPTight_Gsf_L1DoubleEG = {fReader, "HLT_Ele32_WPTight_Gsf_L1DoubleEG"};
#endif 
#if defined(MC_2018) || defined(DATA_2018)
   TTreeReaderValue<Bool_t> HLT_Ele32_WPTight_Gsf = {fReader, "HLT_Ele32_WPTight_Gsf"};
#endif

   //trigger objects
   TTreeReaderValue<UInt_t> nTrigObj = {fReader, "nTrigObj"};
   TTreeReaderArray<Float_t> TrigObj_pt = {fReader, "TrigObj_pt"};
   TTreeReaderArray<Float_t> TrigObj_eta = {fReader, "TrigObj_eta"};
   TTreeReaderArray<Float_t> TrigObj_phi = {fReader, "TrigObj_phi"};
   TTreeReaderArray<Int_t> TrigObj_id = {fReader, "TrigObj_id"};
   TTreeReaderArray<Int_t> TrigObj_filterBits = {fReader, "TrigObj_filterBits"};

#if defined(MC_preVFP2016) || defined(MC_postVFP2016) || defined(MC_2017) || defined(MC_2018)
   TTreeReaderValue<Float_t> Pileup_nTrueInt = {fReader, "Pileup_nTrueInt"};
   TTreeReaderValue<Float_t> genWeight = {fReader, "genWeight"};
   TTreeReaderArray<Int_t> Jet_hadronFlavour = {fReader, "Jet_hadronFlavour"};
#endif


   Reader(TTree * /*tree*/ =0) {}

   virtual ~Reader() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(Reader,0);

};

#endif

#ifdef Reader_cxx
void Reader::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t Reader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef Reader_cxx
