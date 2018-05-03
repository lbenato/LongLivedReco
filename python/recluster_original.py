import FWCore.ParameterSet.Config as cms

from FWCore.ParameterSet.VarParsing import VarParsing

process = cms.Process("USER")

process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag (process.GlobalTag, 'auto:run2_mc')

## Events to process
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(4) )

## Input files
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        #'/store/relval/CMSSW_7_4_1/RelValTTbar_13/MINIAODSIM/PU50ns_MCRUN2_74_V8_gensim_740pre7-v1/00000/7EC72BA9-44EC-E411-9DF3-0025905A60B0.root'
        '/store/user/lbenato/VBFH_HToSSTobbbb_MH-125_MS-40_ctauS-1_Summer16_MINIAOD/VBFH_HToSSTobbbb_MH-125_MS-40_ctauS-1_TuneCUETP8M1_13TeV-powheg-pythia8_PRIVATE-MC/RunIISummer16-PU_standard_mixing-Moriond17_80X_mcRun2_2016_MINIAOD/180201_104029/0000/miniaod_VBFH_SS_m40_ctau1_1.root'
    )
)


#################################################
## Remake jets
#################################################

## Filter out neutrinos from packed GenParticles
process.packedGenParticlesForJetsNoNu = cms.EDFilter("CandPtrSelector", src = cms.InputTag("packedGenParticles"), cut = cms.string("abs(pdgId) != 12 && abs(pdgId) != 14 && abs(pdgId) != 16"))
## Define GenJets
from RecoJets.JetProducers.ak4GenJets_cfi import ak4GenJets
process.ak4GenJetsNoNu = ak4GenJets.clone(src = 'packedGenParticlesForJetsNoNu')

## Select charged hadron subtracted packed PF candidates
process.pfCHS = cms.EDFilter("CandPtrSelector", src = cms.InputTag("packedPFCandidates"), cut = cms.string("fromPV"))


#according to https://cmssdt.cern.ch/lxr/source/PhysicsTools/PatAlgos/test/miniAOD/example_ei.py?%21v=CMSSW_8_0_28
#process.selectedMuons = cms.EDFilter("CandPtrSelector", src = cms.InputTag("slimmedMuons"), cut = cms.string('''abs(eta)<2.5 && pt>10. &&
#   (pfIsolationR04().sumChargedHadronPt+
#    max(0.,pfIsolationR04().sumNeutralHadronEt+
#    pfIsolationR04().sumPhotonEt-
#    0.50*pfIsolationR04().sumPUPt))/pt < 0.20 && 
#    (isPFMuon && (isGlobalMuon || isTrackerMuon) )'''))
#process.selectedElectrons = cms.EDFilter("CandPtrSelector", src = cms.InputTag("slimmedElectrons"), cut = cms.string('''abs(eta)<2.5 && pt>20. &&
#    gsfTrack.isAvailable() &&
#    gsfTrack.hitPattern().numberOfLostHits(\'MISSING_INNER_HITS\') < 2 &&
#    (pfIsolationVariables().sumChargedHadronPt+
#    max(0.,pfIsolationVariables().sumNeutralHadronEt+
#    pfIsolationVariables().sumPhotonEt-
#    0.5*pfIsolationVariables().sumPUPt))/pt < 0.15'''))

#process.pfNoMuon =  cms.EDProducer("CandPtrProjector", src = cms.InputTag("packedPFCandidates"), veto = cms.InputTag("selectedMuons"))
#process.pfNoElectrons = cms.EDProducer("CandPtrProjector", src = cms.InputTag("pfNoMuon"), veto =  cms.InputTag("selectedElectrons"))


from RecoJets.JetProducers.ak4PFJets_cfi import ak4PFJets
## Define PFJetsCHS
process.ak4PFJetsCHS = ak4PFJets.clone(src = 'pfCHS', doAreaFastjet = True)
#according to https://cmssdt.cern.ch/lxr/source/PhysicsTools/PatAlgos/test/miniAOD/example_ei.py?%21v=CMSSW_8_0_28
#process.ak4PFJets = ak4PFJets.clone(src = 'pfNoElectrons', doAreaFastjet = True)#or packedPFCandidates???
#?#
process.ak4PFJets = ak4PFJets.clone(src = 'packedPFCandidates', doAreaFastjet = True)

#################################################
## Remake PAT jets
#################################################

## b-tag discriminators
bTagDiscriminators = [
    'pfCombinedInclusiveSecondaryVertexV2BJetTags'
]

from PhysicsTools.PatAlgos.tools.jetTools import *
## Add PAT jet collection based on the above-defined ak4PFJetsCHS
addJetCollection(
    process,
    labelName = 'AK4PFCHS',
    jetSource = cms.InputTag('ak4PFJetsCHS'),
    pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
    pfCandidates = cms.InputTag('packedPFCandidates'),
    svSource = cms.InputTag('slimmedSecondaryVertices'),
    btagDiscriminators = bTagDiscriminators,
    jetCorrections = ('AK4PFchs', ['L1FastJet', 'L2Relative', 'L3Absolute'], 'None'),
    genJetCollection = cms.InputTag('ak4GenJetsNoNu'),
    genParticles = cms.InputTag('prunedGenParticles'),
    algo = 'AK',
    rParam = 0.4
)
addJetCollection(
    process,
    labelName = 'AK4PF',
    jetSource = cms.InputTag('ak4PFJets'),
    pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
    pfCandidates = cms.InputTag('packedPFCandidates'),
    svSource = cms.InputTag('slimmedSecondaryVertices'),
    btagDiscriminators = bTagDiscriminators,
    jetCorrections = ('AK4PF', ['L1FastJet', 'L2Relative', 'L3Absolute'], 'None'),
    genJetCollection = cms.InputTag('ak4GenJetsNoNu'),
    genParticles = cms.InputTag('prunedGenParticles'),
    algo = 'AK',
    rParam = 0.4
)

pp = process.patJetsAK4PF

print pp

from RecoJets.JetProducers.PileupJetID_cfi import *
from RecoJets.JetProducers.PileupJetIDParams_cfi import *

#process.load('RecoJets.JetProducers.PileupJetID_cfi')#broken, if loaded as it is it does not recognize offlinePrimaryVertices in pileupJetIdProducer. Re-calling it manually

_stdalgos_4x = cms.VPSet(full,   cutbased,PhilV1)
_stdalgos_5x = cms.VPSet(full_53x,cutbased,PhilV1)

_chsalgos_4x = cms.VPSet(full,   cutbased)
_chsalgos_5x = cms.VPSet(full_53x_chs,cutbased)
_chsalgos = _chsalgos_5x

import os
try:
    cmssw_version = os.environ["CMSSW_VERSION"].replace("CMSSW_","")
except:
    cmssw_version = "5_X"

if cmssw_version.startswith("4"):
    _stdalgos    = _stdalgos_4x
    _chsalgos    = _chsalgos_4x
else:
    _stdalgos    = _stdalgos_5x
_chsalgos = _chsalgos_5x

pileupJetIdProducer = cms.EDProducer('PileupJetIdProducer',
                         produceJetIds = cms.bool(True),
                         jetids = cms.InputTag(""),
                         runMvas = cms.bool(True),
                         jets = cms.InputTag("patJetsAK4PF"),
                         vertexes = cms.InputTag("offlineSlimmedPrimaryVertices"),
                         algos = cms.VPSet(_stdalgos),                                    
                         rho     = cms.InputTag("kt6PFJets","rho"),
                         jec     = cms.string("AK4PF"),
                         applyJec = cms.bool(False),
                         inputIsCorrected = cms.bool(True),                                     
                         residualsFromTxt = cms.bool(False),
                         residualsTxt     = cms.string("dummy.txt"),#FileInPath moved to string, otherwise it is broken, it cannot find residualsTxt and if I manually impose the directory still broken, cannot be left empty

)


##This does not work: https://cmssdt.cern.ch/lxr/source/RecoJets/JetProducers/test/testJetTools_onMiniAOD_cfg.py?%21v=CMSSW_9_4_0
process.myPUID = pileupJetIdProducer.clone(vertexes=cms.InputTag("offlineSlimmedPrimaryVertices"), jets=cms.InputTag("patJetsAK4PF"))

from RecoJets.JetProducers.pileupjetidproducer_cfi import pileupJetIdCalculator,pileupJetIdEvaluator
setattr(process,'patJetsAK4PFpileupJetIdCalculator',
        pileupJetIdCalculator.clone(
        jets = cms.InputTag("patJetsAK4PF"),
        rho = cms.InputTag("fixedGridRhoFastjetAll"),
        vertexes = cms.InputTag("offlineSlimmedPrimaryVertices"),
        applyJec = cms.bool(True),
        inputIsCorrected = cms.bool(True)
        ))

setattr(process,'patJetsAK4PFpileupJetIdEvaluator',
        pileupJetIdEvaluator.clone(
        jets = cms.InputTag("patJetsAK4PF"),
        jetids = cms.InputTag("patJetsAK4PFpileupJetIdCalculator"),
        rho = cms.InputTag("fixedGridRhoFastjetAll"),
        vertexes = cms.InputTag("offlineSlimmedPrimaryVertices"),
        ))


#In that way it does not recognize the token because apparently the producer has not run yet, even if included in the sequence. But I cannot do according to https://cmssdt.cern.ch/lxr/source/RecoJets/JetProducers/test/testJetTools_onMiniAOD_cfg.py?%21v=CMSSW_9_4_0 because patAlgosToolsTask.add(process.pileUpJetIDTask) does not work
#pp.userData.userFloats.src += ['pileupJetIdEvaluator:fullDiscriminant']
#pp.userData.userInts.src += ['pileupJetIdEvaluator:cutbasedId','pileupJetIdEvaluator:fullId']
#process.OUT.outputCommands += ['keep *_pileupJetIdEvaluator_*_*']

#process.load('RecoJets.JetProducers.QGTagger_cfi')
#process.ak4PFJets.userData.userFloats.src += ['QGTagger:qgLikelihood']
#process.OUT.outputCommands += ['keep *_QGTagger_*_*']

getattr(process,'selectedPatJetsAK4PFCHS').cut = cms.string('pt > 10')


process.seq = cms.Sequence(
    process.ak4PFJets *
    process.myPUID *
    process.patJetsAK4PFpileupJetIdCalculator *
    process.patJetsAK4PFpileupJetIdEvaluator *
    process.selectedPatJetsAK4PFCHS
)


process.p = cms.Path(process.seq)

from PhysicsTools.PatAlgos.tools.pfTools import *
## Adapt primary vertex collection
adaptPVs(process, pvCollection=cms.InputTag('offlineSlimmedPrimaryVertices'))

process.options = cms.untracked.PSet(
        wantSummary = cms.untracked.bool(True), # while the timing of this is not reliable in unscheduled mode, it still helps understanding what was actually run
        allowUnscheduled = cms.untracked.bool(True)
)


## Output file
from PhysicsTools.PatAlgos.patEventContent_cff import patEventContent
process.OUT = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('test.root'),
    outputCommands = cms.untracked.vstring(['keep *'])#(['drop *','keep patJets_selectedPatJetsAK5PFCHS_*_*'])
)
process.endpath= cms.EndPath(process.OUT)

open('pydump.py','w').write(process.dumpPython())
