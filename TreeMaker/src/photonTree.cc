
#include "DelPanj/TreeMaker/interface/photonTree.h"

photonTree::photonTree(std::string name, TTree* tree, const pset& iConfig):baseTree(name,tree){
  recVtxsLabel_      = iConfig.getParameter<edm::InputTag> ("recVtxsLabel");
  photonLabel_       = iConfig.getParameter<edm::InputTag> ("photonLabel");
  gsfElectronLabel_  = iConfig.getParameter<edm::InputTag> ("gsfElectronLabel");
  convLabel_         = iConfig.getParameter<edm::InputTag> ("convLabel");
  beamSpotLabel_     = iConfig.getParameter<edm::InputTag> ("beamSpotLabel");
  pfCandidatesLabel_ = iConfig.getParameter<edm::InputTag> ("pfCandidatesLabel");
  SetBranches();
}

photonTree::~photonTree(){

}

void photonTree::Fill(const edm::Event& iEvent){
  Clear();

  //fetch the input collection
  edm::Handle<std::vector<pat::Photon> > photonHandle;
  if(not iEvent.getByLabel(photonLabel_,photonHandle))
    {
      std::cout<<"FATAL EXCEPTION: "<<"Following Not Found: "<<photonLabel_<<std::endl; 
      return;
    }  
  pat::PhotonCollection phColl(*(photonHandle.product()));


  edm::Handle<reco::VertexCollection> recVtxs;
  if(not iEvent.getByLabel(recVtxsLabel_, recVtxs))
    {
      std::cout<<"FATAL EXCEPTION: "<<"Following Not Found: "<<recVtxsLabel_<<std::endl; 
      return;
    }


  edm::Handle<double> rhoHandle_enReg;
  if(not iEvent.getByLabel(edm::InputTag("kt6PFJets","rho"), rhoHandle_enReg))
    {
      std::cout<<"FATAL EXCEPTION: "<<"Following Not Found: "<< "kt6PFJets rho"<<std::endl; 
      return; 
    }
  rho2012_ = *(rhoHandle_enReg.product());


  edm::Handle<reco::GsfElectronCollection>  gsfElectronHandle;
  if(not iEvent.getByLabel(gsfElectronLabel_, gsfElectronHandle))
    {
      std::cout<<"FATAL EXCEPTION: "<<"Following Not Found: "<< gsfElectronLabel_ <<std::endl; 
      return;
    }


  edm::Handle<reco::ConversionCollection> convH;
  if(not iEvent.getByLabel(convLabel_, convH))
    {
      std::cout<<"FATAL EXCEPTION: "<<"Following Not Found: "<< convLabel_ <<std::endl; 
      return;
    }


  edm::Handle<reco::BeamSpot> beamSpotHandle;
  if(not  iEvent.getByLabel(beamSpotLabel_, beamSpotHandle))
    {
      std::cout<<"FATAL EXCEPTION: "<<"Following Not Found: "<< beamSpotLabel_ <<std::endl; 
      return;
    }



  // for particle-flow isolation
  edm::Handle<reco::PFCandidateCollection> pfCandidates;
  if(not iEvent.getByLabel(pfCandidatesLabel_, pfCandidates))
    {
      std::cout<<"FATAL EXCEPTION: "<<"Following Not Found: "<< pfCandidatesLabel_ <<std::endl; 
      return;
    }


 //sort the objects by transverse momentum
  std::sort(phColl.begin(),phColl.end(),PtGreater());


  const reco::PFCandidateCollection thePfColl = *(pfCandidates.product());
  PFIsolationEstimator isolator;
  isolator.initializePhotonIsolation(kTRUE);
  isolator.setConeSize(0.3);
  VertexRef myVtxRef(recVtxs, 0);

  pat::PhotonCollection::const_iterator ph;
  for(ph=phColl.begin(); ph!=phColl.end(); ph++){
    nPho_++;
    edm::Ptr<reco::Candidate> recoPhoRef = ph->originalObjectRef();
    const reco::Photon *recoPhoton = dynamic_cast<const reco::Photon *>(recoPhoRef.get());
    phoEt_.push_back(ph->et());
    phoSCEta_.push_back(ph->superCluster()->eta());
    phoPhi_.push_back(ph->phi());
    phoEleVeto_.push_back((int)ConversionTools::hasMatchedPromptElectron(recoPhoton->superCluster(), gsfElectronHandle, convH, beamSpotHandle->position()));
    phoSigmaIEtaIEta_.push_back(ph->sigmaIetaIeta());
    phoHoverE12_.push_back(ph->hadTowOverEm());

    isolator.fGetIsolation(recoPhoton, &thePfColl, myVtxRef, recVtxs);
    phoPFChIso_ .push_back(isolator.getIsolationCharged());
    phoPFNeuIso_.push_back(isolator.getIsolationNeutral());
    phoPFPhoIso_.push_back(isolator.getIsolationPhoton());

    phoR9_.push_back(ph->r9());
    phoHoverE_.push_back(ph->hadronicOverEm());
    phoHcalIsoDR03_.push_back(ph->hcalTowerSumEtConeDR03());
    phoTrkIsoHollowDR03_.push_back(ph->trkSumPtHollowConeDR03());
  }  

}

void photonTree::SetBranches(){
  AddBranch(&rho2012_,"phoRho2012");
  AddBranch(&nPho_,"nPho");
  AddBranch(&phoEt_,"phoEt");
  AddBranch(&phoSCEta_,"phoSCEta");
  AddBranch(&phoPhi_,"phoPhi");
  AddBranch(&phoEleVeto_,"phoEleVeto");
  AddBranch(&phoSigmaIEtaIEta_,"phoSigmaIEtaIEta");
  AddBranch(&phoHoverE12_,"phoHoverE12");
  AddBranch(&phoPFChIso_,"phoPFChIso");
  AddBranch(&phoPFNeuIso_,"phoPFNeuIso");
  AddBranch(&phoPFPhoIso_,"phoPFPhoIso");
  AddBranch(&phoR9_,"phoR9");
  AddBranch(&phoHoverE_,"phoHoverE");
  AddBranch(&phoHcalIsoDR03_,"phoHcalIsoDR03");
  AddBranch(&phoTrkIsoHollowDR03_,"phoTrkIsoHollowDR03");
}

void photonTree::Clear(){
  rho2012_ = 0.;
  nPho_ = 0; 
  phoEt_.clear();
  phoSCEta_.clear();
  phoPhi_.clear();
  phoEleVeto_.clear();
  phoSigmaIEtaIEta_.clear();
  phoHoverE12_.clear();
  phoPFChIso_.clear();
  phoPFNeuIso_.clear();
  phoPFPhoIso_.clear();
  phoR9_.clear();
  phoHoverE_.clear();
  phoHcalIsoDR03_.clear();
  phoTrkIsoHollowDR03_.clear();

}
