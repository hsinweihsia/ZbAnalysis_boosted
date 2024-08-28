#ifndef Obj_cxx
#define Obj_cxx

//The objects are wrapper so that the analysis is independent on variable name on the ntuple, only when the objects are created such dependences occur 

#include "TLorentzVector.h"

//-------------------------------objs------------------------------
class LepObj {

  public:
    
    LepObj(float pt, float eta, float scEta, float phi, float mass, unsigned idx, int charge, 
           float iso) : m_scEta(scEta), m_idx(idx), m_charge(charge), m_iso(iso) { 
             m_lvec.SetPtEtaPhiM(pt, eta, phi, mass) ; 
    } ;

    virtual ~LepObj() {} ;

    TLorentzVector m_lvec ; 
    
    float m_scEta ;
    unsigned m_idx ;
    int m_charge ;
    float m_iso ;
    
} ;

class JetObj {
  
  public: 
    JetObj(float pt, float eta, float phi, float mass, unsigned flav, float particleNetMD_QCD, float particleNetMD_Xbb, float tau1, float tau2, float tau3, float tau4, float msoftdrop,int idx1,int idx2, float n2b1, float n3b1) : m_flav(flav),m_particleNetMD_QCD(particleNetMD_QCD),
m_particleNetMD_Xbb(particleNetMD_Xbb),m_tau1(tau1),m_tau2(tau2),m_tau3(tau3),m_tau4(tau4),m_mSD(msoftdrop),m_idx1(idx1),m_idx2(idx2), m_n2b1(n2b1),m_n3b1(n3b1) {
    m_lvec.SetPtEtaPhiM(pt, eta, phi, mass) ;  
    } ;

    virtual ~JetObj() {} ;

    bool IsLepton(std::vector<LepObj>& leps) {
      float minDr = 1000 ;
      for (std::vector<LepObj>::iterator it = leps.begin() ; it != leps.end() ; ++it) {
        float dRtmp = m_lvec.DeltaR(it->m_lvec) ;
        if (dRtmp < minDr) minDr = dRtmp ;
      }
      return minDr <= 0.8 ;
    }

    void SetSV(std::vector<TLorentzVector>& sv) {
      float maxPt = -1;
      m_svIdx = -1;
      m_mSV = -1;
      for (unsigned isv = 0 ; isv < sv.size() ; ++isv) {
        float dRtmp = m_lvec.DeltaR(sv[isv]);
        if (dRtmp <= 0.4 && sv[isv].Pt() > maxPt) {
          m_svIdx = isv; 
          m_mSV = sv[isv].M();
        }
      }
    } ;

    TLorentzVector m_lvec ;
    unsigned m_flav ;
    float m_deepCSV ;
    unsigned m_svIdx ;
    float m_mSV;
    float m_particleNetMD_QCD; 
    float m_particleNetMD_Xbb; 
    float m_tau1; 
    float m_tau2; 
    float m_tau3; 
    float m_tau4;
    float m_mSD;
    int m_idx1;
    int m_idx2;
    float m_n2b1;
                                                                                                                                     float m_n3b1;
} ;

class ZObj {
  
  public:
    
    ZObj(LepObj lep0, LepObj lep1) : m_lep0(lep0), m_lep1(lep1) {
      m_lvec = m_lep0.m_lvec + m_lep1.m_lvec ;
    } ;

    virtual ~ZObj() {} ;
    
    TLorentzVector m_lvec ;
    LepObj m_lep0 ;
    LepObj m_lep1 ;

} ;

class JetPlot {
  
  public:
    
    JetPlot(JetObj jetcut1) : jet_cut1(jetcut1) {
      m_lvec = jet_cut1.m_lvec  ;
    } ;

    virtual ~JetPlot() {} ;

    TLorentzVector m_lvec ;
    float m_deepCSV ;

	JetObj jet_cut1 ;
} ;


#endif
