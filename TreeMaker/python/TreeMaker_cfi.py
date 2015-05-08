import FWCore.ParameterSet.Config as cms
from DelPanj.TreeMaker.eSelXZh_cff import *
from DelPanj.TreeMaker.muSelXZh_global_cff import *
from DelPanj.TreeMaker.muSelXZh_tracker_cff import *

CA8jecUnc='START53_V23_Uncertainty_AK7PFchs.txt'
CA8jecLevels = [
    'START53_V23_L1FastJet_AK7PFchs.txt',
    'START53_V23_L2Relative_AK7PFchs.txt',
    'START53_V23_L3Absolute_AK7PFchs.txt'
    ]
AK5jecUnc='START53_V23_Uncertainty_AK5PFchs.txt'
AK5jecLevels = [
    'START53_V23_L1FastJet_AK5PFchs.txt',
    'START53_V23_L2Relative_AK5PFchs.txt',
    'START53_V23_L3Absolute_AK5PFchs.txt'
    ]

tree = cms.EDAnalyzer(
    'TreeMaker',
    fillPUweightInfo_ = cms.bool(True),
    fillEventInfo_ = cms.bool(True),
    fillGenInfo_   = cms.bool(True),
    fillMuonInfo_  = cms.bool(True),
    fillElecInfo_  = cms.bool(True),
    fillJetInfo_   = cms.bool(True),
    fillMetInfo_   = cms.bool(True),
    fillTrigInfo_  = cms.bool(True),
    fillPhotInfo_  = cms.bool(True),
    genPartLabel=cms.InputTag("genParticles"),
    patMuons=cms.InputTag("patMuonsWithTrigger"),
    patElectrons = cms.InputTag("patElectronsWithTrigger"),
    PrunedJets=cms.InputTag("selectedPatJetsCA8CHSprunedForBoostedTaus"),
    rhoSrc = cms.InputTag('kt6PFJets', 'rho'),
    pvSrc  = cms.InputTag('goodOfflinePrimaryVertices'),
    ### Photon
    recVtxsLabel = cms.InputTag("offlinePrimaryVertices"),
    photonLabel =  cms.InputTag("cleanPatPhotons"),
    gsfElectronLabel = cms.InputTag("gsfElectrons"),
    convLabel = cms.InputTag("allConversions"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    pfCandidatesLabel =cms.InputTag("pfNoPileUpIso"),
    ### CA8Jet
    CA8Jets=cms.InputTag("selectedPatJetsCA8CHSwithQJetsForBoostedTaus"),
    CA8jecPayloadNames = cms.vstring( CA8jecLevels ),
    CA8jecUncName = cms.string(CA8jecUnc),    
    ### AK5Jet
    AK5Jets=cms.InputTag("patJetsWithVarCHS"),
    AK5jecPayloadNames = cms.vstring( AK5jecLevels ),
    AK5jecUncName = cms.string(AK5jecUnc),    
    e2012IDSet  =  eSelXZh,
    globalMuonIDSet = muSelXZh_global,
    trackerMuonIDSet = muSelXZh_tracker,
    eleRhoIso = cms.InputTag("kt6PFJets","rho"),  
    patMetRaw=cms.InputTag("patMETsRaw"),
    patMet = cms.InputTag("patMetShiftCorrected"),
    outFileName=cms.string('outputFileName.root')
    )

