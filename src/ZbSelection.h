#ifndef ZbSelection_h
#define ZbSelection_h

#include "Reader.h"
#include "Selector.h"
#include "Plots.cxx"


//The Selection does not have Begin, since we do not have anything to do at the begining (overall) at client
//The histograms, ..., are booked and added to output list at SlaveBegin
//We need to have terminate since we might want to do overall tasks related to this selection only. At termination, all inforamtion from slaves is added. Example task is cutflow for this selection, which need information from all slaves.
//SlaveTerminate and Terminate are here for reservation now. histograms are written back in SlaveTerminate of Processor class

class ZbSelection : public Selector {
public:
  ZbSelection() {} ;
  virtual ~ZbSelection() ;
    // These methods are called at the corresponding stage of processing of TSelector
  virtual void SlaveBegin(Reader* r) ;
  virtual void Process(Reader* r) ;
  virtual void SlaveTerminate(Reader* r) {} ;
  virtual void Terminate(TList* mergedList, std::string outFileName) ;
  //virtual void Fill_btagEffi(std::vector<JetObj> jets, std::string bTagWP="T", float w=1) ;
  //virtual void FillUnfolding(std::vector<TLorentzVector> recs, std::vector<TLorentzVector> gens, UnfoldingPlots* h, float w_all, float w_gen) ;
  //virtual void FillUnfolding_1(std::vector<TLorentzVector> recs, std::vector<TLorentzVector> gens, UnfoldingPlots* h, float w_all, float w_gen) ;

    bool IsLepton_gen(std::vector<TLorentzVector> leps, TLorentzVector jet) {
      float minDr = 1000 ;
      for (unsigned it = 0 ; it < leps.size() ; ++it) {
        float dRtmp = jet.DeltaR(leps[it]) ;
        if (dRtmp < minDr) minDr = dRtmp ;
	
      }
      return minDr <= 0.4 ;
	
    }

private:

  //histograms
  ZbPlots* h_zee_jet ;
  ZbPlots* h_zmm_jet ;
  //ZbPlots* h_zee_twojet ;
  //ZbPlots* h_zmm_twojet ;
  ZbPlots* h_zee_bjet_loose ;
  //ZbPlots* h_zee_bjet_medium ;
  //ZbPlots* h_zee_bjet_tight ;
  ZbPlots* h_zee_bjet ;
  ZbPlots* h_zee_bjet_afterMET ;
  ZbPlots* h_zmm_bjet_loose ;
  //ZbPlots* h_zmm_bjet_medium ;
  //ZbPlots* h_zmm_bjet_tight ;
  ZbPlots* h_zmm_bjet ;
  ZbPlots* h_zmm_bjet_afterMET ;
  Z2bPlots* h_zee_2bjet ;
  //Z2bPlots* h_zee_2bjet_bb ;
  //Z2bPlots* h_zee_2bjet_bX ;
  //Z2bPlots* h_zee_2bjet_XX ;
  Z2bPlots* h_zmm_2bjet ;
  //Z2bPlots* h_zmm_2bjet_bb ;
  //Z2bPlots* h_zmm_2bjet_bX ;
  //Z2bPlots* h_zmm_2bjet_XX ;

 /* ZbPlots* h_zee_bjet_deepJet ;
  ZbPlots* h_zmm_bjet_deepJet ;
  Z2bPlots* h_zee_2bjet_deepJet ;
  Z2bPlots* h_zmm_2bjet_deepJet ;*/
 
/*  EffPlots* h_eff_b ;
  EffPlots* h_eff_c ;
  EffPlots* h_eff_l ;
  EffPlots* h_eff_bdj ;
  EffPlots* h_eff_cdj ;
  EffPlots* h_eff_ldj ;*/
 
  //Unfolding Plots
 /* UnfoldingPlots* h_zee_unfolding;
  UnfoldingPlots* h_zmm_unfolding;
  UnfoldingPlots* h_zee_afterMET_unfolding;
  UnfoldingPlots* h_zmm_afterMET_unfolding; */
  

  TH1D* h_evt ;
  TH1D* h_dR_je ;
  TH1D* h_dR_jm ;
  TH1D* h_dR_DYtoQQ_Zmass ;
  TH1D* h_dR_DYtoQQ_Zmass_iso ;
  TH1D* h_dR_DYtoQQ ;
  TH1D* h_dR_DYtoQQ_pT ;
  TH1D* h_dR_DYtoQQ_iso ;
  TH1D* h_dR_DYtoQQ_iso_pT ;
  TH1D* h_nbJet_DYtoQQ ;
  TH1D* h_nMuon ;
  TH1D* h_nEle ;
  TH1D* h_nJet ;
  TH1D* h_ele_cutflow ;
  TH1D* h_muon_cutflow ;
//Hsin-Wei gen plots
  TH1D* h_genzee_cutflow ;
  TH1D* h_genzmm_cutflow ;
  
  TH1D* h_Jet_cutflow ;
  TH1D* h_zee_cutflow ;
  TH1D* h_zmm_cutflow ;
  TH1D* h_zee_cutflow_medium ;
  TH1D* h_zmm_cutflow_medium ;
  TH1D* h_zee_cutflow_tight ;
  TH1D* h_zmm_cutflow_tight ;
  TH1D* h_pt_jet_after_ele_rem ;
 
  TH1D* h_Zee_ZmassFull ;
  TH1D* h_Zmm_ZmassFull ;

  //check trigger matching
  TH1D* h_dR1_muonTrig ;
  TH1D* h_dR2_muonTrig ;
  TH1D* h_pt1_muonTrig ;
  TH1D* h_pt2_muonTrig ;
  
  TH1D* h_dR1_eleTrig ;
  TH1D* h_dR2_eleTrig ;
  TH1D* h_pt1_eleTrig ;
  TH1D* h_pt2_eleTrig ;

//check subleading jet pT
  TH1D* h_Zmm_twojet_pt_jet1 ;
  TH1D* h_Zee_twojet_pt_jet1 ; 
  TH1D* h_Zee_deltaR_ZJet1 ;
  TH1D* h_Zmm_deltaR_ZJet1 ;  

//check jet multiplicity
  
  TH1D* h_nbJet_loose ;  
  TH1D* h_nbJet_medium ;  
  TH1D* h_nbJet_tight ;  
  TH1D* h_Zee_truebJet_pt ;  
  TH1D* h_Zee_truecJet_pt ; 
  TH1D* h_Zee_truelightJet_pt ;   
  TH1D* h_Zee_nJet_trueFlav ;  
  TH1D* h_Zee_nbJet_loose_tagged ;  
  TH1D* h_Zee_bJet_pt_loose_tagged ;  

  TH1D* h_Zmm_truebJet_pt ;  
  TH1D* h_Zmm_truecJet_pt ; 
  TH1D* h_Zmm_truelightJet_pt ;   
  TH1D* h_Zmm_nJet_trueFlav ;  
  TH1D* h_Zmm_nbJet_loose_tagged ;  
  TH1D* h_Zmm_bJet_pt_loose_tagged ;  
  
  TH2D* h_fatjet_mass_n2b1 ;  
  TH2D* h_fatjet_mass_mSD ;  
  TH2D* h_fatjet_pT_mSD ; 
  TH1D* h_dR_fatjet_lepton ;  
  TH2D* h_subjets_minpT_sumpT_deltaR_nocut ;  
  
  //check AK4-AK8 mathicng
  TH1D* h_nAK4_jets ;  
  TH1D* h_nAK8_jets ;  
  TH1D* h_fatslenderjetsmatched ;   
  
  //opposite sign charge check
  TH1D* h_nEvt_oppolepsign ;     
  TH1D* h_nEvt_samelepsign ;
  //tau study
  TH1D* h_Jet_tau21 ;
  TH1D* h_Jet_tau32 ;
  
} ;

#endif
