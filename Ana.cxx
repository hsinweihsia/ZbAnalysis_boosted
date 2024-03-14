#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>

#include "StdArg.hpp"
#include "src/Reader.h" 
#include "src/Processor.h"
#include "src/Selector.h"
#include "src/ZbSelection.h"


#include "src/Global.h"

std::vector<std::string> splitNames(const std::string& files, std::string sep = ",")
{
  std::vector<std::string> fileList;
  for (size_t i=0,n; i <= files.length(); i=n+1)
  {
    n = files.find_first_of(sep,i);
    if (n == string::npos)
      n = files.length();
    std::string tmp = files.substr(i,n-i);
    std::string ttmp;
    for(unsigned int j=0; j<tmp.size(); j++)
    {
      if(tmp[j]==' ' || tmp[j]=='\n') continue;
      ttmp+=tmp[j];
    }
    fileList.push_back(ttmp);
  }
  return fileList;

}

void SetParameters(std::string fName, glob::Parameters& para) {
  std::string line;
  std::ifstream myfile (fName);
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      
      //skip comment line start with "//"
      if (line.find("//") != std::string::npos) continue ;
      
      std::vector<std::string> cont ;
      std::vector<std::string> cont_no_space ;
      //cout << line << '\n';
      std::string delim(" ") ;
      boost::split(cont, line, boost::is_any_of(delim));
      //std::cout << "\nCont size: " << cont.size() ;
      for (size_t i = 0 ; i < cont.size() ; ++i) {
        //std::cout << "\n" << cont[i] << cont[i].find(" ") << " " << std::string::npos;
        if (cont[i].find_first_not_of(' ') != std::string::npos) {
          cont_no_space.push_back(cont[i]) ;
        }
      }
      //std::cout << std::endl ;
      //std::cout << "\nCont no splace size: " << cont_no_space.size() ;
      //for (size_t i = 0 ; i < cont_no_space.size() ; ++i) {
      //  std::cout << " " << cont_no_space[i] ;
      //}
      //std::cout << std::endl ;

      if (cont_no_space.size() != 3) {
        std::cout << "\n Need name, value, value type. Will skip this \"" << line << "\"" << std::endl ;
      }
      else {
        std::string name = cont_no_space[0] ;
        if (cont_no_space[2] == "int") para.Set(name, std::stoi(cont[1])) ;
        if (cont_no_space[2] == "float") para.Set(name, std::stof(cont_no_space[1])) ;
        if (cont_no_space[2] == "string") para.SetStr(name, cont_no_space[1]) ;
      }
    }

    myfile.close();
  }
  
  else cout << "Unable to open file"; 

}



int main(int argc, char *argv[]) {
  
  StdArg arg(argc,argv);
  std::cout << "======================================================================" << std::endl;
  std::cout << "Z+b analysis call:" << std::endl;
  for (int i=0;i<argc;i++) std::cout << argv[i] << " ";
  std::cout << endl;
  std::cout << "======================================================================" << std::endl;
  arg.keys << "-in" << "-filelist" << "-cfg" << "-out" << "-data" << "-year" << "-syst" 
           << "-firstentry" << "-lastentry" ; 
  arg.Process();

  std::vector<std::string> filenames;
  if ( arg.Key("-in")) 
    { 
      string inputfilenames;
      inputfilenames  = arg.Get<string>("-in"); 
      filenames = splitNames(inputfilenames);
    }
  else 
    { 
      string inputfilename;
      if (arg.Key("-filelist"))
	{
	  inputfilename  = arg.Get<string>("-filelist");
	  std::ifstream fList(inputfilename.c_str());
	  if (!fList){
	    cerr << ">>Can't open file " << inputfilename << endl;
	    return 1;
	  }
	  char lineFromFile[10000];
	  while (fList.getline(lineFromFile,10000)){
	    if ( strlen(lineFromFile)>0 ) filenames.push_back(string(lineFromFile));
	  }
	}
    }

  std::string cfgfilename =  "Configs/inputParameters.txt";
  if (arg.Key("-cfg")) cfgfilename = arg.Get<string>("-cfg");
  else std::cout << "\nUsing default configuration " << cfgfilename << std::endl; 
  
  std::string outputfilename =  "output.root";
  if (arg.Key("-out")) outputfilename = arg.Get<string>("-out");
  
  bool isData(false) ;
  
  int intisdata=0;
  int intfirstentry=0;
  long int intlastentry=-1;
  string syst = "none";
  string year = "";

  if (arg.Key("-data")) intisdata = arg.Get<int>("-data");
  if (arg.Key("-year")) year = arg.Get<string>("-year");
  if (arg.Key("-firstentry")) intfirstentry = arg.Get<int>("-firstentry");
  if (arg.Key("-lastentry")) intlastentry = arg.Get<int>("-lastentry");
  if (arg.Key("-syst")) syst = arg.Get<string>("-syst");

  if(intisdata!=0) isData=true;
  
  std::cout << "\n=================================" << std::endl ;
  std::cout << "\nIs data:              " << isData ;
  std::cout << "\nYear:                 " << year ;
  std::cout << "\nFirst and last entry: " << intfirstentry << " " << intlastentry ;
  std::cout << "\nSystematic:           " << syst ;
  
  std::cout << std::endl ;

  SetParameters(cfgfilename,CUTS) ;
  
  std::string chainName("Events") ;
  TChain chain(chainName.c_str()) ;
  for ( std::vector<std::string>::const_iterator it = filenames.begin();
	it != filenames.end(); it++) 
    {
      cout << "reading file " << it->c_str() << endl;
      int retcode = chain.Add(it->c_str(),-1);
      if ( retcode == 0 ) {
	throw std::invalid_argument("the file "+*it+" does not exist of does not contain the tree named "+chainName);
      }
    }

  //chain.Add("/uscms/home/duong/Scratch/test/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_PUMoriond17_Nano25Oct2019_102X_mcRun2_asymptotic_v7_18644D51-7512-5642-B506-C8B6BA051047.root") ;
  
  std::cout << "\n Number of events: " << chain.GetEntries() ;
  if (intlastentry == -1) intlastentry = chain.GetEntries() ;
  
  Processor ana ;
  ana.setOutPutFileName(outputfilename) ;
  ana.SetDataInfo(isData,year) ;
  
  //collection of all selectors
  std::vector<Selector*> sels;
  
  //Selection for Zb
  ZbSelection sel ;
  
  
  std::string fName_btagSF;
  std::string fName_PUjetID_SF;
  std::string fName_PUjetID_eff;
  std::vector<std::string> fName_eleTrig ;
  std::string fName_eleRecSF;
  std::string fName_eleIDSF;
  std::vector<float> lw_eleTrig; 
  std::vector<std::string> fName_muonTrig ;
  std::vector<std::string> fName_muonID ;
  std::vector<std::string> fName_muonIso ;
  std::vector<std::string> fName_muonReco ;
  std::vector<float> lw_muonTrig; 
  std::vector<float> lw_muonID;
  std::vector<float> lw_muonIso;
  std::vector<float> lw_muonReco;

  std::string fName_puSF;

#if defined(MC_preVFP2016) || defined(DATA_preVFP2016)
  std::string fName_roc("CalibData/RoccoR2016aUL.txt") ;
#endif
#if defined(MC_postVFP2016) || defined(DATA_postVFP2016)
  std::string fName_roc("CalibData/RoccoR2016bUL.txt") ;
#endif
#if defined(MC_2017) || defined(DATA_2017)
  std::string fName_roc("CalibData/RoccoR2017UL.txt") ;
#endif
#if defined(MC_2018) || defined(DATA_2018)
  std::string fName_roc("CalibData/RoccoR2018UL.txt") ;
#endif

#if defined(DATA_preVFP2016) || defined(DATA_postVFP2016)
  //std::string fName_lumiMaskFilter("CalibData/Cert_271036-284044_13TeV_PromptReco_Collisions16_JSON.txt");
  std::string fName_lumiMaskFilter("CalibData/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt");
#endif
#if defined(DATA_2017)
  std::string fName_lumiMaskFilter("CalibData/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt");
#endif
#if defined(DATA_2018)
  //std::string fName_lumiMaskFilter("CalibData/Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt");
  std::string fName_lumiMaskFilter("CalibData/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt");
#endif

#if defined(MC_preVFP2016) 
  fName_btagSF = "CalibData/DeepCSV_2016LegacySF_WP_V1.csv" ;//FIXME move to PNET
  //ele trig SF: https://twiki.cern.ch/twiki/bin/view/CMS/EgHLTScaleFactorMeasurements
  fName_eleTrig.push_back("CalibData/egammaTrigEffi_wp90noiso_preVFP_EGM2D_2016.root");
  //ele reco SF: https://twiki.cern.ch/twiki/bin/view/CMS/EgammaUL2016To2018
  fName_eleRecSF = "CalibData/egammaEffi_ptAbove20.txt_EGM2D_UL2016preVFP.root";
  //ele ID SF: https://twiki.cern.ch/twiki/bin/view/CMS/EgammaUL2016To2018
  fName_eleIDSF = "CalibData/egammaEffi.txt_Ele_Tight_preVFP_EGM2D.root" ;
  lw_eleTrig.push_back(1.0);
  //Muon:https://twiki.cern.ch/twiki/bin/viewauth/CMS/MuonUL2016#Medium_pT_from_15_to_120_GeV
  fName_muonTrig.push_back("CalibData/Efficiencies_muon_generalTracks_Z_Run2016_UL_HIPM_SingleMuonTriggers.root");
  lw_muonTrig.push_back(1.0);
  fName_muonID.push_back("CalibData/Efficiencies_muon_generalTracks_Z_Run2016_UL_HIPM_ID.root");
  lw_muonID.push_back(1.0);
  fName_muonIso.push_back("CalibData/Efficiencies_muon_generalTracks_Z_Run2016_UL_HIPM_ISO.root");
  lw_muonIso.push_back(1.0);
  fName_muonReco.push_back("CalibData/Efficiency_muon_generalTracks_Run2016preVFP_UL_trackerMuon.root");
  lw_muonReco.push_back(1.0);

  fName_puSF = "CalibData/2016_pileup_ratio.root";//FIXME
#endif
#if defined(MC_postVFP2016) 
  fName_btagSF = "CalibData/DeepCSV_2016LegacySF_WP_V1.csv" ;//FIXME move to PNET
  //ele trig SF: https://twiki.cern.ch/twiki/bin/view/CMS/EgHLTScaleFactorMeasurements
  fName_eleTrig.push_back("CalibData/egammaTrigEffi_wp90noiso_postVFP_EGM2D_2016.root");
  //ele reco SF: https://twiki.cern.ch/twiki/bin/view/CMS/EgammaUL2016To2018
  fName_eleRecSF = "CalibData/egammaEffi_ptAbove20.txt_EGM2D_UL2016postVFP.root";
  //ele ID SF: https://twiki.cern.ch/twiki/bin/view/CMS/EgammaUL2016To2018
  fName_eleIDSF = "CalibData/egammaEffi.txt_Ele_Tight_postVFP_EGM2D.root" ;
  lw_eleTrig.push_back(1.0);
  fName_muonTrig.push_back("CalibData/Efficiencies_muon_generalTracks_Z_Run2016_UL_SingleMuonTriggers.root");
  lw_muonTrig.push_back(1.0);
  fName_muonID.push_back("CalibData/Efficiencies_muon_generalTracks_Z_Run2016_UL_ID.root");
  lw_muonID.push_back(1.0);
  fName_muonIso.push_back("CalibData/Efficiencies_muon_generalTracks_Z_Run2016_UL_ISO.root");
  lw_muonIso.push_back(1.0);
  fName_muonReco.push_back("CalibData/Efficiency_muon_generalTracks_Run2016postVFP_UL_trackerMuon.root");
  lw_muonReco.push_back(1.0);

  fName_puSF = "CalibData/2016_pileup_ratio.root";//FIXME
#endif

#ifdef MC_2017
  fName_btagSF = "CalibData/DeepCSV_94XSF_WP_V4_B_F.csv";//FIXME
  fName_eleTrig.push_back("CalibData/egammaTrigEffi_wp90noiso_EGM2D_2017.root");
  fName_eleRecSF = "CalibData/egammaEffi_ptAbove20.txt_EGM2D_UL2017.root";
  fName_eleIDSF = "CalibData/egammaEffi.txt_EGM2D_Tight_UL17.root";
  lw_eleTrig.push_back(1.0);
  fName_muonTrig.push_back("CalibData/Efficiencies_muon_generalTracks_Z_Run2017_UL_SingleMuonTriggers.root");
  lw_muonTrig.push_back(1.);
  fName_muonID.push_back("CalibData/Efficiencies_muon_generalTracks_Z_Run2017_UL_ID.root");
  lw_muonID.push_back(1.);
  fName_muonIso.push_back("CalibData/Efficiencies_muon_generalTracks_Z_Run2017_UL_ISO.root");
  lw_muonIso.push_back(1.);
  fName_muonReco.push_back("CalibData/Efficiency_muon_generalTracks_Run2017_UL_trackerMuon.root");
  lw_muonReco.push_back(1.0);


  fName_puSF = "CalibData/2017_pileup_ratio.root";
#endif
#ifdef MC_2018
  fName_btagSF = "CalibData/DeepCSV_102XSF_WP_V1.csv";//FIXME
  fName_eleTrig.push_back("CalibData/egammaTrigEffi_wp90noiso_EGM2D_2018.root");
  fName_eleRecSF = "CalibData/egammaEffi_ptAbove20.txt_EGM2D_UL2018.root";
  fName_eleIDSF = "CalibData/egammaEffi.txt_Ele_Tight_EGM2D.root";
  lw_eleTrig.push_back(1.0);
  fName_muonTrig.push_back("CalibData/Efficiencies_muon_generalTracks_Z_Run2018_UL_SingleMuonTriggers.root");
  lw_muonTrig.push_back(1.0);
  fName_muonID.push_back("CalibData/Efficiencies_muon_generalTracks_Z_Run2018_UL_ID.root");
  lw_muonID.push_back(1.);
  fName_muonIso.push_back("CalibData/Efficiencies_muon_generalTracks_Z_Run2018_UL_ISO.root");
  lw_muonIso.push_back(1.);
  fName_muonReco.push_back("CalibData/Efficiency_muon_generalTracks_Run2018_UL_trackerMuon.root");
  lw_muonReco.push_back(1.0);
  fName_puSF = "CalibData/2018_pileup_ratio.root";
#endif
#if defined(MC_preVFP2016) || defined(MC_postVFP2016) || defined(MC_2017) || defined(MC_2018)
  fName_PUjetID_SF = "CalibData/scalefactorsPUID_81Xtraining.root";
  fName_PUjetID_eff = "CalibData/effcyPUID_81Xtraining.root";
  sel.SetRandom() ; //used for muon rochestor correction (used when correcting for MC)
  if (CUTS.GetStr("jet_main_btagWP")=="deepCSVT") sel.SetBtagCalib(fName_btagSF,"DeepCSV","CalibData/effT.root");
  if (CUTS.GetStr("jet_main_btagWP")=="deepJetT") sel.SetBtagCalib(fName_btagSF,"DeepJet","CalibData/effT.root");
  if (CUTS.GetStr("jet_main_btagWP")=="deepCSVM") sel.SetBtagCalib(fName_btagSF,"DeepCSV","CalibData/effM.root");
  if (CUTS.GetStr("jet_main_btagWP")=="deepJetM") sel.SetBtagCalib(fName_btagSF,"DeepJet","CalibData/effM.root");
  sel.SetEleEffCorr(fName_eleTrig,fName_eleRecSF,fName_eleIDSF,lw_eleTrig);
  sel.SetMuonEffCorr(fName_muonTrig,fName_muonID,fName_muonIso,fName_muonReco,lw_muonTrig,lw_muonID,lw_muonIso,lw_muonReco);
  sel.SetPileupSF(fName_puSF);
  sel.SetPUjetidCalib(fName_PUjetID_SF,fName_PUjetID_eff); //pileup jet ID SF
#endif
  sel.SetRochesterCorr(fName_roc) ;
#if defined(DATA_preVFP2016) || defined(DATA_postVFP2016) || defined(DATA_2017) || defined(DATA_2018)
  sel.SetLumiMaskFilter(fName_lumiMaskFilter);
#endif

  sels.push_back(&sel) ;
  
  //add all selectors to processors
  for (std::vector<Selector*>::iterator it = sels.begin() ; it != sels.end() ; it++) ana.addSelector(*it) ;
  
  chain.Process(&ana,"",intlastentry,intfirstentry) ;
  
  return 0 ;
}
