###Pre-requisites:
###1. cmsenv in a CMSSW area
###2. load CRAB: source /cvmfs/cms.cern.ch/crab3/crab.sh
###3. set a proxy: voms-proxy-init --voms cms   (certificate password will be asked)

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
import os
config = config()

###Name of the main crab area
config.General.workArea = 'reconstruction_v2_4May2018'#'crab_projects_LL_14feb'
###If not planning to transfer on T2, this could probably be commented out...
config.General.transferOutputs = True
config.General.transferLogs = True

###If running on already existing datasets: pluginName must be Analysis
config.JobType.pluginName = 'Analysis'
###Config file for cmsRun
config.JobType.psetName = 'python/RecoStudies.py'
###If additional files are required (root files for weights, etc..), CRAB must load them
config.JobType.inputFiles = ['data']

###Name of the working dir
#config.General.requestName = 'WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8-v1' 
config.General.requestName = 'VBFH_HToSSTobbbb_MH-125_MS-40_ctauS-0_Summer16_MINIAOD'

###Name of the sample in DAS
#config.Data.inputDataset = '/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v3/MINIAODSIM'
config.Data.inputDataset =  '/VBFH_HToSSTobbbb_MH-125_MS-40_ctauS-0_TuneCUETP8M1_13TeV-powheg-pythia8_PRIVATE-MC/lbenato-RunIISummer16-PU_standard_mixing-Moriond17_80X_mcRun2_2016_MINIAOD-28028af67189b3de7224b79195bd0e1d/USER'

#Private production:
#config.Data.inputDBS = 'phys03'
config.Data.inputDBS = 'global'

#config.Data.splitting = 'LumiBased'
#config.Data.splitting = 'FileBased'
config.Data.splitting = 'Automatic'

###If real data, we can specify the json file, CRAB automatically takes care of it:
#config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'
###this number could need to be tuned for larger datasets--CRAB cannot handle too many jobs, or few jobs with too many data (timeout)
#config.Data.unitsPerJob = 10

###In case you need to publish your output files in a T2 (they must be edm files)
config.Data.outLFNDirBase = '/store/user/lbenato/Brian_ntuples_v1'
#config.Data.publication = False
#config.Data.outputDatasetTag = 'MET_trigger'
#config.Data.publishDBS = 'https://cmsweb.cern.ch/dbs/prod/phys03/DBSWriter/'

###Storage site in case you want to write on a T2, this is not needed
#config.Site.storageSite = 'T2_IT_Legnaro'
config.Site.storageSite = 'T2_DE_DESY'

config.Site.blacklist   = ['T2_FR_IPHC']
