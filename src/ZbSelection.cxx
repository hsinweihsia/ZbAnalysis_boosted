#define ZbSelection_cxx

#include <math.h>
#include <iostream>

#include "TList.h"
#include "TParameter.h"
#include "TLorentzVector.h"

#include "ZbSelection.h"
#include "Global.h"
#include "Obj.cxx"

#include "TH1.h"

//#include "BTagCalibrationStandalone.h"
//#include "BTagCalibrationStandalone.cpp"

using namespace std;
float PI = M_PI;

//ZbSelection::ZbSelection(bool isData, std::string year) : Selector(isData, year), h_zee_jet(0), h_zmm_jet(0) {}

ZbSelection::~ZbSelection() {
  //if (h_zee_jet) delete h_zee_jet;
  //if (h_zmm_jet) delete h_zmm_jet;
} 

void ZbSelection::SlaveBegin(Reader* r) {
 h_evt = new TH1D("Nevt","",4,-1.5,2.5) ; //bin 1: total negative weight events, bin 2: total positive weight events, bin 3: total event weighted by genWeight (= bin2 - bin1, if genWeight are always -1,1
  h_zee_jet = new ZbPlots("Zee_jet") ;
  //h_zee_twojet = new ZbPlots("Zee_twojet") ;
  h_zee_bjet = new ZbPlots("Zee_bjet") ;
  h_zee_bjet_loose = new ZbPlots("Zee_bjet_loose") ;
  //h_zee_bjet_medium = new ZbPlots("Zee_bjet_medium") ;
  //h_zee_bjet_tight = new ZbPlots("Zee_bjet_tight") ;
  h_zee_bjet_afterMET = new ZbPlots("Zee_bjet_afterMET") ;
  h_zee_2bjet = new Z2bPlots("Zee_2bjet") ;

  //h_zee_2bjet_bb = new Z2bPlots("Zee_2bjet_bb") ; //two tagged bjets are bb
  //h_zee_2bjet_bX = new Z2bPlots("Zee_2bjet_bX") ; //two tagged bjets are bb
  //h_zee_2bjet_XX = new Z2bPlots("Zee_2bjet_XX") ; //two tagged bjets are bb
  //h_zee_bjet_deepJet = new ZbPlots("Zee_bjetDeepJet") ;
  //h_zee_2bjet_deepJet = new Z2bPlots("Zee_2bjetDeepJet") ;
  
  h_zmm_jet = new ZbPlots("Zmm_jet") ;
  //h_zmm_twojet = new ZbPlots("Zmm_twojet") ;
  h_zmm_bjet = new ZbPlots("Zmm_bjet") ;
  h_zmm_bjet_loose = new ZbPlots("Zmm_bjet_loose") ;
  //h_zmm_bjet_medium = new ZbPlots("Zmm_bjet_medium") ;
  //h_zmm_bjet_tight = new ZbPlots("Zmm_bjet_tight") ;
  h_zmm_bjet_afterMET = new ZbPlots("Zmm_bjet_afterMET") ;
  h_zmm_2bjet = new Z2bPlots("Zmm_2bjet") ;
  //h_zmm_2bjet_bb = new Z2bPlots("Zmm_2bjet_bb") ; //two tagged bjets are bb
  //h_zmm_2bjet_bX = new Z2bPlots("Zmm_2bjet_bX") ; //two tagged bjets are bb
  //h_zmm_2bjet_XX = new Z2bPlots("Zmm_2bjet_XX") ; //two tagged bjets are bb
  //h_zmm_bjet_deepJet = new ZbPlots("Zmm_bjetDeepJet") ;
  //h_zmm_2bjet_deepJet = new Z2bPlots("Zmm_2bjetDeepJet") ;
  
  /*unsigned nBins = 9 ;
  float bins[10] = {20, 30, 50, 70, 100, 140, 200, 300, 600, 1000} ;
  h_eff_b = new EffPlots("b", nBins, bins) ;
  h_eff_c = new EffPlots("c", nBins, bins) ;
  h_eff_l = new EffPlots("l", nBins, bins) ;
  h_eff_bdj = new EffPlots("bdj", nBins, bins) ;
  h_eff_cdj = new EffPlots("cdj", nBins, bins) ;
  h_eff_ldj = new EffPlots("ldj", nBins, bins) ;

  //Unfolding plots
  h_zee_unfolding = new UnfoldingPlots("zee");
  h_zmm_unfolding = new UnfoldingPlots("zmm");
  
  h_zee_afterMET_unfolding = new UnfoldingPlots("zee_afterMET");
  h_zmm_afterMET_unfolding = new UnfoldingPlots("zmm_afterMET");*/

  h_dR_je = new TH1D("h_dR_je","",500,0,5) ;
  h_dR_jm = new TH1D("h_dR_jm","",500,0,5) ;
  h_dR_DYtoQQ = new TH1D("h_dR_DYtoQQ","",500,0,5) ;
  h_dR_DYtoQQ_Zmass = new TH1D("h_dR_DYtoQQ_Zmass","",300,0,300) ;
  h_dR_DYtoQQ_Zmass_iso = new TH1D("h_dR_DYtoQQ_Zmass_iso","",300,0,300) ;
  h_dR_DYtoQQ_pT = new TH1D("h_dR_DYtoQQ_pT","",500,0,5) ;
  h_dR_DYtoQQ_iso = new TH1D("h_dR_DYtoQQ_iso","",500,0,5) ;
  h_dR_DYtoQQ_iso_pT = new TH1D("h_dR_DYtoQQ_iso_pT","",500,0,5) ;
  h_nbJet_DYtoQQ = new TH1D("h_nbJet_DYtoQQ","",10,-0.5,9.5) ;

  h_Zee_ZmassFull = new TH1D("Zee_ZmassFull","",300,0,300) ;
  h_Zmm_ZmassFull = new TH1D("Zmm_ZmassFull","",300,0,300) ;

  h_nMuon = new TH1D("h_nMuon","",10,-0.5,9.5) ;
  h_nEle = new TH1D("h_nEle","",10,-0.5,9.5) ;
  h_nJet = new TH1D("h_nJet","",10,-0.5,9.5) ;

  h_ele_cutflow = new TH1D("ele_cutflow","",10,-0.5,9.5) ;
  h_muon_cutflow = new TH1D("muon_cutflow","",10,-0.5,9.5) ;
//Hsin-Wei: gen cutflow
  h_genzee_cutflow = new TH1D("genzee_cutflow","",10,-0.5,9.5) ;
  h_genzmm_cutflow = new TH1D("genzmm_cutflow","",10,-0.5,9.5) ;

  h_Jet_cutflow = new TH1D("Jet_cutflow","",10,-0.5,9.5) ;
  h_zee_cutflow = new TH1D("zee_cutflow","",10,-0.5,9.5) ;
  h_zmm_cutflow = new TH1D("zmm_cutflow","",10,-0.5,9.5) ;
  h_zee_cutflow_medium = new TH1D("zee_cutflow_medium","",10,-0.5,9.5) ;
  h_zmm_cutflow_medium = new TH1D("zmm_cutflow_medium","",10,-0.5,9.5) ;
  h_zee_cutflow_tight = new TH1D("zee_cutflow_tight","",10,-0.5,9.5) ;
  h_zmm_cutflow_tight = new TH1D("zmm_cutflow_tight","",10,-0.5,9.5) ;

  h_pt_jet_after_ele_rem = new TH1D("jet_pt_after_ele_rem","",200,0.0,200) ;
  h_dR1_muonTrig = new TH1D("dR1_muonTrig","",100,0,10) ;
  h_dR2_muonTrig = new TH1D("dR2_muonTrig","",100,0,10) ;
  h_pt1_muonTrig = new TH1D("pt1_muonTrig","",200,0,200) ;
  h_pt2_muonTrig = new TH1D("pt2_muonTrig","",200,0,200) ;
  
  h_dR1_eleTrig = new TH1D("dR1_eleTrig","",100,0,10) ;
  h_dR2_eleTrig = new TH1D("dR2_eleTrig","",100,0,10) ;
  h_pt1_eleTrig = new TH1D("pt1_eleTrig","",200,0,200) ;
  h_pt2_eleTrig = new TH1D("pt2_eleTrig","",200,0,200) ;


  h_Zmm_twojet_pt_jet1 = new TH1D("Zmm_twojet_pt_jet1","",1000,0.,1000.) ;
  h_Zee_twojet_pt_jet1 = new TH1D("Zee_twojet_pt_jet1","",1000,0.,1000.) ;
  h_Zee_deltaR_ZJet1 = new TH1D("Zee_deltaR_ZJet1","",10000,-0.5,9.5) ;
  h_Zmm_deltaR_ZJet1 = new TH1D("Zmm_deltaR_ZJet1","",10000,-0.5,9.5) ;

  
  h_nbJet_medium = new TH1D ("h_nbJet_medium","",10,-0.5,9.5) ;
  h_nbJet_tight = new TH1D ("h_nbJet_tight","",10,-0.5,9.5) ;
  h_Zee_truebJet_pt = new TH1D ("h_Zee_truebJet_pt","",1000,0.,1000.) ;
  h_Zee_truecJet_pt = new TH1D ("h_Zee_truecJet_pt","",1000,0.,1000.) ;
  h_Zee_truelightJet_pt = new TH1D ("h_Zee_truelightJet_pt","",1000,0.,1000.) ;
  h_Zee_nJet_trueFlav = new TH1D("h_Zee_nJet_trueFlav","",10,-0.5,9.5) ;
  h_Zee_nbJet_loose_tagged = new TH1D("h_Zee_nbJet_loose_tagged","",10,-0.5,9.5) ;
  h_Zee_bJet_pt_loose_tagged = new TH1D("h_Zee_bJet_pt_loose_tagged","",3000,0.0,3000) ;

  h_Zmm_truebJet_pt = new TH1D ("h_Zmm_truebJet_pt","",1000,0.,1000.) ;
  h_Zmm_truecJet_pt = new TH1D ("h_Zmm_truecJet_pt","",1000,0.,1000.) ;
  h_Zmm_truelightJet_pt = new TH1D ("h_Zmm_truelightJet_pt","",1000,0.,1000.) ;
  h_Zmm_nJet_trueFlav = new TH1D("h_Zmm_nJet_trueFlav","",10,-0.5,9.5) ;
  h_Zmm_nbJet_loose_tagged = new TH1D("h_Zmm_nbJet_loose_tagged","",10,-0.5,9.5) ;
  h_Zmm_bJet_pt_loose_tagged = new TH1D("h_Zmm_bJet_pt_loose_tagged","",3000,0.0,3000) ;
  
  h_fatjet_mass_n2b1 = new TH2D("h_fatjet_mass_n2b1","",25,0,0.5,20,0,200) ;
  h_fatjet_mass_mSD = new TH2D("h_fatjet_mass_mSD","",30,0,300,30,0,300) ;
  h_fatjet_pT_mSD = new TH2D("h_fatjet_pT_mSD","",100,0,1000,30,0,300) ;
  h_dR_fatjet_lepton  = new TH1D ("h_dR_fatjet_lepton","",1000,0.,10.) ;
  h_subjets_minpT_sumpT_deltaR_nocut = new TH2D("h_subjets_minpT_sumpT_deltaR_nocut","",1000,0,10,10000,-0.5,9.5) ;
  
  //AK4-AK8 matching study
  h_nAK4_jets = new TH1D("nAK4_jets","",10,-0.5,9.5) ;
  h_nAK8_jets = new TH1D("nAK8_jets","",10,-0.5,9.5) ;
  h_fatslenderjetsmatched = new TH1D("fatslenderjetsmatched","",10,-0.5,9.5) ;
  
  //opposite sign charge check
  h_nEvt_oppolepsign = new TH1D("nEvt_oppolepsign","",10,-0.5,9.5) ;
  h_nEvt_samelepsign = new TH1D("nEvt_samelepsign","",10,-0.5,9.5) ;
  //tau study
  h_Jet_tau21 = new TH1D ("Jet_tau21","",20,0.0,1.0);
  h_Jet_tau32 = new TH1D ("Jet_tau32","",20,0.0,1.0);

  //Sumw2
 h_Zee_ZmassFull->Sumw2() ;
  h_Zmm_ZmassFull->Sumw2() ;
  h_Jet_tau21->Sumw2();
  h_Jet_tau32->Sumw2();

  //Add histograms to fOutput so they can be saved in Processor::SlaveTerminate
  r->GetOutputList()->Add(h_evt) ;

  std::vector<TH1*> tmp = h_zee_jet->returnHisto() ;
  for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);

  tmp = h_zmm_jet->returnHisto() ;
  for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);

  //tmp = h_zee_twojet->returnHisto() ;
  //for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);

  //tmp = h_zmm_twojet->returnHisto() ;
  //for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);

  tmp = h_zee_bjet->returnHisto() ;
  for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]); 

  tmp = h_zee_bjet_loose->returnHisto() ;
  for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);

  //tmp = h_zee_bjet_medium->returnHisto() ;
  //for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);
  
  //tmp = h_zee_bjet_tight->returnHisto() ;
  //for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);

  tmp = h_zee_bjet_afterMET->returnHisto() ;
  for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);

  tmp = h_zmm_bjet->returnHisto() ;
  for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);
  
  tmp = h_zmm_bjet_loose->returnHisto() ;
  for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);

  //tmp = h_zmm_bjet_medium->returnHisto() ;
  //for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);

  //tmp = h_zmm_bjet_tight->returnHisto() ;
  //for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);
  
  tmp = h_zmm_bjet_afterMET->returnHisto() ;
  for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);

  tmp = h_zee_2bjet->returnHisto() ;
  for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);
  
  //tmp = h_zee_2bjet_bb->returnHisto() ;
  //for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);
  
  //tmp = h_zee_2bjet_bX->returnHisto() ;
  //for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);

  //tmp = h_zee_2bjet_XX->returnHisto() ;
  //for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);
  
  tmp = h_zmm_2bjet->returnHisto() ;
  for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);

  //tmp = h_zmm_2bjet_bb->returnHisto() ;
  //for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);
  
  //tmp = h_zmm_2bjet_bX->returnHisto() ;
  //for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);

  //tmp = h_zmm_2bjet_XX->returnHisto() ;
  //for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);
  
  //tmp = h_zee_bjet_deepJet->returnHisto() ;
  //for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);
  
  //tmp = h_zmm_bjet_deepJet->returnHisto() ;
  //for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);

  //tmp = h_zee_2bjet_deepJet->returnHisto() ;
  //for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);
  
  //tmp = h_zmm_2bjet_deepJet->returnHisto() ;
  //for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);
  
 /* tmp = h_eff_b->returnHisto() ;
  for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);
  tmp = h_eff_c->returnHisto() ;
  for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);
  tmp = h_eff_l->returnHisto() ;
  for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);
  tmp = h_eff_bdj->returnHisto() ;
  for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);
  tmp = h_eff_cdj->returnHisto() ;
  for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);
  tmp = h_eff_ldj->returnHisto() ;
  for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);*/

  //Unfolding plots 
 /* tmp = h_zee_unfolding->returnHisto() ;
  for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);
  tmp = h_zmm_unfolding->returnHisto() ;
  for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);
  tmp = h_zee_afterMET_unfolding->returnHisto() ;
  for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);
  tmp = h_zmm_afterMET_unfolding->returnHisto() ;
  for(size_t i=0;i<tmp.size();i++) r->GetOutputList()->Add(tmp[i]);*/


  r->GetOutputList()->Add(h_dR_je) ;
  r->GetOutputList()->Add(h_dR_jm) ;
  r->GetOutputList()->Add(h_dR_DYtoQQ) ;
  r->GetOutputList()->Add(h_dR_DYtoQQ_Zmass) ;
  r->GetOutputList()->Add(h_dR_DYtoQQ_Zmass_iso) ;
  r->GetOutputList()->Add(h_dR_DYtoQQ_pT) ;
  r->GetOutputList()->Add(h_dR_DYtoQQ_iso) ;
  r->GetOutputList()->Add(h_dR_DYtoQQ_iso_pT) ;
  r->GetOutputList()->Add(h_nbJet_DYtoQQ) ;
  //r->GetOutputList()->Add(h_nMuon) ;
  //r->GetOutputList()->Add(h_nEle) ;
  //r->GetOutputList()->Add(h_nJet) ;
  r->GetOutputList()->Add(h_Zee_ZmassFull) ;
  r->GetOutputList()->Add(h_Zmm_ZmassFull) ;
  r->GetOutputList()->Add(h_ele_cutflow) ;
  r->GetOutputList()->Add(h_muon_cutflow) ;
//Hsin-Wei: gen cutflow
  r->GetOutputList()->Add(h_genzee_cutflow) ;
  r->GetOutputList()->Add(h_genzmm_cutflow) ;

  r->GetOutputList()->Add(h_Jet_cutflow) ;
  r->GetOutputList()->Add(h_zee_cutflow) ;
  r->GetOutputList()->Add(h_zmm_cutflow) ;
  r->GetOutputList()->Add(h_zee_cutflow_medium) ;
  r->GetOutputList()->Add(h_zmm_cutflow_medium) ;
  r->GetOutputList()->Add(h_zee_cutflow_tight) ;
  r->GetOutputList()->Add(h_zmm_cutflow_tight) ;
  r->GetOutputList()->Add(h_pt_jet_after_ele_rem) ;
  r->GetOutputList()->Add(h_dR1_muonTrig) ;
  r->GetOutputList()->Add(h_dR2_muonTrig) ;
  r->GetOutputList()->Add(h_pt1_muonTrig) ;
  r->GetOutputList()->Add(h_pt2_muonTrig) ;
  r->GetOutputList()->Add(h_dR1_eleTrig) ;
  r->GetOutputList()->Add(h_dR2_eleTrig) ;
  r->GetOutputList()->Add(h_pt1_eleTrig) ;
  r->GetOutputList()->Add(h_pt2_eleTrig) ;
  r->GetOutputList()->Add(h_Zmm_twojet_pt_jet1) ;
  r->GetOutputList()->Add(h_Zee_twojet_pt_jet1) ;
  r->GetOutputList()->Add(h_Zee_deltaR_ZJet1) ;
  r->GetOutputList()->Add(h_Zmm_deltaR_ZJet1) ;
  r->GetOutputList()->Add(h_nJet) ;
  r->GetOutputList()->Add(h_Zee_truebJet_pt) ;
  r->GetOutputList()->Add(h_Zee_truecJet_pt) ;
  r->GetOutputList()->Add(h_Zee_truelightJet_pt) ;
  r->GetOutputList()->Add(h_Zee_nJet_trueFlav) ;
  r->GetOutputList()->Add(h_Zee_nbJet_loose_tagged) ;
  r->GetOutputList()->Add(h_Zee_bJet_pt_loose_tagged) ;

  r->GetOutputList()->Add(h_Zmm_truebJet_pt) ;
  r->GetOutputList()->Add(h_Zmm_truecJet_pt) ;
  r->GetOutputList()->Add(h_Zmm_truelightJet_pt) ;
  r->GetOutputList()->Add(h_Zmm_nJet_trueFlav) ;
  r->GetOutputList()->Add(h_Zmm_nbJet_loose_tagged) ;
  r->GetOutputList()->Add(h_Zmm_bJet_pt_loose_tagged) ;
  r->GetOutputList()->Add(h_fatjet_mass_n2b1) ;
  r->GetOutputList()->Add(h_fatjet_mass_mSD) ;
  r->GetOutputList()->Add(h_fatjet_pT_mSD) ;
  r->GetOutputList()->Add(h_dR_fatjet_lepton) ;
  r->GetOutputList()->Add(h_subjets_minpT_sumpT_deltaR_nocut) ;
  
  r->GetOutputList()->Add(h_nAK4_jets) ;
  r->GetOutputList()->Add(h_nAK8_jets) ;
  r->GetOutputList()->Add(h_fatslenderjetsmatched) ;
  
  r->GetOutputList()->Add(h_nEvt_oppolepsign) ;
  r->GetOutputList()->Add(h_nEvt_samelepsign) ;
  r->GetOutputList()->Add(h_Jet_tau21);
  r->GetOutputList()->Add(h_Jet_tau32);
  
  const Int_t nx = 5, nx1 = 4, yx= 6, nzee=8, nzmm=8;
  const char *ele_cut[nx] = {"all","ip","kine","EB-EE gap","ID"};
  const char *muon_cut[nx1] = {"all","kine","medium muon ID", "iso"};
  const char *jet_cut[yx] = {"all", "kine", "ele overlap removal","muon overlap removal","jet ID", "jet puID"};
  const char *zee_cut[nzee] = {"all event (not cut)","trigger","pass electron  cuts","MET","pass Z mass cuts", "pass jet cuts", "pass b-jet", "pass 2 b-jets"};
  const char *zmm_cut[nzmm] = {"all event (not cut)","trigger","pass muon  cuts", "MET","pass Z mass cuts", "pass jet cuts", "pass b-jet", "pass 2 b-jets"};
  for (int i=1;i<=nx;i++) h_ele_cutflow->GetXaxis()->SetBinLabel(i+1.5,ele_cut[i-1]);
  for (int i=1;i<=nx1;i++) h_muon_cutflow->GetXaxis()->SetBinLabel(i+1.5,muon_cut[i-1]);
  for (int i=1;i<=yx;i++) h_Jet_cutflow->GetXaxis()->SetBinLabel(i+1.5,jet_cut[i-1]);
  for (int i=1;i<=nzee;i++) h_zee_cutflow->GetXaxis()->SetBinLabel(i+1.5,zee_cut[i-1]);
  for (int i=1;i<=nzmm;i++) h_zmm_cutflow->GetXaxis()->SetBinLabel(i+1.5,zmm_cut[i-1]);
  for (int i=1;i<=nzee;i++) h_zee_cutflow_medium->GetXaxis()->SetBinLabel(i+1.5,zee_cut[i-1]);
  for (int i=1;i<=nzmm;i++) h_zmm_cutflow_medium->GetXaxis()->SetBinLabel(i+1.5,zmm_cut[i-1]);
  for (int i=1;i<=nzee;i++) h_zee_cutflow_tight->GetXaxis()->SetBinLabel(i+1.5,zee_cut[i-1]);
  for (int i=1;i<=nzmm;i++) h_zmm_cutflow_tight->GetXaxis()->SetBinLabel(i+1.5,zmm_cut[i-1]);
//Hsin-Wei: gen cut flow
  const Int_t ngenzll = 6;
  const char *genzee_cut[ngenzll] = {"total events","two electrons","kine","pass 1 jet","pass 1 b jet","pass 2 b jets"};
  const char *genzmm_cut[ngenzll] = {"totla events","two muons","kine","pass 1 jet","pass 1 b jet","pass 2 b jets"};
  for (int i=1;i<=ngenzll;i++) h_genzee_cutflow->GetXaxis()->SetBinLabel(i+1.5,genzee_cut[i-1]);
  for (int i=1;i<=ngenzll;i++) h_genzmm_cutflow->GetXaxis()->SetBinLabel(i+1.5,genzmm_cut[i-1]);
  
}

void ZbSelection::Process(Reader* r) {
//std::cout << "new event: " << std::endl;
  //Weights
  float genWeight = 1.;
  float puSF = 1.;
  float l1preW = 1.;
#if defined(MC_preVFP2016) || defined(MC_postVFP2016) || defined(MC_2017) || defined(MC_2018)
  if (*(r->genWeight) < 0) genWeight = -1. ;
  if (*(r->genWeight) == 0) h_evt->Fill(0) ; 
  if (*(r->genWeight) < 0) h_evt->Fill(-1) ; 
  if (*(r->genWeight) > 0) h_evt->Fill(1) ;
  //puSF = PileupSF(*(r->Pileup_nTrueInt));
  
  //genWeight = *(r->genWeight)/124598120.; //only for Sherpa
#endif

h_evt->Fill(2,genWeight);

#if defined(MC_preVFP2016) || defined(MC_postVFP2016) || defined(MC_2017)
  l1preW = *(r->L1PreFiringWeight_Nom);  
  //std::cout << "\nPrefiring: " << l1preW;
#endif 
#if defined(DATA_preVFP2016) || defined(DATA_postVFP2016) || defined(DATA_2017) || defined(DATA_2018)
  h_evt->Fill(-1) ;
  if (!m_lumiFilter.Pass(*(r->run),*(r->luminosityBlock))) return;
  //h_evt->Fill(1) ;
#endif

  float evtW = 1. ;
  
  if (!m_isData) evtW *= genWeight*puSF*l1preW;

  //=============Get objects============= 

  //electrons
  std::vector<LepObj> eles ;
  std::vector<LepObj> eles_jetOverlap ;

  for (unsigned int i = 0 ; i < *(r->nElectron) ; ++i) {
    h_ele_cutflow->Fill(1) ;
    
    float etaSC = (r->Electron_eta)[i]+(r->Electron_deltaEtaSC[i]) ;
    LepObj ele((r->Electron_pt)[i],(r->Electron_eta)[i],etaSC,(r->Electron_phi)[i],(r->Electron_mass)[i],i,(r->Electron_charge)[i],0) ;

    float dz = (r->Electron_dz)[i]; 
    float dxy = (r->Electron_dxy)[i]; //dxy=d0
    if ((fabs(etaSC) < 1.4442) && (fabs(dz) > CUTS.Get<float>("ele_dz_b") || fabs(dxy) > CUTS.Get<float>("ele_d0_b"))) continue;
    if ((fabs(etaSC) >= 1.4442) && (fabs(dz) > CUTS.Get<float>("ele_dz_e") || fabs(dxy) > CUTS.Get<float>("ele_d0_e"))) continue;
    h_ele_cutflow->Fill(2) ;

 
    int eleId = r->Electron_cutBased[i] ; //cut-based ID Fall17 V2 (0:fail, 1:veto, 2:loose, 3:medium, 4:tight)
    //electron for electron jet overlap removal
    if (ele.m_lvec.Pt() > CUTS.Get<float>("lep_jetOverlap_pt") && fabs(ele.m_lvec.Eta()) < CUTS.Get<float>("lep_jetOverlap_eta")) {
      if (eleId >= 4) { //tightId for jet removal
        eles_jetOverlap.push_back(ele) ;
      }
    }

    if (ele.m_lvec.Pt() < CUTS.Get<float>("lep_pt1") || fabs(ele.m_lvec.Eta()) > CUTS.Get<float>("lep_eta")) continue ; //use lower pt threshold to select both leading and subleading lepton
    h_ele_cutflow->Fill(3)  ;
    if (fabs(ele.m_scEta) < 1.566 && fabs(ele.m_scEta) > 1.442) continue ; //EB-EE gap removal
    h_ele_cutflow->Fill(4)  ;

    if (eleId < 4) continue; //use tightId to be consistent with single electron trigger
    h_ele_cutflow->Fill(5)  ;

	  eles.push_back(ele) ;
    //h_nEle->Fill(eles.size()) ;
  }
  
  //muons
  
  std::vector<LepObj> muons ;
  std::vector<LepObj> muons_jetOverlap ;
  std::vector<LepObj> muons_test ;
  for (unsigned int i = 0 ; i < *(r->nMuon) ; ++i) {

    h_muon_cutflow->Fill(1) ;
    
    LepObj muon((r->Muon_pt)[i],(r->Muon_eta)[i],-1,(r->Muon_phi)[i],(r->Muon_mass)[i],i,(r->Muon_charge)[i],(r->Muon_pfRelIso04_all)[i]) ;
    muons_test.push_back(muon);
    float sf_rc = MuonRcSF(r, muon, 13) ;
    //TEMP
    //sf_rc = 1.0;
    //std::cout << "\n Before correction: " <<  sf_rc << " " << muon.m_lvec.Pt() ;
    //muon.m_lvec.Print() ;
    muon.m_lvec.SetPtEtaPhiM(muon.m_lvec.Pt()*sf_rc,muon.m_lvec.Eta(),muon.m_lvec.Phi(),muon.m_lvec.M()) ;

    //std::cout << "\n After " << muon.m_lvec.Pt() ;
    //muon.m_lvec.Print() ;
    
    //muon for muon jet overlap removal
    if (muon.m_lvec.Pt() > CUTS.Get<float>("lep_jetOverlap_pt") && fabs(muon.m_lvec.Eta()) < CUTS.Get<float>("lep_jetOverlap_eta")) {
      if (r-> Muon_mediumId[i] > 0 && r->Muon_pfRelIso04_all[i] < CUTS.Get<float>("muon_iso")) {
        muons_jetOverlap.push_back(muon) ;
      }
    }
    
    if (muon.m_lvec.Pt() < CUTS.Get<float>("lep_pt1") || fabs(muon.m_lvec.Eta()) > CUTS.Get<float>("lep_eta")) continue ; 
    h_muon_cutflow->Fill(2) ;
    
    if (r-> Muon_mediumId[i] <= 0) continue;
    h_muon_cutflow->Fill(3) ;
	  
    if (muon.m_iso > CUTS.Get<float>("muon_iso")) continue ; 
    h_muon_cutflow->Fill(4) ;

    muons.push_back(muon) ;
    //h_nMuon->Fill(muons.size()) ;
  }

  //sv
  std::vector<TLorentzVector> lvec_SVs ;
  for (unsigned i = 0 ; i < *(r->nSV) ; ++i) {
    TLorentzVector tmp ;
    tmp.SetPtEtaPhiM((r->SV_pt)[i], (r->SV_eta)[i], (r->SV_phi)[i], (r->SV_mass)[i]) ;
    lvec_SVs.push_back(tmp);
  }

//turn off for AK4 jet study 
/*
std::vector<JetObj> jets ;
  std::vector<JetObj> jets_ele_removal ;
  std::vector<JetObj> bjets_loose ;
  //std::vector<JetObj> bjets_medium ;
  //std::vector<JetObj> bjets_tight ;
  std::vector<JetObj> bjets_true ;
  std::vector<JetObj> subjets ;
  std::vector<JetObj> bL_subjets ;
  std::vector<JetObj> bM_subjets ;
  std::vector<JetObj> bT_subjets ;

bool pushed_subjetidx1 = false; 
bool pushed_bL_subjets = false; 
bool pushed_bM_subjets = false; 
bool pushed_bT_subjets = false; 
float btagTCSV_cut = CUTS.Get<float>("jet_deepCSVT_"+m_year) ;  
  float btagL_cut = CUTS.Get<float>("jet_PNETL_"+m_year) ;  
  float btagM_cut = CUTS.Get<float>("jet_PNETM_"+m_year) ;
  float btagT_cut = CUTS.Get<float>("jet_PNETT_"+m_year) ;
  //std::cout << "2017 jet_deepCSVM = " <<jet_deepCSVM<<std::endl;
  for (unsigned int i = 0 ; i < *(r->nJet) ; ++i) {
    float m_SD = 0;
    h_Jet_cutflow->Fill(1) ;
    int jetFlav = -1 ;
#if defined(MC_preVFP2016) || defined(MC_postVFP2016) || defined(MC_2017) || defined(MC_2018)
    jetFlav = (r->FatJet_hadronFlavour)[i];
#endif 
    JetObj jet((r->FatJet_pt)[i],(r->FatJet_eta)[i],(r->FatJet_phi)[i],(r->FatJet_mass)[i],jetFlav,(r->FatJet_particleNetMD_QCD)[i],(r->FatJet_particleNetMD_Xbb)[i],(r->FatJet_tau1)[i],(r->FatJet_tau2)[i],(r->FatJet_tau3)[i],(r->FatJet_tau4)[i],(r->FatJet_msoftdrop)[i],(r->FatJet_subJetIdx1)[i],(r->FatJet_subJetIdx2)[i],(r->FatJet_n2b1)[i],(r->FatJet_n3b1)[i]) ;
  
    

    float totXbb = (jet.m_particleNetMD_Xbb+jet.m_particleNetMD_QCD);
    float PNet = -1;
    if(totXbb>0) PNet = (jet.m_particleNetMD_Xbb)/(totXbb);
    
    //std::cout << "FatJet_subJetIdx2 = " <<(r->FatJet_subJetIdx2)[i]<<std::endl;

    if (jet.IsLepton(eles_jetOverlap)) continue ;
    jets_ele_removal.push_back(jet) ;
    h_Jet_cutflow->Fill(2) ;
      
    if (jet.IsLepton(muons_jetOverlap)) continue ;
    h_Jet_cutflow->Fill(3) ;
    
    if (r->Jet_jetId[i] < 2 ) continue ;
    h_Jet_cutflow->Fill(4) ;
    
    //if (jet.m_lvec.Pt()<40 && jet.m_lvec.Pt()>30 && jet.m_puid<0.86 ) continue;    
    //if (jet.m_lvec.Pt()<50 && jet.m_lvec.Pt()>40 && jet.m_puid<0.93 ) continue;
    //h_Jet_cutflow->Fill(6) ;
     if (jet.m_idx1 < 0 || jet.m_idx2 <0) continue ;
     h_Jet_cutflow->Fill(5) ;
	  
    jets.push_back(jet) ;
/*
    if (PNet >= btagT_cut) bjets_tight.push_back(jet) ;
    if (PNet >= btagM_cut) bjets_medium.push_back(jet) ;
    if (PNet >= btagL_cut) bjets_loose.push_back(jet) ;
    if (fabs(jet.m_flav) == 5)bjets_true.push_back(jet);
    if (!pushed_subjetidx1) {
            int subjetFlav_idx1 = -1 ;
            int subjetFlav_idx2 = -1 ;
            #if defined(MC_preVFP2016) || defined(MC_postVFP2016) || defined(MC_2017) || defined(MC_2018)
            subjetFlav_idx1 = (r->SubJet_hadronFlavour)[jets[0].m_idx1];
            subjetFlav_idx2 = (r->SubJet_hadronFlavour)[jets[0].m_idx2];
            #endif 
            JetObj subjetidx1((r->SubJet_pt)[jets[0].m_idx1], (r->SubJet_eta)[jets[0].m_idx1], (r->SubJet_phi)[jets[0].m_idx1],
                              (r->SubJet_mass)[jets[0].m_idx1], subjetFlav_idx1, -1, -1, 
                              (r->SubJet_tau1)[jets[0].m_idx1], (r->SubJet_tau2)[jets[0].m_idx1], 
                              (r->SubJet_tau3)[jets[0].m_idx1], (r->SubJet_tau4)[jets[0].m_idx1], -1, -1, -1,(r->SubJet_n2b1)[jets[0].m_idx1], (r->SubJet_n3b1)[jets[0].m_idx1]);
            JetObj subjetidx2((r->SubJet_pt)[jets[0].m_idx2], (r->SubJet_eta)[jets[0].m_idx2], (r->SubJet_phi)[jets[0].m_idx2],
                              (r->SubJet_mass)[jets[0].m_idx2], subjetFlav_idx2, -1, -1, 
                              (r->SubJet_tau1)[jets[0].m_idx2], (r->SubJet_tau2)[jets[0].m_idx2], 
                              (r->SubJet_tau3)[jets[0].m_idx2], (r->SubJet_tau4)[jets[0].m_idx2], -1, -1, -1,(r->SubJet_n2b1)[jets[0].m_idx2], (r->SubJet_n3b1)[jets[0].m_idx2]);
            subjets.push_back(subjetidx1);
            subjets.push_back(subjetidx2);
            pushed_subjetidx1 = true;
        }
 if ((bjets_loose.size()>0)&&!pushed_bL_subjets) {
            int subjetFlav_idx1 = -1 ;
            int subjetFlav_idx2 = -1 ;
            #if defined(MC_preVFP2016) || defined(MC_postVFP2016) || defined(MC_2017) || defined(MC_2018)
            subjetFlav_idx1 = (r->SubJet_hadronFlavour)[bjets_loose[0].m_idx1];
            subjetFlav_idx2 = (r->SubJet_hadronFlavour)[bjets_loose[0].m_idx2];
            #endif 
            JetObj bL_subjetidx1((r->SubJet_pt)[bjets_loose[0].m_idx1], (r->SubJet_eta)[bjets_loose[0].m_idx1], (r->SubJet_phi)[bjets_loose[0].m_idx1],
                              (r->SubJet_mass)[bjets_loose[0].m_idx1], subjetFlav_idx1, -1, -1, 
                              (r->SubJet_tau1)[bjets_loose[0].m_idx1], (r->SubJet_tau2)[bjets_loose[0].m_idx1], 
                              (r->SubJet_tau3)[bjets_loose[0].m_idx1], (r->SubJet_tau4)[bjets_loose[0].m_idx1], -1, -1, -1,(r->SubJet_n2b1)[bjets_loose[0].m_idx1], (r->SubJet_n3b1)[bjets_loose[0].m_idx1]);
            JetObj bL_subjetidx2((r->SubJet_pt)[bjets_loose[0].m_idx2], (r->SubJet_eta)[bjets_loose[0].m_idx2], (r->SubJet_phi)[bjets_loose[0].m_idx2],
                              (r->SubJet_mass)[bjets_loose[0].m_idx2], subjetFlav_idx2, -1, -1, 
                              (r->SubJet_tau1)[bjets_loose[0].m_idx2], (r->SubJet_tau2)[bjets_loose[0].m_idx2], 
                              (r->SubJet_tau3)[bjets_loose[0].m_idx2], (r->SubJet_tau4)[bjets_loose[0].m_idx2], -1, -1, -1,(r->SubJet_n2b1)[bjets_loose[0].m_idx2], (r->SubJet_n3b1)[bjets_loose[0].m_idx2]);
            bL_subjets.push_back(bL_subjetidx1);
            bL_subjets.push_back(bL_subjetidx2);
            pushed_bL_subjets = true;
        } 
/* if ((bjets_medium.size()>0)&&(!pushed_bM_subjets)) {
            int subjetFlav_idx1 = -1 ;
            int subjetFlav_idx2 = -1 ;
            #if defined(MC_preVFP2016) || defined(MC_postVFP2016) || defined(MC_2017) || defined(MC_2018)
            subjetFlav_idx1 = (r->SubJet_hadronFlavour)[bjets_medium[0].m_idx1];
            subjetFlav_idx2 = (r->SubJet_hadronFlavour)[bjets_medium[0].m_idx2];
            #endif 
            JetObj bM_subjetidx1((r->SubJet_pt)[bjets_medium[0].m_idx1], (r->SubJet_eta)[bjets_medium[0].m_idx1], (r->SubJet_phi)[bjets_medium[0].m_idx1],
                              (r->SubJet_mass)[bjets_medium[0].m_idx1], subjetFlav_idx1, -1, -1, 
                              (r->SubJet_tau1)[bjets_medium[0].m_idx1], (r->SubJet_tau2)[bjets_medium[0].m_idx1], 
                              (r->SubJet_tau3)[bjets_medium[0].m_idx1], (r->SubJet_tau4)[bjets_medium[0].m_idx1], -1, -1, -1,(r->SubJet_n2b1)[bjets_medium[0].m_idx1], (r->SubJet_n3b1)[bjets_medium[0].m_idx1]);
            JetObj bM_subjetidx2((r->SubJet_pt)[bjets_medium[0].m_idx2], (r->SubJet_eta)[bjets_medium[0].m_idx2], (r->SubJet_phi)[bjets_medium[0].m_idx2],
                              (r->SubJet_mass)[bjets_medium[0].m_idx2], subjetFlav_idx2, -1, -1, 
                              (r->SubJet_tau1)[bjets_medium[0].m_idx2], (r->SubJet_tau2)[bjets_medium[0].m_idx2], 
                              (r->SubJet_tau3)[bjets_medium[0].m_idx2], (r->SubJet_tau4)[bjets_medium[0].m_idx2], -1, -1, -1,(r->SubJet_n2b1)[bjets_medium[0].m_idx2], (r->SubJet_n3b1)[bjets_medium[0].m_idx1]);
            bM_subjets.push_back(bM_subjetidx1);
            bM_subjets.push_back(bM_subjetidx2);
            pushed_bM_subjets = true;
        }*/
/* if ((bjets_tight.size()>0)&&!pushed_bT_subjets) {
            int subjetFlav_idx1 = -1 ;
            int subjetFlav_idx2 = -1 ;
            #if defined(MC_preVFP2016) || defined(MC_postVFP2016) || defined(MC_2017) || defined(MC_2018)
            subjetFlav_idx1 = (r->SubJet_hadronFlavour)[bjets_tight[0].m_idx1];
            subjetFlav_idx2 = (r->SubJet_hadronFlavour)[bjets_tight[0].m_idx2];
            #endif 
            JetObj bT_subjetidx1((r->SubJet_pt)[bjets_tight[0].m_idx1], (r->SubJet_eta)[bjets_tight[0].m_idx1], (r->SubJet_phi)[bjets_tight[0].m_idx1],
                              (r->SubJet_mass)[bjets_tight[0].m_idx1], subjetFlav_idx1, -1, -1, 
                              (r->SubJet_tau1)[bjets_tight[0].m_idx1], (r->SubJet_tau2)[bjets_tight[0].m_idx1], 
                              (r->SubJet_tau3)[bjets_tight[0].m_idx1], (r->SubJet_tau4)[bjets_tight[0].m_idx1], -1, -1, -1,(r->SubJet_n2b1)[bjets_tight[0].m_idx1], (r->SubJet_n3b1)[bjets_tight[0].m_idx1]);
            JetObj bT_subjetidx2((r->SubJet_pt)[bjets_tight[0].m_idx2], (r->SubJet_eta)[bjets_tight[0].m_idx2], (r->SubJet_phi)[bjets_tight[0].m_idx2],
                              (r->SubJet_mass)[bjets_tight[0].m_idx2], subjetFlav_idx2, -1, -1, 
                              (r->SubJet_tau1)[bjets_tight[0].m_idx2], (r->SubJet_tau2)[bjets_tight[0].m_idx2], 
                              (r->SubJet_tau3)[bjets_tight[0].m_idx2], (r->SubJet_tau4)[bjets_tight[0].m_idx2], -1, -1, -1,(r->SubJet_n2b1)[bjets_tight[0].m_idx2], (r->SubJet_n3b1)[bjets_tight[0].m_idx2]);
            bT_subjets.push_back(bT_subjetidx1);
            bT_subjets.push_back(bT_subjetidx2);
            pushed_bT_subjets = true;
        }*/

  //}*/ Enf of trun of for AK4 study
/*
       for (unsigned int i = 0 ; i < *(r->nSubJet) ; ++i) {
       
            
            float eta = (r->SubJet_eta)[0]-(r->SubJet_eta)[1];
            float phi = (r->SubJet_phi)[0]-(r->SubJet_phi)[1];
            float test = sqrt(pow(eta,2)+pow(phi,2));
        
        //h_subjets_minpT_sumpT_deltaR_nocut->Fill((r->SubJet_pt[1])/(r->SubJet_pt[1]+r->SubJet_pt[0]),test);

        //std::cout << "delta R: "<< test <<std::endl;
        
    
        
        
    }

    
    if (Fatjet_plot.size()>0){

    h_fatjet_mass_n2b1->Fill(Fatjet_plot[0].m_n2b1,Fatjet_plot[0].m_lvec.M());
    h_fatjet_mass_mSD->Fill(Fatjet_plot[0].m_lvec.M(),Fatjet_plot[0].m_mSD);
    h_fatjet_pT_mSD->Fill(Fatjet_plot[0].m_lvec.Pt(),Fatjet_plot[0].m_mSD);

    }
    for (unsigned int i = 0 ; i < Fatjet_plot.size() ; ++i) {
    for (unsigned int j = 0 ; j < muons_test.size() ; ++j) {
    h_dR_fatjet_lepton->Fill(Fatjet_plot[i].m_lvec.DeltaR(muons_test[j].m_lvec));
    }
    }*/

/*for (unsigned int i = 0 ; i < (bjets_loose.size()) ; ++i) {
 std::cout << "QCD =" <<bjets_loose[i].m_particleNetMD_QCD<<std::endl;
std::cout << "Xbb =" <<bjets_loose[i].m_particleNetMD_Xbb<<std::endl;
 std::cout << "PNet =" <<bjets_loose[i].m_particleNetMD_Xbb/(bjets_loose[i].m_particleNetMD_QCD+bjets_loose[i].m_particleNetMD_Xbb)<<std::endl;
}*/
  std::vector<JetObj> jets ;
  std::vector<JetObj> jets_ele_removal ;
  std::vector<JetObj> bjets ;
  float btagT_cut = CUTS.Get<float>("jet_deepCSVT_"+m_year) ;
  float PUIdJet_cut_30to40 = CUTS.Get<float>("jet_PUIddisc_30to40_"+m_year) ;
  float PUIdJet_cut_40to50 = CUTS.Get<float>("jet_PUIddisc_40to50_"+m_year) ;
    for (unsigned int i = 0 ; i < *(r->nJet) ; ++i) {
    
    h_Jet_cutflow->Fill(1) ;
    
    int jetFlav = -1 ;
#if defined(MC_2016) || defined(MC_2017) || defined(MC_2018)
    jetFlav = (r->Jet_hadronFlavour)[i];
#endif 
    
    float jetPt = (r->Jet_pt)[i];


    //std::cout << "\n Jet pt: " << m_jetmetSystType << " " << jetPt << " " << (r->Jet_pt_nom)[i];

    JetObj jet((r->Jet_pt)[i],(r->Jet_eta)[i],(r->Jet_phi)[i],(r->Jet_mass)[i],jetFlav,(r->Jet_btagDeepB)[i],(r->Jet_btagDeepFlavB)[i]) ;
    jet.SetSV(lvec_SVs);

    if (jet.m_lvec.Pt() < CUTS.Get<float>("jet_pt") || fabs(jet.m_lvec.Eta()) > CUTS.Get<float>("jet_eta")) continue ;
    h_Jet_cutflow->Fill(2) ;
    
    if (jet.IsLepton(eles_jetOverlap)) continue ;
    jets_ele_removal.push_back(jet) ;
    h_Jet_cutflow->Fill(3) ;
      
    if (jet.IsLepton(muons_jetOverlap)) continue ;
    h_Jet_cutflow->Fill(4) ;
    
    if (r->Jet_jetId[i] < 2 ) continue ;
    
    //if (r->Jet_jetId[i] <= 0 ) continue ;
    h_Jet_cutflow->Fill(5) ;
    

    if (jet.m_lvec.Pt()<50 && jet.m_lvec.Pt()>40 && (r->Jet_puIdDisc)[i]<PUIdJet_cut_40to50 ) continue;
    if (jet.m_lvec.Pt()<40 && jet.m_lvec.Pt()>30 && (r->Jet_puIdDisc)[i]<PUIdJet_cut_30to40 ) continue;
    h_Jet_cutflow->Fill(6) ;
	  
    jets.push_back(jet) ;

    if (jet.m_deepCSV >= btagT_cut) bjets.push_back(jet) ;
 

  }
  
  
  //calculate SF for eletron, muon and btagging
  float eleSF_w(1.);
  float muonSF_w(1.);
  float btag_w(1.);
  float pujet_w(1.);
  if (!m_isData) {   
    //btag_w = CalBtagWeight(jets,CUTS.GetStr("jet_main_btagWP"),m_btagUncType) ;//FIXME
    //std::cout << "\n Btag: " << btag_w;
    if (eles.size()>=2) eleSF_w = CalEleSF(eles[0],eles[1]) ;  
    if (muons.size()>=2) {
      muonSF_w = CalMuonSF_id_iso(muons[0],muons[1]);
      //std::cout << "\n Muon SF, " << muonSF_w;
    }
  }
  
  //if (bjets.size()>=1) std::cout << "\n btagWeight: " << btagWeight ;

  //trigger stuffs  
  bool eleTrig(false) ;
  bool muonTrig(false) ;
  float ptThr_ele(0) ;
  float ptThr_muon(0) ;
//Get trigger objects
  TLorentzVector muon_trigObj ;
  TLorentzVector ele_trigObj ;
  unsigned ele_bits ;
  unsigned muon_bits ;
#if defined(MC_preVFP2016) || defined(MC_postVFP2016) || defined(DATA_preVFP2016) || defined(DATA_postVFP2016) 
  if (*(r->HLT_Ele27_WPTight_Gsf)) eleTrig = true ;
  if (*(r->HLT_IsoMu24) || *(r->HLT_IsoTkMu24)) muonTrig = true ;
  //sel.qualityBitsDoc = cms.string("1 = TrkIsoVVL, 2 = Iso, 4 = OverlapFilter PFTau, 8 = IsoTkMu, 1024 = 1mu (Mu50)")
  //https://github.com/cms-nanoAOD/cmssw/blob/master-102X/PhysicsTools/NanoAOD/python/triggerObjects_cff.py
  muon_bits = (2+8) ; //iso + IsoTkMu
  //qualityBitsDoc = cms.string("1 = CaloIdL_TrackIdL_IsoVL, 2 = 1e (WPTight), 4 = 1e (WPLoose), 8 = OverlapFilter PFTau, 16 = 2e, 32 = 1e-1mu, 64 = 1e-1tau, 128 = 3e, 256 = 2e-1mu, 512 = 1e-2mu, 1024 = 1e (32_L1DoubleEG_AND_L1SingleEGOr), 2048 = 1e (CaloIdVT_GsfTrkIdT), 4096 = 1e (PFJet), 8192 = 1e (Photon175_OR_Photon200)"),),
  ele_bits = (2) ;
  ptThr_ele = 27 ;
  ptThr_muon = 24 ;
#endif

#if defined(MC_2017) || defined(DATA_2017) 
  //https://indico.cern.ch/event/787358/contributions/3504805/attachments/1883444/3112792/trigger_sf_vgg_HLTEle32_2017_290719.pdf
  if (*(r->HLT_Ele32_WPTight_Gsf_L1DoubleEG)) eleTrig = true ;
  if (*(r->HLT_IsoMu27)) muonTrig = true ;
  //qualityBitsDoc = cms.string("1 = TrkIsoVVL, 2 = Iso, 4 = OverlapFilter PFTau, 8 = 1mu, 16 = 2mu, 32 = 1mu-1e, 64 = 1mu-1tau, 128 = 3mu, 256 = 2mu-1e, 512 = 1mu-2e, 1024 = 1mu (Mu50), 2048 = 1mu (Mu100)"),),
  ele_bits = (2) ;
  muon_bits = (2) ;
  ptThr_ele = 32 ;
  ptThr_muon = 27 ;
#endif

#if defined(MC_2018) || defined(DATA_2018) 
  if (*(r->HLT_Ele32_WPTight_Gsf)) eleTrig = true ;
  if (*(r->HLT_IsoMu24)) muonTrig = true ;
  ele_bits = (2) ;
  muon_bits = (2) ;
  ptThr_ele = 32 ;
  ptThr_muon = 24 ;
#endif

  TLorentzVector trigObj_ele = GetTrigObj(r, 11, ele_bits, ptThr_ele) ;
  TLorentzVector trigObj_muon = GetTrigObj(r, 13, muon_bits, ptThr_muon) ;

  float trigSF_ele(1) ;
  if (!m_isData && (eles.size() >= 2)) {
    trigSF_ele =  CalTrigSF(11,eles[0], eles[1], trigObj_ele, h_dR1_eleTrig, h_dR2_eleTrig, h_pt1_eleTrig, h_pt2_eleTrig) ;
  }

  
  float trigSF_muon(1) ;
  if (!m_isData && (muons.size() >= 2)) trigSF_muon =  CalTrigSF(13,muons[0], muons[1], trigObj_muon, h_dR1_muonTrig, h_dR2_muonTrig, h_pt1_muonTrig, h_pt2_muonTrig) ; //uncertainties already calculate inside CalTrigSF

  //TEMP
  //eleTrig = true ;
  ////////////////////////////////////
  //Zee + jets
  ////////////////////////////////////
  /* turn off for AK4 study
  h_zee_cutflow->Fill(1); //all events (not cut)
  h_zee_cutflow_medium->Fill(1); //all events (not cut)
  h_zee_cutflow_tight->Fill(1); //all events (not cut)
  std::vector<TLorentzVector> zee_rec_uf; //0: leading lepton, 1: subleading lepton, 2: bjet 1, 3: bjet 2
  std::vector<TLorentzVector> zee_rec_afterMET_uf; //0: leading lepton, 1: subleading lepton, 2: bjet 1, 3: bjet 2
  float w_zee_rec_uf(1);
  float w_zee_rec_afterMET_uf(1);
  if (eleTrig) {
    h_zee_cutflow->Fill(2); //trigger
    h_zee_cutflow_medium->Fill(2); //trigger
    h_zee_cutflow_tight->Fill(2); //trigger
    if (eles.size() >= 2 && eles[0].m_lvec.Pt() >= CUTS.Get<float>("lep_pt0")) {

	h_zee_cutflow->Fill(3) ; //pass electron cuts
	h_zee_cutflow_medium->Fill(3) ; //pass electron cuts
	h_zee_cutflow_tight->Fill(3) ; //pass electron cuts
      
      float zee_w = evtW*eleSF_w*trigSF_ele*pujet_w ;
//std::cout << "\nweights: " << "  " << evtW << "  " << pujet_w << "  " << btag_w; 
      
      //TEMP
      //std::cout << "\n Ele weights: " << "  " << evtW << "  " << eleSF_w << "  " << trigSF_ele << "  " << zee_w; 
      float zeeb_w = zee_w*btag_w;

      //std::cout << "\n Ele weights with b tag: " << "  " << evtW << "  " << eleSF_w << "  " << trigSF_ele << "  " << zeeb_w; 
      
      ZObj Z(eles[0],eles[1]) ;

       h_Zee_ZmassFull->Fill(Z.m_lvec.M(),zee_w) ;

      if (Z.m_lvec.M() >= CUTS.Get<float>("ZMassL") && Z.m_lvec.M() <= CUTS.Get<float>("ZMassH")) { 
	     
        h_zee_cutflow->Fill(4) ; //pass Z mass cuts
        h_zee_cutflow_medium->Fill(4) ; //pass Z mass cuts
        h_zee_cutflow_tight->Fill(4) ; //pass Z mass cuts
       
       if (*(r->MET_pt) < CUTS.Get<float>("MET")) { 
        h_zee_cutflow->Fill(5) ;//pass MET cut
        h_zee_cutflow_medium->Fill(5) ;//pass MET cut
        h_zee_cutflow_tight->Fill(5) ;//pass MET cut
        h_zee_jet->FillNjet(jets.size(),zee_w) ;
        //at least one jet
        if (jets.size() >= 1) { //1 inclusive jet
        //leading jets should pass kinematic cuts
           
        if (jets[0].m_lvec.Pt() >=CUTS.Get<float>("jet_pt") && fabs(jets[0].m_lvec.Eta()) < CUTS.Get<float>("jet_eta")){ 

          h_zee_cutflow->Fill(6) ; //pass jet cuts
          h_zee_cutflow_medium->Fill(6) ; //pass jet cuts
          h_zee_cutflow_tight->Fill(6) ; //pass jet cuts

          h_zee_jet->Fill(Z, jets[0],subjets[0],subjets[1], zee_w) ;
          h_zee_jet->FillMet(*(r->MET_pt), *(r->PuppiMET_pt), zee_w);
 	  h_zee_jet->FillMet_Sig(*(r->MET_significance), zee_w);
	  //tau study

        
          // isolation
          float deltaRelelep0 = Z.m_lep0.m_lvec.DeltaR(jets[0].m_lvec);
          float deltaRelelep1 = Z.m_lep1.m_lvec.DeltaR(jets[0].m_lvec); 
          h_dR_je->Fill(std::min(deltaRelelep0,deltaRelelep1), zee_w) ;
          
         h_Zee_nJet_trueFlav->Fill(jets[0].m_flav, zee_w);  
         if(fabs(jets[0].m_flav)==5){h_Zee_truebJet_pt->Fill(jets[0].m_lvec.Pt(),zee_w);}
         if(fabs(jets[0].m_flav)==4){h_Zee_truecJet_pt->Fill(jets[0].m_lvec.Pt(),zee_w);}
         if(fabs(jets[0].m_flav)!=4 and fabs(jets[0].m_flav)!=5){h_Zee_truelightJet_pt->Fill(jets[0].m_lvec.Pt(),zee_w);}
         float totXbb_leading = (jets[0].m_particleNetMD_Xbb+jets[0].m_particleNetMD_QCD);
         float PNet_leading = -1;
         if(totXbb_leading>0) PNet_leading = (jets[0].m_particleNetMD_Xbb)/(totXbb_leading);
         if (PNet_leading>=btagL_cut){
         h_Zee_nbJet_loose_tagged->Fill(jets[0].m_flav, zee_w) ;
         h_Zee_bJet_pt_loose_tagged->Fill(jets[0].m_lvec.Pt(),zee_w);
         }

        } //end at least one jet

       }//end leading jet kinematic cuts

        //at least two jet
        if (jets.size() >= 2 && jets[0].m_lvec.Pt() >=CUTS.Get<float>("jet_pt") && fabs(jets[0].m_lvec.Eta()) < CUTS.Get<float>("jet_eta")) { //2 inclusive jet
          h_Zee_twojet_pt_jet1->Fill(jets[1].m_lvec.Pt(), zee_w) ;
          h_zee_twojet->Fill(Z, jets[0], subjets[0],subjets[1],zee_w) ;
          h_zee_twojet->FillMet(*(r->MET_pt), *(r->PuppiMET_pt), zee_w);
          h_Zee_deltaR_ZJet1->Fill(Z.m_lvec.DeltaR(jets[1].m_lvec), zee_w);
 	  
	} //end at least two jet
        
        //at least one b-tagged jets
        h_zee_bjet_loose->FillNjet(bjets_loose.size(),zeeb_w) ; 
        h_zee_bjet_medium->FillNjet(bjets_medium.size(),zeeb_w) ; 
        h_zee_bjet_tight->FillNjet(bjets_tight.size(),zeeb_w) ; 
        if (*(r->MET_pt) < CUTS.Get<float>("MET")) h_zee_bjet_afterMET->FillNjet(bjets_loose.size(),zeeb_w);

        
        if (bjets_loose.size() >=1 ) {
           if (bjets_loose[0].m_lvec.Pt() >=CUTS.Get<float>("jet_pt") && fabs(bjets_loose[0].m_lvec.Eta()) < CUTS.Get<float>("jet_eta")){
          //std::cout<<"bjet after cut = "<< bjets[0].m_lvec.Pt()<<" "<<bjets[0].m_lvec.Eta()<<std::endl<<""<<PNet_T;
          h_zee_cutflow->Fill(7) ;

          //h_zee_bjet_loose->Fill(Z, bjets_loose[0], subjets[0],subjets[1],zeeb_w) ;
          h_zee_bjet_loose->FillMet(*(r->MET_pt), *(r->PuppiMET_pt), zeeb_w);
 	  h_zee_bjet_loose->FillMet_Sig(*(r->MET_significance), zeeb_w);
        }
      }
        //at least two b-tagged jets
        if (bjets_loose.size() >=2 && bjets_loose[0].m_lvec.Pt() >=CUTS.Get<float>("jet_pt") && fabs(bjets_loose[0].m_lvec.Eta()) < CUTS.Get<float>("jet_eta")) {
          
          h_zee_cutflow->Fill(8) ;

            


	  h_zee_2bjet->Fill(Z, bjets_loose[0], bjets_loose[1],bL_subjets[0],bL_subjets[1], evtW) ;
            h_zee_2bjet->FillMet(*(r->MET_pt), *(r->PuppiMET_pt), evtW);
	    h_zee_2bjet->FillMet_Sig(*(r->MET_significance), evtW);
            h_zee_2bjet->FillNjet(bjets_loose.size(),evtW) ; 


          
        } //end two b-tagged PNET jets

       }//end MET cut
       }//end Z mass
       } //end two electrons
       } //end ele. trigger
  */
  // turn off for AK4 study
    ////////////////////////////////////
  h_zee_cutflow->Fill(1); //all events (not cut)
  std::vector<TLorentzVector> zee_rec_uf; //0: leading lepton, 1: subleading lepton, 2: bjet 1, 3: bjet 2
  std::vector<TLorentzVector> zee_rec_afterMET_uf; //0: leading lepton, 1: subleading lepton, 2: bjet 1, 3: bjet 2
  float w_zee_rec_uf(1);
  float w_zee_rec_afterMET_uf(1);
  if (eleTrig) {
    h_zee_cutflow->Fill(2); //trigger
    if (eles.size() >= 2 && eles[0].m_lvec.Pt() >= CUTS.Get<float>("lep_pt0")) {

	    h_zee_cutflow->Fill(3) ; //pass electron  cuts
      
      float zee_w = evtW*eleSF_w*trigSF_ele ;
      //TEMP
      //std::cout << "\n Ele weights: " << "  " << evtW << "  " << eleSF_w << "  " << trigSF_ele << "  " << zee_w; 
      float zeeb_w = zee_w*btag_w;
      
      ZObj Z(eles[0],eles[1]) ;

      h_Zee_ZmassFull->Fill(Z.m_lvec.M(), zee_w) ;

      if (Z.m_lvec.M() >= CUTS.Get<float>("ZMassL") && Z.m_lvec.M() <= CUTS.Get<float>("ZMassH")) { 
      
        h_zee_cutflow->Fill(4) ; //pass Z mass cuts

        h_zee_jet->FillNjet(jets.size(), zee_w) ;
        
        //at least on jet
        if (jets.size() >= 1) {

          h_zee_cutflow->Fill(5) ; //pass jet cuts

          h_zee_jet->Fill(Z, jets[0], zee_w) ;

          h_zee_jet->FillMet(*(r->MET_pt), *(r->PuppiMET_pt), zee_w);
        
          // isolation
          float deltaRelelep0 = Z.m_lep0.m_lvec.DeltaR(jets[0].m_lvec);
          float deltaRelelep1 = Z.m_lep1.m_lvec.DeltaR(jets[0].m_lvec); 
          h_dR_je->Fill(std::min(deltaRelelep0,deltaRelelep1), zee_w) ;


        } //end at least one jet
        
        //at least one b-tagged jets
        h_zee_bjet->FillNjet(bjets.size(),evtW) ; 
        if (*(r->MET_pt) < CUTS.Get<float>("MET")) h_zee_bjet_afterMET->FillNjet(bjets.size(),evtW);

        if (bjets.size() >=1) {
           
          h_zee_cutflow->Fill(6) ;

          h_zee_bjet->Fill(Z, bjets[0], zeeb_w) ;
          h_zee_bjet->FillMet(*(r->MET_pt), *(r->PuppiMET_pt), zeeb_w);
          if (*(r->MET_pt) < CUTS.Get<float>("MET")) {
            h_zee_bjet_afterMET->Fill(Z, bjets[0], zeeb_w) ;
            h_zee_bjet_afterMET->FillMet(*(r->MET_pt), *(r->PuppiMET_pt), zeeb_w);
          }
        }

        //at least two b-tagged jets
        if (bjets.size() >=2) {
          
          h_zee_cutflow->Fill(7) ;
        
          if (*(r->MET_pt) < CUTS.Get<float>("MET")) {
            
            h_zee_cutflow->Fill(8) ;

            h_zee_2bjet->Fill(Z, bjets[0], bjets[1], zeeb_w) ;
            h_zee_2bjet->FillMet(*(r->MET_pt), *(r->PuppiMET_pt), zeeb_w);

          } //end MET cut
        } //end two b-tagged deepCSV jets

        //at least one b-tagged jets using deepJet
        //at least two b-tagged jets using deepJet
      }//end Z mass
    } //end two electrons
  } //end ele. trigger
  
  if (jets_ele_removal.size() > 0) {
    JetPlot J_cut1(jets_ele_removal[0]);
    h_pt_jet_after_ele_rem->Fill(J_cut1.m_lvec.Pt(), evtW);
  }

  

  ///////////////////////////
  //Zmm + jets
  ///////////////////////////
/*  h_zmm_cutflow->Fill(1); //all events (not cut)
  h_zmm_cutflow_medium->Fill(1); //all events (not cut)
  h_zmm_cutflow_tight->Fill(1); //all events (not cut)
  
  std::vector<TLorentzVector> zmm_rec_uf; //0: leading lepton, 1: subleading lepton, 2: bjet 1, 3: bjet 2
  float w_zmm_rec_uf(1);
  std::vector<TLorentzVector> zmm_rec_afterMET_uf; //0: leading lepton, 1: subleading lepton, 2: bjet 1, 3: bjet 2
  float w_zmm_rec_afterMET_uf(1);
  //trigger cuts
  if (muonTrig) {
    h_zmm_cutflow->Fill(2); //trigger
    h_zmm_cutflow_medium->Fill(2); //trigger
    h_zmm_cutflow_tight->Fill(2); //trigger
    if (muons.size() >= 2 && muons[0].m_lvec.Pt() >= CUTS.Get<float>("lep_pt0")) {
	    h_zmm_cutflow->Fill(3) ; //pass muon  cuts
	    h_zmm_cutflow_medium->Fill(3) ; //pass muon  cuts
	    h_zmm_cutflow_tight->Fill(3) ; //pass muon  cuts

      float zmm_w = evtW*muonSF_w*trigSF_muon*pujet_w ;
      //std::cout << "zmm_w =" <<zmm_w<<std::endl;
      //TEMP
      //std::cout << "\n evtW: " << evtW << " " << muonSF_w << " " << trigSF_muon << " " << zmm_w; 
      float zmmb_w = zmm_w*btag_w;
      //std::cout << "\n zmmb_w: " << " " << zmmb_w; 
      
      ZObj Z(muons[0],muons[1]) ;
      
      h_Zmm_ZmassFull->Fill(Z.m_lvec.M(), evtW) ;
      
      if (Z.m_lvec.M() >= CUTS.Get<float>("ZMassL") ) { 
      
        h_zmm_cutflow->Fill(4) ; //pass Z mass cuts
        h_zmm_cutflow_medium->Fill(4) ; //pass Z mass cuts
        h_zmm_cutflow_tight->Fill(4) ; //pass Z mass cuts
       
      if (*(r->MET_pt) < CUTS.Get<float>("MET")) {
          h_zmm_cutflow->Fill(5) ; //pass jet cuts
          h_zmm_cutflow_medium->Fill(5) ; //pass jet cuts
          h_zmm_cutflow_tight->Fill(5) ; //pass jet cuts
        h_zmm_jet->FillNjet(jets.size(), zmm_w) ;
        if (jets.size() >= 1) { //1 inclusive jet
        //leading jets should pass kinematic cuts
        if (jets[0].m_lvec.Pt() >=CUTS.Get<float>("jet_pt") && fabs(jets[0].m_lvec.Eta()) < CUTS.Get<float>("jet_eta")){
          h_zmm_cutflow->Fill(6) ; //pass jet cuts
          h_zmm_cutflow_medium->Fill(6) ; //pass jet cuts
          h_zmm_cutflow_tight->Fill(6) ; //pass jet cuts

          float deltaRmuonlep0 = Z.m_lep0.m_lvec.DeltaR(jets[0].m_lvec);
          float deltaRmuonlep1 = Z.m_lep1.m_lvec.DeltaR(jets[0].m_lvec);
        
          h_zmm_jet->Fill(Z, jets[0], subjets[0],subjets[1],zmm_w) ;
          h_zmm_jet->FillMet(*(r->MET_pt), *(r->PuppiMET_pt), zmm_w);
          h_zmm_jet->FillMet_Sig(*(r->MET_significance), zmm_w);
	  h_Jet_tau21->Fill(jets[0].m_tau2/jets[0].m_tau1,evtW);
	  h_Jet_tau32->Fill(jets[0].m_tau3/jets[0].m_tau2,evtW);
	  
	  h_dR_jm->Fill(std::min(deltaRmuonlep0,deltaRmuonlep1), zmm_w) ;
          if (muons[0].m_charge*muons[1].m_charge == -1){h_nEvt_oppolepsign->Fill(1.0);}
          if (muons[0].m_charge*muons[1].m_charge == 1){h_nEvt_samelepsign->Fill(1.0);}

         h_Zmm_nJet_trueFlav->Fill(jets[0].m_flav, zmm_w);  
         if(fabs(jets[0].m_flav)==5){h_Zmm_truebJet_pt->Fill(jets[0].m_lvec.Pt(),zmm_w);}
         if(fabs(jets[0].m_flav)==4){h_Zmm_truecJet_pt->Fill(jets[0].m_lvec.Pt(),zmm_w);}
         if(fabs(jets[0].m_flav)!=4 and fabs(jets[0].m_flav)!=5){h_Zmm_truelightJet_pt->Fill(jets[0].m_lvec.Pt(),zmm_w);}
         float totXbb_leading = (jets[0].m_particleNetMD_Xbb+jets[0].m_particleNetMD_QCD);
         float PNet_leading = -1;
         if(totXbb_leading>0) PNet_leading = (jets[0].m_particleNetMD_Xbb)/(totXbb_leading);
         if (PNet_leading>=btagL_cut){
         h_Zmm_nbJet_loose_tagged->Fill(jets[0].m_flav, zmm_w) ;
         h_Zmm_bJet_pt_loose_tagged->Fill(jets[0].m_lvec.Pt(),zmm_w);}
         }//end leading jet kinematic cuts
        } //end at least one jet

        if (jets.size() >= 2 && jets[0].m_lvec.Pt() >=CUTS.Get<float>("jet_pt") && fabs(jets[0].m_lvec.Eta()) < CUTS.Get<float>("jet_eta")) { //2 inclusive jet

          h_Zmm_twojet_pt_jet1->Fill(jets[1].m_lvec.Pt(),zmm_w) ;
          h_zmm_twojet->Fill(Z, jets[0], subjets[0],subjets[1],zmm_w) ;
          h_zmm_twojet->FillMet(*(r->MET_pt), *(r->PuppiMET_pt), zmm_w);
          h_Zmm_deltaR_ZJet1->Fill(Z.m_lvec.DeltaR(jets[1].m_lvec), zmm_w);
        } //end at least two jet
        
        //Zmm+bjets
        h_zmm_bjet_loose->FillNjet(bjets_loose.size(),zmmb_w) ; 
        h_zmm_bjet_medium->FillNjet(bjets_medium.size(),zmmb_w) ; 	
        h_zmm_bjet_tight->FillNjet(bjets_tight.size(),zmmb_w) ; 
        if (*(r->MET_pt) < CUTS.Get<float>("MET")) h_zmm_bjet_afterMET->FillNjet(bjets_loose.size(),zmmb_w) ; 
        
        if (bjets_loose.size() >= 1) {
          if (bjets_loose[0].m_lvec.Pt() >=CUTS.Get<float>("jet_pt") && fabs(bjets_loose[0].m_lvec.Eta()) < CUTS.Get<float>("jet_eta")){
          h_zmm_cutflow->Fill(7) ;
          
          h_zmm_bjet_loose->Fill(Z, bjets_loose[0], bL_subjets[0],bL_subjets[1],zmmb_w) ; 
          h_zmm_bjet_loose->FillMet(*(r->MET_pt), *(r->PuppiMET_pt), zmmb_w);
          h_zmm_bjet_loose->FillMet_Sig(*(r->MET_significance), zmmb_w);
         }
        }
      
        //Zmm+2bjets
        if (bjets_loose.size() >= 2 && bjets_loose[0].m_lvec.Pt() >=CUTS.Get<float>("jet_pt") && fabs(bjets_loose[0].m_lvec.Eta()) < CUTS.Get<float>("jet_eta")) {
          
          h_zmm_cutflow->Fill(8) ;
      
#if defined(MC_preVFP2016) || defined(MC_postVFP2016) || defined(MC_2017) || defined(MC_2018)
          //Unfolding plots
          if (bjets_loose[0].m_flav == 5 && bjets_loose[1].m_flav == 5) {
            w_zmm_rec_uf = zmmb_w;
            zmm_rec_uf.push_back(muons[0].m_lvec);
            zmm_rec_uf.push_back(muons[1].m_lvec);
            zmm_rec_uf.push_back(bjets_loose[0].m_lvec);
            zmm_rec_uf.push_back(bjets_loose[1].m_lvec);
          }
#endif
	
          
            
            
	  h_zmm_2bjet->FillNjet(bjets_loose.size(),evtW) ; 
	  h_zmm_2bjet->Fill(Z, bjets_loose[0], bjets_loose[1],bL_subjets[0],bL_subjets[1], evtW) ; 
            h_zmm_2bjet->FillMet(*(r->MET_pt), *(r->PuppiMET_pt), evtW);

            h_zmm_2bjet->FillMet_Sig(*(r->MET_significance), evtW);
            


          
        } //end at least two b-tagged jets
       } //end met cut
      } //end Z mass cut   

      } //end two muons
    } //end trigger
*/
  h_zmm_cutflow->Fill(1); //all events (not cut)
  
  std::vector<TLorentzVector> zmm_rec_uf; //0: leading lepton, 1: subleading lepton, 2: bjet 1, 3: bjet 2
  float w_zmm_rec_uf(1);
  std::vector<TLorentzVector> zmm_rec_afterMET_uf; //0: leading lepton, 1: subleading lepton, 2: bjet 1, 3: bjet 2
  float w_zmm_rec_afterMET_uf(1);
  //trigger cuts
  if (muonTrig) {
    h_zmm_cutflow->Fill(2); //trigger
    if (muons.size() >= 2 && muons[0].m_lvec.Pt() >= CUTS.Get<float>("lep_pt0")) {
	    h_zmm_cutflow->Fill(3) ; //pass muon  cuts

      float zmm_w = evtW*muonSF_w*trigSF_muon ;
      //TEMP
      //zmm_w = evtW*muonSF_w;
      //std::cout << "\n evtW: " << evtW << " " << muonSF_w << " " << trigSF_muon << " " << zmm_w; 
      float zmmb_w = zmm_w*btag_w;
      
      ZObj Z(muons[0],muons[1]) ;
      
      h_Zmm_ZmassFull->Fill(Z.m_lvec.M(), zmm_w) ;
      
      if (Z.m_lvec.M() >= CUTS.Get<float>("ZMassL") && Z.m_lvec.M() <= CUTS.Get<float>("ZMassH")) { 
      
        h_zmm_cutflow->Fill(4) ; //pass Z mass cuts
        
        h_zmm_jet->FillNjet(jets.size(), zmm_w) ;
        
        if (jets.size() >= 1) {

          h_zmm_cutflow->Fill(5) ; //pass jet cuts

          float deltaRmuonlep0 = Z.m_lep0.m_lvec.DeltaR(jets[0].m_lvec);
          float deltaRmuonlep1 = Z.m_lep1.m_lvec.DeltaR(jets[0].m_lvec);
        
          h_zmm_jet->Fill(Z, jets[0], zmm_w) ;
          h_zmm_jet->FillMet(*(r->MET_pt), *(r->PuppiMET_pt), zmm_w);

          h_dR_jm->Fill(std::min(deltaRmuonlep0,deltaRmuonlep1), zmm_w) ;
 
        } //end at least one jet
        
        //Zmm+bjets
        h_zmm_bjet->FillNjet(bjets.size(),zmmb_w) ; 

        if (*(r->MET_pt) < CUTS.Get<float>("MET")) h_zmm_bjet_afterMET->FillNjet(bjets.size(),zmmb_w) ; 

        if (bjets.size() >= 1) {
          
          h_zmm_cutflow->Fill(6) ;
          
          h_zmm_bjet->Fill(Z, bjets[0], zmmb_w) ; 
          h_zmm_bjet->FillMet(*(r->MET_pt), *(r->PuppiMET_pt), zmmb_w);
          
          if (*(r->MET_pt) < CUTS.Get<float>("MET")) {
            h_zmm_bjet_afterMET->Fill(Z, bjets[0], zmmb_w) ; 
            h_zmm_bjet_afterMET->FillMet(*(r->MET_pt), *(r->PuppiMET_pt), zmmb_w);
          }

        }
      
        //Zmm+2bjets
        if (bjets.size() >= 2) {
          
          h_zmm_cutflow->Fill(7) ;

          if (*(r->MET_pt) < CUTS.Get<float>("MET")) {
            
            h_zmm_cutflow->Fill(8) ;
            
            h_zmm_2bjet->Fill(Z, bjets[0], bjets[1], zmmb_w) ; 
            h_zmm_2bjet->FillMet(*(r->MET_pt), *(r->PuppiMET_pt), zmmb_w);
          } //end met cut
        } //end at least two b-tagged jets


      } //end Z mass cut

    } //end two muons
  } //end trigger
 
  //Fill additional unfolding plots

  return;

} //end Process



void ZbSelection::Terminate(TList* mergedList, std::string outFileName) {
  
  TList* aList = new TList() ;
  TParameter<double>* a = new TParameter<double>("lep_eta",CUTS.Get<float>("lep_eta")) ;
  aList->Add(a) ;
  a = new TParameter<double>("lep_pt0",CUTS.Get<float>("lep_pt0")) ;
  aList->Add(a) ;
  a = new TParameter<double>("lep_pt1",CUTS.Get<float>("lep_pt1")) ;
  aList->Add(a) ;
  a = new TParameter<double>("ZMassL",CUTS.Get<float>("ZMassL")) ;
  aList->Add(a) ;
  a = new TParameter<double>("ZMassH",CUTS.Get<float>("ZMassH")) ;
  aList->Add(a) ;
  a = new TParameter<double>("muon_iso",CUTS.Get<float>("muon_iso")) ;
  aList->Add(a) ;
  a = new TParameter<double>("lep_jetOverlap_pt",CUTS.Get<float>("lep_jetOverlap_pt")) ;
  aList->Add(a) ;
  a = new TParameter<double>("lep_jetOverlap_eta",CUTS.Get<float>("lep_jetOverlap_eta")) ;
  aList->Add(a) ;
  a = new TParameter<double>("jet_pt",CUTS.Get<float>("jet_pt")) ;
  aList->Add(a) ;
  a = new TParameter<double>("jet_eta",CUTS.Get<float>("jet_eta")) ;
  aList->Add(a) ;
  std::string name = "jet_PNETT_" + m_year ;
  a = new TParameter<double>(name.c_str(),CUTS.Get<float>(name)) ;
  aList->Add(a) ;
  std::string name_M = "jet_PNETM_" + m_year ;
  a = new TParameter<double>(name_M.c_str(),CUTS.Get<float>(name_M)) ;
  aList->Add(a) ;
  std::string name_L = "jet_PNETL_" + m_year ;
  a = new TParameter<double>(name_L.c_str(),CUTS.Get<float>(name_L)) ;
  aList->Add(a) ;
  //For AK4 study
  
  std::string name_jet_PUIddisc_30to40= "jet_PUIddisc_30to40_" + m_year ;
  a = new TParameter<double>(name_jet_PUIddisc_30to40.c_str(),CUTS.Get<float>(name_jet_PUIddisc_30to40)) ;
  aList->Add(a) ;
  std::string name_jet_PUIddisc_40to50= "jet_PUIddisc_40to50_" + m_year ;
  a = new TParameter<double>(name_jet_PUIddisc_40to50.c_str(),CUTS.Get<float>(name_jet_PUIddisc_40to50)) ;
  aList->Add(a) ;
  
  std::string  name_deepCSVM = "jet_deepCSVM_" + m_year ;
  a = new TParameter<double>(name_deepCSVM.c_str(),CUTS.Get<float>(name_deepCSVM)) ;
  aList->Add(a) ;
  
  std::string  name_deepCSVT = "jet_deepCSVT_" + m_year ;
  a = new TParameter<double>(name_deepCSVT.c_str(),CUTS.Get<float>(name_deepCSVT)) ;
  aList->Add(a) ;
  
  

  
  TFile* f = new TFile(outFileName.c_str(), "UPDATE") ;
  aList->Write("ZbSelectionCuts",TObject::kSingleKey) ;

  f->Close() ;

}
