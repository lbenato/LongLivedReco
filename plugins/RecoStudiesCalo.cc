// -*- C++ -*-
//
// Package:    Analyzer/LongLivedReco
// Class:      RecoStudiesCalo
// 
/**\class RecoStudiesCalo RecoStudiesCalo.cc Analyzer/LongLivedReco/plugins/RecoStudiesCalo.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Lisa Benato
//         Created:  Mon, 30 Apr 2018 12:29:19 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Framework/interface/EDConsumerBase.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"

#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h" 
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "TTree.h"
#include <string>
//#include "RecoStudies.h"
#include "JetAnalyzer.h"
#include "GenAnalyzer.h"
#include "PileupAnalyzer.h"
#include "TriggerAnalyzer.h"
#include "Objects.h"
#include "ObjectsFormat.h"

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class RecoStudiesCalo : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit RecoStudiesCalo(const edm::ParameterSet&);
      //RecoStudiesCalo(const edm::ParameterSet&, edm::ConsumesCollector&&);
      ~RecoStudiesCalo();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
      virtual bool isLooseJet(pat::Jet&);
      virtual bool isTightJet(pat::Jet&);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      bool passIDWP(std::string, bool, float, float, float, float, float, float, float, bool, int);

      // ----------member data ---------------------------
    edm::EDGetTokenT<edm::TriggerResults> trigResultsToken;
    edm::EDGetTokenT<edm::TriggerResults> filterResultsToken;
    edm::EDGetTokenT<bool> badChCandFilterToken;
    edm::EDGetTokenT<bool> badPFMuonFilterToken;
    edm::EDGetTokenT<reco::GenJetCollection> genJetToken;
  //edm::EDGetTokenT<pat::METCollection> metToken;
  //edm::EDGetTokenT<pat::JetCollection> jetToken;
  //edm::EDGetTokenT<pat::JetCollection> fatjetToken;
  //edm::EDGetTokenT<pat::MuonCollection> muonToken;
  //edm::EDGetTokenT<reco::VertexCollection> vertexToken;
  //edm::EDGetTokenT<pat::ElectronCollection> electronToken;
    edm::EDGetTokenT<reco::CaloJetCollection> caloJetToken;
    edm::ParameterSet GenPSet;
    edm::ParameterSet PileupPSet;
    edm::ParameterSet TriggerPSet;
    edm::ParameterSet CHSJetPSet;
    edm::ParameterSet PuppiJetPSet;
    edm::ParameterSet JetPSet;
    edm::ParameterSet CHSFatJetPSet;
    edm::ParameterSet FatJetPSet;
    //edm::ParameterSet RecoJetPSet;
    //std::string JerName_res;

    JetAnalyzer* theCHSJetAnalyzer;
    JetAnalyzer* thePuppiJetAnalyzer;
    JetAnalyzer* theJetAnalyzer;
    JetAnalyzer* theCHSFatJetAnalyzer;
    JetAnalyzer* theFatJetAnalyzer;
    GenAnalyzer* theGenAnalyzer;
    PileupAnalyzer* thePileupAnalyzer;
    TriggerAnalyzer* theTriggerAnalyzer;

    //int WriteNElectrons, WriteNMuons, WriteNLeptons, WriteNTaus, WriteNPhotons, WriteNFatJets;
    double MinGenBpt, MaxGenBeta;
    int WriteNJets, WriteNFatJets, WriteNGenBquarks, WriteNGenLongLiveds;

    std::vector<JetType> Jets;
    std::vector<JetType> MatchedJets;
    std::vector<JetType> MatchedCHSJets;
    std::vector<JetType> CHSJets;
    std::vector<JetType> MatchedPuppiJets;
    std::vector<JetType> PuppiJets;
    std::vector<CaloJetType> MatchedCaloJets;
    std::vector<CustomFatJetType> FatJets;
    std::vector<FatJetType> CHSFatJets;
    std::vector<GenPType> GenBquarks;
    std::vector<GenPType> GenLongLiveds;

    std::map<std::string, bool> TriggerMap;
    std::map<std::string, int> PrescalesTriggerMap;
    std::map<std::string, bool> MetFiltersMap;
    //bool BadPFMuonFlag, BadChCandFlag;
    

    TTree* tree;
    bool isVerbose, isVerboseTrigger;
    bool isMC;
    long int EventNumber, LumiNumber, RunNumber, nPV;
    //float muon1_pt, muon1_pfIso04, electron1_pt, fatjet1_pt, jet1_pt;
    //float met_pt, met_pt_nomu_L, met_pt_nomu_T, m_ht, m_ht_nomu_L, m_ht_nomu_T, min_met_mht, min_met_mht_nomu_L, min_met_mht_nomu_T, met_phi, met_phi_nomu_L, met_phi_nomu_T;
    //bool fatjet1_isLoose, fatjet1_isTight, muon1_isLoose, muon1_isTight;
    //long int nTightMuons, nTightElectrons, nTightFatJets, nLooseMuons, nLooseElectrons, nLooseFatJets;
  long int nLooseJets, nTightJets, nJets, nLooseCHSJets, nTightCHSJets, nCHSJets, nLooseFatJets, nTightFatJets, nFatJets, nLooseCHSFatJets, nTightCHSFatJets, nCHSFatJets, nGenBquarks, nGenLL, nMatchedJets, nMatchedCaloJets, nMatchedCHSJets, nCaloJets, nPuppiJets, nMatchedPuppiJets;
  long int nJets_bFlav, nJets_bHadronFlav, nJets_bPartonFlav, nCHSJets_bFlav, nCHSJets_bHadronFlav, nCHSJets_bPartonFlav, nFatJets_bFlav, nCHSFatJets_bFlav, nPuppiJets_bFlav, nPuppiJets_bHadronFlav, nPuppiJets_bPartonFlav;
    long int nJets_0bMatch, nJets_1bMatch, nJets_2bMatch, nJets_3bMatch, nJets_4bMatch;
    long int nJets_0piMatch, nJets_1piMatch, nJets_2piMatch;
    //long int nJets_match_pi1, nJets_match_pi2, nJets_match_b1, nJets_match_b2, nJets_match_b3, nJets_match_b4;
  long int nJets_piMother, nCHSJets_piMother, nPuppiJets_piMother, number_of_b_matched_to_Jets, number_of_b_matched_to_CHSJets, number_of_b_matched_to_CaloJets, number_of_b_matched_to_PuppiJets;
    float PUWeight;
    //bool   trig_bit_pfmet110_pfmht110;
    //bool   trig_bit_pfmet120_pfmht120;
    //bool   trig_bit_pfmet120_pfmht120_PFHT60;
    //bool   trig_bit_pfmet130_pfmht130;
    //bool   trig_bit_pfmet140_pfmht140;
    //bool   trig_bit_pfmetTypeOne110_pfmht110;
    //bool   trig_bit_pfmetTypeOne120_pfmht120;
    //bool   trig_bit_pfmetTypeOne120_pfmht120_PFHT60;
    //bool   trig_bit_pfmetTypeOne130_pfmht130;
    //bool   trig_bit_pfmetTypeOne140_pfmht140;
    //bool   trig_bit_pfmetnomu110_pfmhtnomu110;
    //bool   trig_bit_pfmetnomu120_pfmhtnomu120;
    //bool   trig_bit_pfmetnomu120_pfmhtnomu120_PFHT60;
    //bool   trig_bit_pfmetnomu130_pfmhtnomu130;
    //bool   trig_bit_pfmetnomu140_pfmhtnomu140;
    //bool   trig_bit_ele27_wptight_gsf;
    //bool   trig_bit_isomu24;
    //MET filters
    bool trig_bit_flag_HBHENoiseFilter;
    bool trig_bit_flag_HBHENoiseIsoFilter;
    bool trig_bit_flag_EcalDeadCellTriggerPrimitiveFilter;
    bool trig_bit_flag_goodVertices;
    bool trig_bit_flag_eeBadScFilter;
    bool trig_bit_flag_globalSuperTightHalo2016Filter;
    bool flag_BadChCand;
    bool flag_BadPFMuon;

  //TH1F* Index_q_match;

    //TH1F* Matching_to_b_AK4Jets;
    //TH1F* Matching_to_b_CHSAK4Jets;
    //TH1F* Matching_to_b_AK4Jets_simplified;
    //TH1F* Matching_to_b_CHSAK4Jets_simplified;

    //TH1F* Matching_to_pi_AK4Jets;
    //TH1F* Matching_to_pi_CHSAK4Jets;

    //TH1F* Matching_to_b_AK8Jets;
    //TH1F* Matching_to_b_CHSAK8Jets;
  //TH1F* Matching_to_b_AK8Jets_simplified;
  //TH1F* Matching_to_b_CHSAK8Jets_simplified;

    //TH1F* Matching_to_pi_AK8Jets;
    //TH1F* Matching_to_pi_CHSAK8Jets;

    //TH1F* Matching_to_b_AK8Jets_sj1;
    //TH1F* Matching_to_b_CHSAK8Jets_sj1;
    //TH1F* Matching_to_pi_AK8Jets_sj1;
    //TH1F* Matching_to_pi_CHSAK8Jets_sj1;
    //TH1F* Matching_to_b_AK8Jets_sj2;
    //TH1F* Matching_to_b_CHSAK8Jets_sj2;
    //TH1F* Matching_to_pi_AK8Jets_sj2;
    //TH1F* Matching_to_pi_CHSAK8Jets_sj2;

  //TH1F* CSV_AK4Jets_matched_to_0b;
  //TH1F* CSV_CHSAK4Jets_matched_to_0b;
  //TH1F* CSV_AK4Jets_matched_to_1b;
  //TH1F* CSV_CHSAK4Jets_matched_to_1b;
  //TH1F* CSV_AK4Jets_matched_to_2b;
  //TH1F* CSV_CHSAK4Jets_matched_to_2b;
  //TH1F* CSV_AK4Jets_matched_to_more_2b;
  //TH1F* CSV_CHSAK4Jets_matched_to_more_2b;

  //TH1F* CSV_AK4Jets_matched_to_0pi;
  //TH1F* CSV_CHSAK4Jets_matched_to_0pi;
  //TH1F* CSV_AK4Jets_matched_to_1pi;
  //TH1F* CSV_CHSAK4Jets_matched_to_1pi;
  //TH1F* CSV_AK4Jets_matched_to_2pi;
  //TH1F* CSV_CHSAK4Jets_matched_to_2pi;

  //TH1F* pT_AK4Jets_matched_to_0b;
  //TH1F* pT_CHSAK4Jets_matched_to_0b;
  //TH1F* pT_AK4Jets_matched_to_1b;
  //TH1F* pT_CHSAK4Jets_matched_to_1b;
  //TH1F* pT_AK4Jets_matched_to_2b;
  //TH1F* pT_CHSAK4Jets_matched_to_2b;
  //TH1F* pT_AK4Jets_matched_to_more_2b;
  //TH1F* pT_CHSAK4Jets_matched_to_more_2b;

  //TH1F* pT_AK4Jets_matched_to_0pi;
  //TH1F* pT_CHSAK4Jets_matched_to_0pi;
  //TH1F* pT_AK4Jets_matched_to_1pi;
  //TH1F* pT_CHSAK4Jets_matched_to_1pi;
  //TH1F* pT_AK4Jets_matched_to_2pi;
  //TH1F* pT_CHSAK4Jets_matched_to_2pi;
};


//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
//RecoStudiesCalo::RecoStudiesCalo(const edm::ParameterSet& iConfig, edm::ConsumesCollector&& CColl):
RecoStudiesCalo::RecoStudiesCalo(const edm::ParameterSet& iConfig):
    GenPSet(iConfig.getParameter<edm::ParameterSet>("genSet")),
    PileupPSet(iConfig.getParameter<edm::ParameterSet>("pileupSet")),
    TriggerPSet(iConfig.getParameter<edm::ParameterSet>("triggerSet")),
    CHSJetPSet(iConfig.getParameter<edm::ParameterSet>("chsJetSet")),
    PuppiJetPSet(iConfig.getParameter<edm::ParameterSet>("puppiJetSet")),
    JetPSet(iConfig.getParameter<edm::ParameterSet>("jetSet")),
    CHSFatJetPSet(iConfig.getParameter<edm::ParameterSet>("chsFatJetSet")),
    FatJetPSet(iConfig.getParameter<edm::ParameterSet>("fatJetSet")),
    MinGenBpt(iConfig.getParameter<double>("minGenBpt")),
    MaxGenBeta(iConfig.getParameter<double>("maxGenBeta")),
    WriteNJets(iConfig.getParameter<int>("writeNJets")),
    WriteNFatJets(iConfig.getParameter<int>("writeNFatJets")),
    WriteNGenBquarks(iConfig.getParameter<int>("writeNGenBquarks")),
    WriteNGenLongLiveds(iConfig.getParameter<int>("writeNGenLongLiveds")),
    isVerbose(iConfig.getParameter<bool> ("verbose")),
    isVerboseTrigger(iConfig.getParameter<bool> ("verboseTrigger"))

{
    //Initalize objects
    theCHSJetAnalyzer      = new JetAnalyzer(CHSJetPSet, consumesCollector());
    thePuppiJetAnalyzer      = new JetAnalyzer(PuppiJetPSet, consumesCollector());
    theJetAnalyzer      = new JetAnalyzer(JetPSet, consumesCollector());
    theCHSFatJetAnalyzer      = new JetAnalyzer(CHSFatJetPSet, consumesCollector());
    theFatJetAnalyzer      = new JetAnalyzer(FatJetPSet, consumesCollector());
    theGenAnalyzer      = new GenAnalyzer(GenPSet, consumesCollector());
    thePileupAnalyzer   = new PileupAnalyzer(PileupPSet, consumesCollector());
    theTriggerAnalyzer  = new TriggerAnalyzer(TriggerPSet, consumesCollector());

    std::vector<std::string> TriggerList(TriggerPSet.getParameter<std::vector<std::string> >("paths"));
    for(unsigned int i = 0; i < TriggerList.size(); i++) TriggerMap[ TriggerList[i] ] = false;
    for(unsigned int i = 0; i < TriggerList.size(); i++) PrescalesTriggerMap[ TriggerList[i] ] = -1;
    std::vector<std::string> MetFiltersList(TriggerPSet.getParameter<std::vector<std::string> >("metpaths"));
    for(unsigned int i = 0; i < MetFiltersList.size(); i++) MetFiltersMap[ MetFiltersList[i] ] = false;

    //Input tags
    edm::InputTag IT_trigResults = edm::InputTag("TriggerResults::HLT");
    trigResultsToken= consumes<edm::TriggerResults>(IT_trigResults);
    edm::InputTag IT_filterResults = edm::InputTag("TriggerResults::RECO");
    filterResultsToken= consumes<edm::TriggerResults>(IT_filterResults);

    edm::InputTag IT_badChCandFilter = edm::InputTag("BadChargedCandidateFilter");
    badChCandFilterToken= consumes<bool>(IT_badChCandFilter);
    edm::InputTag IT_badPFMuonFilter = edm::InputTag("BadPFMuonFilter");
    badPFMuonFilterToken= consumes<bool>(IT_badPFMuonFilter);

    edm::InputTag IT_genJetToken = edm::InputTag("slimmedGenJets");//Lisa
    genJetToken= consumes<reco::GenJetCollection>(IT_genJetToken);//Lisa

    edm::InputTag IT_caloJets = edm::InputTag("ak4CaloJets");
    caloJetToken = consumes<reco::CaloJetCollection>(IT_caloJets);

    if(isVerbose) std::cout << "CONSTRUCTOR" << std::endl;
    if(isVerbose) std::cout << "ONLY EVENTS WITH 4 GEN B QUARKS IN ACCEPTANCE!!!!!!!!" << std::endl;

    //now do what ever initialization is needed
    usesResource("TFileService");

    edm::Service<TFileService> fs;

    //Tree branches
    tree = fs->make<TTree>("tree", "tree");
    tree -> Branch("isMC" , &isMC, "isMC/O");
    tree -> Branch("EventNumber" , &EventNumber , "EventNumber/L");
    tree -> Branch("LumiNumber" , &LumiNumber , "LumiNumber/L");
    tree -> Branch("RunNumber" , &RunNumber , "RunNumber/L");
    tree -> Branch("nPV" , &nPV , "nPV/L");
    tree -> Branch("PUWeight", &PUWeight, "PUWeight/F");
    //tree -> Branch("nLooseMuons" , &nLooseMuons , "nLooseMuons/L");
    //tree -> Branch("nLooseElectrons" , &nLooseElectrons , "nLooseElectrons/L");
    //tree -> Branch("nLooseFatJets" , &nLooseFatJets , "nLooseFatJets/L");
    tree -> Branch("nGenBquarks" , &nGenBquarks , "nGenBquarks/L");
    tree -> Branch("nGenLL" , &nGenLL , "nGenLL/L");
    tree -> Branch("nJets" , &nJets , "nJets/L");
    tree -> Branch("nCaloJets" , &nCaloJets , "nCaloJets/L");
    tree -> Branch("nMatchedJets" , &nMatchedJets , "nMatchedJets/L");
    tree -> Branch("nMatchedCaloJets" , &nMatchedCaloJets , "nMatchedCaloJets/L");
    tree -> Branch("nMatchedCHSJets" , &nMatchedCHSJets , "nMatchedCHSJets/L");
    tree -> Branch("nMatchedPuppiJets" , &nMatchedPuppiJets , "nMatchedPuppiJets/L");
    tree -> Branch("nPuppiJets" , &nPuppiJets , "nPuppiJets/L");
    tree -> Branch("nJets_bFlav" , &nJets_bFlav , "nJets_bFlav/L");
    tree -> Branch("nJets_bHadronFlav" , &nJets_bHadronFlav , "nJets_bHadronFlav/L");
    tree -> Branch("nJets_bPartonFlav" , &nJets_bPartonFlav , "nJets_bPartonFlav/L");
    tree -> Branch("nJets_piMother", &nJets_piMother, "nJets_piMother/L");
    tree -> Branch("number_of_b_matched_to_Jets", &number_of_b_matched_to_Jets, "number_of_b_matched_to_Jets/L");
    tree -> Branch("number_of_b_matched_to_CaloJets", &number_of_b_matched_to_CaloJets, "number_of_b_matched_to_CaloJets/L");
    tree -> Branch("number_of_b_matched_to_CHSJets", &number_of_b_matched_to_CHSJets, "number_of_b_matched_to_CHSJets/L");
    tree -> Branch("number_of_b_matched_to_PuppiJets", &number_of_b_matched_to_PuppiJets, "number_of_b_matched_to_PuppiJets/L");
    tree -> Branch("nCHSJets_bFlav" , &nCHSJets_bFlav , "nCHSJets_bFlav/L");
    tree -> Branch("nCHSJets_bHadronFlav" , &nCHSJets_bHadronFlav , "nCHSJets_bHadronFlav/L");
    tree -> Branch("nCHSJets_bPartonFlav" , &nCHSJets_bPartonFlav , "nCHSJets_bPartonFlav/L");
    tree -> Branch("nCHSJets_piMother", &nCHSJets_piMother, "nCHSJets_piMother/L");
    tree -> Branch("nPuppiJets_bFlav" , &nPuppiJets_bFlav , "nPuppiJets_bFlav/L");
    tree -> Branch("nPuppiJets_bHadronFlav" , &nPuppiJets_bHadronFlav , "nPuppiJets_bHadronFlav/L");
    tree -> Branch("nPuppiJets_bPartonFlav" , &nPuppiJets_bPartonFlav , "nPuppiJets_bPartonFlav/L");
    tree -> Branch("nPuppiJets_piMother", &nPuppiJets_piMother, "nPuppiJets_piMother/L");

    tree -> Branch("nFatJets_bFlav" , &nFatJets_bFlav , "nFatJets_bFlav/L");
    tree -> Branch("nCHSFatJets_bFlav" , &nCHSFatJets_bFlav , "nCHSFatJets_bFlav/L");
    //tree -> Branch("nJets_match_pi1" , &nJets_match_pi1, "nJets_match_pi1/L");
    //tree -> Branch("nJets_match_pi2" , &nJets_match_pi2, "nJets_match_pi2/L");
    //tree -> Branch("nJets_match_b1" , &nJets_match_b1, "nJets_match_b1/L");
    //tree -> Branch("nJets_match_b2" , &nJets_match_b2, "nJets_match_b2/L");
    //tree -> Branch("nJets_match_b3" , &nJets_match_b3, "nJets_match_b3/L");
    //tree -> Branch("nJets_match_b4" , &nJets_match_b4, "nJets_match_b4/L");
    tree -> Branch("nJets_0bMatch" , &nJets_0bMatch , "nJets_0bMatch/L");
    tree -> Branch("nJets_1bMatch" , &nJets_1bMatch , "nJets_1bMatch/L");
    tree -> Branch("nJets_2bMatch" , &nJets_2bMatch , "nJets_2bMatch/L");
    tree -> Branch("nJets_3bMatch" , &nJets_3bMatch , "nJets_3bMatch/L");
    tree -> Branch("nJets_4bMatch" , &nJets_4bMatch , "nJets_4bMatch/L");
    tree -> Branch("nJets_0piMatch" , &nJets_0piMatch , "nJets_0piMatch/L");
    tree -> Branch("nJets_1piMatch" , &nJets_1piMatch , "nJets_1piMatch/L");
    tree -> Branch("nJets_2piMatch" , &nJets_2piMatch , "nJets_2piMatch/L");
    //    tree -> Branch("index_q_match", &index_q_match, "index_q_match/L";
    tree -> Branch("nLooseJets" , &nLooseJets , "nLooseJets/L");
    tree -> Branch("nTightJets" , &nTightJets , "nTightJets/L");
    tree -> Branch("nCHSJets" , &nCHSJets , "nCHSJets/L");
    tree -> Branch("nLooseCHSJets" , &nLooseCHSJets , "nLooseCHSJets/L");
    tree -> Branch("nTightCHSJets" , &nTightCHSJets , "nTightCHSJets/L");
    tree -> Branch("nFatJets" , &nFatJets , "nFatJets/L");
    tree -> Branch("nLooseFatJets" , &nLooseFatJets , "nLooseFatJets/L");
    tree -> Branch("nTightFatJets" , &nTightFatJets , "nTightFatJets/L");
    tree -> Branch("nCHSFatJets" , &nCHSFatJets , "nCHSFatJets/L");
    tree -> Branch("nLooseCHSFatJets" , &nLooseCHSFatJets , "nLooseCHSFatJets/L");
    tree -> Branch("nTightCHSFatJets" , &nTightCHSFatJets , "nTightCHSFatJets/L");
    tree -> Branch("Flag_HBHENoiseFilter", &trig_bit_flag_HBHENoiseFilter, "Flag_HBHENoiseFilter/B");
    tree -> Branch("Flag_HBHENoiseIsoFilter", &trig_bit_flag_HBHENoiseIsoFilter, "Flag_HBHENoiseIsoFilter/B");
    tree -> Branch("Flag_EcalDeadCellTriggerPrimitiveFilter", &trig_bit_flag_EcalDeadCellTriggerPrimitiveFilter, "Flag_EcalDeadCellTriggerPrimitiveFilter/B");
    tree -> Branch("Flag_goodVertices", &trig_bit_flag_goodVertices, "Flag_goodVertices/B");
    tree -> Branch("Flag_eeBadScFilter", &trig_bit_flag_eeBadScFilter, "Flag_eeBadScFilter/B");
    tree -> Branch("Flag_globalSuperTightHalo2016Filter", &trig_bit_flag_globalSuperTightHalo2016Filter, "Flag_globalSuperTightHalo2016Filter/B");
    tree -> Branch("Flag_BadChCand", &flag_BadChCand, "Flag_BadChCand/B");
    tree -> Branch("Flag_BadPFMuon", &flag_BadPFMuon, "Flag_BadPFMuon/B");

    // Set trigger branches
    for(auto it = TriggerMap.begin(); it != TriggerMap.end(); it++) tree->Branch(it->first.c_str(), &(it->second), (it->first+"/O").c_str());
    if(isVerboseTrigger)//save PS values in ntuple
        { 
  	    for(auto it = PrescalesTriggerMap.begin(); it != PrescalesTriggerMap.end(); it++) {
	        tree->Branch( ("PS_" + it->first).c_str(), &(it->second), ("PS_" + it->first+"/I").c_str());
	    }
        }
    for(auto it = MetFiltersMap.begin(); it != MetFiltersMap.end(); it++) tree->Branch(it->first.c_str(), &(it->second), (it->first+"/O").c_str());
    //tree->Branch("Flag_BadPFMuon", &BadPFMuonFlag, "Flag_BadPFMuon/O");
    //tree->Branch("Flag_BadChCand", &BadChCandFlag, "Flag_BadChCand/O");

    //Histograms
    //Index_q_match= fs->make<TH1F>("Index_q_match", "Index_q_match", 5,0,5);
    //Matching_to_b_AK4Jets = fs->make<TH1F>("Matching_to_b_AK4Jets", "Matching_to_b_AK4Jets", 10,0,10);
    //Matching_to_b_CHSAK4Jets = fs->make<TH1F>("Matching_to_b_CHSAK4Jets", "Matching_to_b_CHSAK4Jets", 10,0,10);
    //Matching_to_b_AK4Jets_simplified = fs->make<TH1F>("Matching_to_b_AK4Jets_simplified", "Matching_to_b_AK4Jets_simplified", 4,0,4);
    //Matching_to_b_CHSAK4Jets_simplified = fs->make<TH1F>("Matching_to_b_CHSAK4Jets_simplified", "Matching_to_b_CHSAK4Jets_simplified", 4,0,4);
    //Matching_to_pi_AK4Jets = fs->make<TH1F>("Matching_to_pi_AK4Jets", "Matching_to_pi_AK4Jets", 10,0,10);
    //Matching_to_pi_CHSAK4Jets = fs->make<TH1F>("Matching_to_pi_CHSAK4Jets", "Matching_to_pi_CHSAK4Jets", 10,0,10);

    //Matching_to_b_AK8Jets = fs->make<TH1F>("Matching_to_b_AK8Jets", "Matching_to_b_AK8Jets", 10,0,10);
    //Matching_to_b_CHSAK8Jets = fs->make<TH1F>("Matching_to_b_CHSAK8Jets", "Matching_to_b_CHSAK8Jets", 10,0,10);
    //Matching_to_b_AK8Jets_simplified = fs->make<TH1F>("Matching_to_b_AK8Jets_simplified", "Matching_to_b_AK8Jets_simplified", 4,0,4);
    //Matching_to_b_CHSAK8Jets_simplified = fs->make<TH1F>("Matching_to_b_CHSAK8Jets_simplified", "Matching_to_b_CHSAK8Jets_simplified", 4,0,4);
    //Matching_to_pi_AK8Jets = fs->make<TH1F>("Matching_to_pi_AK8Jets", "Matching_to_pi_AK8Jets", 10,0,10);
    //Matching_to_pi_CHSAK8Jets = fs->make<TH1F>("Matching_to_pi_CHSAK8Jets", "Matching_to_pi_CHSAK8Jets", 10,0,10);

    //Matching_to_b_AK8Jets_sj1 = fs->make<TH1F>("Matching_to_b_AK8Jets_sj1", "Matching_to_b_AK8Jets_sj1", 10,0,10);
    //Matching_to_b_CHSAK8Jets_sj1 = fs->make<TH1F>("Matching_to_b_CHSAK8Jets_sj1", "Matching_to_b_CHSAK8Jets_sj1", 10,0,10);
    //Matching_to_pi_AK8Jets_sj1 = fs->make<TH1F>("Matching_to_pi_AK8Jets_sj1", "Matching_to_pi_AK8Jets_sj1", 10,0,10);
    //Matching_to_pi_CHSAK8Jets_sj1 = fs->make<TH1F>("Matching_to_pi_CHSAK8Jets_sj1", "Matching_to_pi_CHSAK8Jets_sj1", 10,0,10);
    //Matching_to_b_AK8Jets_sj2 = fs->make<TH1F>("Matching_to_b_AK8Jets_sj2", "Matching_to_b_AK8Jets_sj2", 10,0,10);
    //Matching_to_b_CHSAK8Jets_sj2 = fs->make<TH1F>("Matching_to_b_CHSAK8Jets_sj2", "Matching_to_b_CHSAK8Jets_sj2", 10,0,10);
    //Matching_to_pi_AK8Jets_sj2 = fs->make<TH1F>("Matching_to_pi_AK8Jets_sj2", "Matching_to_pi_AK8Jets_sj2", 10,0,10);
    //Matching_to_pi_CHSAK8Jets_sj2 = fs->make<TH1F>("Matching_to_pi_CHSAK8Jets_sj2", "Matching_to_pi_CHSAK8Jets_sj2", 10,0,10);

    //CSV_AK4Jets_matched_to_0b = fs->make<TH1F>("CSV_AK4Jets_matched_to_0b", "CSV_AK4Jets_matched_to_0b", 50,0,1);
    //CSV_CHSAK4Jets_matched_to_0b = fs->make<TH1F>("CSV_CHSAK4Jets_matched_to_0b", "CSV_CHSAK4Jets_matched_to_0b", 50,0,1);
    //CSV_AK4Jets_matched_to_1b = fs->make<TH1F>("CSV_AK4Jets_matched_to_1b", "CSV_AK4Jets_matched_to_1b", 50,0,1);
    //CSV_CHSAK4Jets_matched_to_1b = fs->make<TH1F>("CSV_CHSAK4Jets_matched_to_1b", "CSV_CHSAK4Jets_matched_to_1b", 50,0,1);
    //CSV_AK4Jets_matched_to_2b = fs->make<TH1F>("CSV_AK4Jets_matched_to_2b", "CSV_AK4Jets_matched_to_2b", 50,0,1);
    //CSV_CHSAK4Jets_matched_to_2b = fs->make<TH1F>("CSV_CHSAK4Jets_matched_to_2b", "CSV_CHSAK4Jets_matched_to_2b", 50,0,1);
    //CSV_AK4Jets_matched_to_more_2b = fs->make<TH1F>("CSV_AK4Jets_matched_to_more_2b", "CSV_AK4Jets_matched_to_more_2b", 50,0,1);
    //CSV_CHSAK4Jets_matched_to_more_2b = fs->make<TH1F>("CSV_CHSAK4Jets_matched_to_more_2b", "CSV_CHSAK4Jets_matched_to_more_2b", 50,0,1);

    //CSV_AK4Jets_matched_to_0pi = fs->make<TH1F>("CSV_AK4Jets_matched_to_0pi", "CSV_AK4Jets_matched_to_0pi", 50,0,1);
    //CSV_CHSAK4Jets_matched_to_0pi = fs->make<TH1F>("CSV_CHSAK4Jets_matched_to_0pi", "CSV_CHSAK4Jets_matched_to_0pi", 50,0,1);
    //CSV_AK4Jets_matched_to_1pi = fs->make<TH1F>("CSV_AK4Jets_matched_to_1pi", "CSV_AK4Jets_matched_to_1pi", 50,0,1);
    //CSV_CHSAK4Jets_matched_to_1pi = fs->make<TH1F>("CSV_CHSAK4Jets_matched_to_1pi", "CSV_CHSAK4Jets_matched_to_1pi", 50,0,1);
    //CSV_AK4Jets_matched_to_2pi = fs->make<TH1F>("CSV_AK4Jets_matched_to_2pi", "CSV_AK4Jets_matched_to_2pi", 50,0,1);
    //CSV_CHSAK4Jets_matched_to_2pi = fs->make<TH1F>("CSV_CHSAK4Jets_matched_to_2pi", "CSV_CHSAK4Jets_matched_to_2pi", 50,0,1);

    //pT_AK4Jets_matched_to_0b = fs->make<TH1F>("pT_AK4Jets_matched_to_0b", "pT_AK4Jets_matched_to_0b", 100,0,1000);
    //pT_CHSAK4Jets_matched_to_0b = fs->make<TH1F>("pT_CHSAK4Jets_matched_to_0b", "pT_CHSAK4Jets_matched_to_0b", 100,0,1000);
    //pT_AK4Jets_matched_to_1b = fs->make<TH1F>("pT_AK4Jets_matched_to_1b", "pT_AK4Jets_matched_to_1b", 100,0,1000);
    //pT_CHSAK4Jets_matched_to_1b = fs->make<TH1F>("pT_CHSAK4Jets_matched_to_1b", "pT_CHSAK4Jets_matched_to_1b", 100,0,1000);
    //pT_AK4Jets_matched_to_2b = fs->make<TH1F>("pT_AK4Jets_matched_to_2b", "pT_AK4Jets_matched_to_2b", 100,0,1000);
    //pT_CHSAK4Jets_matched_to_2b = fs->make<TH1F>("pT_CHSAK4Jets_matched_to_2b", "pT_CHSAK4Jets_matched_to_2b", 100,0,1000);
    //pT_AK4Jets_matched_to_more_2b = fs->make<TH1F>("pT_AK4Jets_matched_to_more_2b", "pT_AK4Jets_matched_to_more_2b", 100,0,1000);
    //pT_CHSAK4Jets_matched_to_more_2b = fs->make<TH1F>("pT_CHSAK4Jets_matched_to_more_2b", "pT_CHSAK4Jets_matched_to_more_2b", 100,0,1000);

    //pT_AK4Jets_matched_to_0pi = fs->make<TH1F>("pT_AK4Jets_matched_to_0pi", "pT_AK4Jets_matched_to_0pi", 100,0,1000);
    //pT_CHSAK4Jets_matched_to_0pi = fs->make<TH1F>("pT_CHSAK4Jets_matched_to_0pi", "pT_CHSAK4Jets_matched_to_0pi", 100,0,1000);
    //pT_AK4Jets_matched_to_1pi = fs->make<TH1F>("pT_AK4Jets_matched_to_1pi", "pT_AK4Jets_matched_to_1pi", 100,0,1000);
    //pT_CHSAK4Jets_matched_to_1pi = fs->make<TH1F>("pT_CHSAK4Jets_matched_to_1pi", "pT_CHSAK4Jets_matched_to_1pi", 100,0,1000);
    //pT_AK4Jets_matched_to_2pi = fs->make<TH1F>("pT_AK4Jets_matched_to_2pi", "pT_AK4Jets_matched_to_2pi", 100,0,1000);
    //pT_CHSAK4Jets_matched_to_2pi = fs->make<TH1F>("pT_CHSAK4Jets_matched_to_2pi", "pT_CHSAK4Jets_matched_to_2pi", 100,0,1000);
    

    if(isVerbose) std::cout << "---------- STARTING ----------" << std::endl;

}


RecoStudiesCalo::~RecoStudiesCalo()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
    if(isVerbose) std::cout << "---------- ENDING  ----------" << std::endl;

    delete theCHSJetAnalyzer;
    delete thePuppiJetAnalyzer;
    delete theJetAnalyzer;
    delete theCHSFatJetAnalyzer;
    delete theFatJetAnalyzer;
    delete theGenAnalyzer;
    delete thePileupAnalyzer;
    delete theTriggerAnalyzer;
}


//
// member functions
//

// ------------ method called for each event  ------------
void
RecoStudiesCalo::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;
    using namespace reco;
    using namespace std;

    // Initialize types
    for(int i = 0; i < WriteNJets; i++) ObjectsFormat::ResetJetType(Jets[i]);
    for(int i = 0; i < 4; i++) ObjectsFormat::ResetJetType(MatchedJets[i]);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    for(int i = 0; i < 4; i++) ObjectsFormat::ResetJetType(MatchedCHSJets[i]);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    for(int i = 0; i < 4; i++) ObjectsFormat::ResetJetType(MatchedPuppiJets[i]);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    for(int i = 0; i < 4; i++) ObjectsFormat::ResetCaloJetType(MatchedCaloJets[i]);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    for(int i = 0; i < WriteNJets; i++) ObjectsFormat::ResetJetType(CHSJets[i]);//!!
    for(int i = 0; i < WriteNJets; i++) ObjectsFormat::ResetJetType(PuppiJets[i]);//!!
    for(int i = 0; i < WriteNFatJets; i++) ObjectsFormat::ResetCustomFatJetType(FatJets[i]);//??
    for(int i = 0; i < WriteNFatJets; i++) ObjectsFormat::ResetFatJetType(CHSFatJets[i]);//??
    for(int i = 0; i < WriteNGenBquarks; i++) ObjectsFormat::ResetGenPType(GenBquarks[i]);
    for(int i = 0; i < WriteNGenLongLiveds; i++) ObjectsFormat::ResetGenPType(GenLongLiveds[i]);

    isMC = false;
    EventNumber = LumiNumber = RunNumber = nPV = 0;
    nJets = nLooseJets = nTightJets = nCHSJets = nLooseCHSJets = nTightCHSJets = nFatJets = nLooseFatJets = nTightFatJets = nCHSFatJets = nLooseCHSFatJets = nTightCHSFatJets = nGenBquarks = nGenLL = nPV = nMatchedJets = nMatchedCaloJets = nMatchedCHSJets = nCaloJets = nPuppiJets = nMatchedPuppiJets =0;
    nJets_bFlav = nJets_bHadronFlav = nJets_bPartonFlav= nJets_piMother = nCHSJets_bFlav = nCHSJets_bHadronFlav = nCHSJets_bPartonFlav= nCHSJets_piMother = nPuppiJets_bFlav = nPuppiJets_bHadronFlav = nPuppiJets_bPartonFlav= nPuppiJets_piMother = nFatJets_bFlav = nCHSFatJets_bFlav = number_of_b_matched_to_Jets = number_of_b_matched_to_CaloJets = number_of_b_matched_to_CHSJets = number_of_b_matched_to_PuppiJets = 0;
    nJets_0bMatch = nJets_1bMatch = nJets_2bMatch = nJets_3bMatch = nJets_4bMatch = 0;
    nJets_0piMatch = nJets_1piMatch = nJets_2piMatch = 0;
    //nJets_match_pi1 = nJets_match_pi2 = nJets_match_b1 = nJets_match_b2 = nJets_match_b3 = nJets_match_b4 = 0;
    //index_q_match = -1;

    PUWeight = 1.;
    //MinGenBpt = -1.;
    //MaxGenBeta = -9.;

    // Trigger
    theTriggerAnalyzer->FillTriggerMap(iEvent, TriggerMap, PrescalesTriggerMap, isVerboseTrigger);
    theTriggerAnalyzer->FillMetFiltersMap(iEvent, MetFiltersMap);
    //BadPFMuonFlag = theTriggerAnalyzer->GetBadPFMuonFlag(iEvent);
    //BadChCandFlag = theTriggerAnalyzer->GetBadChCandFlag(iEvent);
    
    //MET filters
    edm::Handle<edm::TriggerResults> filterResults; 
    iEvent.getByToken(filterResultsToken, filterResults);

    if( !filterResults.failedToGet() ) { 
        int N_Filters = filterResults->size();
        const edm::TriggerNames & filterName = iEvent.triggerNames(*filterResults);

        for( int i_Trig = 0; i_Trig < N_Filters; ++i_Trig ) { 
	    if (filterResults.product()->accept(i_Trig)) {
	        TString TrigPath =filterName.triggerName(i_Trig);

	        if ( TrigPath.Contains("Flag_HBHENoiseFilter") ) trig_bit_flag_HBHENoiseFilter = true;
	        if ( TrigPath.Contains("Flag_HBHENoiseIsoFilter") ) trig_bit_flag_HBHENoiseIsoFilter = true;
	        if ( TrigPath.Contains("Flag_EcalDeadCellTriggerPrimitiveFilter") ) trig_bit_flag_EcalDeadCellTriggerPrimitiveFilter = true;
	        if ( TrigPath.Contains("Flag_goodVertices") ) trig_bit_flag_goodVertices = true;
	        if ( TrigPath.Contains("Flag_eeBadScFilter") ) trig_bit_flag_eeBadScFilter = true;
	        if ( TrigPath.Contains("Flag_globalSuperTightHalo2016Filter") ) trig_bit_flag_globalSuperTightHalo2016Filter = true;
	    }
        }
    }

    //BadChCand and BadPFMuon filters
    edm::Handle<bool> filterBadChCand; 
    iEvent.getByToken(badChCandFilterToken, filterBadChCand);
    flag_BadChCand = *filterBadChCand;

    edm::Handle<bool> filterBadPFMuon; 
    iEvent.getByToken(badPFMuonFilterToken, filterBadPFMuon);
    flag_BadPFMuon = *filterBadPFMuon;
    

    //Event info
    isMC = !iEvent.isRealData();
    EventNumber = iEvent.id().event();
    LumiNumber = iEvent.luminosityBlock();
    RunNumber = iEvent.id().run();


    // Gen particles
    std::vector<reco::GenParticle> GenLongLivedVect = theGenAnalyzer->FillGenVectorByIdAndStatus(iEvent,9000006,22);
    nGenLL = GenLongLivedVect.size();
    std::vector<reco::GenParticle> GenBquarksVect;
    if(nGenLL>0)
      {
	//GenBquarksVect = theGenAnalyzer->FillGenVectorByIdStatusAndMother(iEvent,5,23,9000006);
	GenBquarksVect = theGenAnalyzer->FillGenVectorByIdStatusAndMotherAndKin(iEvent,5,23,9000006,float(MinGenBpt),float(MaxGenBeta));
      }
    else
      {
	//GenBquarksVect = theGenAnalyzer->FillGenVectorByIdAndStatus(iEvent,5,23);
	GenBquarksVect = theGenAnalyzer->FillGenVectorByIdAndStatusAndKin(iEvent,5,23,float(MinGenBpt),float(MaxGenBeta));
      }
    //std::vector<reco::GenParticle> GenBquarksVect = theGenAnalyzer->FillGenVectorByIdAndStatus(iEvent,5,23);
    nGenBquarks = GenBquarksVect.size();
    //std::vector<reco::GenParticle> GenBquarksFromLLVect = theGenAnalyzer->FillGenVectorByIdStatusAndMother(iEvent,5,23,9000006);

    
    if(nGenBquarks<4)
      {
	GenBquarksVect.clear();
	GenLongLivedVect.clear();
	return; //First step: only full reconstruction!
      }
    

    //right now: if LL, remove quarks not coming from LL particle
    /*
    if(nGenBquarks>4 && nGenLL>0) {
          std::cout << "more than 4 b quarks: " << nGenBquarks << std::endl;
	  for(unsigned int q = 0; q<GenBquarksVect.size(); q++) {
	      std::cout << "quark n. " << q << std::endl;
	      std::cout << "mother id: " << GenBquarksVect[q].mother()->pdgId() << std::endl;
	      std::cout << "quark pt: " << GenBquarksVect[q].pt() << std::endl;
	      //std::cout << "is last copy? " << GenBquarksVect[q].isLastCopy() << std::endl;
	      //if( fabs(GenBquarksVect[q].mother()->pdgId())!= 9000006 ) GenBquarksVect.erase(GenBquarksVect.begin() + q);
	    }

	  //for(unsigned int w = 0; w<GenBquarksFromLLVect.size(); w++) {
	  //std::cout << "BBB quark n. " << w << std::endl;
	  //std::cout << "BBB quark pt: " << GenBquarksFromLLVect[w].pt() << std::endl;
	  //}
    }
    */
    //nGenBquarks = GenBquarksVect.size();
    //std::cout << "nGenB quark " << nGenBquarks << std::endl;
    //std::cout << "nGenB quark from LL only " << GenBquarksFromLLVect.size() << std::endl;

    // Pu weight
    PUWeight     = thePileupAnalyzer->GetPUWeight(iEvent);
    ////PUWeightUp   = thePileupAnalyzer->GetPUWeightUp(iEvent);
    ////PUWeightDown = thePileupAnalyzer->GetPUWeightDown(iEvent);
    nPV = thePileupAnalyzer->GetPV(iEvent);

    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------
    // AK4 Jets
    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------
    std::vector<pat::Jet> JetsVect = theJetAnalyzer->FillJetVector(iEvent);
    nJets = JetsVect.size();
    std::vector<pat::Jet> MatchedJetsVect;

    for(unsigned int a = 0; a<JetsVect.size(); a++) {
      /*
      //**Checks performed for studying genjets**
        if(isVerbose && JetsVect.size()>0) {
	  std::cout << "AK4 Jet n. " << a << " and gen jets:" << std::endl;
	  std::cout << "jet hadron flavour: " << JetsVect[a].hadronFlavour() << std::endl;
	  std::cout << "jet parton flavour: " << JetsVect[a].partonFlavour() << std::endl;
	  if(JetsVect[a].genJet()) 
	    {
	      std::cout << "gen jet pt" << std::endl;
	      std::cout << JetsVect[a].genJet()->pt() << std::endl;
	      //std::cout << JetsVect[a].genJet()->numberOfDaughters() << std::endl;
	    }
	  if(JetsVect[a].genParton()) 
	    {
	      std::cout << "gen parton pt and pdgid pt" << std::endl;
	      std::cout << JetsVect[a].genParton()->pt() << std::endl;
	      std::cout << JetsVect[a].genParton()->pdgId() << std::endl;
	    }

	}*/
	if(fabs(JetsVect[a].hadronFlavour())==5 || fabs(JetsVect[a].partonFlavour())==5) nJets_bFlav++;
	if(fabs(JetsVect[a].hadronFlavour())==5) nJets_bHadronFlav++;
	if(JetsVect[a].genParton() && fabs(JetsVect[a].partonFlavour())==5) nJets_bPartonFlav++;
	if(JetsVect[a].genParton() && abs(Utilities::FindMotherId(JetsVect[a].genParton()))==9000006) nJets_piMother++;
        if(JetsVect[a].hasUserInt("isLoose") && JetsVect[a].userInt("isLoose")>0) nLooseJets++;
        if(JetsVect[a].hasUserInt("isTight") && JetsVect[a].userInt("isTight")>0) nTightJets++;

	
	//Matching to b quarks of AK4Jets
	//Starting point: AK4 jets
	//Only define matching for jets fulfilling all the properties
	int n_b_matched_to_Jets = 0;
	for(unsigned int b = 0; b<GenBquarksVect.size(); b++) {
  	    if(fabs(reco::deltaR(JetsVect[a].eta(),JetsVect[a].phi(),GenBquarksVect[b].eta(),GenBquarksVect[b].phi()))<0.4 && JetsVect[a].genParton() && (fabs(JetsVect[a].hadronFlavour())==5 || fabs(JetsVect[a].partonFlavour())==5) && abs( Utilities::FindMotherId(JetsVect[a].genParton()) )==9000006) 
	      {
		n_b_matched_to_Jets++;
		//Index_q_match->Fill(b+1);
		//if(b==0) nJets_match_b1++; 
		//else if(b==1) nJets_match_b2++; 
		//else if(b==2) nJets_match_b3++; 
		//else if(b==3) nJets_match_b4++; 
	      }
	}
	JetsVect[a].addUserInt("hasMatchedBquarks",n_b_matched_to_Jets);
	//Matching_to_b_AK4Jets->Fill(n_b_matched_to_Jets);

	if(n_b_matched_to_Jets==0)
	  {
	    //Matching_to_b_AK4Jets_simplified->Fill(0);
	    nJets_0bMatch++;
	  }
	else if(n_b_matched_to_Jets==1)
	  {
	    //Matching_to_b_AK4Jets_simplified->Fill(1);
	    nJets_1bMatch++;
	  }
	else if(n_b_matched_to_Jets==2)
	  {
	    //Matching_to_b_AK4Jets_simplified->Fill(2);
	    nJets_2bMatch++;
	  }
	else if(n_b_matched_to_Jets==3)
	  {
	    //Matching_to_b_AK4Jets_simplified->Fill(3);
	    nJets_3bMatch++;
	  }
	else
	  {
	    //Matching_to_b_AK4Jets_simplified->Fill(3);
	    nJets_4bMatch++;
	  }

	/*
	//Matching to dark pions of AK4Jets
	//Starting point: AK4 jets
	int n_pi_matched = 0;
	for(unsigned int pi = 0; pi<GenLongLivedVect.size(); pi++) {
  	    if(fabs(reco::deltaR(JetsVect[a].eta(),JetsVect[a].phi(),GenLongLivedVect[pi].eta(),GenLongLivedVect[pi].phi()))<0.4 && JetsVect[a].genParton() && (fabs(JetsVect[a].hadronFlavour())==5 || fabs(JetsVect[a].partonFlavour())==5) && abs( Utilities::FindMotherId(JetsVect[a].genParton()) )==9000006) 
	      {
		n_pi_matched++;
		if(pi==0) nJets_match_pi1++; 
		else if(pi==1) nJets_match_pi2++; 
	      }
	}
	JetsVect[a].addUserInt("hasMatchedLL",n_pi_matched);
	//Matching_to_pi_AK4Jets->Fill(n_pi_matched);

	if(n_pi_matched==0)
	  {
	    nJets_0piMatch++;
	  }
	else if(n_pi_matched==1)
	  {
	    nJets_1piMatch++;
	  }
        else if(n_pi_matched==2)
	  {
	    nJets_2piMatch++;
	  }
	*/
	
    }

    //Matching the b quarks to AK4 jets
    //Starting point: b-quark
    //Postponed after loop on jets, so that Matched jets have all the additional informations
    int matching_index_Jets;//local variable
    float delta_R_Jets;//local variable
    float current_delta_R_Jets;//local variable

    for(unsigned int b = 0; b<GenBquarksVect.size(); b++)
      {
	delta_R_Jets = 1000.;
	current_delta_R_Jets = 1000.;
	matching_index_Jets = -1;
	for(unsigned int a = 0; a<JetsVect.size(); a++)
	  {
	    current_delta_R_Jets = fabs(reco::deltaR(JetsVect[a].eta(),JetsVect[a].phi(),GenBquarksVect[b].eta(),GenBquarksVect[b].phi()));
	    if(current_delta_R_Jets<0.4 && current_delta_R_Jets<delta_R_Jets && JetsVect[a].genParton() && (fabs(JetsVect[a].hadronFlavour())==5 || fabs(JetsVect[a].partonFlavour())==5) && abs( Utilities::FindMotherId(JetsVect[a].genParton()) )==9000006)
	      //this implements all the reasonable possibilities!
	      {
	      delta_R_Jets = min(delta_R_Jets,current_delta_R_Jets);
	      matching_index_Jets = a;
	      JetsVect[a].addUserInt("original_jet_index",a+1);
	      MatchedJetsVect.push_back(JetsVect[a]);//avoid duplicates!
	      }
	  }
	if(matching_index_Jets>=0){
	  number_of_b_matched_to_Jets++;
	  //if(isVerbose) std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	  //if(isVerbose) std::cout << "b quark considered: " << b+1 << std::endl;
	  //if(isVerbose) std::cout << "jet matched: " << matching_index_Jets+1 << std::endl;
	  //if(isVerbose) std::cout << "their dR: " << delta_R_Jets << std::endl;
	  //if(isVerbose && JetsVect[matching_index_Jets].genParton()) std::cout << "mother of the jet: " << Utilities::FindMotherId(JetsVect[matching_index_Jets].genParton()) << std::endl;
	  //if(isVerbose) std::cout << "flavour of the jet: " << JetsVect[matching_index_Jets].partonFlavour() << std::endl;
	  //if(isVerbose) std::cout << "- - - - - - - - - - - - - - - -" << std::endl;
	}
      }


    //Remove duplicates from Matched Jets Vector
    for(unsigned int r = 0; r<MatchedJetsVect.size(); r++)
      {
	for(unsigned int s = 0; s<MatchedJetsVect.size(); s++)
	  {
	    if(r!=s && MatchedJetsVect[s].pt()==MatchedJetsVect[r].pt()) MatchedJetsVect.erase(MatchedJetsVect.begin()+s);
	  }//duplicates removed
      }
    nMatchedJets = MatchedJetsVect.size();

    //if(isVerbose) std::cout << "N of b quarks matched to 1 jet: " << number_of_b_matched_to_Jets << std::endl;
    //if(isVerbose) std::cout << "N of matched jets: " << nMatchedJets << std::endl;
    //if(isVerbose) std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------
    // AK4 CHS Jets
    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------
    std::vector<pat::Jet> CHSJetsVect = theCHSJetAnalyzer->FillJetVector(iEvent);
    nCHSJets = CHSJetsVect.size();
    std::vector<pat::Jet> MatchedCHSJetsVect;

    for(unsigned int a = 0; a<CHSJetsVect.size(); a++) {
	if(fabs(CHSJetsVect[a].hadronFlavour())==5 || fabs(CHSJetsVect[a].partonFlavour())==5) nCHSJets_bFlav++;
	if(fabs(CHSJetsVect[a].hadronFlavour())==5) nCHSJets_bHadronFlav++;
	if(CHSJetsVect[a].genParton() && fabs(CHSJetsVect[a].partonFlavour())==5) nCHSJets_bPartonFlav++;
	if(CHSJetsVect[a].genParton() && abs(Utilities::FindMotherId(CHSJetsVect[a].genParton()))==9000006) nCHSJets_piMother++;
        if(CHSJetsVect[a].hasUserInt("isLoose") && CHSJetsVect[a].userInt("isLoose")>0) nLooseCHSJets++;
        if(CHSJetsVect[a].hasUserInt("isTight") && CHSJetsVect[a].userInt("isTight")>0) nTightCHSJets++;

	
	//Matching to b quarks of AK4CHSJets
	//Starting point: AK4 jets
	//Only define matching for jets fulfilling all the properties
	int n_b_matched_to_CHSJets = 0;
	for(unsigned int b = 0; b<GenBquarksVect.size(); b++) {
  	    if(fabs(reco::deltaR(CHSJetsVect[a].eta(),CHSJetsVect[a].phi(),GenBquarksVect[b].eta(),GenBquarksVect[b].phi()))<0.4 && CHSJetsVect[a].genParton() && (fabs(CHSJetsVect[a].hadronFlavour())==5 || fabs(CHSJetsVect[a].partonFlavour())==5) && abs( Utilities::FindMotherId(CHSJetsVect[a].genParton()) )==9000006) 
	      {
		n_b_matched_to_CHSJets++;
	      }
	}
	CHSJetsVect[a].addUserInt("hasMatchedBquarks",n_b_matched_to_CHSJets);	
    }

    //Matching the b quarks to AK4 jets
    //Starting point: b-quark
    //Postponed after loop on jets, so that Matched jets have all the additional informations
    int matching_index_CHSJets;//local variable
    float delta_R_CHSJets;//local variable
    float current_delta_R_CHSJets;//local variable
    for(unsigned int b = 0; b<GenBquarksVect.size(); b++)
      {
	delta_R_CHSJets = 1000.;
	current_delta_R_CHSJets = 1000.;
	matching_index_CHSJets = -1;
	for(unsigned int a = 0; a<CHSJetsVect.size(); a++)
	  {
	    current_delta_R_CHSJets = fabs(reco::deltaR(CHSJetsVect[a].eta(),CHSJetsVect[a].phi(),GenBquarksVect[b].eta(),GenBquarksVect[b].phi()));
	    if(current_delta_R_CHSJets<0.4 && current_delta_R_CHSJets<delta_R_CHSJets && CHSJetsVect[a].genParton() && (fabs(CHSJetsVect[a].hadronFlavour())==5 || fabs(CHSJetsVect[a].partonFlavour())==5) && abs( Utilities::FindMotherId(CHSJetsVect[a].genParton()) )==9000006)
	      //this implements all the reasonable possibilities!
	      {
	      delta_R_CHSJets = min(delta_R_CHSJets,current_delta_R_CHSJets);
	      matching_index_CHSJets = a;
	      CHSJetsVect[a].addUserInt("original_jet_index",a+1);
	      MatchedCHSJetsVect.push_back(CHSJetsVect[a]);//avoid duplicates!
	      }
	  }
	if(matching_index_CHSJets>=0){
	  number_of_b_matched_to_CHSJets++;
	}
      }


    //Remove duplicates from Matched CHSJets Vector
    for(unsigned int r = 0; r<MatchedCHSJetsVect.size(); r++)
      {
	for(unsigned int s = 0; s<MatchedCHSJetsVect.size(); s++)
	  {
	    if(r!=s && MatchedCHSJetsVect[s].pt()==MatchedCHSJetsVect[r].pt()) MatchedCHSJetsVect.erase(MatchedCHSJetsVect.begin()+s);
	  }//duplicates removed
      }
    nMatchedCHSJets = MatchedCHSJetsVect.size();

    //////////PUPPI

    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------
    // AK4 Puppi Jets
    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------
    std::vector<pat::Jet> PuppiJetsVect = thePuppiJetAnalyzer->FillJetVector(iEvent);
    nPuppiJets = PuppiJetsVect.size();
    std::vector<pat::Jet> MatchedPuppiJetsVect;

    for(unsigned int a = 0; a<PuppiJetsVect.size(); a++) {
	if(fabs(PuppiJetsVect[a].hadronFlavour())==5 || fabs(PuppiJetsVect[a].partonFlavour())==5) nPuppiJets_bFlav++;
	if(fabs(PuppiJetsVect[a].hadronFlavour())==5) nPuppiJets_bHadronFlav++;
	if(PuppiJetsVect[a].genParton() && fabs(PuppiJetsVect[a].partonFlavour())==5) nPuppiJets_bPartonFlav++;
	if(PuppiJetsVect[a].genParton() && abs(Utilities::FindMotherId(PuppiJetsVect[a].genParton()))==9000006) nPuppiJets_piMother++;
        //if(PuppiJetsVect[a].hasUserInt("isLoose") && PuppiJetsVect[a].userInt("isLoose")>0) nLoosePuppiJets++;
        //if(PuppiJetsVect[a].hasUserInt("isTight") && PuppiJetsVect[a].userInt("isTight")>0) nTightPuppiJets++;

	
	//Matching to b quarks of AK4PuppiJets
	//Starting point: AK4 jets
	//Only define matching for jets fulfilling all the properties
	int n_b_matched_to_PuppiJets = 0;
	for(unsigned int b = 0; b<GenBquarksVect.size(); b++) {
  	    if(fabs(reco::deltaR(PuppiJetsVect[a].eta(),PuppiJetsVect[a].phi(),GenBquarksVect[b].eta(),GenBquarksVect[b].phi()))<0.4 && PuppiJetsVect[a].genParton() && (fabs(PuppiJetsVect[a].hadronFlavour())==5 || fabs(PuppiJetsVect[a].partonFlavour())==5) && abs( Utilities::FindMotherId(PuppiJetsVect[a].genParton()) )==9000006) 
	      {
		n_b_matched_to_PuppiJets++;
	      }
	}
	PuppiJetsVect[a].addUserInt("hasMatchedBquarks",n_b_matched_to_PuppiJets);	
    }

    //Matching the b quarks to AK4 jets
    //Starting point: b-quark
    //Postponed after loop on jets, so that Matched jets have all the additional informations
    int matching_index_PuppiJets;//local variable
    float delta_R_PuppiJets;//local variable
    float current_delta_R_PuppiJets;//local variable
    for(unsigned int b = 0; b<GenBquarksVect.size(); b++)
      {
	delta_R_PuppiJets = 1000.;
	current_delta_R_PuppiJets = 1000.;
	matching_index_PuppiJets = -1;
	for(unsigned int a = 0; a<PuppiJetsVect.size(); a++)
	  {
	    current_delta_R_PuppiJets = fabs(reco::deltaR(PuppiJetsVect[a].eta(),PuppiJetsVect[a].phi(),GenBquarksVect[b].eta(),GenBquarksVect[b].phi()));
	    if(current_delta_R_PuppiJets<0.4 && current_delta_R_PuppiJets<delta_R_PuppiJets && PuppiJetsVect[a].genParton() && (fabs(PuppiJetsVect[a].hadronFlavour())==5 || fabs(PuppiJetsVect[a].partonFlavour())==5) && abs( Utilities::FindMotherId(PuppiJetsVect[a].genParton()) )==9000006)
	      //this implements all the reasonable possibilities!
	      {
	      delta_R_PuppiJets = min(delta_R_PuppiJets,current_delta_R_PuppiJets);
	      matching_index_PuppiJets = a;
	      PuppiJetsVect[a].addUserInt("original_jet_index",a+1);
	      MatchedPuppiJetsVect.push_back(PuppiJetsVect[a]);//avoid duplicates!
	      }
	  }
	if(matching_index_PuppiJets>=0){
	  number_of_b_matched_to_PuppiJets++;
	}
      }


    //Remove duplicates from Matched PuppiJets Vector
    for(unsigned int r = 0; r<MatchedPuppiJetsVect.size(); r++)
      {
	for(unsigned int s = 0; s<MatchedPuppiJetsVect.size(); s++)
	  {
	    if(r!=s && MatchedPuppiJetsVect[s].pt()==MatchedPuppiJetsVect[r].pt()) MatchedPuppiJetsVect.erase(MatchedPuppiJetsVect.begin()+s);
	  }//duplicates removed
      }
    nMatchedPuppiJets = MatchedPuppiJetsVect.size();




    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------
    // Gen matcher - with AK4
    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------

    // GenBquarksVect
    theJetAnalyzer->GenMatcher(JetsVect, GenBquarksVect, "q");
    theJetAnalyzer->GenMatcher(MatchedJetsVect, GenBquarksVect, "q");
    theCHSJetAnalyzer->GenMatcher(CHSJetsVect, GenBquarksVect, "q");
    thePuppiJetAnalyzer->GenMatcher(PuppiJetsVect, GenBquarksVect, "q");
    theCHSJetAnalyzer->GenMatcher(MatchedCHSJetsVect, GenBquarksVect, "q");
    thePuppiJetAnalyzer->GenMatcher(MatchedPuppiJetsVect, GenBquarksVect, "q");
    //GenLongLivedVect
    theJetAnalyzer->GenMatcher(JetsVect, GenLongLivedVect, "pi");
    theJetAnalyzer->GenMatcher(MatchedJetsVect, GenLongLivedVect, "pi");
    theCHSJetAnalyzer->GenMatcher(CHSJetsVect, GenLongLivedVect, "pi");
    theCHSJetAnalyzer->GenMatcher(MatchedCHSJetsVect, GenLongLivedVect, "pi");
    thePuppiJetAnalyzer->GenMatcher(PuppiJetsVect, GenLongLivedVect, "pi");
    thePuppiJetAnalyzer->GenMatcher(MatchedPuppiJetsVect, GenLongLivedVect, "pi");


    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------
    // AK8 Jets
    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------

    std::vector<pat::Jet> CHSFatJetsVect = theCHSFatJetAnalyzer->FillJetVector(iEvent);
    std::vector<pat::Jet> FatJetsVect = theFatJetAnalyzer->FillJetVector(iEvent);
    nFatJets = FatJetsVect.size();
    nCHSFatJets = CHSFatJetsVect.size();
    //int nFatJets_bFlav = 0;
    //int nCHSFatJets_bFlav = 0;

    //if(nGenBquarks<4)
    //{
    //FatJetsVect.clear();
    //CHSFatJetsVect.clear();
    //return; //First step: only full reconstruction!
    //}

    // GenBquarksVect
    theFatJetAnalyzer->GenMatcher(FatJetsVect, GenBquarksVect, "q");
    theCHSFatJetAnalyzer->GenMatcher(CHSFatJetsVect, GenBquarksVect, "q");
    //theCHSJetAnalyzer->GenMatcher(FatJetsVect, GenBquarksVect, "q");
    //GenLongLivedVect
    theFatJetAnalyzer->GenMatcher(FatJetsVect, GenLongLivedVect, "pi");
    theCHSFatJetAnalyzer->GenMatcher(CHSFatJetsVect, GenLongLivedVect, "pi");
    //theCHSJetAnalyzer->GenMatcher(FatJetsVect, GenLongLivedVect, "pi");

    for(unsigned int a = 0; a<FatJetsVect.size(); a++) {
        //std::cout << "Looking at jet n. " << a << std::endl;
	if(fabs(FatJetsVect[a].hadronFlavour())==5 || fabs(FatJetsVect[a].partonFlavour())==5) nFatJets_bFlav++;
        if(FatJetsVect[a].hasUserInt("isLoose") && FatJetsVect[a].userInt("isLoose")>0) nLooseFatJets++;
        if(FatJetsVect[a].hasUserInt("isTight") && FatJetsVect[a].userInt("isTight")>0) nTightFatJets++;
	//if(FatJetsVect[a].hasUserFloat("ak8PFJetsPrunedMass")) std::cout << "non chs pruned mass: " << FatJetsVect[a].userFloat("ak8PFJetsPrunedMass") << std::endl;
	//if(FatJetsVect[a].hasUserFloat("ak8PFJetsSoftDropMass")) std::cout << "non chs softdrop mass: " << FatJetsVect[a].userFloat("ak8PFJetsSoftDropMass") << std::endl;
	//if(FatJetsVect[a].hasUserFloat("NjettinessAK8:tau1")) std::cout << "tau 1: " << FatJetsVect[a].userFloat("NjettinessAK8:tau1") << std::endl;
	//if(FatJetsVect[a].hasUserFloat("NjettinessAK8Puppi:tau1")) std::cout << "puppi tau 1: " << FatJetsVect[a].userFloat("NjettinessAK8Puppi:tau1") << std::endl;
	//if(FatJetsVect[a].hasSubjets("SoftDropPuppi"))
	//{
	//if(FatJetsVect[a].subjets("SoftDropPuppi").size() > 0) std::cout << "SoftDropPuppi subjet 1 pt: " << FatJetsVect[a].subjets("SoftDropPuppi")[0]->pt() << std::endl;
	//}
        //if(FatJetsVect[a].hasSubjets("SoftDrop"))
	//{
	//if(FatJetsVect[a].subjets("SoftDrop").size() > 0) std::cout << "SoftDrop subjet 1 pt: " << FatJetsVect[a].subjets("SoftDrop")[0]->pt() << std::endl;
	//}
	/*
	if(isVerbose) {
	  if(FatJetsVect[a].genJet())
	    {
	      std::cout << FatJetsVect[a].genJet()->pt() << std::endl;
	      std::cout << FatJetsVect[a].genJet()->numberOfDaughters() << std::endl;
	    }

	  if(FatJetsVect[a].genParton()) 
	    {
	      std::cout << FatJetsVect[a].genParton()->pt() << std::endl;
	      std::cout << FatJetsVect[a].genParton()->pdgId() << std::endl;
	    }
	}
	*/

	//Matching to b quarks of AK8Jets
	int n_b_matched = 0;
	int n_b_matched_sj1 = 0;
	int n_b_matched_sj2 = 0;
	for(unsigned int b = 0; b<GenBquarksVect.size(); b++) {
  	    if(fabs(reco::deltaR(FatJetsVect[a].eta(),FatJetsVect[a].phi(),GenBquarksVect[b].eta(),GenBquarksVect[b].phi()))<0.8) n_b_matched++;
	    if(FatJetsVect[a].subjets("SoftDrop").size() > 0 && fabs(reco::deltaR(FatJetsVect[a].subjets("SoftDrop")[0]->eta(),FatJetsVect[a].subjets("SoftDrop")[0]->phi(),GenBquarksVect[b].eta(),GenBquarksVect[b].phi())) <0.4) n_b_matched_sj1++; 
	    if(FatJetsVect[a].subjets("SoftDrop").size() > 1 && fabs(reco::deltaR(FatJetsVect[a].subjets("SoftDrop")[1]->eta(),FatJetsVect[a].subjets("SoftDrop")[1]->phi(),GenBquarksVect[b].eta(),GenBquarksVect[b].phi())) <0.4) n_b_matched_sj2++; 
	}
	FatJetsVect[a].addUserInt("hasMatchedBquarks",n_b_matched);
	//Matching_to_b_AK8Jets->Fill(n_b_matched);
	//Matching_to_b_AK8Jets_sj1->Fill(n_b_matched_sj1);
	//Matching_to_b_AK8Jets_sj2->Fill(n_b_matched_sj2);

	//if(n_b_matched==0)
	//{
	//Matching_to_b_AK8Jets_simplified->Fill(0);
	    //CSV_AK8Jets_matched_to_0b->Fill(JetsVect[a].bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
	    //pT_AK8Jets_matched_to_0b->Fill(JetsVect[a].pt());
	//}
	//else if(n_b_matched==1)
	//{
	//Matching_to_b_AK8Jets_simplified->Fill(1);
	    //CSV_AK8Jets_matched_to_1b->Fill(JetsVect[a].bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
	    //pT_AK8Jets_matched_to_1b->Fill(JetsVect[a].pt());
	//}
	//else if(n_b_matched==2)
	//{
	//Matching_to_b_AK8Jets_simplified->Fill(2);
	    //CSV_AK8Jets_matched_to_2b->Fill(JetsVect[a].bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
	    //pT_AK8Jets_matched_to_2b->Fill(JetsVect[a].pt());
	//}
	//else
	//{
	//Matching_to_b_AK8Jets_simplified->Fill(3);
	    //CSV_AK8Jets_matched_to_more_2b->Fill(JetsVect[a].bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
	    //pT_AK8Jets_matched_to_more_2b->Fill(JetsVect[a].pt());
	//}
	//std::cout<<"jet n. " << a << " has " << n_b_matched << " matched b quarks" << std::endl;


	//Matching to dark pions of AK8Jets
	int n_pi_matched = 0;
	int n_pi_matched_sj1 = 0;
	int n_pi_matched_sj2 = 0;
	for(unsigned int pi = 0; pi<GenLongLivedVect.size(); pi++) {
  	    if(fabs(reco::deltaR(FatJetsVect[a].eta(),FatJetsVect[a].phi(),GenLongLivedVect[pi].eta(),GenLongLivedVect[pi].phi()))<0.8) n_pi_matched++;
	    if(FatJetsVect[a].subjets("SoftDrop").size() > 0 && fabs(reco::deltaR(FatJetsVect[a].subjets("SoftDrop")[0]->eta(),FatJetsVect[a].subjets("SoftDrop")[0]->phi(),GenLongLivedVect[pi].eta(),GenLongLivedVect[pi].phi())) <0.4) n_pi_matched_sj1++; 
	    if(FatJetsVect[a].subjets("SoftDrop").size() > 1 && fabs(reco::deltaR(FatJetsVect[a].subjets("SoftDrop")[1]->eta(),FatJetsVect[a].subjets("SoftDrop")[1]->phi(),GenLongLivedVect[pi].eta(),GenLongLivedVect[pi].phi())) <0.4) n_pi_matched_sj2++; 
	}
	FatJetsVect[a].addUserInt("hasMatchedLL",n_pi_matched);
	//Matching_to_pi_AK8Jets->Fill(n_pi_matched);
	//Matching_to_pi_AK8Jets_sj1->Fill(n_pi_matched_sj1);
	//Matching_to_pi_AK8Jets_sj2->Fill(n_pi_matched_sj2);

	//if(n_pi_matched==0)
	//{
	//CSV_AK8Jets_matched_to_0pi->Fill(JetsVect[a].bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
	//pT_AK8Jets_matched_to_0pi->Fill(JetsVect[a].pt());
	//}
	//else if(n_pi_matched==1)
	//{
	//CSV_AK8Jets_matched_to_1pi->Fill(JetsVect[a].bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
	//pT_AK8Jets_matched_to_1pi->Fill(JetsVect[a].pt());
	//}
	//else if(n_pi_matched==2)
	//{
	//CSV_AK8Jets_matched_to_2pi->Fill(JetsVect[a].bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
	//pT_AK8Jets_matched_to_2pi->Fill(JetsVect[a].pt());
	//}
	
    }

    for(unsigned int a = 0; a<CHSFatJetsVect.size(); a++) {
        if(CHSFatJetsVect[a].hasUserInt("isLoose") && CHSFatJetsVect[a].userInt("isLoose")>0) nLooseCHSFatJets++;
        if(CHSFatJetsVect[a].hasUserInt("isTight") && CHSFatJetsVect[a].userInt("isTight")>0) nTightCHSFatJets++;
	if(fabs(CHSFatJetsVect[a].hadronFlavour())==5 || fabs(CHSFatJetsVect[a].partonFlavour())==5) nCHSFatJets_bFlav++;

	//if(isVerbose) {
	  //if(CHSFatJetsVect[a].genJet())
	    //{
	      //std::cout << CHSFatJetsVect[a].genJet()->pt() << std::endl;
	      //std::cout << CHSFatJetsVect[a].genJet()->numberOfDaughters() << std::endl;
	      //}

	  //if(CHSFatJetsVect[a].genParton()) 
	    //{
	      //std::cout << CHSFatJetsVect[a].genParton()->pt() << std::endl;
	      //std::cout << CHSFatJetsVect[a].genParton()->pdgId() << std::endl;
	      //}
	  //}


	//Matching to b quarks of CHSAK8Jets
	int n_b_matched_chs = 0;
	int n_b_matched_sj1_chs = 0;
	int n_b_matched_sj2_chs = 0;
	for(unsigned int b = 0; b<GenBquarksVect.size(); b++) {
  	    if(fabs(reco::deltaR(CHSFatJetsVect[a].eta(),CHSFatJetsVect[a].phi(),GenBquarksVect[b].eta(),GenBquarksVect[b].phi()))<0.8) n_b_matched_chs++;
	    if(CHSFatJetsVect[a].subjets("SoftDrop").size() > 0 && fabs(reco::deltaR(CHSFatJetsVect[a].subjets("SoftDrop")[0]->eta(),CHSFatJetsVect[a].subjets("SoftDrop")[0]->phi(),GenBquarksVect[b].eta(),GenBquarksVect[b].phi())) <0.4) n_b_matched_sj1_chs++; 
	    if(CHSFatJetsVect[a].subjets("SoftDrop").size() > 1 && fabs(reco::deltaR(CHSFatJetsVect[a].subjets("SoftDrop")[1]->eta(),CHSFatJetsVect[a].subjets("SoftDrop")[1]->phi(),GenBquarksVect[b].eta(),GenBquarksVect[b].phi())) <0.4) n_b_matched_sj2_chs++; 
	}
	CHSFatJetsVect[a].addUserInt("hasMatchedBquarks",n_b_matched_chs);
	//Matching_to_b_CHSAK8Jets->Fill(n_b_matched_chs);
	//Matching_to_b_CHSAK8Jets_sj1->Fill(n_b_matched_sj1_chs);
	//Matching_to_b_CHSAK8Jets_sj2->Fill(n_b_matched_sj2_chs);

	//Matching to dark pions of CHSAK8Jets
	int n_pi_matched_chs = 0;
	int n_pi_matched_sj1_chs = 0;
	int n_pi_matched_sj2_chs = 0;
	for(unsigned int pi = 0; pi<GenLongLivedVect.size(); pi++) {
  	    if(fabs(reco::deltaR(CHSFatJetsVect[a].eta(),CHSFatJetsVect[a].phi(),GenLongLivedVect[pi].eta(),GenLongLivedVect[pi].phi()))<0.8) n_pi_matched_chs++;
	    if(CHSFatJetsVect[a].subjets("SoftDrop").size() > 0 && fabs(reco::deltaR(CHSFatJetsVect[a].subjets("SoftDrop")[0]->eta(),CHSFatJetsVect[a].subjets("SoftDrop")[0]->phi(),GenLongLivedVect[pi].eta(),GenLongLivedVect[pi].phi())) <0.4) n_pi_matched_sj1_chs++; 
	    if(CHSFatJetsVect[a].subjets("SoftDrop").size() > 1 && fabs(reco::deltaR(CHSFatJetsVect[a].subjets("SoftDrop")[1]->eta(),CHSFatJetsVect[a].subjets("SoftDrop")[1]->phi(),GenLongLivedVect[pi].eta(),GenLongLivedVect[pi].phi())) <0.4) n_pi_matched_sj2_chs++; 
	}
	CHSFatJetsVect[a].addUserInt("hasMatchedLL",n_pi_matched_chs);
	//Matching_to_pi_CHSAK8Jets->Fill(n_pi_matched_chs);
	//Matching_to_pi_CHSAK8Jets_sj1->Fill(n_pi_matched_sj1_chs);
	//Matching_to_pi_CHSAK8Jets_sj2->Fill(n_pi_matched_sj2_chs);	
    }

    if(isVerbose)
      {
	std::cout << "n of AK8 with b flav: " << nFatJets_bFlav << std::endl;
	std::cout << "n of CHS AK8 with b flav: " << nCHSFatJets_bFlav << std::endl;
      }


    //Gen Jets
    /*
    edm::Handle<reco::GenJetCollection> GenJetColl;//Lisa
    iEvent.getByToken( genJetToken, GenJetColl);//Lisa
    //easy loop Lisa
    for(std::vector<reco::GenJet>::const_iterator it=GenJetColl->begin(); it!=GenJetColl->end(); ++it) {
         reco::GenJet jet=*it;
	 int idx=it-GenJetColl->begin();
	 std::cout << " Looping over genjet n. " << idx << std::endl;
	 std::cout << jet.pt() << std::endl;
	 //std::cout << jet.() << std::endl;
    }
    */


    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------
    // AK4 CALO Jets
    //------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------
    edm::Handle<std::vector<reco::CaloJet>> caloJets;
    iEvent.getByToken( caloJetToken, caloJets );
    std::vector<reco::CaloJet> CaloJetsVect;
    std::vector<reco::CaloJet> MatchedCaloJetsVect;


    //Do what is done for Jet analyzer, hardcoded, without JEC:    
    //As a first guess, let's restrict calo jet to tracker
    float PtTh = 15.;
    float EtaTh = 2.4;
    for(std::vector<reco::CaloJet>::const_iterator it=caloJets->begin(); it!=caloJets->end(); it++) {
      reco::CaloJet jet=*it;
      // Pt and eta cut
      if(jet.pt()<PtTh || fabs(jet.eta())>EtaTh) continue;
      CaloJetsVect.push_back(jet);
    }
    
    nCaloJets = CaloJetsVect.size();

    
    //Matching the b quarks to AK4 calo jets
    //Starting point: b-quark
    int matching_index_CaloJets;//local variable
    float delta_R_CaloJets;//local variable
    float current_delta_R_CaloJets;//local variable

    for(unsigned int b = 0; b<GenBquarksVect.size(); b++)
      {
	delta_R_CaloJets = 1000.;
	current_delta_R_CaloJets = 1000.;
	matching_index_CaloJets = -1;
	for(unsigned int a = 0; a<CaloJetsVect.size(); a++)
	  {
	    current_delta_R_CaloJets = fabs(reco::deltaR(CaloJetsVect[a].eta(),CaloJetsVect[a].phi(),GenBquarksVect[b].eta(),GenBquarksVect[b].phi()));
	    if(current_delta_R_CaloJets<0.4 && current_delta_R_CaloJets<delta_R_CaloJets)
	      //this implements all the reasonable possibilities!
	      {
	      delta_R_CaloJets = min(delta_R_CaloJets,current_delta_R_CaloJets);
	      matching_index_CaloJets = a;
	      //JetsVect[a].addUserInt("original_jet_index",a+1);
	      MatchedCaloJetsVect.push_back(CaloJetsVect[a]);//avoid duplicates!
	      }
	  }
	if(matching_index_CaloJets>=0){
	  number_of_b_matched_to_CaloJets++;
	}
      }


    //Remove duplicates from Matched Jets Vector
    for(unsigned int r = 0; r<MatchedCaloJetsVect.size(); r++)
      {
	for(unsigned int s = 0; s<MatchedCaloJetsVect.size(); s++)
	  {
	    if(r!=s && MatchedCaloJetsVect[s].pt()==MatchedCaloJetsVect[r].pt()) MatchedCaloJetsVect.erase(MatchedCaloJetsVect.begin()+s);
	  }//duplicates removed
      }
    nMatchedCaloJets = MatchedCaloJetsVect.size();

    /*
    //Vertices
    edm::Handle<reco::VertexCollection> VertexColl;
    iEvent.getByToken( vertexToken, VertexColl);
    nPV = VertexColl->size();
    const reco::Vertex* vertex=&VertexColl->front();
    reco::TrackBase::Point vtxPoint(0,0,0);
    if(  VertexColl->size() >= 1 ) {
        vtxPoint = VertexColl->at(0).position();
    }
    */


    if(isVerbose) {
      std::cout << " --- Event n. " << iEvent.id().event() << ", lumi " << iEvent.luminosityBlock() << ", run " << iEvent.id().run() << std::endl;
      //std::cout << "number of electrons: " << ElecVect.size() << std::endl;
      //for(unsigned int i = 0; i < ElecVect.size(); i++) std::cout << "  electron [" << i << "]\tpt: " << ElecVect[i].pt() << "\teta: " << ElecVect[i].eta() << "\tphi: " << ElecVect[i].phi() << "\tmass: " << ElecVect[i].mass() << "\tcharge: " << ElecVect[i].charge() << std::endl;
      //std::cout << "number of muons:     " << MuonVect.size() << std::endl;
      //for(unsigned int i = 0; i < MuonVect.size(); i++) std::cout << "  muon     [" << i << "]\tpt: " << MuonVect[i].pt() << "\teta: " << MuonVect[i].eta() << "\tphi: " << MuonVect[i].phi() << "\tmass: " << MuonVect[i].mass() << "\tcharge: " << MuonVect[i].charge() << std::endl;
      //std::cout << "number of taus:  " << TauVect.size() << std::endl;
      //for(unsigned int i = 0; i < TauVect.size(); i++) std::cout << "  tau  [" << i << "]\tpt: " << TauVect[i].pt() << "\teta: " << TauVect[i].eta() << "\tphi: " << TauVect[i].phi() << std::endl;
      //std::cout << "number of photons:  " << PhotonVect.size() << std::endl;
      //for(unsigned int i = 0; i < PhotonVect.size(); i++) std::cout << "  photon  [" << i << "]\tpt: " << PhotonVect[i].pt() << "\teta: " << PhotonVect[i].eta() << "\tphi: " << PhotonVect[i].phi() << std::endl;
      std::cout << "number of Matched AK4 jets:  " << MatchedJetsVect.size() << std::endl;
      for(unsigned int i = 0; i < MatchedJetsVect.size(); i++) std::cout << "  Matched AK4 jet  [" << i << "]\tpt: " << MatchedJetsVect[i].pt() << "\teta: " << MatchedJetsVect[i].eta() << "\tphi: " << MatchedJetsVect[i].phi() << "\tmass: " << MatchedJetsVect[i].mass() << std::endl;
      std::cout << "number of CHS AK4 jets:  " << CHSJetsVect.size() << std::endl;
      for(unsigned int i = 0; i < CHSJetsVect.size(); i++) std::cout << "  CHS AK4 jet  [" << i << "]\tpt: " << CHSJetsVect[i].pt() << "\teta: " << CHSJetsVect[i].eta() << "\tphi: " << CHSJetsVect[i].phi() << "\tmass: " << CHSJetsVect[i].mass() << std::endl;
      std::cout << "number of AK4 jets:  " << JetsVect.size() << std::endl;
      for(unsigned int i = 0; i < JetsVect.size(); i++) std::cout << "  AK4 jet  [" << i << "]\tpt: " << JetsVect[i].pt() << "\teta: " << JetsVect[i].eta() << "\tphi: " << JetsVect[i].phi() << "\tmass: " << JetsVect[i].mass() << std::endl;
      std::cout << "number of Macthed Calo AK4 jets:  " << MatchedCaloJetsVect.size() << std::endl;
      for(unsigned int i = 0; i < MatchedCaloJetsVect.size(); i++) std::cout << "  Calo AK4 jet  [" << i << "]\tpt: " << MatchedCaloJetsVect[i].pt() << "\teta: " << MatchedCaloJetsVect[i].eta() << "\tphi: " << MatchedCaloJetsVect[i].phi() << "\tmass: " << MatchedCaloJetsVect[i].mass() << std::endl;
      //std::cout << "number of Gen B quarks:  " << GenBquarksVect.size() << std::endl;
      //for(unsigned int i = 0; i < GenBquarksVect.size(); i++) std::cout << "  Gen B quark  [" << i << "]\tpt: " << GenBquarksVect[i].pt() << "\teta: " << GenBquarksVect[i].eta() << "\tphi: " << GenBquarksVect[i].phi() << "\tmass: " << GenBquarksVect[i].mass() << std::endl;
     std::cout << "number of AK8 jets:  " << FatJetsVect.size() << std::endl;
     for(unsigned int i = 0; i < FatJetsVect.size(); i++) std::cout << "  AK8 jet  [" << i << "]\tpt: " << FatJetsVect[i].pt() << "\teta: " << FatJetsVect[i].eta() << "\tphi: " << FatJetsVect[i].phi() << "\tmass: " << FatJetsVect[i].mass() << std::endl;
     std::cout << "number of CHS AK8 jets:  " << CHSFatJetsVect.size() << std::endl;
     for(unsigned int i = 0; i < CHSFatJetsVect.size(); i++) std::cout << "  AK8 jet  [" << i << "]\tpt: " << CHSFatJetsVect[i].pt() << "\teta: " << CHSFatJetsVect[i].eta() << "\tphi: " << CHSFatJetsVect[i].phi() << "\tmass: " << CHSFatJetsVect[i].mass() << std::endl;
      //std::cout << "number of AK8 jets:  " << FatJetsVect.size() << std::endl;
      //for(unsigned int i = 0; i < FatJetsVect.size(); i++) std::cout << "  AK8 jet  [" << i << "]\tpt: " << FatJetsVect[i].pt() << "\teta: " << FatJetsVect[i].eta() << "\tphi: " << FatJetsVect[i].phi() << "\tmass: " << FatJetsVect[i].mass() << std::endl;
      //std::cout << "Missing energy:      " << MET.pt() << std::endl;
      //std::cout << "V leptonic mass:     " << theV.mass() << std::endl;
    }


    // ---------- Fill objects ----------

    if(isVerbose) std::cout << " - Filling objects" << std::endl;

    for(unsigned int i = 0; i < Jets.size() && i < JetsVect.size(); i++) ObjectsFormat::FillJetType(Jets[i], &JetsVect[i], isMC);
    for(unsigned int i = 0; i < MatchedJets.size() && i < MatchedJetsVect.size(); i++) ObjectsFormat::FillJetType(MatchedJets[i], &MatchedJetsVect[i], isMC);
    for(unsigned int i = 0; i < MatchedCHSJets.size() && i < MatchedCHSJetsVect.size(); i++) ObjectsFormat::FillJetType(MatchedCHSJets[i], &MatchedCHSJetsVect[i], isMC);
    for(unsigned int i = 0; i < MatchedPuppiJets.size() && i < MatchedPuppiJetsVect.size(); i++) ObjectsFormat::FillJetType(MatchedPuppiJets[i], &MatchedPuppiJetsVect[i], isMC);
    for(unsigned int i = 0; i < MatchedCaloJets.size() && i < MatchedCaloJetsVect.size(); i++) ObjectsFormat::FillCaloJetType(MatchedCaloJets[i], &MatchedCaloJetsVect[i], isMC);
    for(unsigned int i = 0; i < CHSJets.size() && i < CHSJetsVect.size(); i++) ObjectsFormat::FillJetType(CHSJets[i], &CHSJetsVect[i], isMC);
    for(unsigned int i = 0; i < PuppiJets.size() && i < PuppiJetsVect.size(); i++) ObjectsFormat::FillJetType(PuppiJets[i], &PuppiJetsVect[i], isMC);
    for(unsigned int i = 0; i < FatJets.size() && i < FatJetsVect.size(); i++) ObjectsFormat::FillCustomFatJetType(FatJets[i], &FatJetsVect[i], isMC);//??
    for(unsigned int i = 0; i < CHSFatJets.size() && i < CHSFatJetsVect.size(); i++) ObjectsFormat::FillFatJetType(CHSFatJets[i], &CHSFatJetsVect[i], isMC);//??
    for(unsigned int i = 0; i < GenBquarks.size() && i < GenBquarksVect.size(); i++) ObjectsFormat::FillGenPType(GenBquarks[i], &GenBquarksVect[i]);
    for(unsigned int i = 0; i < GenLongLiveds.size() && i < GenLongLivedVect.size(); i++) ObjectsFormat::FillGenPType(GenLongLiveds[i], &GenLongLivedVect[i]);

    tree -> Fill();




}


// ------------ method called once each job just before starting event loop  ------------
void 
RecoStudiesCalo::beginJob()
{
    for(int i = 0; i < WriteNJets; i++) Jets.push_back( JetType() );
    for(int i = 0; i < 4; i++) MatchedJets.push_back( JetType() );
    for(int i = 0; i < 4; i++) MatchedCHSJets.push_back( JetType() );
    for(int i = 0; i < 4; i++) MatchedPuppiJets.push_back( JetType() );
    for(int i = 0; i < 4; i++) MatchedCaloJets.push_back( CaloJetType() );
    for(int i = 0; i < WriteNJets; i++) CHSJets.push_back( JetType() );
    for(int i = 0; i < WriteNJets; i++) PuppiJets.push_back( JetType() );
    for(int i = 0; i < WriteNFatJets; i++) FatJets.push_back( CustomFatJetType() );//??
    for(int i = 0; i < WriteNFatJets; i++) CHSFatJets.push_back( FatJetType() );//??
    for(int i = 0; i < WriteNGenBquarks; i++) GenBquarks.push_back( GenPType() );
    for(int i = 0; i < WriteNGenLongLiveds; i++) GenLongLiveds.push_back( GenPType() );

    //Set branches for objects
    for(int i = 0; i < WriteNJets; i++) tree->Branch(("Jet"+std::to_string(i+1)).c_str(), &(Jets[i].pt), ObjectsFormat::ListJetType().c_str());
    for(int i = 0; i < 4; i++) tree->Branch(("MatchedJet"+std::to_string(i+1)).c_str(), &(MatchedJets[i].pt), ObjectsFormat::ListJetType().c_str());
    for(int i = 0; i < 4; i++) tree->Branch(("MatchedCHSJet"+std::to_string(i+1)).c_str(), &(MatchedCHSJets[i].pt), ObjectsFormat::ListJetType().c_str());
    for(int i = 0; i < 4; i++) tree->Branch(("MatchedPuppiJet"+std::to_string(i+1)).c_str(), &(MatchedPuppiJets[i].pt), ObjectsFormat::ListJetType().c_str());
    for(int i = 0; i < 4; i++) tree->Branch(("MatchedCaloJet"+std::to_string(i+1)).c_str(), &(MatchedCaloJets[i].pt), ObjectsFormat::ListCaloJetType().c_str());
    for(int i = 0; i < WriteNJets; i++) tree->Branch(("CHSJet"+std::to_string(i+1)).c_str(), &(CHSJets[i].pt), ObjectsFormat::ListJetType().c_str());
    for(int i = 0; i < WriteNJets; i++) tree->Branch(("PuppiJet"+std::to_string(i+1)).c_str(), &(PuppiJets[i].pt), ObjectsFormat::ListJetType().c_str());
    for(int i = 0; i < WriteNFatJets; i++) tree->Branch(("FatJet"+std::to_string(i+1)).c_str(), &(FatJets[i].pt), ObjectsFormat::ListCustomFatJetType().c_str());//??
    for(int i = 0; i < WriteNFatJets; i++) tree->Branch(("CHSFatJet"+std::to_string(i+1)).c_str(), &(CHSFatJets[i].pt), ObjectsFormat::ListFatJetType().c_str());//??
    for(int i = 0; i < WriteNGenBquarks; i++) tree->Branch(("GenBquark"+std::to_string(i+1)).c_str(), &(GenBquarks[i].pt), ObjectsFormat::ListGenPType().c_str());
    for(int i = 0; i < WriteNGenLongLiveds; i++) tree->Branch(("GenLongLived"+std::to_string(i+1)).c_str(), &(GenLongLiveds[i].pt), ObjectsFormat::ListGenPType().c_str());
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RecoStudiesCalo::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
RecoStudiesCalo::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}


//Method to define loose jet ID (2016 data)
bool RecoStudiesCalo::isLooseJet(pat::Jet& jet){
    if(fabs(jet.eta())<=2.7){/// |eta| < 2.7
        if(jet.neutralHadronEnergyFraction()>=0.99) return false;
        if(jet.neutralEmEnergyFraction()>=0.99) return false;
        if((jet.chargedMultiplicity()+jet.neutralMultiplicity())<=1) return false;
            if(fabs(jet.eta())<=2.4) { /// |eta| < 2.4
                if(jet.chargedHadronEnergyFraction()<=0.) return false;
                if(jet.chargedMultiplicity()<=0) return false;
                if(jet.chargedEmEnergyFraction()>=0.99) return false;
            }
    }
    else{ /// |eta| > 2.7
        if(jet.neutralEmEnergyFraction()>=0.90) return false;
        if (fabs(jet.eta())<=3.0) { /// 2.7 < |eta| < 3.0
            if(jet.neutralMultiplicity()<=2) return false;
        }
        else{ /// |eta| > 3.0
           if(jet.neutralMultiplicity()<=10) return false;
        }
    }

    return true;
}

//Method to define tight jet ID (2016 data)
bool RecoStudiesCalo::isTightJet(pat::Jet& jet){
    if(fabs(jet.eta())<=2.7){/// |eta| < 2.7
        if(jet.neutralHadronEnergyFraction()>=0.90) return false;
        if(jet.neutralEmEnergyFraction()>=0.90) return false;
        if((jet.chargedMultiplicity()+jet.neutralMultiplicity())<=1) return false;
            if(fabs(jet.eta())<=2.4) { /// |eta| < 2.4
                if(jet.chargedHadronEnergyFraction()<=0.) return false;
                if(jet.chargedMultiplicity()<=0) return false;
                if(jet.chargedEmEnergyFraction()>=0.99) return false;
            }
    }
    else{ /// |eta| > 2.7
        if(jet.neutralEmEnergyFraction()>=0.90) return false;
        if (fabs(jet.eta())<=3.0) { /// 2.7 < |eta| < 3.0
            if(jet.neutralMultiplicity()<=2) return false;
        }
        else{ /// |eta| > 3.0
           if(jet.neutralMultiplicity()<=10) return false;
        }
    }

    return true;
}


bool RecoStudiesCalo::passIDWP(std::string WP, bool isEB, float dEtaIn, float dPhiIn, float full5x5, float hoe, float d0, float dz, float ooemoop, bool conv, int missHits){
  bool pass = false;

  if(WP == "VETO"){
    if(isEB){
      pass = (fabs(dEtaIn) <  0.0126 ) && (fabs(dPhiIn) <  0.107 ) && (full5x5 < 0.012 ) && (hoe <  0.186 ) && (fabs(d0) < 0.0621 ) && (fabs(dz) <  0.613 ) && (fabs(ooemoop) <  0.239 ) && !conv && (missHits <= 2);
    }
    else{
      pass = (fabs(dEtaIn) <  0.0109 ) && (fabs(dPhiIn) <  0.219 ) && (full5x5 < 0.0339 ) && (hoe <  0.0962 ) && (fabs(d0) < 0.279 ) && (fabs(dz) < 0.947 ) && (fabs(ooemoop) < 0.141 ) && !conv && (missHits <= 3);
    }
  }
  if(WP == "LOOSE"){
    if(isEB){
      pass = (fabs(dEtaIn) < 0.00976 ) && (fabs(dPhiIn) < 0.0929 ) && (full5x5 <  0.0105 ) && (hoe < 0.0765 ) && (fabs(d0) < 0.0227 ) && (fabs(dz) < 0.379 ) && (fabs(ooemoop) <  0.184 ) && !conv && (missHits <= 2);
    }
    else{
      pass = (fabs(dEtaIn) < 0.00952 ) && (fabs(dPhiIn) < 0.181 ) && (full5x5 < 0.0318 ) && (hoe < 0.0824 ) && (fabs(d0) < 0.242 ) && (fabs(dz) < 0.921 ) && (fabs(ooemoop) < 0.125 ) && !conv && (missHits <= 1);
    }
  }

  if(WP == "MEDIUM"){
    if(isEB){
      pass = (fabs(dEtaIn) <  0.0094 ) && (fabs(dPhiIn) <  0.0296 ) && (full5x5 <  0.0101 ) && (hoe <  0.0372 ) && (fabs(d0) <  0.0151 ) && (fabs(dz) <  0.238 ) && (fabs(ooemoop) <  0.118 ) && !conv && (missHits <= 2);
    }
    else{
      pass = (fabs(dEtaIn) <  0.00773 ) && (fabs(dPhiIn) <  0.148 ) && (full5x5 <  0.0287 ) && (hoe <  0.0546 ) && (fabs(d0) <  0.0535 ) && (fabs(dz) <  0.572 ) && (fabs(ooemoop) <  0.104 ) && !conv && (missHits <= 1);
    }
  }

  if(WP == "TIGHT"){
    if(isEB){
      pass = (fabs(dEtaIn) <  0.0095 ) && (fabs(dPhiIn) <  0.0291 ) && (full5x5 <  0.0101 ) && (hoe <  0.0372 ) && (fabs(d0) <  0.0144 ) && (fabs(dz) <  0.323 ) && (fabs(ooemoop) <  0.0174 ) && !conv && (missHits <= 2);
    }
    else{
      pass = (fabs(dEtaIn) <  0.00762 ) && (fabs(dPhiIn) <  0.0439 ) && (full5x5 <  0.0287 ) && (hoe <  0.0544 ) && (fabs(d0) <  0.0377 ) && (fabs(dz) <  0.571 ) && (fabs(ooemoop) <  0.01 ) && !conv && (missHits <= 1);
    }
  }
  return pass;
}


//define this as a plug-in
DEFINE_FWK_MODULE(RecoStudiesCalo);

