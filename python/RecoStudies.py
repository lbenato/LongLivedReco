import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing
import os

options = VarParsing('analysis')
options.parseArguments()

process = cms.Process("Reconstruction")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'ERROR'

#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000000) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000000) )


if len(options.inputFiles) == 0:
    process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
        fileNames = cms.untracked.vstring(
            #'/store/data/Run2017A/SingleElectron/MINIAOD/PromptReco-v2/000/296/168/00000/9ED74C00-5D4C-E711-9499-02163E01A667.root'
            #'/store/data/Run2017A/SingleMuon/MINIAOD/PromptReco-v2/000/296/168/00000/084C505D-784C-E711-8140-02163E019DA4.root'
            #'/store/data/Run2017B/SingleMuon/MINIAOD/PromptReco-v2/000/298/678/00000/B48DBFCD-A466-E711-A86B-02163E01A456.root'
            #'/store/data/Run2017C/SingleMuon/MINIAOD/PromptReco-v2/000/300/087/00000/009C8147-0D77-E711-A1EA-02163E0145A7.root',
            #'/store/data/Run2017D/SingleMuon/MINIAOD/PromptReco-v1/000/302/031/00000/2411F4EE-2D8F-E711-B514-02163E0134D6.root',
            #MINIAOD
            #'/store/user/lbenato/VBFH_HToSSTobbbb_MH-125_MS-40_ctauS-1_Summer16_MINIAOD/VBFH_HToSSTobbbb_MH-125_MS-40_ctauS-1_TuneCUETP8M1_13TeV-powheg-pythia8_PRIVATE-MC/RunIISummer16-PU_standard_mixing-Moriond17_80X_mcRun2_2016_MINIAOD/180201_104029/0000/miniaod_VBFH_SS_m40_ctau1_1.root',
            'file:test.root'
            #'file:test_ttbar.root'
            #'file:/pnfs/desy.de/cms/tier2/store/user/lbenato/test_recluster_ak4Jets_miniaod_3May2018/ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-0p05_TuneCUETP8M1_13TeV-powheg-pythia8/test_recluster_ak4Jets_miniaod_3May2018/180503_180425/0000/test_ttbar_1.root'
            #AOD
            #'/store/user/lbenato/VBFH_HToSSTobbbb_MH-125_MS-40_ctauS-1_Summer16_AODSIM/VBFH_HToSSTobbbb_MH-125_MS-40_ctauS-1_TuneCUETP8M1_13TeV-powheg-pythia8_PRIVATE-MC/RunIISummer16-PU_standard_mixing-Moriond17_80X_mcRun2_2016_AODSIM/180131_222020/0000/aodsim_VBFH_SS_m40_ctau1_1.root',
        )
    )
else:
    filelist = open(options.inputFiles[0], 'r').readlines()
    process.source = cms.Source ('PoolSource', fileNames = cms.untracked.vstring(filelist) )

isAOD = True if ("AODSIM" in process.source.fileNames[0]) else False

if isAOD:
    print "AOD!"

process.TFileService = cms.Service( "TFileService",
    fileName = cms.string('output.root' if len(options.outputFile)==0 else options.outputFile),
    closeFileFast = cms.untracked.bool(True),
)

#-----------------------#
#     DATA FLAGS        #
#-----------------------#
isData            = ('/store/data/' in process.source.fileNames[0])
isReHLT           = ('_reHLT_' in process.source.fileNames[0])
isReReco          = ('23Sep2016' in process.source.fileNames[0])
isReMiniAod       = ('03Feb2017' in process.source.fileNames[0])
isPromptReco      = ('PromptReco' in process.source.fileNames[0])
theRunBCD = ['Run2016B','Run2016C','Run2016D']
theRunEF  = ['Run2016E','Run2016F']
theRunG   = ['Run2016G']
theRunH   = ['Run2016H']

print 'isData',isData
print 'isReHLT',isReHLT
print 'isReReco',isReReco
print 'isReMiniAod',isReMiniAod
print 'isPromptReco',isPromptReco

#-----------------------#
#    VERTEX FILTER      #
#-----------------------#

import RecoVertex.PrimaryVertexProducer.OfflinePrimaryVertices_cfi
process.primaryVertexFilter = cms.EDFilter('GoodVertexFilter',
    vertexCollection = cms.InputTag('offlineSlimmedPrimaryVertices'),# if not isAOD else 'offlinePrimaryVertices'),
    minimumNDOF = cms.uint32(4),
    maxAbsZ = cms.double(24),
    maxd0 = cms.double(2)
)


#-----------------------#
#     GLOBAL TAG        #
#-----------------------#

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
GT = ''
if isData:
    if isPromptReco: GT = "92X_dataRun2_Prompt_v4"
    print "data 2017, PromptReco"
#else:
#    GT = "90X_upgrade2017_realistic_v20"
elif not(isData):                                       
    GT = '80X_mcRun2_asymptotic_2016_TrancheIV_v8'#Moriond17 GT

process.GlobalTag = GlobalTag(process.GlobalTag, GT)
print 'GlobalTag loaded: ', GT

#-----------------------#
#         JEC           #
#-----------------------#

JECstring = ''
if isData and (isReReco or isReMiniAod):
  if any(s in process.source.fileNames[0] for s in theRunBCD):
    JECstring = "Summer16_23Sep2016BCDV3_DATA" #if isReMiniAod else "Summer16_23Sep2016BCDV3_DATA"
  if any(s in process.source.fileNames[0] for s in theRunEF):
    JECstring = "Summer16_23Sep2016EFV3_DATA" #if isReMiniAod else "Summer16_23Sep2016EFV3_DATA"
  if any(s in process.source.fileNames[0] for s in theRunG):
    JECstring = "Summer16_23Sep2016GV3_DATA" #if isReMiniAod else "Summer16_23Sep2016GV3_DATA"
  if any(s in process.source.fileNames[0] for s in theRunH):
    JECstring = "Summer16_23Sep2016HV3_DATA" #if isReMiniAod else "Summer16_23Sep2016HV3_DATA"
elif isData and isPromptReco:
    JECstring = "Spring16_25nsV6_DATA"
elif not isData:
    JECstring = "Summer16_23Sep2016V3_MC"

print "JEC ->",JECstring

#-----------------------#
#        FILTERS        #
#-----------------------#

# JSON filter
if isData:
    import FWCore.PythonUtilities.LumiList as LumiList
    jsonName = "Cert_294927-305364_13TeV_PromptReco_Collisions17_JSON"#"Cert_294927-301567_13TeV_PromptReco_Collisions17_JSON" #golden json
    process.source.lumisToProcess = LumiList.LumiList(filename = 'data/JSON/'+jsonName+'.txt').getVLuminosityBlockRange()
    print "JSON file loaded: ", jsonName

# MET filters
process.load('RecoMET.METFilters.BadPFMuonFilter_cfi')
process.BadPFMuonFilter.muons = cms.InputTag('slimmedMuons')# if not isAOD else 'muons')
process.BadPFMuonFilter.PFCandidates = cms.InputTag('packedPFCandidates')# if not isAOD else 'PFCandidates')

process.load('RecoMET.METFilters.BadChargedCandidateFilter_cfi')
process.BadChargedCandidateFilter.muons = cms.InputTag('slimmedMuons')# if not isAOD else 'muons')
process.BadChargedCandidateFilter.PFCandidates = cms.InputTag('packedPFCandidates')# if not isAOD else 'PFCandidates')


#-----------------------#
#       ANALYZER        #
#-----------------------#

process.reconstruction = cms.EDAnalyzer('RecoStudies',
    genSet = cms.PSet(
        genProduct = cms.InputTag('generator'),
        lheProduct = cms.InputTag('externalLHEProducer'),
        genParticles = cms.InputTag('prunedGenParticles'),# if not isAOD else 'genParticles'),
        pdgId = cms.vint32(5,9000006),#(1, 2, 3, 4, 5, 6, 11, 12, 13, 14, 15, 16, 21, 23, 24, 25, 36, 39, 1000022, 9100000, 9000001, 9000002, 9100012, 9100022, 9900032, 1023),
        status = cms.vint32(22,23),
        samplesDYJetsToLL = cms.vstring(),
        samplesZJetsToNuNu = cms.vstring(),
        samplesWJetsToLNu = cms.vstring(),
        samplesDir = cms.string('data/Stitch/'),
        sample = cms.string("" ), #( sample )
        ewkFile = cms.string('data/scalefactors_v4.root'),
        applyEWK = cms.bool(False),#(True if sample.startswith('DYJets') or sample.startswith('WJets') else False),
        applyTopPtReweigth = cms.bool(False),#(True if sample.startswith('TT_') else False),
        pythiaLOSample = cms.bool(False),#(True if isDibosonInclusive else False),
    ),
    chsJetSet = cms.PSet(
        #recoJets = cms.InputTag('ak4PFJets'),#('slimmedJetsAK8'), #selectedPatJetsAK8PFCHSPrunedPacked
        jets = cms.InputTag('slimmedJets'),#,#('slimmedJets'),#('slimmedJetsAK8'), #selectedPatJetsAK8PFCHSPrunedPacked
        jetid = cms.int32(0), # 0: no selection, 1: loose, 2: medium, 3: tight                                                                                    
        jet1pt = cms.double(15.),
        jet2pt = cms.double(15.),
        jeteta = cms.double(2.4),
        addQGdiscriminator = cms.bool(False),
        recalibrateJets = cms.bool(True),
        recalibrateMass = cms.bool(False),
        recalibratePuppiMass = cms.bool(False),
        smearJets = cms.bool(True),
        vertices = cms.InputTag('offlineSlimmedPrimaryVertices'),# if not isAOD else 'offlinePrimaryVertices'),
        rho = cms.InputTag('fixedGridRhoFastjetAll'),
        jecUncertaintyDATA = cms.string('data/%s/%s_Uncertainty_AK4PFchs.txt' % (JECstring, JECstring)),#updating
        jecUncertaintyMC = cms.string('data/Summer16_23Sep2016V3_MC/Summer16_23Sep2016V3_MC_Uncertainty_AK4PFchs.txt'),#updating
        jecCorrectorDATA = cms.vstring(#updating
            'data/%s/%s_L1FastJet_AK4PFchs.txt' % (JECstring, JECstring),
            'data/%s/%s_L2Relative_AK4PFchs.txt' % (JECstring, JECstring),
            'data/%s/%s_L3Absolute_AK4PFchs.txt' % (JECstring, JECstring),
            'data/%s/%s_L2L3Residual_AK4PFchs.txt' % (JECstring, JECstring),
        ),
        jecCorrectorMC = cms.vstring(#updating!!!
            'data/Summer16_23Sep2016V3_MC/Summer16_23Sep2016V3_MC_L1FastJet_AK4PFchs.txt',
            'data/Summer16_23Sep2016V3_MC/Summer16_23Sep2016V3_MC_L2Relative_AK4PFchs.txt',
            'data/Summer16_23Sep2016V3_MC/Summer16_23Sep2016V3_MC_L3Absolute_AK4PFchs.txt',
        ),
        massCorrectorDATA = cms.vstring(#updating!!!
            'data/%s/%s_L2Relative_AK4PFchs.txt' % (JECstring, JECstring),
            'data/%s/%s_L3Absolute_AK4PFchs.txt' % (JECstring, JECstring),
            'data/%s/%s_L2L3Residual_AK4PFchs.txt' % (JECstring, JECstring),
        ),
        massCorrectorMC = cms.vstring(#updating!!!                                                                                                           
            'data/Summer16_23Sep2016V3_MC/Summer16_23Sep2016V3_MC_L2Relative_AK4PFchs.txt',
            'data/Summer16_23Sep2016V3_MC/Summer16_23Sep2016V3_MC_L3Absolute_AK4PFchs.txt',
        ),
        massCorrectorPuppi = cms.string('data/puppiCorrSummer16.root'),#updating
        reshapeBTag = cms.bool(True),
        btag = cms.string('pfCombinedInclusiveSecondaryVertexV2BJetTags'),
        btagDB = cms.string('data/CSVv2_Moriond17_B_H.csv'),
        jet1btag = cms.int32(0), # 0: no selection, 1: loose, 2: medium, 3: tight                                                                                                       
        jet2btag = cms.int32(0),
        met = cms.InputTag('slimmedMETsMuEGClean', '', '') if isReMiniAod else cms.InputTag('slimmedMETs', '', 'ALPHA'),# if not isAOD else 'pfMet', '', 'ALPHA'),
        #recoMet = cms.InputTag('pfMet', '', 'ALPHA'),
        metRecoil = cms.bool(False),
        metRecoilMC = cms.string('data/recoilfit_gjetsMC_Zu1_pf_v5.root'),
        metRecoilData = cms.string('data/recoilfit_gjetsData_Zu1_pf_v5.root'),
        metTriggerFileName = cms.string('data/MET_trigger_eff_data_SingleMuRunBH.root'),
        jerNameRes = cms.string('data/JER/Spring16_25nsV10_MC_PtResolution_AK4PFchs.txt'),#v10 is the latest                                                                            
        jerNameSf = cms.string('data/JER/Spring16_25nsV10_MC_SF_AK4PFchs.txt'),#v10 is the latest
    ),
    jetSet = cms.PSet(
        #recoJets = cms.InputTag('ak4PFJets'),#('slimmedJetsAK8'), #selectedPatJetsAK8PFCHSPrunedPacked
        jets = cms.InputTag('patJetsAK4PF', '','USER'),#('slimmedJets'),##('slimmedJetsAK8'), #selectedPatJetsAK8PFCHSPrunedPacked
        jetid = cms.int32(0), # 0: no selection, 1: loose, 2: medium, 3: tight                                                                                    
        jet1pt = cms.double(15.),
        jet2pt = cms.double(15.),
        jeteta = cms.double(2.4),
        addQGdiscriminator = cms.bool(False),
        recalibrateJets = cms.bool(True),#(True),!!!!!!!!!!!!!!!!!!!
        recalibrateMass = cms.bool(False),
        recalibratePuppiMass = cms.bool(False),
        smearJets = cms.bool(True),#(True),!!!!!!!!!!!!!!!!!
        vertices = cms.InputTag('offlineSlimmedPrimaryVertices'),# if not isAOD else 'offlinePrimaryVertices'),
        rho = cms.InputTag('fixedGridRhoFastjetAll'),
        jecUncertaintyDATA = cms.string('data/%s/%s_Uncertainty_AK4PF.txt' % (JECstring, JECstring)),#updating
        jecUncertaintyMC = cms.string('data/Summer16_23Sep2016V3_MC/Summer16_23Sep2016V3_MC_Uncertainty_AK4PF.txt'),#updating
        jecCorrectorDATA = cms.vstring(#updating
            'data/%s/%s_L1FastJet_AK4PF.txt' % (JECstring, JECstring),
            'data/%s/%s_L2Relative_AK4PF.txt' % (JECstring, JECstring),
            'data/%s/%s_L3Absolute_AK4PF.txt' % (JECstring, JECstring),
            'data/%s/%s_L2L3Residual_AK4PF.txt' % (JECstring, JECstring),
        ),
        jecCorrectorMC = cms.vstring(#updating!!!
            'data/Summer16_23Sep2016V3_MC/Summer16_23Sep2016V3_MC_L1FastJet_AK4PF.txt',
            'data/Summer16_23Sep2016V3_MC/Summer16_23Sep2016V3_MC_L2Relative_AK4PF.txt',
            'data/Summer16_23Sep2016V3_MC/Summer16_23Sep2016V3_MC_L3Absolute_AK4PF.txt',
        ),
        massCorrectorDATA = cms.vstring(#updating!!!
            'data/%s/%s_L2Relative_AK4PF.txt' % (JECstring, JECstring),
            'data/%s/%s_L3Absolute_AK4PF.txt' % (JECstring, JECstring),
            'data/%s/%s_L2L3Residual_AK4PF.txt' % (JECstring, JECstring),
        ),
        massCorrectorMC = cms.vstring(#updating!!!                                                                                                           
            'data/Summer16_23Sep2016V3_MC/Summer16_23Sep2016V3_MC_L2Relative_AK4PF.txt',
            'data/Summer16_23Sep2016V3_MC/Summer16_23Sep2016V3_MC_L3Absolute_AK4PF.txt',
        ),
        massCorrectorPuppi = cms.string('data/puppiCorrSummer16.root'),#updating
        reshapeBTag = cms.bool(True),#(True),!!!!!
        btag = cms.string('pfCombinedInclusiveSecondaryVertexV2BJetTags'),
        btagDB = cms.string('data/CSVv2_Moriond17_B_H.csv'),
        jet1btag = cms.int32(0), # 0: no selection, 1: loose, 2: medium, 3: tight                                                                                                       
        jet2btag = cms.int32(0),
        met = cms.InputTag('slimmedMETsMuEGClean', '', '') if isReMiniAod else cms.InputTag('slimmedMETs', '', 'ALPHA'),# if not isAOD else 'pfMet', '', 'ALPHA'),
        #recoMet = cms.InputTag('pfMet', '', 'ALPHA'),
        metRecoil = cms.bool(False),
        metRecoilMC = cms.string('data/recoilfit_gjetsMC_Zu1_pf_v5.root'),
        metRecoilData = cms.string('data/recoilfit_gjetsData_Zu1_pf_v5.root'),
        metTriggerFileName = cms.string('data/MET_trigger_eff_data_SingleMuRunBH.root'),
        jerNameRes = cms.string('data/JER/Spring16_25nsV10_MC_PtResolution_AK4PF.txt'),#v10 is the latest                                                                            
        jerNameSf = cms.string('data/JER/Spring16_25nsV10_MC_SF_AK4PF.txt'),#v10 is the latest
    ),

    writeNJets = cms.int32(8),
    writeNGenBquarks = cms.int32(4),
    writeNGenLongLiveds = cms.int32(2),
    verbose = cms.bool(True),
)

process.seq = cms.Sequence(
    process.BadPFMuonFilter *
    process.BadChargedCandidateFilter *
    process.reconstruction
)

process.p = cms.Path(process.seq)
#process.p = cms.Path(process.reconstruction)

#open('pydump_recostudies.py','w').write(process.dumpPython())
