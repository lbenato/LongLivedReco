#!/usr/bin/env python
import os


########parser#######
import optparse
usage = "usage: %prog [options]"
parser = optparse.OptionParser(usage)
parser.add_option("-a", "--crabaction", action="store", type="string", dest="crabaction", default="")
parser.add_option("-l", "--lists", action="store", type="string", dest="lists", default="recluster")
(options, args) = parser.parse_args()


####################
crabConfig = ''
if options.lists == "Brian":
    from crab_requests_lists_Brian import *
    crabConfig = 'crabConfig_Brian.py'
    folder = "Brian_ntuples_v1"
elif options.lists == "VH_reco":
    from crab_requests_lists_VH_reco import *
    crabConfig = 'crabConfig_VH_reco.py'
    folder = "LL_reco_with_JECJER_v1"
elif options.lists == "recluster":
    from crab_requests_lists_recluster_jets import *
    crabConfig = 'crabConfig_recluster_jets.py'
    folder = "test_recluster_ak4Jets_miniaod_3May2018"
else:
    print "No list indicated, aborting!"
    exit()

for a, j in enumerate(requests):
    if options.crabaction=="submit":
        if "VBFH_HToSS" in j:
            os.system('echo submitting... ' + crabConfig + ' with options... General.requestName=' + j + ' Data.inputDataset=' + requests[j] + ' Data.inputDBS="phys03" '  + '\n')
            os.system('crab submit -c ' + crabConfig + ' General.requestName=' + j + ' Data.inputDataset=' + requests[j] + ' Data.inputDBS="phys03" '  + '\n')
        else:
            os.system('echo submitting... ' + crabConfig + ' with options... General.requestName=' + j + ' Data.inputDataset=' + requests[j] + '\n')
            os.system('crab submit -c ' + crabConfig + ' General.requestName=' + j + ' Data.inputDataset=' + requests[j] + '\n')
    elif options.crabaction=="status":
        os.system('echo status -d ' + folder + '/crab_'+j+'\n')
        os.system('crab status -d ' + folder + '/crab_'+j+'\n')
        os.system('echo ----------------------------------------------------\n') 
    elif options.crabaction=="resubmit":
        os.system('echo resubmit -d ' + folder + '/crab_'+j+'\n')
        os.system('crab resubmit -d ' + folder + '/crab_'+j+'\n')
    elif options.crabaction=="getoutput":
        os.system('echo getoutput -d ' + folder + '/crab_'+j+'\n')
        os.system('crab getoutput -d ' + folder + '/crab_'+j+'\n')
    elif options.crabaction=="kill":
        os.system('echo kill -d ' + folder + '/crab_'+j+'\n')
        os.system('crab kill -d ' + folder + '/crab_'+j+'\n')
    elif options.crabaction=="report":
        os.system('echo report -d ' + folder + '/crab_'+j+'\n')
        os.system('crab report -d ' + folder + '/crab_'+j+'\n')
    else:
        print "Invalid crab action. Please type: -a submit/status/resubmit/getoutput/kill"
        exit()
os.system('echo -%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-%-\n') 

