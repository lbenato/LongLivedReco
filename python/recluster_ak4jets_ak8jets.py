import FWCore.ParameterSet.Config as cms

from FWCore.ParameterSet.VarParsing import VarParsing

process = cms.Process("USER")

## Events to process
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

## Input files
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        #'/store/relval/CMSSW_7_4_1/RelValTTbar_13/MINIAODSIM/PU50ns_MCRUN2_74_V8_gensim_740pre7-v1/00000/7EC72BA9-44EC-E411-9DF3-0025905A60B0.root'
        #'/store/user/lbenato/VBFH_HToSSTobbbb_MH-125_MS-40_ctauS-1_Summer16_MINIAOD/VBFH_HToSSTobbbb_MH-125_MS-40_ctauS-1_TuneCUETP8M1_13TeV-powheg-pythia8_PRIVATE-MC/RunIISummer16-PU_standard_mixing-Moriond17_80X_mcRun2_2016_MINIAOD/180201_104029/0000/miniaod_VBFH_SS_m40_ctau1_1.root'
        #'/store/mc/RunIISummer16MiniAODv2/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/80000/FED04F50-A3BE-E611-A893-0025900E3502.root'
        #'file:VBFHToSS_m60_miniaod.root'
        #'/store/user/lbenato/recluster_ak4Jets_miniaod_29May2018/VBFH_HToSSTobbbb_MH-125_MS-40_ctauS-0_TuneCUETP8M1_13TeV-powheg-pythia8_PRIVATE-MC/recluster_ak4Jets_miniaod_29May2018/180529_123139/0000/test_ttbar_1.root'
        '/store/user/lbenato/VBFH_HToSSTobbbb_MH-125_MS-40_ctauS-0_Summer16_MINIAODSIM_24May2018/VBFH_HToSSTobbbb_MH-125_MS-40_ctauS-0_TuneCUETP8M1_13TeV-powheg-pythia8_PRIVATE-MC/RunIISummer16-PU_premix-Moriond17_80X_mcRun2_2016_MINIAODSIM_24May2018/180529_093853/0000/miniaod_1.root'
    )
)

isData = ('/store/data/' in process.source.fileNames[0])

process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag (process.GlobalTag, 'auto:run2_mc')#default option, but we have the best global tag manually

GT = ''
if isData:
    GT = '80X_dataRun2_2016SeptRepro_v7'
    print "data 2016, ReMiniaod GT"
elif not(isData):
    GT = '80X_mcRun2_asymptotic_2016_TrancheIV_v8'#Moriond17 GT

process.GlobalTag = GlobalTag (process.GlobalTag, GT)

#################################################
## Remake jets
#################################################

fatjet_ptmin = 50.

##Dummy copy for having pf candidates into the process
#process.packed = cms.EDFilter("CandPtrSelector", src = cms.InputTag("packedGenParticles"), cut = cms.string("abs(pdgId) != 12 && abs(pdgId) != 14 && abs(pdgId) != 16"))


## Filter out neutrinos from packed GenParticles
process.packedGenParticlesForJetsNoNu = cms.EDFilter("CandPtrSelector", src = cms.InputTag("packedGenParticles"), cut = cms.string("abs(pdgId) != 12 && abs(pdgId) != 14 && abs(pdgId) != 16"))
## Define GenJets
from RecoJets.JetProducers.ak4GenJets_cfi import ak4GenJets
process.ak4GenJetsNoNu = ak4GenJets.clone(src = 'packedGenParticlesForJetsNoNu')

from RecoJets.JetProducers.ak5GenJets_cfi import ak5GenJets
process.ak8GenJetsNoNu = ak5GenJets.clone(src = 'packedGenParticlesForJetsNoNu', rParam = 0.8)

## Standard AK4 and AK8 jets without CHS
from RecoJets.JetProducers.ak4PFJets_cfi import ak4PFJets
process.ak4PFJets = ak4PFJets.clone(src = 'packedPFCandidates', doAreaFastjet = True)#HERE!!! add jetPtMin = (fatjet_ptmin)
process.ak8PFJets  = ak4PFJets.clone (src = 'packedPFCandidates', rParam = 0.8, doAreaFastjet = True, jetPtMin = fatjet_ptmin)

## Pruned AK8 without CHS
from RecoJets.JetProducers.ak4PFJetsPruned_cfi import ak4PFJetsPruned
process.ak8PFJetsPruned = ak4PFJetsPruned.clone(rParam = 0.8, doAreaFastjet = True, src = 'packedPFCandidates', jetPtMin = fatjet_ptmin)

## Softdrop AK8 without CHS
from RecoJets.JetProducers.ak4PFJetsSoftDrop_cfi import ak4PFJetsSoftDrop
process.ak8PFJetsSoftDrop = ak4PFJetsSoftDrop.clone(R0 = 0.8, rParam = 0.8, doAreaFastjet = True, src = 'packedPFCandidates', jetPtMin = fatjet_ptmin)

## PUPPI AK8
## Pre-requisites: re-build puppi jets

###Robin's way:

process.load('CommonTools/PileupAlgos/Puppi_cff')
## e.g. to run on miniAOD
process.puppi.candName = cms.InputTag('packedPFCandidates')
process.puppi.vertexName = cms.InputTag('offlineSlimmedPrimaryVertices')
process.puppi.clonePackedCands   = cms.bool(True)
process.puppi.useExistingWeights = cms.bool(True)

from RecoJets.JetProducers.ak4PFJetsPuppi_cfi import ak4PFJetsPuppi
process.ak8PFJetsPuppi = ak4PFJetsPuppi.clone(rParam = 0.8, doAreaFastjet = True, jetPtMin = fatjet_ptmin)

## Softdrop AK8 with Puppi
from RecoJets.Configuration.RecoPFJets_cff import ak8PFJetsPuppiSoftDrop
process.ak8PFJetsPuppiSoftDrop = ak8PFJetsPuppiSoftDrop.clone(jetPtMin = fatjet_ptmin)

###PERRCHE NON CONOSCE PIU' PACKED PF CANDIDATES??????????????
##print process.packedPFCandidates
#################
### Tentative n.2: association track-vtx
'''
It says that 
Looking for type: std::vector<reco::Track>
Looking for module label: generalTracks

from RecoJets.JetAssociationProducers.j2tParametersVX_cfi import j2tParametersVX
process.ak8PFJetsPuppiTracksAssociatorAtVertex = cms.EDProducer("JetTracksAssociatorAtVertex",
        j2tParametersVX,
        jets = cms.InputTag("ak8PFJetsPuppi")
)

process.patJetPuppiCharge = cms.EDProducer("JetChargeProducer",
        src = cms.InputTag("ak8PFJetsPuppiTracksAssociatorAtVertex"),
        var = cms.string('Pt'),
        exp = cms.double(1.0)
)

from RecoJets.JetAssociationProducers.j2tParametersVX_cfi import j2tParametersVX
process.ak8PFJetsPuppiTracksAssociatorAtVertex = cms.EDProducer("JetTracksAssociatorAtVertex",
        j2tParametersVX,
        jets = cms.InputTag("ak8PFJetsPuppi")
)

process.patJetAK8PuppiCharge = cms.EDProducer("JetChargeProducer",
        src = cms.InputTag("ak8PFJetsPuppiTracksAssociatorAtVertex"),
        var = cms.string('Pt'),
        exp = cms.double(1.0)
)
'''





#################################################
## Remake PAT jets without CHS
#################################################

## b-tag discriminators
bTagDiscriminators = [
    'pfCombinedInclusiveSecondaryVertexV2BJetTags'
]

from PhysicsTools.PatAlgos.tools.jetTools import *
## Add PAT jet collection based on the above-defined ak4PFJetsCHS
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

addJetCollection(
    process,
    labelName = 'AK8PF',
    jetSource = cms.InputTag('ak8PFJets'),
    pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
    pfCandidates = cms.InputTag('packedPFCandidates'),
    svSource = cms.InputTag('slimmedSecondaryVertices'),
    btagDiscriminators = bTagDiscriminators,
    jetCorrections = ('AK8PF', ['L1FastJet', 'L2Relative', 'L3Absolute'], 'None'),
    genJetCollection = cms.InputTag('ak8GenJetsNoNu'),
    genParticles = cms.InputTag('prunedGenParticles'),
    algo = 'AK',
    rParam = 0.8
)

addJetCollection(
    process,
    labelName = 'AK8Puppi',
    jetSource = cms.InputTag('ak8PFJetsPuppi'),
    pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
    pfCandidates = cms.InputTag('packedPFCandidates'),
    svSource = cms.InputTag('slimmedSecondaryVertices'),
    btagDiscriminators = bTagDiscriminators,
    jetCorrections = ('AK8PFPuppi', ['L1FastJet', 'L2Relative', 'L3Absolute'], 'None'),
    genJetCollection = cms.InputTag('ak8GenJetsNoNu'),
    genParticles = cms.InputTag('prunedGenParticles'),
    algo = 'AK',
    rParam = 0.8
)


##
## PF AK8 groomed masses without CHS
process.patJetsAK8PF.userData.userFloats.src = []
from RecoJets.JetProducers.ak8PFJetsCHS_groomingValueMaps_cfi import ak8PFJetsCHSPrunedMass, ak8PFJetsCHSSoftDropMass
process.ak8PFJetsSoftDropMass = ak8PFJetsCHSSoftDropMass.clone(src = 'ak8PFJets', matched = 'ak8PFJetsSoftDrop')
process.ak8PFJetsPrunedMass = ak8PFJetsCHSPrunedMass.clone(src = 'ak8PFJets', matched = 'ak8PFJetsPruned')
process.patJetsAK8PF.userData.userFloats.src += ['ak8PFJetsPrunedMass','ak8PFJetsSoftDropMass']

##
## PF AK8 Puppi groomed masses with Puppi
process.patJetsAK8Puppi.userData.userFloats.src = []
process.load("RecoJets.JetProducers.ak8PFJetsPuppi_groomingValueMaps_cfi")
process.patJetsAK8Puppi.userData.userFloats.src += ['ak8PFJetsPuppiSoftDropMass']

##
## N-subjettiness without CHS
from RecoJets.JetProducers.nJettinessAdder_cfi import *
process.NjettinessAK8 = Njettiness.clone(src='ak8PFJets')#src='ak8PFJets', cone=0.8)
process.NjettinessAK8.cone = cms.double(0.8)
process.patJetsAK8PF.userData.userFloats.src += ['NjettinessAK8:tau1','NjettinessAK8:tau2','NjettinessAK8:tau3']

##
## Puppi N-subjettiness
from RecoJets.JetProducers.nJettinessAdder_cfi import *
process.NjettinessAK8Puppi = Njettiness.clone(src='ak8PFJetsPuppi')
process.NjettinessAK8Puppi.cone = cms.double(0.8)
process.patJetsAK8Puppi.userData.userFloats.src += ['NjettinessAK8Puppi:tau1','NjettinessAK8Puppi:tau2','NjettinessAK8Puppi:tau3']


##THESE VALUE MAPS ARE PROBABLY NOT NEEDED
## PF AK8 matching to PF Puppi AK8
process.ak8PFJetsPuppiValueMap = cms.EDProducer("RecoJetToPatJetDeltaRValueMapProducer",
                                                src = cms.InputTag("ak8PFJets"),
                                                matched = cms.InputTag("patJetsAK8Puppi"),                                         
                                                distMax = cms.double(0.8),
                                                values = cms.vstring([
            'userFloat("NjettinessAK8Puppi:tau1")',
            'userFloat("NjettinessAK8Puppi:tau2")',
            'userFloat("NjettinessAK8Puppi:tau3")',
            'pt','eta','phi','mass'
            ]),
                                                valueLabels = cms.vstring( [
            'NjettinessAK8PuppiTau1',
            'NjettinessAK8PuppiTau2',
            'NjettinessAK8PuppiTau3',
            'pt','eta','phi','mass'
            ])
)


process.patJetsAK8PF.userData.userFloats.src += [cms.InputTag('ak8PFJetsPuppiValueMap','NjettinessAK8PuppiTau1'),
                                               cms.InputTag('ak8PFJetsPuppiValueMap','NjettinessAK8PuppiTau2'),
                                               cms.InputTag('ak8PFJetsPuppiValueMap','NjettinessAK8PuppiTau3'),
                                               cms.InputTag('ak8PFJetsPuppiValueMap','pt'),
                                               cms.InputTag('ak8PFJetsPuppiValueMap','eta'),
                                               cms.InputTag('ak8PFJetsPuppiValueMap','phi'),
                                               cms.InputTag('ak8PFJetsPuppiValueMap','mass'),
                                               ]

######



### here we try to have selectedPatJetsAK8PFCHSSoftDrop, slimmedJetsAK8PFCHSSoftDropSubjets

###LATER

###################################################

### here we need to pattify AK8PFSoftDrop jets

addJetCollection(
        process,
        labelName = 'AK8PFSoftDrop',
        jetSource = cms.InputTag('ak8PFJetsSoftDrop'),
        pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
        pfCandidates = cms.InputTag('packedPFCandidates'),
        svSource = cms.InputTag('slimmedSecondaryVertices'),
        btagDiscriminators = ['None'],
        jetCorrections = ('AK8PF', ['L1FastJet', 'L2Relative', 'L3Absolute'], 'None'),
        getJetMCFlavour = False, # jet flavor disabled
        genParticles = cms.InputTag('prunedGenParticles'),
        genJetCollection = cms.InputTag('ak8GenJetsNoNu'),
        algo = 'AK',
        rParam = 0.8
)

###try subjets, this will probably fail
addJetCollection(
        process,
        labelName = 'AK8PFSoftDropSubjets',
        jetSource = cms.InputTag('ak8PFJetsSoftDrop','SubJets'),
        algo = 'ak',  # needed for subjet flavor clustering
        rParam = 0.8, # needed for subjet flavor clustering
        btagDiscriminators = ['pfCombinedSecondaryVertexV2BJetTags', 'pfCombinedInclusiveSecondaryVertexV2BJetTags'],
        jetCorrections = ('AK4PF', ['L1FastJet', 'L2Relative', 'L3Absolute'], 'None'),
        explicitJTA = True,  # needed for subjet b tagging
        svClustering = True, # needed for subjet b tagging
        pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
        pfCandidates = cms.InputTag('packedPFCandidates'),
        svSource = cms.InputTag('slimmedSecondaryVertices'),
        genParticles = cms.InputTag('prunedGenParticles'),
        genJetCollection = cms.InputTag('ak4GenJetsNoNu'), 
        fatJets=cms.InputTag('ak8PFJets'),             # needed for subjet flavor clustering
        groomedFatJets=cms.InputTag('ak8PFJetsSoftDrop') # needed for subjet flavor clustering
)

### here we need to pattify AK8PFPuppiSoftDrop jets
addJetCollection(
        process,
        labelName = 'AK8PFPuppiSoftDrop',
        jetSource = cms.InputTag('ak8PFJetsPuppiSoftDrop'),
        pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
        pfCandidates = cms.InputTag('packedPFCandidates'),
        svSource = cms.InputTag('slimmedSecondaryVertices'),
        btagDiscriminators = ['None'],
        #btagDiscriminators = bTagDiscriminators,
        jetCorrections = ('AK8PFPuppi', ['L1FastJet', 'L2Relative', 'L3Absolute'], 'None'),
        getJetMCFlavour = False, # jet flavor disabled
        genParticles = cms.InputTag('prunedGenParticles'),
        genJetCollection = cms.InputTag('ak8GenJetsNoNu'),
        algo = 'AK',
        rParam = 0.8
)

### here we need to pattify AK8PFPuppiSoftDropSubjets, that are AK4
addJetCollection(
        process,
        labelName = 'AK8PFPuppiSoftDropSubjets',
        jetSource = cms.InputTag('ak8PFJetsPuppiSoftDrop','SubJets'),
        algo = 'ak',  # needed for subjet flavor clustering
        rParam = 0.8, # needed for subjet flavor clustering
        btagDiscriminators = ['pfCombinedSecondaryVertexV2BJetTags', 'pfCombinedInclusiveSecondaryVertexV2BJetTags'],
        jetCorrections = ('AK4PFPuppi', ['L1FastJet', 'L2Relative', 'L3Absolute'], 'None'),
        explicitJTA = True,  # needed for subjet b tagging
        svClustering = True, # needed for subjet b tagging
        pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
        pfCandidates = cms.InputTag('packedPFCandidates'),
        svSource = cms.InputTag('slimmedSecondaryVertices'),
        genParticles = cms.InputTag('prunedGenParticles'),
        genJetCollection = cms.InputTag('ak4GenJetsNoNu'), 
        fatJets=cms.InputTag('ak8PFJetsPuppi'),             # needed for subjet flavor clustering
        groomedFatJets=cms.InputTag('ak8PFJetsPuppiSoftDrop'), # needed for subjet flavor clustering
)


### here we try to have selectedPatJetsAK8PFPuppiSoftDrop

#process.selectedPatJetsAK8PFPuppiSoftDrop.cut = cms.string("pt > "+fatjet_ptmin)

#testing, not necessary!
#process.selectedPatJetsAK8PFPuppiSoftDropSubjets = cms.EDFilter("PATJetSelector",
#    cut = cms.string('pt > 10'),
#    src = cms.InputTag("patJetsAK8PFPuppiSoftDropSubjets")
#)

### here we try to have slimmedJetsAK8PFPuppiSoftDropSubjets ---> does not work and not necessary!
#testing, not necessary!
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#Does not work because of edm::Association<std::vector<pat::PackedCandidate> > Looking for module label: packedPFCandidates not found
'''
process.slimmedJetsAK8TEST = cms.EDProducer("PATJetSlimmer",
   src = cms.InputTag("patJetsAK8PF"),
   packedPFCandidates = cms.InputTag("packedPFCandidates"),
   dropJetVars = cms.string("1"),
   dropDaughters = cms.string("0"),
   rekeyDaughters = cms.string("1"),
   dropTrackRefs = cms.string("1"),
   dropSpecific = cms.string("0"),
   dropTagInfos = cms.string("1"),#?#("0"),
   modifyJets = cms.bool(True),
   mixedDaughters = cms.bool(False),
   modifierConfig = cms.PSet( modifications = cms.VPSet() )
)
'''

'''
process.slimmedJetsAK8PFPuppiSoftDropSubjets = cms.EDProducer("PATJetSlimmer",
        src = cms.InputTag("selectedPatJetsAK8PFPuppiSoftDropSubjets"),#no need of selected
        #src = cms.InputTag("patJetsAK8PFPuppiSoftDropSubjets"),
        packedPFCandidates = cms.InputTag("packedPFCandidates"),
        dropJetVars = cms.string("1"),
        dropDaughters = cms.string("0"),
        rekeyDaughters = cms.string("1"),
        dropTrackRefs = cms.string("1"),
        dropSpecific = cms.string("1"),
        dropTagInfos = cms.string("1"),
        modifyJets = cms.bool(True),
        modifierConfig = cms.PSet( modifications = cms.VPSet() )
)
'''

##
## here we try to have slimmedJetsAK8PFCHSSoftDropPacked
#process.slimmedJetsAK8PFCHSSoftDropPacked = cms.EDProducer("BoostedJetMerger",
#        jetSrc=cms.InputTag("selectedPatJetsAK8PFCHSSoftDrop"),
#        subjetSrc=cms.InputTag("slimmedJetsAK8PFCHSSoftDropSubjets")
#)

## here we try to have patJetsAK8PFPuppiSoftDropPacked and patJetsAK8PFPuppiSoftDropPacked

process.patJetsAK8PFSoftDropPacked = cms.EDProducer("BoostedJetMerger",
        jetSrc=cms.InputTag("patJetsAK8PFSoftDrop"),#selectedPat..
        subjetSrc=cms.InputTag("patJetsAK8PFSoftDropSubjets")#("slimmedJetsAK8PFPuppiSoftDropSubjets")
)

process.patJetsAK8PFPuppiSoftDropPacked = cms.EDProducer("BoostedJetMerger",
        jetSrc=cms.InputTag("patJetsAK8PFPuppiSoftDrop"),
        subjetSrc=cms.InputTag("patJetsAK8PFPuppiSoftDropSubjets")
)

#From miniaod dump ---> for some reasons packedPFCandidates is unknown now...
#process.packedPFCandidates = cms.EDProducer("PATPackedCandidateProducer",
    #PuppiNoLepSrc = cms.InputTag("puppiNoLep"),
    #PuppiSrc = cms.InputTag("puppi"),
    #inputCollection = cms.InputTag("particleFlow"),
    #inputVertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    #minPtForTrackProperties = cms.double(0.95),
    #originalTracks = cms.InputTag("generalTracks"),
    #originalVertices = cms.InputTag("offlinePrimaryVertices"),
    #secondaryVerticesForWhiteList = cms.VInputTag(cms.InputTag("inclusiveCandidateSecondaryVertices"), cms.InputTag("inclusiveCandidateSecondaryVerticesCvsL")),
    #vertexAssociator = cms.InputTag("primaryVertexAssociation","original")
#)

#From miniaod dump ---> this should give all the proper subjets.

process.packedPatJetsAK8 = cms.EDProducer("JetSubstructurePacker",
    algoLabels = cms.vstring('SoftDrop',
                             'SoftDropPuppi'
                             ),
    algoTags = cms.VInputTag(cms.InputTag("patJetsAK8PFSoftDropPacked"), 
                             cms.InputTag("patJetsAK8PFPuppiSoftDropPacked")
                             ),#I need those, before
    #algoTags = cms.VInputTag(cms.InputTag("slimmedJetsAK8PFCHSSoftDropPacked"), cms.InputTag("slimmedJetsAK8PFPuppiSoftDropPacked")),#I need those, before
    distMax = cms.double(0.8),
    fixDaughters = cms.bool(False),
    jetSrc = cms.InputTag("patJetsAK8PF"),
    packedPFCandidates = cms.InputTag("packedPFCandidates"),
    #candidates = cms.InputTag("packedPFCandidates"),
)

#Let's try an easier version first
'''
process.packedPatJetsAK8 = cms.EDProducer("JetSubstructurePacker",
    algoLabels = cms.vstring(#'SoftDrop',
                             'SoftDropPuppi'),
    algoTags = cms.VInputTag(#cms.InputTag("slimmedJetsAK8PFCHSSoftDropPacked"), 
                             cms.InputTag("slimmedJetsAK8PFPuppiSoftDropPacked")),#I need those, before
    distMax = cms.double(0.8),
    fixDaughters = cms.bool(True),
    jetSrc = cms.InputTag("patJetsAK8PF"),
    packedPFCandidates = cms.InputTag("packedPFCandidates")
)
'''

##getattr(process,'selectedPatJetsAK4PFCHS').cut = cms.string('pt > 10')

process.seq = cms.Sequence(
    process.ak4PFJets *
    process.ak8PFJets *
    process.packedPatJetsAK8
    #process.selectedPatJetsAK4PF
)


process.p = cms.Path(process.seq)

from PhysicsTools.PatAlgos.tools.pfTools import *
## Adapt primary vertex collection
adaptPVs(process, pvCollection=cms.InputTag('offlineSlimmedPrimaryVertices'))

process.options = cms.untracked.PSet(
        wantSummary = cms.untracked.bool(False), # while the timing of this is not reliable in unscheduled mode, it still helps understanding what was actually run
        allowUnscheduled = cms.untracked.bool(True)
)


## Output file
from PhysicsTools.PatAlgos.patEventContent_cff import patEventContent
process.OUT = cms.OutputModule("PoolOutputModule",
    #fileName = cms.untracked.string('test_ak4ak8_large.root'),
    fileName = cms.untracked.string('test_ak4ak8.root'),
    outputCommands = cms.untracked.vstring(['keep *', 'drop *_selectedPatJets*_*_*'])#(['drop *','keep patJets_selectedPatJetsAK5PFCHS_*_*'])
)
process.endpath= cms.EndPath(process.OUT)

print process.p

open('pydump_recluster_ak4jets_ak8jets.py','w').write(process.dumpPython())
