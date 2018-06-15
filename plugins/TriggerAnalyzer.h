#ifndef TRIGGERANALYZER_H
#define TRIGGERANALYZER_H

#include <iostream>
#include <cmath>
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EDConsumerBase.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"

#include "TFile.h"
#include "TH3.h"
#include "TKey.h"

class TriggerAnalyzer {
    public:
        TriggerAnalyzer(edm::ParameterSet&, edm::ConsumesCollector&&);
        ~TriggerAnalyzer();
        
        virtual void FillTriggerMap(const edm::Event&, std::map<std::string, bool>&, std::map<std::string, int>&, bool&);
        virtual void FillMetFiltersMap(const edm::Event&, std::map<std::string, bool>&);//, edm::EDGetTokenT<edm::TriggerResults>&, std::vector<std::string>&);
	virtual bool GetBadPFMuonFlag(const edm::Event&);
	virtual bool GetBadChCandFlag(const edm::Event&);
      
    private:
    
        edm::EDGetTokenT<edm::TriggerResults> TriggerToken;
        std::vector<std::string> TriggerList;
        edm::EDGetTokenT<edm::TriggerResults> MetFiltersToken;
        std::vector<std::string> MetFiltersList;
	edm::EDGetTokenT<pat::PackedTriggerPrescales> PrescalesToken;
	edm::EDGetTokenT<pat::PackedTriggerPrescales> L1MinPrescalesToken;
	edm::EDGetTokenT<pat::PackedTriggerPrescales> L1MaxPrescalesToken;
	edm::EDGetTokenT<bool> BadPFMuonFilterToken;
	edm::EDGetTokenT<bool> BadChCandFilterToken;
};


#endif
