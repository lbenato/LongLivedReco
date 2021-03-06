// -*- C++ -*-
//
// Package:    Analyzer/LongLivedReco
// Class:      RecoStudiesAK8
// 
/**\class RecoStudiesAK8 RecoStudiesAK8.cc Analyzer/LongLivedReco/plugins/RecoStudiesAK8.cc

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

class RecoStudiesAK8 : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit RecoStudiesAK8(const edm::ParameterSet&);
      //RecoStudiesAK8(const edm::ParameterSet&, edm::ConsumesCollector&&);
      ~RecoStudiesAK8();

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
    edm::EDGetTokenT<pat::METCollection> metToken;
    edm::EDGetTokenT<pat::JetCollection> jetToken;
    edm::EDGetTokenT<pat::JetCollection> fatjetToken;
    edm::EDGetTokenT<pat::MuonCollection> muonToken;
    edm::EDGetTokenT<reco::VertexCollection> vertexToken;
    edm::EDGetTokenT<pat::ElectronCollection> electronToken;
    edm::EDGetTokenT<reco::Jet> recoJetToken;
    //edm::EDGetToken token_tipo;
    //const edm::TypeID tipo;
    edm::ParameterSet GenPSet;
    edm::ParameterSet CHSFatJetPSet;
    edm::ParameterSet FatJetPSet;
    //edm::ParameterSet RecoJetPSet;
    //std::string JerName_res;

    JetAnalyzer* theCHSFatJetAnalyzer;
    JetAnalyzer* theFatJetAnalyzer;
    GenAnalyzer* theGenAnalyzer;

    //int WriteNElectrons, WriteNMuons, WriteNLeptons, WriteNTaus, WriteNPhotons, WriteNFatJets;
    int WriteNFatJets, WriteNGenBquarks, WriteNGenLongLiveds;

    std::vector<CustomFatJetType> FatJets;
    std::vector<FatJetType> CHSFatJets;
    std::vector<GenPType> GenBquarks;
    std::vector<GenPType> GenLongLiveds;

    TTree* tree;
    bool isVerbose;
    bool isMC;
    long int EventNumber, LumiNumber, RunNumber, nPV;
    //float muon1_pt, muon1_pfIso04, electron1_pt, fatjet1_pt, jet1_pt;
    //float met_pt, met_pt_nomu_L, met_pt_nomu_T, m_ht, m_ht_nomu_L, m_ht_nomu_T, min_met_mht, min_met_mht_nomu_L, min_met_mht_nomu_T, met_phi, met_phi_nomu_L, met_phi_nomu_T;
    //bool fatjet1_isLoose, fatjet1_isTight, muon1_isLoose, muon1_isTight;
    //long int nTightMuons, nTightElectrons, nTightFatJets, nLooseMuons, nLooseElectrons, nLooseFatJets;
    long int nLooseFatJets, nTightFatJets, nFatJets, nLooseCHSFatJets, nTightCHSFatJets, nCHSFatJets, nGenBquarks, nGenLL;
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

    TH1F* Matching_to_b_AK4Jets;
    TH1F* Matching_to_b_CHSAK4Jets;
    TH1F* Matching_to_b_AK4Jets_simplified;
    TH1F* Matching_to_b_CHSAK4Jets_simplified;

    TH1F* Matching_to_pi_AK4Jets;
    TH1F* Matching_to_pi_CHSAK4Jets;

    TH1F* Matching_to_b_AK8Jets;
    TH1F* Matching_to_b_CHSAK8Jets;
    TH1F* Matching_to_b_AK8Jets_simplified;
    TH1F* Matching_to_b_CHSAK8Jets_simplified;

    TH1F* Matching_to_pi_AK8Jets;
    TH1F* Matching_to_pi_CHSAK8Jets;

    TH1F* Matching_to_b_AK8Jets_sj1;
    TH1F* Matching_to_b_CHSAK8Jets_sj1;
    TH1F* Matching_to_pi_AK8Jets_sj1;
    TH1F* Matching_to_pi_CHSAK8Jets_sj1;
    TH1F* Matching_to_b_AK8Jets_sj2;
    TH1F* Matching_to_b_CHSAK8Jets_sj2;
    TH1F* Matching_to_pi_AK8Jets_sj2;
    TH1F* Matching_to_pi_CHSAK8Jets_sj2;

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
//RecoStudiesAK8::RecoStudiesAK8(const edm::ParameterSet& iConfig, edm::ConsumesCollector&& CColl):
RecoStudiesAK8::RecoStudiesAK8(const edm::ParameterSet& iConfig):
    GenPSet(iConfig.getParameter<edm::ParameterSet>("genSet")),
    CHSFatJetPSet(iConfig.getParameter<edm::ParameterSet>("chsFatJetSet")),
    FatJetPSet(iConfig.getParameter<edm::ParameterSet>("fatJetSet")),
    WriteNFatJets(iConfig.getParameter<int>("writeNFatJets")),
    WriteNGenBquarks(iConfig.getParameter<int>("writeNGenBquarks")),
    WriteNGenLongLiveds(iConfig.getParameter<int>("writeNGenLongLiveds")),
    isVerbose(iConfig.getParameter<bool> ("verbose"))

{
    //Initalize objects
    theCHSFatJetAnalyzer      = new JetAnalyzer(CHSFatJetPSet, consumesCollector());
    theFatJetAnalyzer      = new JetAnalyzer(FatJetPSet, consumesCollector());
    theGenAnalyzer      = new GenAnalyzer(GenPSet, consumesCollector());


    //Input tags
    edm::InputTag IT_trigResults = edm::InputTag("TriggerResults::HLT");
    trigResultsToken= consumes<edm::TriggerResults>(IT_trigResults);
    edm::InputTag IT_filterResults = edm::InputTag("TriggerResults::RECO");
    filterResultsToken= consumes<edm::TriggerResults>(IT_filterResults);

    edm::InputTag IT_badChCandFilter = edm::InputTag("BadChargedCandidateFilter");
    badChCandFilterToken= consumes<bool>(IT_badChCandFilter);
    edm::InputTag IT_badPFMuonFilter = edm::InputTag("BadPFMuonFilter");
    badPFMuonFilterToken= consumes<bool>(IT_badPFMuonFilter);

    if(isVerbose) std::cout << "CONSTRUCTOR" << std::endl;

    //now do what ever initialization is needed
    usesResource("TFileService");

    edm::Service<TFileService> fs;

    //Tree branches
    tree = fs->make<TTree>("tree", "tree");
    tree -> Branch("isMC" , &isMC, "isMC/O");
    tree -> Branch("EventNumber" , &EventNumber , "EventNumber/L");
    tree -> Branch("LumiNumber" , &LumiNumber , "LumiNumber/L");
    tree -> Branch("RunNumber" , &RunNumber , "RunNumber/L");
    //tree -> Branch("nPV" , &nPV , "nPV/L");
    //tree -> Branch("nLooseMuons" , &nLooseMuons , "nLooseMuons/L");
    //tree -> Branch("nLooseElectrons" , &nLooseElectrons , "nLooseElectrons/L");
    //tree -> Branch("nLooseFatJets" , &nLooseFatJets , "nLooseFatJets/L");
    tree -> Branch("nGenBquarks" , &nGenBquarks , "nGenBquarks/L");
    tree -> Branch("nGenLL" , &nGenLL , "nGenLL/L");
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

    //Histograms
    Matching_to_b_AK4Jets = fs->make<TH1F>("Matching_to_b_AK4Jets", "Matching_to_b_AK4Jets", 10,0,10);
    Matching_to_b_CHSAK4Jets = fs->make<TH1F>("Matching_to_b_CHSAK4Jets", "Matching_to_b_CHSAK4Jets", 10,0,10);
    Matching_to_b_AK4Jets_simplified = fs->make<TH1F>("Matching_to_b_AK4Jets_simplified", "Matching_to_b_AK4Jets_simplified", 4,0,4);
    Matching_to_b_CHSAK4Jets_simplified = fs->make<TH1F>("Matching_to_b_CHSAK4Jets_simplified", "Matching_to_b_CHSAK4Jets_simplified", 4,0,4);
    Matching_to_pi_AK4Jets = fs->make<TH1F>("Matching_to_pi_AK4Jets", "Matching_to_pi_AK4Jets", 10,0,10);
    Matching_to_pi_CHSAK4Jets = fs->make<TH1F>("Matching_to_pi_CHSAK4Jets", "Matching_to_pi_CHSAK4Jets", 10,0,10);

    Matching_to_b_AK8Jets = fs->make<TH1F>("Matching_to_b_AK8Jets", "Matching_to_b_AK8Jets", 10,0,10);
    Matching_to_b_CHSAK8Jets = fs->make<TH1F>("Matching_to_b_CHSAK8Jets", "Matching_to_b_CHSAK8Jets", 10,0,10);
    Matching_to_b_AK8Jets_simplified = fs->make<TH1F>("Matching_to_b_AK8Jets_simplified", "Matching_to_b_AK8Jets_simplified", 4,0,4);
    Matching_to_b_CHSAK8Jets_simplified = fs->make<TH1F>("Matching_to_b_CHSAK8Jets_simplified", "Matching_to_b_CHSAK8Jets_simplified", 4,0,4);
    Matching_to_pi_AK8Jets = fs->make<TH1F>("Matching_to_pi_AK8Jets", "Matching_to_pi_AK8Jets", 10,0,10);
    Matching_to_pi_CHSAK8Jets = fs->make<TH1F>("Matching_to_pi_CHSAK8Jets", "Matching_to_pi_CHSAK8Jets", 10,0,10);

    Matching_to_b_AK8Jets_sj1 = fs->make<TH1F>("Matching_to_b_AK8Jets_sj1", "Matching_to_b_AK8Jets_sj1", 10,0,10);
    Matching_to_b_CHSAK8Jets_sj1 = fs->make<TH1F>("Matching_to_b_CHSAK8Jets_sj1", "Matching_to_b_CHSAK8Jets_sj1", 10,0,10);
    Matching_to_pi_AK8Jets_sj1 = fs->make<TH1F>("Matching_to_pi_AK8Jets_sj1", "Matching_to_pi_AK8Jets_sj1", 10,0,10);
    Matching_to_pi_CHSAK8Jets_sj1 = fs->make<TH1F>("Matching_to_pi_CHSAK8Jets_sj1", "Matching_to_pi_CHSAK8Jets_sj1", 10,0,10);
    Matching_to_b_AK8Jets_sj2 = fs->make<TH1F>("Matching_to_b_AK8Jets_sj2", "Matching_to_b_AK8Jets_sj2", 10,0,10);
    Matching_to_b_CHSAK8Jets_sj2 = fs->make<TH1F>("Matching_to_b_CHSAK8Jets_sj2", "Matching_to_b_CHSAK8Jets_sj2", 10,0,10);
    Matching_to_pi_AK8Jets_sj2 = fs->make<TH1F>("Matching_to_pi_AK8Jets_sj2", "Matching_to_pi_AK8Jets_sj2", 10,0,10);
    Matching_to_pi_CHSAK8Jets_sj2 = fs->make<TH1F>("Matching_to_pi_CHSAK8Jets_sj2", "Matching_to_pi_CHSAK8Jets_sj2", 10,0,10);

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


RecoStudiesAK8::~RecoStudiesAK8()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
    if(isVerbose) std::cout << "---------- ENDING  ----------" << std::endl;

    delete theCHSFatJetAnalyzer;
    delete theFatJetAnalyzer;
    delete theGenAnalyzer;
}


//
// member functions
//

// ------------ method called for each event  ------------
void
RecoStudiesAK8::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;
    using namespace reco;
    using namespace std;

    // Initialize types
    for(int i = 0; i < WriteNFatJets; i++) ObjectsFormat::ResetCustomFatJetType(FatJets[i]);//??
    for(int i = 0; i < WriteNFatJets; i++) ObjectsFormat::ResetFatJetType(CHSFatJets[i]);//??
    for(int i = 0; i < WriteNGenBquarks; i++) ObjectsFormat::ResetGenPType(GenBquarks[i]);
    for(int i = 0; i < WriteNGenLongLiveds; i++) ObjectsFormat::ResetGenPType(GenLongLiveds[i]);

    isMC = false;
    EventNumber = LumiNumber = RunNumber = nPV = 0;
    nFatJets = nLooseFatJets = nTightFatJets = nCHSFatJets = nLooseCHSFatJets = nTightCHSFatJets = nGenBquarks = nGenLL = 0;

    
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

    //Initialize met no mu
    //float met_pt_nomu_x_L(0.), met_pt_nomu_y_L(0.), met_pt_nomu_x_T(0.), met_pt_nomu_y_T(0.);


    // Gen particles
    std::vector<reco::GenParticle> GenLongLivedVect = theGenAnalyzer->FillGenVectorByIdAndStatus(iEvent,9000006,22);
    nGenLL = GenLongLivedVect.size();
    std::vector<reco::GenParticle> GenBquarksVect;
    if(nGenLL>0)
      {
	GenBquarksVect = theGenAnalyzer->FillGenVectorByIdStatusAndMother(iEvent,5,23,9000006);
      }
    else
      {
	GenBquarksVect = theGenAnalyzer->FillGenVectorByIdAndStatus(iEvent,5,23);
      }
    //std::vector<reco::GenParticle> GenBquarksVect = theGenAnalyzer->FillGenVectorByIdAndStatus(iEvent,5,23);
    nGenBquarks = GenBquarksVect.size();
    //std::vector<reco::GenParticle> GenBquarksFromLLVect = theGenAnalyzer->FillGenVectorByIdStatusAndMother(iEvent,5,23,9000006);

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

    // Jets
    std::vector<pat::Jet> CHSFatJetsVect = theCHSFatJetAnalyzer->FillJetVector(iEvent);
    std::vector<pat::Jet> FatJetsVect = theFatJetAnalyzer->FillJetVector(iEvent);
    nFatJets = FatJetsVect.size();
    nCHSFatJets = CHSFatJetsVect.size();

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
	Matching_to_b_AK8Jets->Fill(n_b_matched);
	Matching_to_b_AK8Jets_sj1->Fill(n_b_matched_sj1);
	Matching_to_b_AK8Jets_sj2->Fill(n_b_matched_sj2);

	if(n_b_matched==0)
	  {
	    Matching_to_b_AK8Jets_simplified->Fill(0);
	    //CSV_AK8Jets_matched_to_0b->Fill(JetsVect[a].bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
	    //pT_AK8Jets_matched_to_0b->Fill(JetsVect[a].pt());
	  }
	else if(n_b_matched==1)
	  {
	    Matching_to_b_AK8Jets_simplified->Fill(1);
	    //CSV_AK8Jets_matched_to_1b->Fill(JetsVect[a].bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
	    //pT_AK8Jets_matched_to_1b->Fill(JetsVect[a].pt());
	  }
	else if(n_b_matched==2)
	  {
	    Matching_to_b_AK8Jets_simplified->Fill(2);
	    //CSV_AK8Jets_matched_to_2b->Fill(JetsVect[a].bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
	    //pT_AK8Jets_matched_to_2b->Fill(JetsVect[a].pt());
	  }
	else
	  {
	    Matching_to_b_AK8Jets_simplified->Fill(3);
	    //CSV_AK8Jets_matched_to_more_2b->Fill(JetsVect[a].bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
	    //pT_AK8Jets_matched_to_more_2b->Fill(JetsVect[a].pt());
	  }
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
	Matching_to_pi_AK8Jets->Fill(n_pi_matched);
	Matching_to_pi_AK8Jets_sj1->Fill(n_pi_matched_sj1);
	Matching_to_pi_AK8Jets_sj2->Fill(n_pi_matched_sj2);

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

	/*
	//Matching to b quarks of CHSAK8Jets
	int n_b_matched_chs = 0;
	for(unsigned int b = 0; b<GenBquarksVect.size(); b++) {
  	    if(fabs(reco::deltaR(CHSJetsVect[a].eta(),CHSJetsVect[a].phi(),GenBquarksVect[b].eta(),GenBquarksVect[b].phi()))<0.8) n_b_matched_chs++;
	}
	CHSJetsVect[a].addUserInt("hasMatchedBquarks",n_b_matched_chs);
	Matching_to_b_CHSAK8Jets->Fill(n_b_matched_chs);
	if(n_b_matched_chs==0)
	  {
	    Matching_to_b_CHSAK8Jets_simplified->Fill(0);
	    CSV_CHSAK8Jets_matched_to_0b->Fill(CHSJetsVect[a].bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
	    pT_CHSAK8Jets_matched_to_0b->Fill(CHSJetsVect[a].pt());
	  }
	else if(n_b_matched_chs==1)
	  {
	    Matching_to_b_CHSAK8Jets_simplified->Fill(1);
	    CSV_CHSAK8Jets_matched_to_1b->Fill(CHSJetsVect[a].bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
	    pT_CHSAK8Jets_matched_to_1b->Fill(CHSJetsVect[a].pt());
	  }
	else if(n_b_matched_chs==2)
	  {
	    Matching_to_b_CHSAK8Jets_simplified->Fill(2);
	    CSV_CHSAK8Jets_matched_to_2b->Fill(CHSJetsVect[a].bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
	    pT_CHSAK8Jets_matched_to_2b->Fill(CHSJetsVect[a].pt());
	  }
	else
	  {
	    Matching_to_b_CHSAK8Jets_simplified->Fill(3);
	    CSV_CHSAK8Jets_matched_to_more_2b->Fill(CHSJetsVect[a].bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
	    pT_CHSAK8Jets_matched_to_more_2b->Fill(CHSJetsVect[a].pt());
	  }

	//Matching to dark pions of CHSAK8Jets
	int n_pi_matched_chs = 0;
	for(unsigned int pi = 0; pi<GenLongLivedVect.size(); pi++) {
  	    if(fabs(reco::deltaR(CHSJetsVect[a].eta(),CHSJetsVect[a].phi(),GenLongLivedVect[pi].eta(),GenLongLivedVect[pi].phi()))<0.8) n_pi_matched_chs++;
	}
	CHSJetsVect[a].addUserInt("hasMatchedLL",n_pi_matched_chs);
	Matching_to_pi_CHSAK8Jets->Fill(n_pi_matched_chs);
	if(n_pi_matched_chs==0)
	  {
	    CSV_CHSAK8Jets_matched_to_0pi->Fill(CHSJetsVect[a].bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
	    pT_CHSAK8Jets_matched_to_0pi->Fill(CHSJetsVect[a].pt());
	  }
	else if(n_pi_matched_chs==1)
	  {
	    CSV_CHSAK8Jets_matched_to_1pi->Fill(CHSJetsVect[a].bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
	    pT_CHSAK8Jets_matched_to_1pi->Fill(CHSJetsVect[a].pt());
	  }
	else if(n_pi_matched_chs==2)
	  {
	    CSV_CHSAK8Jets_matched_to_2pi->Fill(CHSJetsVect[a].bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
	    pT_CHSAK8Jets_matched_to_2pi->Fill(CHSJetsVect[a].pt());
	  }

	//std::cout<<"jet n. " << a << " has " << n_b_matched << " matched b quarks" << std::endl;
	*/
    }


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
      //std::cout << "number of CHS AK4 jets:  " << CHSJetsVect.size() << std::endl;
      //for(unsigned int i = 0; i < CHSJetsVect.size(); i++) std::cout << "  CHS AK4 jet  [" << i << "]\tpt: " << CHSJetsVect[i].pt() << "\teta: " << CHSJetsVect[i].eta() << "\tphi: " << CHSJetsVect[i].phi() << "\tmass: " << CHSJetsVect[i].mass() << std::endl;
      //std::cout << "number of AK4 jets:  " << JetsVect.size() << std::endl;
      //for(unsigned int i = 0; i < JetsVect.size(); i++) std::cout << "  AK4 jet  [" << i << "]\tpt: " << JetsVect[i].pt() << "\teta: " << JetsVect[i].eta() << "\tphi: " << JetsVect[i].phi() << "\tmass: " << JetsVect[i].mass() << std::endl;
      //std::cout << "number of Gen B quarks:  " << GenBquarksVect.size() << std::endl;
      //for(unsigned int i = 0; i < GenBquarksVect.size(); i++) std::cout << "  Gen B quark  [" << i << "]\tpt: " << GenBquarksVect[i].pt() << "\teta: " << GenBquarksVect[i].eta() << "\tphi: " << GenBquarksVect[i].phi() << "\tmass: " << GenBquarksVect[i].mass() << std::endl;
      std::cout << "number of AK8 jets:  " << FatJetsVect.size() << std::endl;
      for(unsigned int i = 0; i < FatJetsVect.size(); i++) std::cout << "  AK8 jet  [" << i << "]\tpt: " << FatJetsVect[i].pt() << "\teta: " << FatJetsVect[i].eta() << "\tphi: " << FatJetsVect[i].phi() << "\tmass: " << FatJetsVect[i].mass() << std::endl;
      std::cout << "number of CHS AK8 jets:  " << CHSFatJetsVect.size() << std::endl;
      for(unsigned int i = 0; i < CHSFatJetsVect.size(); i++) std::cout << "  AK8 jet  [" << i << "]\tpt: " << CHSFatJetsVect[i].pt() << "\teta: " << CHSFatJetsVect[i].eta() << "\tphi: " << CHSFatJetsVect[i].phi() << "\tmass: " << CHSFatJetsVect[i].mass() << std::endl;
      //std::cout << "Missing energy:      " << MET.pt() << std::endl;
      //std::cout << "V leptonic mass:     " << theV.mass() << std::endl;
    }


    // ---------- Fill objects ----------

    if(isVerbose) std::cout << " - Filling objects" << std::endl;

    for(unsigned int i = 0; i < FatJets.size() && i < FatJetsVect.size(); i++) ObjectsFormat::FillCustomFatJetType(FatJets[i], &FatJetsVect[i], isMC);//??
    for(unsigned int i = 0; i < CHSFatJets.size() && i < CHSFatJetsVect.size(); i++) ObjectsFormat::FillFatJetType(CHSFatJets[i], &CHSFatJetsVect[i], isMC);//??
    for(unsigned int i = 0; i < GenBquarks.size() && i < GenBquarksVect.size(); i++) ObjectsFormat::FillGenPType(GenBquarks[i], &GenBquarksVect[i]);
    for(unsigned int i = 0; i < GenLongLiveds.size() && i < GenLongLivedVect.size(); i++) ObjectsFormat::FillGenPType(GenLongLiveds[i], &GenLongLivedVect[i]);

    tree -> Fill();




}


// ------------ method called once each job just before starting event loop  ------------
void 
RecoStudiesAK8::beginJob()
{
    for(int i = 0; i < WriteNFatJets; i++) FatJets.push_back( CustomFatJetType() );//??
    for(int i = 0; i < WriteNFatJets; i++) CHSFatJets.push_back( FatJetType() );//??
    for(int i = 0; i < WriteNGenBquarks; i++) GenBquarks.push_back( GenPType() );
    for(int i = 0; i < WriteNGenLongLiveds; i++) GenLongLiveds.push_back( GenPType() );

    //Set branches for objects
    for(int i = 0; i < WriteNFatJets; i++) tree->Branch(("FatJet"+std::to_string(i+1)).c_str(), &(FatJets[i].pt), ObjectsFormat::ListCustomFatJetType().c_str());//??
    for(int i = 0; i < WriteNFatJets; i++) tree->Branch(("CHSFatJet"+std::to_string(i+1)).c_str(), &(CHSFatJets[i].pt), ObjectsFormat::ListFatJetType().c_str());//??
    for(int i = 0; i < WriteNGenBquarks; i++) tree->Branch(("GenBquark"+std::to_string(i+1)).c_str(), &(GenBquarks[i].pt), ObjectsFormat::ListGenPType().c_str());
    for(int i = 0; i < WriteNGenLongLiveds; i++) tree->Branch(("GenLongLived"+std::to_string(i+1)).c_str(), &(GenLongLiveds[i].pt), ObjectsFormat::ListGenPType().c_str());
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RecoStudiesAK8::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
RecoStudiesAK8::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}


//Method to define loose jet ID (2016 data)
bool RecoStudiesAK8::isLooseJet(pat::Jet& jet){
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
bool RecoStudiesAK8::isTightJet(pat::Jet& jet){
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


bool RecoStudiesAK8::passIDWP(std::string WP, bool isEB, float dEtaIn, float dPhiIn, float full5x5, float hoe, float d0, float dz, float ooemoop, bool conv, int missHits){
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
DEFINE_FWK_MODULE(RecoStudiesAK8);

