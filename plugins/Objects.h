#ifndef OBJECTS_H
#define OBJECTS_H

struct LeptonType {
LeptonType(): pt(-1.), eta(-9.), phi(-9.), mass(-1.), energy(-1.), inTrkPt(-1.), pfIso03(-1.), pfIso04(-1.), trkIso(-1.), miniIso(-1.), dxy(-99.), dz(-99.), ip3d(-99.), sip3d(-99.), nPixelHits(-1.), dPhi_met(-1.), charge(0), pdgId(0), isElectron(false), isMuon(false), isVeto(false), isLoose(false), isMedium(false), isTight(false), isHighPt(false), isTrackerHighPt(false), SSscale(-1.), SSsigma(-1.), SSscaleUnc(-1.), SSsigmaUncUp(-1.), SSsigmaUncDown(-1.), SScorr(-1.), energySScorr(-1.), energySScorrUncUp(-1.), energySScorrUncDown(-1.), ptSScorr(-1.), ptSScorrUncUp(-1.), ptSScorrUncDown(-1.), isMatched(false) {} // isHEEP(false), isMVANonTrigMedium(false), isMVANonTrigTight(false), isMVATrigMedium(false), isMVATrigTight(false)
    float pt;
    float eta;
    float phi;
    float mass;
    float energy;
    float inTrkPt;
    float pfIso03;
    float pfIso04;
    float trkIso;
    float miniIso;
    float dxy;
    float dz;
    float ip3d;
    float sip3d;
    float nPixelHits;
    float dPhi_met;
    int charge;
    int pdgId;
    bool isElectron;
    bool isMuon;
    bool isVeto;
    bool isLoose;
    bool isMedium;
    bool isTight;
//    bool isHEEP;
//    bool isMVANonTrigMedium;
//    bool isMVANonTrigTight;
//    bool isMVATrigMedium;
//    bool isMVATrigTight;
    bool isHighPt;
    bool isTrackerHighPt;

    float SSscale;
    float SSsigma;
    float SSscaleUnc;
    float SSsigmaUncUp;
    float SSsigmaUncDown;
    float SScorr;
    float energySScorr;
    float energySScorrUncUp;
    float energySScorrUncDown;
    float ptSScorr;
    float ptSScorrUncUp;
    float ptSScorrUncDown;

    bool isMatched;
};

struct PhotonType {
PhotonType(): pt(-1.), eta(-9.), phi(-9.), mass(-1.), energy(-1.), pfIso(-1.), dz(-99.), charge(0), pdgId(0), isLoose(false), isMedium(false), isTight(false), isMVANonTrigMedium(false), isMatched(false) {}
    float pt;
    float eta;
    float phi;
    float mass;
    float energy;
    float pfIso;
    float dz;
    int charge;
    int pdgId;
    bool isLoose;
    bool isMedium;
    bool isTight;
    bool isMVANonTrigMedium;
    bool isMatched;
};

struct TauType {
TauType(): pt(-1.), eta(-9.), phi(-9.), mass(-1.), energy(-1.), pfIso(-1.), dz(-99.), charge(0), pdgId(0), isLoose(false), isMedium(false), isTight(false), isMatched(false) {}
    float pt;
    float eta;
    float phi;
    float mass;
    float energy;
    float pfIso;
    float dz;
    int charge;
    int pdgId;
    bool isLoose;
    bool isMedium;
    bool isTight;
    bool isMatched;
};


struct JetType {
JetType(): pt(-1.), eta(-9.), phi(-9.), mass(-1.), energy(-1.), ptRaw(-1.), ptUnc(-1.), dPhi_met(-1.), dPhi_Jet1(-1.), puId(-1.), CSV(-99.), CSVR(-99.), CSVRUp(-99.), CSVRDown(-99.), CMVA(-99.), CMVAR(-99.), CMVARUp(-99.), CMVARDown(-99.), QGLikelihood(-1.), chf(-1.), nhf(-1.), phf(-1.), elf(-1.), muf(-1.), ptGenJ(-10.), etaGenJ(-4.), phiGenJ(-4.), massGenJ(-10.),ptGen(-10.), etaGen(-4.), phiGen(-4.), massGen(-10.), pdgIdGen(0.), ptLhe(-10.), etaLhe(-4.), phiLhe(-4.), chm(-1), npr(-1), cm(-1), nm(-1), partonFlavour(0), hadronFlavour(0), mother(0), isLoose(false), isMedium(false), isTight(false), isTightLepVeto(false), isCSVL(false), isCSVM(false), isCSVT(false), isMatched(false), dR_q1(1000), dR_q2(1000), dR_q3(1000), dR_q4(1000), m_q1(false), m_q2(false), m_q3(false), m_q4(false), dR_pi1(1000), dR_pi2(1000), matchBquark(-1), matchLL(-1), original_jet_index(-1) {}
    float pt;
    float eta;
    float phi;
    float mass;
    float energy;
    float ptRaw;
    float ptUnc;
    float dPhi_met;
    float dPhi_Jet1;
    float puId;
    float CSV;
    float CSVR;
    float CSVRUp;
    float CSVRDown;
    float CMVA;
    float CMVAR;
    float CMVARUp;
    float CMVARDown;
    float QGLikelihood;
    float chf;
    float nhf;
    float phf;
    float elf;
    float muf;
    float ptGenJ; 
    float etaGenJ;
    float phiGenJ;
    float massGenJ;
    float ptGen;
    float etaGen;
    float phiGen;
    float massGen;
    int pdgIdGen;
    float ptLhe;
    float etaLhe;
    float phiLhe;
    int chm;
    int npr;
    int cm;
    int nm;
    int partonFlavour;
    int hadronFlavour;
    int mother;
    bool isLoose;
    bool isMedium;
    bool isTight;
    bool isTightLepVeto;
    bool isCSVL;
    bool isCSVM;
    bool isCSVT;
    bool isMatched;
    float dR_q1;
    float dR_q2;
    float dR_q3;
    float dR_q4;
    bool m_q1;
    bool m_q2;
    bool m_q3;
    bool m_q4;
    float dR_pi1;
    float dR_pi2;
    int matchBquark;
    int matchLL;
    int original_jet_index;
};



struct FatJetType {
FatJetType(): pt(-1.), eta(-9.), phi(-9.), mass(-1.), energy(-1.), ptRaw(-1.), ptUnc(-1.), dPhi_met(-1.), dPhi_Jet1(-1.), puId(-1.), CSV(-99.), CSVR(-99.), CSVRUp(-99.), CSVRDown(-99.), CHSprunedMass(-1.), CHSsoftdropMass(-1.), softdropPuppiMass(-1.), CHSprunedMassCorr(-1.), CHSsoftdropMassCorr(-1.), softdropPuppiMassCorr(-1.), softdropPuppiMassCorrNotSmeared(-1.), pt1(-1.), eta1(-9.), phi1(-9.), mass1(-1.), CSV1(-99.), CSVR1(-99.), CSVR1Up(-99.), CSVR1Down(-99.), CMVA1(-99.), CMVAR1(-99.), CMVAR1Up(-99.), CMVAR1Down(-99.), flavour1(-1.), pt2(-1.), eta2(-9.), phi2(-9.), mass2(-1.), CSV2(-99.), CSVR2(-99.), CSVR2Up(-99.), CSVR2Down(-99.), CMVA2(-99.), CMVAR2(-99.), CMVAR2Up(-99.), CMVAR2Down(-99.), flavour2(-1.), dR(-1.), chsTau21(-1.), puppiTau21(-1.), BDSV(-1.), chf(-1.), nhf(-1.), phf(-1.), elf(-1.), muf(-1.), chm(-1), npr(-1), partonFlavour(0), hadronFlavour(0), mother(0), isLoose(false), isMedium(false), isTight(false), isTightLepVeto(false), isMatched(false), JESUnc(-1.), ptJERUp(-1.), etaJERUp(-1.), phiJERUp(-9.), energyJERUp(-1.), ptJERDown(-1.), etaJERDown(-1.), phiJERDown(-9.), energyJERDown(-1.), smearFact(-1.), smearFactUp(-1.), smearFactDown(-1.), softdropPuppiMassCorrJMS(-1.), softdropPuppiMassCorrJMSUp(-1.), softdropPuppiMassCorrJMSDown(-1.), softdropPuppiMassCorrJMR(-1.), softdropPuppiMassCorrJMRUp(-1.), softdropPuppiMassCorrJMRDown(-1.), dR_q1(1000), dR_q2(1000), dR_q3(1000), dR_q4(1000), m_q1(false), m_q2(false), m_q3(false), m_q4(false), dR_pi1(1000), dR_pi2(1000), matchBquark(-1), matchLL(-1) {}
    float pt;
    float eta;
    float phi;
    float mass;
    float energy;
    float ptRaw;
    float ptUnc;
    float dPhi_met;
    float dPhi_Jet1;
    float puId;
    float CSV;
    float CSVR;
    float CSVRUp;
    float CSVRDown;
    float CHSprunedMass;
    float CHSsoftdropMass;
    float softdropPuppiMass;
    float CHSprunedMassCorr;
    float CHSsoftdropMassCorr;
    float softdropPuppiMassCorr;
    float softdropPuppiMassCorrNotSmeared;
    float pt1;
    float eta1;
    float phi1;
    float mass1;
    float CSV1;
    float CSVR1;
    float CSVR1Up;
    float CSVR1Down;
    float CMVA1;
    float CMVAR1;
    float CMVAR1Up;
    float CMVAR1Down;
    float flavour1;
    float pt2;
    float eta2;
    float phi2;
    float mass2;
    float CSV2;
    float CSVR2;
    float CSVR2Up;
    float CSVR2Down;
    float CMVA2;
    float CMVAR2;
    float CMVAR2Up;
    float CMVAR2Down;
    float flavour2;
    float dR;
    float chsTau21;
    float puppiTau21;
    float ddtTau21;
    float BDSV;
    float chf;
    float nhf;
    float phf;
    float elf;
    float muf;
    int chm;
    int npr;
    int partonFlavour;
    int hadronFlavour;
    int mother;
    bool isLoose;
    bool isMedium;
    bool isTight;
    bool isTightLepVeto;
    bool isMatched;
    float JESUnc;
    float ptJERUp;
    float etaJERUp;
    float phiJERUp;
    float energyJERUp;
    float ptJERDown;
    float etaJERDown;
    float phiJERDown;
    float energyJERDown;
    float smearFact;
    float smearFactUp;
    float smearFactDown;
    float softdropPuppiMassCorrJMS;
    float softdropPuppiMassCorrJMSUp;
    float softdropPuppiMassCorrJMSDown;
    float softdropPuppiMassCorrJMR;
    float softdropPuppiMassCorrJMRUp;
    float softdropPuppiMassCorrJMRDown;
    float dR_q1;
    float dR_q2;
    float dR_q3;
    float dR_q4;
    bool m_q1;
    bool m_q2;
    bool m_q3;
    bool m_q4;
    float dR_pi1;
    float dR_pi2;
    int matchBquark;
    int matchLL;
};


//struct MEtType {
//    MEtType(): pt(-1.), eta(-9.), phi(-9.), sign(-1.) {}
//    float pt;
//    float eta;
//    float phi;
//    float sign;
//};

struct MEtType {
  //MEtType(): pt(-1.), eta(-9.), phi(-9.), sign(-1.), ptRaw(-1.), phiRaw(-9.), ptType1(-1.), phiType1(-9.), ptGen(-1.), phiGen(-9.), ptScaleUp(-1.), ptScaleDown(-1.), ptResUp(-1.), ptResDown(-1.), ptCalo(-1.) {}
    MEtType(): pt(-1.), eta(-9.), phi(-9.), sign(-1.), ptShiftJetResUp(-1.), ptShiftJetResDown(-1.), ptShiftJetEnUp(-1.), ptShiftJetEnDown(-1.), ptShiftUnclusteredEnUp(-1.), ptShiftUnclusteredEnDown(-1.), ptShiftJetResUpSmear(-1.), ptShiftJetResDownSmear(-1.), ptRaw(-1.), phiRaw(-9.), ptGen(-1.), phiGen(-9.), ptCalo(-1.) {}
    float pt;
    float eta;
    float phi;
    float sign;
    float ptShiftJetResUp;
    float ptShiftJetResDown;
    float ptShiftJetEnUp;
    float ptShiftJetEnDown;
    float ptShiftUnclusteredEnUp;
    float ptShiftUnclusteredEnDown;
    float ptShiftJetResUpSmear;
    float ptShiftJetResDownSmear;
    float ptRaw;
    float phiRaw;
  //float ptType1;
  //float phiType1;
    float ptGen;
    float phiGen;
  //float ptScaleUp;
  //float ptScaleDown;
  //float ptResUp;
  //float ptResDown;
    float ptCalo;
};

struct MEtFullType {
    MEtFullType(): pt(-1.), eta(-9.), phi(-9.), sign(-1.), ptRaw(-1.), phiRaw(-9.), ptGen(-1.), phiGen(-9.), ptJERUp(-1.), ptJERDown(-1.), ptJERUpSmear(-1.), ptJERDownSmear(-1.), ptJESUp(-1.), ptJESDown(-1.), ptMUSUp(-1.), ptMUSDown(-1.), ptELSUp(-1.), ptELSDown(-1.), ptTAUUp(-1.), ptTAUDown(-1.), ptUNCUp(-1.), ptUNCDown(-1.), ptPHOUp(-1.), ptPHODown(-1.), phf(-1.), nhf(-1.), elf(-1.), chf(-1.), muf(-1.) {}
    float pt;
    float eta;
    float phi;
    float sign;
    float ptRaw;
    float phiRaw;
    float ptGen;
    float phiGen;
    float ptJERUp;
    float ptJERDown;
    float ptJERUpSmear;
    float ptJERDownSmear;
    float ptJESUp;
    float ptJESDown;
    float ptMUSUp;
    float ptMUSDown;
    float ptELSUp;
    float ptELSDown;
    float ptTAUUp;
    float ptTAUDown;
    float ptUNCUp;
    float ptUNCDown;
    float ptPHOUp;
    float ptPHODown;
    float phf;
    float nhf;
    float elf;
    float chf;
    float muf;
};


struct CandidateType {
    CandidateType(): pt(-1.), eta(-9.), phi(-9.), mass(-1.), tmass(-1.), dR(-1.), dEta(-1.), dPhi(-1.), twist(-1.) {} // angle(-1.), ptBalance(-9.), centrality(-1.), charge(0), 
    float pt;
    float eta;
    float phi;
    float mass;
    float tmass;
//    float softdropMass;
//    float tmassScaleUp;
//    float tmassScaleDown;
//    float tmassResUp;
//    float tmassResDown;
    float dR;
    float dEta;
    float dPhi;
    float twist;
  //  float angle;
  //  float ptBalance;
  //  float centrality;
  //  int charge;
//    bool isMatched;
};





struct LorentzType {
  LorentzType(): pt(-1.), eta(-9.), phi(-9.), energy(-1.), mass(-1.) {}
  float pt;
  float eta;
  float phi;
  float energy;
  float mass;
};

struct EventType {
  EventType(): id1(-9), id2(-9), x1(-1.), x2(-1.), Q(-1.) {}
  int id1;
  int id2;
  float x1;
  float x2;
  float Q;
};

struct GenPType {
GenPType(): pt(-1.), eta(-9.), phi(-9.), mass(-1.), energy(-1.), charge(0), pdgId(0), status(0), radius(-1), motherid(0) {}
    float pt;
    float eta;
    float phi;
    float mass;
    float energy;
    int charge;
    int pdgId;
    int status;
    float radius;
    int motherid;
};


struct CustomFatJetType {
//CustomFatJetType(): pt(-1.), eta(-9.), phi(-9.), mass(-1.), energy(-1.), ptRaw(-1.), ptUnc(-1.), dPhi_met(-1.), dPhi_Jet1(-1.), puId(-1.), CSV(-99.), CSVR(-99.), CSVRUp(-99.), CSVRDown(-99.), CHSprunedMass(-1.), CHSsoftdropMass(-1.), prunedMass(-1.), softdropMass(-1.), softdropPuppiMass(-1.), CHSprunedMassCorr(-1.), CHSsoftdropMassCorr(-1.), prunedMassCorr(-1.), softdropMassCorr(-1.), softdropPuppiMassCorr(-1.), softdropPuppiMassCorrNotSmeared(-1.), pt1(-1.), eta1(-9.), phi1(-9.), mass1(-1.), CSV1(-99.), CSVR1(-99.), CSVR1Up(-99.), CSVR1Down(-99.), CMVA1(-99.), CMVAR1(-99.), CMVAR1Up(-99.), CMVAR1Down(-99.), flavour1(-1.), pt2(-1.), eta2(-9.), phi2(-9.), mass2(-1.), CSV2(-99.), CSVR2(-99.), CSVR2Up(-99.), CSVR2Down(-99.), CMVA2(-99.), CMVAR2(-99.), CMVAR2Up(-99.), CMVAR2Down(-99.), flavour2(-1.), dR(-1.), Tau21(-1.), puppiTau21(-1.), BDSV(-1.), chf(-1.), nhf(-1.), phf(-1.), elf(-1.), muf(-1.), chm(-1), npr(-1), flavour(0), mother(0), isLoose(false), isMedium(false), isTight(false), isTightLepVeto(false), isMatched(false), JESUnc(-1.), ptJERUp(-1.), etaJERUp(-1.), phiJERUp(-9.), energyJERUp(-1.), ptJERDown(-1.), etaJERDown(-1.), phiJERDown(-9.), energyJERDown(-1.), smearFact(-1.), smearFactUp(-1.), smearFactDown(-1.), softdropPuppiMassCorrJMS(-1.), softdropPuppiMassCorrJMSUp(-1.), softdropPuppiMassCorrJMSDown(-1.), softdropPuppiMassCorrJMR(-1.), softdropPuppiMassCorrJMRUp(-1.), softdropPuppiMassCorrJMRDown(-1.), dR_q1(1000), dR_q2(1000), dR_q3(1000), dR_q4(1000), m_q1(false), m_q2(false), m_q3(false), m_q4(false), dR_pi1(1000), dR_pi2(1000), matchBquark(-1), matchLL(-1) {}
//simplified version
CustomFatJetType(): pt(-1.), eta(-9.), phi(-9.), mass(-1.), energy(-1.), ptRaw(-1.), ptUnc(-1.), dPhi_met(-1.), dPhi_Jet1(-1.), puId(-1.), CSV(-99.), CHSprunedMass(-1.), CHSsoftdropMass(-1.), prunedMass(-1.), softdropMass(-1.), softdropPuppiMass(-1.), CHSprunedMassCorr(-1.), CHSsoftdropMassCorr(-1.), prunedMassCorr(-1.), softdropMassCorr(-1.), softdropPuppiMassCorr(-1.), softdropPuppiMassCorrNotSmeared(-1.), pt1(-1.), eta1(-9.), phi1(-9.), mass1(-1.), CSV1(-99.), CMVA1(-99.), flavour1(-1.), pt2(-1.), eta2(-9.), phi2(-9.), mass2(-1.), CSV2(-99.), CMVA2(-99.), flavour2(-1.), pt1SDP(-1.), eta1SDP(-9.), phi1SDP(-9.), mass1SDP(-1.), CSV1SDP(-99.), CMVA1SDP(-99.), flavour1SDP(-1.), pt2SDP(-1.), eta2SDP(-9.), phi2SDP(-9.), mass2SDP(-1.), CSV2SDP(-99.), CMVA2SDP(-99.), flavour2SDP(-1.), dR(-1.), Tau21(-1.), puppiTau21(-1.), BDSV(-1.), chf(-1.), nhf(-1.), phf(-1.), elf(-1.), muf(-1.), chm(-1), npr(-1), partonFlavour(0), hadronFlavour(0), mother(0), isLoose(false), isMedium(false), isTight(false), isTightLepVeto(false), dR_q1(1000), dR_q2(1000), dR_q3(1000), dR_q4(1000), m_q1(false), m_q2(false), m_q3(false), m_q4(false), dR_pi1(1000), dR_pi2(1000), matchBquark(-1), matchLL(-1), dR_q1_sj1(1000), dR_q2_sj1(1000), dR_q3_sj1(1000), dR_q4_sj1(1000), dR_pi1_sj1(1000), dR_pi2_sj1(1000), dR_q1_sj2(1000), dR_q2_sj2(1000), dR_q3_sj2(1000), dR_q4_sj2(1000), dR_pi1_sj2(1000), dR_pi2_sj2(1000) {}
    float pt;
    float eta;
    float phi;
    float mass;
    float energy;
    float ptRaw;
    float ptUnc;
    float dPhi_met;
    float dPhi_Jet1;
    float puId;
    float CSV;
  //float CSVR;
  //float CSVRUp;
  //float CSVRDown;
    float CHSprunedMass;
    float CHSsoftdropMass;
    float prunedMass;
    float softdropMass;
    float softdropPuppiMass;
    float CHSprunedMassCorr;
    float CHSsoftdropMassCorr;
    float prunedMassCorr;
    float softdropMassCorr;
    float softdropPuppiMassCorr;
    float softdropPuppiMassCorrNotSmeared;
    float pt1;
    float eta1;
    float phi1;
    float mass1;
    float CSV1;
  //float CSVR1;
  //float CSVR1Up;
  //float CSVR1Down;
    float CMVA1;
  //float CMVAR1;
  //float CMVAR1Up;
  //float CMVAR1Down;
    float flavour1;
    float pt2;
    float eta2;
    float phi2;
    float mass2;
    float CSV2;
  //float CSVR2;
  //float CSVR2Up;
  //float CSVR2Down;
    float CMVA2;
  //float CMVAR2;
  //float CMVAR2Up;
  //float CMVAR2Down;
    float flavour2;
    float pt1SDP;
    float eta1SDP;
    float phi1SDP;
    float mass1SDP;
    float CSV1SDP;
    float CMVA1SDP;
    float flavour1SDP;
    float pt2SDP;
    float eta2SDP;
    float phi2SDP;
    float mass2SDP;
    float CSV2SDP;
    float CMVA2SDP;
    float flavour2SDP;
    float dR;
    float Tau21;
    float puppiTau21;
    float ddtTau21;
    float BDSV;
    float chf;
    float nhf;
    float phf;
    float elf;
    float muf;
    int chm;
    int npr;
    int partonFlavour;
    int hadronFlavour;
    int mother;
    bool isLoose;
    bool isMedium;
    bool isTight;
    bool isTightLepVeto;
  //bool isMatched;
  //float JESUnc;
  //float ptJERUp;
  //float etaJERUp;
  //float phiJERUp;
  //float energyJERUp;
  //float ptJERDown;
  //float etaJERDown;
  //float phiJERDown;
  //float energyJERDown;
  //float smearFact;
  //float smearFactUp;
  //float smearFactDown;
  //float softdropPuppiMassCorrJMS;
  //float softdropPuppiMassCorrJMSUp;
  //float softdropPuppiMassCorrJMSDown;
  //float softdropPuppiMassCorrJMR;
  //float softdropPuppiMassCorrJMRUp;
  //float softdropPuppiMassCorrJMRDown;
    float dR_q1;
    float dR_q2;
    float dR_q3;
    float dR_q4;
    bool m_q1;
    bool m_q2;
    bool m_q3;
    bool m_q4;
    float dR_pi1;
    float dR_pi2;
    int matchBquark;
    int matchLL;
    float dR_q1_sj1;
    float dR_q2_sj1;
    float dR_q3_sj1;
    float dR_q4_sj1;
    float dR_pi1_sj1;
    float dR_pi2_sj1;
    float dR_q1_sj2;
    float dR_q2_sj2;
    float dR_q3_sj2;
    float dR_q4_sj2;
    float dR_pi1_sj2;
    float dR_pi2_sj2;
};



struct CaloJetType {
CaloJetType(): pt(-1.), eta(-9.), phi(-9.), mass(-1.), energy(-1.), ptUnc(-1.), dPhi_met(-1.), dPhi_Jet1(-1.), puId(-1.), CSV(-99.), CSVR(-99.), CSVRUp(-99.), CSVRDown(-99.), CMVA(-99.), CMVAR(-99.), CMVARUp(-99.), CMVARDown(-99.), QGLikelihood(-1.), chf(-1.), nhf(-1.), phf(-1.), elf(-1.), muf(-1.), ptGenJ(-10.), etaGenJ(-4.), phiGenJ(-4.), massGenJ(-10.),ptGen(-10.), etaGen(-4.), phiGen(-4.), massGen(-10.), pdgIdGen(0.), ptLhe(-10.), etaLhe(-4.), phiLhe(-4.), chm(-1), npr(-1), cm(-1), nm(-1), partonFlavour(0), hadronFlavour(0), mother(0), isLoose(false), isMedium(false), isTight(false), isTightLepVeto(false), isCSVL(false), isCSVM(false), isCSVT(false), isMatched(false), dR_q1(1000), dR_q2(1000), dR_q3(1000), dR_q4(1000), m_q1(false), m_q2(false), m_q3(false), m_q4(false), dR_pi1(1000), dR_pi2(1000), matchBquark(-1), matchLL(-1), original_jet_index(-1) {}
    float pt;
    float eta;
    float phi;
    float mass;
    float energy;
  //    float ptRaw;
    float ptUnc;
    float dPhi_met;
    float dPhi_Jet1;
    float puId;
    float CSV;
    float CSVR;
    float CSVRUp;
    float CSVRDown;
    float CMVA;
    float CMVAR;
    float CMVARUp;
    float CMVARDown;
    float QGLikelihood;
    float chf;
    float nhf;
    float phf;
    float elf;
    float muf;
    float ptGenJ; 
    float etaGenJ;
    float phiGenJ;
    float massGenJ;
    float ptGen;
    float etaGen;
    float phiGen;
    float massGen;
    int pdgIdGen;
    float ptLhe;
    float etaLhe;
    float phiLhe;
    int chm;
    int npr;
    int cm;
    int nm;
    int partonFlavour;
    int hadronFlavour;
    int mother;
    bool isLoose;
    bool isMedium;
    bool isTight;
    bool isTightLepVeto;
    bool isCSVL;
    bool isCSVM;
    bool isCSVT;
    bool isMatched;
    float dR_q1;
    float dR_q2;
    float dR_q3;
    float dR_q4;
    bool m_q1;
    bool m_q2;
    bool m_q3;
    bool m_q4;
    float dR_pi1;
    float dR_pi2;
    int matchBquark;
    int matchLL;
    int original_jet_index;
};


#endif

