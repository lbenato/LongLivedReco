variable = {}

var_template = {
    "EventNumber": {
      "title" : "event number",
      "nbins" : 10000000,
      "min" : 0,
      "max" : 1.e7,
      "log" : False,
    },
    "LumiNumber": {
      "title" : "lumisection number",
      "nbins" : 2000,
      "min" : 0,
      "max" : 2000,
      "log" : False,
    },
    "RunNumber": {
      "title" : "run number",
      "nbins" : 7000,
      "min" : 254000,
      "max" : 261000,
      "log" : False,
    },
    "nPV": {
      "title" : "number of reconstructed Primary Vertices",
      "nbins" : 50,
      "min" : -0.5,
      "max" : 49.5,
      "log" : False,
    },
    "nJets": {
      "title" : "number of jets",
      "nbins" : 10,
      "min" : -0.5,
      "max" : 9.5,
      "log" : True,
    },
    "nFatJets": {
      "title" : "number of AK8 jets",
      "nbins" : 5,
      "min" : 0.5,
      "max" : 5.5,
      "log" : True,
    },
    # Jets
    "Jet[N].pt": {
      "title" : "jet [N] p_{T} (GeV)",
      "nbins" : 40,
      "min" : 0,
      "max" : 800,
      "log" : True,
    },
    "Jet[N].eta": {
      "title" : "jet [N] #eta",
      "nbins" : 30,
      "min" : -3,
      "max" : 3,
      "log" : False,
    },
    "Jet[N].phi": {
      "title" : "jet [N] #varphi",
      "nbins" : 60,
      "min" : -3.15,
      "max" : 3.15,
      "log" : False,
    },
    "Jet[N].mass": {
      "title" : "jet [N] mass (GeV)",
      "nbins" : 50,
      "min" : 0,
      "max" : 150,
      "log" : False,
    },
    "Jet[N].CSV": {
      "title" : "jet [N] CSV",
      "nbins" : 50,
      "min" : 0,
      "max" : 1,
      "log" : False,
    },
    "Jet[N].flavour": {
      "title" : "jet [N] flavour",
      "nbins" : 25,
      "min" : -0.5,
      "max" : 24.5,
      "log" : False,
    },
    "Jet[N].chf": {
      "title" : "jet [N] charged hadron fraction",
      "nbins" : 20,
      "min" : 0,
      "max" : 1,
      "log" : False,
    },
    "Jet[N].nhf": {
      "title" : "jet [N] neutral hadron fraction",
      "nbins" : 20,
      "min" : 0,
      "max" : 1,
      "log" : False,
    },
    "Jet[N].phf": {
      "title" : "jet [N] photon fraction",
      "nbins" : 20,
      "min" : 0,
      "max" : 1,
      "log" : False,
    },
    "Jet[N].elf": {
      "title" : "jet [N] electron fraction",
      "nbins" : 20,
      "min" : 0,
      "max" : 1,
      "log" : False,
    },
    "Jet[N].muf": {
      "title" : "jet [N] muon fraction",
      "nbins" : 20,
      "min" : 0,
      "max" : 1,
      "log" : False,
    },
    "Jet[N].chm": {
      "title" : "jet [N] charged multiplicity",
      "nbins" : 20,
      "min" : 0,
      "max" : 50,
      "log" : False,
    },

    # MatchedJets
    "MatchedJet[N].pt": {
      "title" : "jet [N] p_{T} (GeV)",
      "nbins" : 40,
      "min" : 0,
      "max" : 800,
      "log" : True,
    },
    "MatchedJet[N].eta": {
      "title" : "jet [N] #eta",
      "nbins" : 30,
      "min" : -3,
      "max" : 3,
      "log" : False,
    },
    "MatchedJet[N].phi": {
      "title" : "jet [N] #varphi",
      "nbins" : 60,
      "min" : -3.15,
      "max" : 3.15,
      "log" : False,
    },
    "MatchedJet[N].mass": {
      "title" : "jet [N] mass (GeV)",
      "nbins" : 50,
      "min" : 0,
      "max" : 150,
      "log" : False,
    },
    "MatchedJet[N].CSV": {
      "title" : "jet [N] CSV",
      "nbins" : 50,
      "min" : 0,
      "max" : 1,
      "log" : False,
    },
    "MatchedJet[N].flavour": {
      "title" : "jet [N] flavour",
      "nbins" : 25,
      "min" : -0.5,
      "max" : 24.5,
      "log" : False,
    },
    "MatchedJet[N].chf": {
      "title" : "jet [N] charged hadron fraction",
      "nbins" : 20,
      "min" : 0,
      "max" : 1,
      "log" : False,
    },
    "MatchedJet[N].nhf": {
      "title" : "jet [N] neutral hadron fraction",
      "nbins" : 20,
      "min" : 0,
      "max" : 1,
      "log" : False,
    },
    "MatchedJet[N].phf": {
      "title" : "jet [N] photon fraction",
      "nbins" : 20,
      "min" : 0,
      "max" : 1,
      "log" : False,
    },
    "MatchedJet[N].elf": {
      "title" : "jet [N] electron fraction",
      "nbins" : 20,
      "min" : 0,
      "max" : 1,
      "log" : False,
    },
    "MatchedJet[N].muf": {
      "title" : "jet [N] muon fraction",
      "nbins" : 20,
      "min" : 0,
      "max" : 1,
      "log" : False,
    },
    "MatchedJet[N].chm": {
      "title" : "jet [N] charged multiplicity",
      "nbins" : 20,
      "min" : 0,
      "max" : 50,
      "log" : False,
    },
    
    # Fatjets
    "FatJet[N].pt": {
      "title" : "jet  p_{T} (GeV)",
      "nbins" : 37,
      "min" : 200,
      "max" : 2050,
      "log" : True,
    },
    "FatJet[N].eta": {
      "title" : "jet [N] #eta",
      "nbins" : 30,
      "min" : -3,
      "max" : 3,
      "log" : False,
    },
    "FatJet[N].phi": {
      "title" : "jet [N] #varphi",
      "nbins" : 60,
      "min" : -3.15,
      "max" : 3.15,
      "log" : False,
    },
    "FatJet[N].mass": {
      "title" : "jet [N] mass (GeV)",
      "nbins" : 54,
      "min" : 30.,
      "max" : 300,
      "log" : False,
    },
    "FatJet[N].CSV": {
      "title" : "fatjet CSV",
      "nbins" : 50,
      "min" : 0,
      "max" : 1,
      "log" : False,
    },
    "FatJet[N].chf": {
      "title" : "jet [N] charged hadron fraction",
      "nbins" : 20,
      "min" : 0,
      "max" : 1,
      "log" : False,
    },
    "FatJet[N].nhf": {
      "title" : "jet [N] neutral hadron fraction",
      "nbins" : 20,
      "min" : 0,
      "max" : 1,
      "log" : False,
    },
    "FatJet[N].phf": {
      "title" : "jet [N] photon fraction",
      "nbins" : 20,
      "min" : 0,
      "max" : 1,
      "log" : False,
    },
    "FatJet[N].elf": {
      "title" : "jet [N] electron fraction",
      "nbins" : 20,
      "min" : 0,
      "max" : 1,
      "log" : False,
    },
    "FatJet[N].muf": {
      "title" : "jet [N] muon fraction",
      "nbins" : 20,
      "min" : 0,
      "max" : 1,
      "log" : False,
    },
    "FatJet[N].chm": {
      "title" : "jet [N] charged multiplicity",
      "nbins" : 50,
      "min" : 0,
      "max" : 50,
      "log" : False,
    },
    # GenBquarks
    "GenBquark[N].pt": {
      "title" : "gen b-quark [N] p_{T} (GeV)",
      "nbins" : 40,
      "min" : 0,
      "max" : 800,
      "log" : True,
    },
    "GenBquark[N].radius": {
      "title" : "gen b-quark [N] radius (mm)",
      "bins" : [0,0.0001,0.001,0.01,0.1,0.5,1,2,5,10,25,50,100,200,300,500,700,1000,2000,3000,5000,7000,10000,20000,50000],
      "nbins" : 100,
      "min" : 0.000001,
      "max" : 100000,
      "log" : True,
      "logx" : True,
    },
}


for n, v in var_template.iteritems():
    if '[N]' in n:
        for i in range(1, 5):
            ni = n.replace('[N]', "%d" % i)
            variable[ni] = v.copy()
            variable[ni]['title'] = variable[ni]['title'].replace('[N]', "%d" % i)
    elif n.startswith('H.'):
        variable[n] = v
        variable[n.replace('H.', 'HMerged.')] = v.copy()
        variable[n.replace('H.', 'HResolved.')] = v.copy()
        variable[n.replace('H.', 'HResolvedHpt.')] = v.copy()
    elif n.startswith('X.'):
        variable[n] = v
        variable[n.replace('X.', 'XMerged.')] = v.copy()
        variable[n.replace('X.', 'XResolved.')] = v.copy()
        variable[n.replace('X.', 'XResolvedHpt.')] = v.copy()
    else:
        variable[n] = v

# Custom settings
variable['Jet2.pt']['max'] = 400
variable['Jet3.pt']['max'] = 200
variable['Jet4.pt']['max'] = 200

# For treealpha
#for n, v in var_template.iteritems(): variable[n.replace('.', '_')] = v.copy()
