#!/usr/bin/env python
import os, re
import multiprocessing
import logging
import commands
import math, time
import sys
from ROOT import TObject, TFile, TH1, TH1F
#from Analysis.ALPHA.samples import sample
from array import array

LUMI        =  35867#36814# in pb-1

# use the following lists to include/exclude samples to be merged

blacklist = []
whitelist = []

TIP = "/pnfs/desy.de/cms/tier2/store/user/lbenato/"
#DEST = "/afs/desy.de/user/l/lbenato/LongLivedReconstruction/CMSSW_8_0_26_patch1/src/Analyzer/LongLivedReco/test_recluster_ak4Jets_miniaod_3May2018/"
DEST = "/nfs/dust/cms/user/lbenato/RecoStudies_ntuples_v8/"

########## DO NOT TOUCH BELOW THIS POINT ##########

import argparse

parser = argparse.ArgumentParser(description='combine the LSF outputs into one tree')
parser.add_argument('folder', help='the folder containing the LSF output')
args = parser.parse_args()

if not os.path.exists(os.path.expandvars(args.folder)):
    print '--- ERROR ---'
    print '  \''+args.folder+'\' path not found'
    print '  please point to the correct path to the folder containing the CRAB output' 
    print '  example on NAF: '
    print TIP
    print 
    exit()

jobs = []
names = []

def hadd_singoli(name):
    #if len(whitelist)>0 and not name in whitelist: return
    #if len(blacklist)>0 and name in blacklist: return
    #os.system('pwd')
    #os.system('ls *root')
    if "_PRIVATE-MC" in name:
        short_name = name[:-11]
    else:
        short_name = name
    #if "TT_Tune" in name:
    #    print name
    #    os.system('hadd -f '+DEST+name+'.root '+name+'/*/*/*/output_1*.root')        
    if ("TT_Tune" in name):
        print name
        #os.system('hadd -f '+DEST+name+'.root '+name+'/*/*/*/*.root')# + ' ' +name+'/*/*/*/*_1.root')        
    elif ("QCD_HT50To100" in name) or ("QCD_HT100To200" in name):
        print name
        #os.system('hadd -f '+DEST+name+'.root '+name+'/*/*/*/*.root')# + ' ' +name+'/*/*/*/*_1.root')
    elif ("ZH" in name):
        print name
        #os.system('hadd -f '+DEST+short_name+'.root '+name+'/*/*/*/*.root')
    else:
        print name
        os.system('hadd -f '+DEST+short_name+'.root '+name+'/*/*/*/*.root')
        #os.system('ls '+DEST+name+'.root\n')
pass

subdirs = [x for x in os.listdir(args.folder) if os.path.isdir(os.path.join(args.folder, x))]
#print subdirs

#print args.folder
os.chdir(args.folder)
#print "we are here:"
#os.system('pwd')
#print "list things"
#os.system('ls')
#exit()
for l in subdirs:
    p = multiprocessing.Process(target=hadd_singoli, args=(l,))
    jobs.append(p)
    #print p.name
    p.start()

print "Ntuples ready in ", DEST
os.system('cd '+DEST+".. ")

