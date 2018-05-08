import FWCore.ParameterSet.Config as cms

from FWCore.ParameterSet.VarParsing import VarParsing

process = cms.Process("USER")

process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag (process.GlobalTag, 'auto:run2_mc')

## Events to process
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

## Input files
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        #'/store/relval/CMSSW_7_4_1/RelValTTbar_13/MINIAODSIM/PU50ns_MCRUN2_74_V8_gensim_740pre7-v1/00000/7EC72BA9-44EC-E411-9DF3-0025905A60B0.root'
        #'/store/user/lbenato/VBFH_HToSSTobbbb_MH-125_MS-40_ctauS-1_Summer16_MINIAOD/VBFH_HToSSTobbbb_MH-125_MS-40_ctauS-1_TuneCUETP8M1_13TeV-powheg-pythia8_PRIVATE-MC/RunIISummer16-PU_standard_mixing-Moriond17_80X_mcRun2_2016_MINIAOD/180201_104029/0000/miniaod_VBFH_SS_m40_ctau1_1.root'
        '/store/mc/RunIISummer16MiniAODv2/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/80000/FED04F50-A3BE-E611-A893-00\
25900E3502.root'
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
#process.pfCHS = cms.EDFilter("CandPtrSelector", src = cms.InputTag("packedPFCandidates"), cut = cms.string("fromPV"))

from RecoJets.JetProducers.ak4PFJets_cfi import ak4PFJets
## Define PFJetsCHS
#process.ak4PFJetsCHS = ak4PFJets.clone(src = 'pfCHS', doAreaFastjet = True)
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
'''addJetCollection(
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
)'''
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

#getattr(process,'selectedPatJetsAK4PFCHS').cut = cms.string('pt > 10')

process.seq = cms.Sequence(
    process.ak4PFJets #*
    #process.selectedPatJetsAK4PF
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
    fileName = cms.untracked.string('test_ttbar.root'),
    outputCommands = cms.untracked.vstring(['keep *'])#(['drop *','keep patJets_selectedPatJetsAK5PFCHS_*_*'])
)
process.endpath= cms.EndPath(process.OUT)

#open('pydump.py','w').write(process.dumpPython())
