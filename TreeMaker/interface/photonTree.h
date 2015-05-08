#ifndef __PHOTON_TREE_H_
#define __PHOTON_TREE_H_

/*
Log:
Sep 10, 2011
Anil Singh: Empty template created. 
*/

#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include "TTree.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "RecoEgamma/EgammaTools/interface/ConversionFinder.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "EGamma/EGammaAnalysisTools/src/PFIsolationEstimator.cc"
#include "DelPanj/TreeMaker/interface/utils.h"
#include "DelPanj/TreeMaker/interface/baseTree.h"

using namespace std;
using namespace edm;

class photonTree : public baseTree{

 public:
  photonTree(std::string name, TTree* tree, const edm::ParameterSet& cfg);
  ~photonTree();
  void Fill(const edm::Event& iEvent);
  void SetBranches();
  void Clear();

 private:
  photonTree(){};
  edm::InputTag recVtxsLabel_;
  edm::InputTag photonLabel_;
  edm::InputTag gsfElectronLabel_;
  edm::InputTag convLabel_;
  edm::InputTag beamSpotLabel_;
  edm::InputTag pfCandidatesLabel_;

  //variables which would become branches
  Float_t rho2012_;
  Int_t nPho_;
  std::vector<Float_t> phoEt_;
  std::vector<Float_t> phoSCEta_;
  std::vector<Float_t> phoPhi_;  
  std::vector<Int_t>   phoEleVeto_;
  std::vector<Float_t> phoSigmaIEtaIEta_;
  std::vector<Float_t> phoHoverE12_;
  std::vector<Float_t> phoPFChIso_;
  std::vector<Float_t> phoPFNeuIso_;
  std::vector<Float_t> phoPFPhoIso_;
  std::vector<Float_t> phoR9_;
  std::vector<Float_t> phoHoverE_;
  std::vector<Float_t> phoHcalIsoDR03_;
  std::vector<Float_t> phoTrkIsoHollowDR03_;
  std::vector<std::vector<Float_t>> phoCiCPF4chgpfIso02_;

};

#endif

