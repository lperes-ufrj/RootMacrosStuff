//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Apr 13 08:43:04 2021 by ROOT version 6.16/00
// from TChain RecoParticles//
//////////////////////////////////////////////////////////

#ifndef bdm_h
#define bdm_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"
#include "vector"
#include "TVector3.h"

class bdm {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           EventNo;
   Int_t           RunNo;
   Int_t           SubRunNo;
   Int_t           nPrimaries;
   vector<int>     *nDaughters;
   vector<int>     *PFP_PdgCode;
   vector<int>     *PFP_Parent;
   vector<int>     *PFParticleID;
   Int_t           nPFParticle;
   Int_t           nPFParticleVtxDaughters;
   Int_t           nPFParticleTrkDaughters;
   Int_t           nPFParticleSwrDaughters;
   vector<int>     *VtxStatus;
   vector<int>     *VtxID;
   vector<TVector3> *VtxXYZ;
   vector<bool>    *IsVtxPrimary;
   vector<bool>    *IsVtxDaughter;
   vector<double>  *DaughterTrackLengths;
   vector<TVector3> *DaughterVertexTrack;
   vector<double>  *DaughterStartMomentumTrack;
   vector<double>  *DaughterEndMomentumTrack;
   vector<int>     *intCCNC;
   vector<double>  *SwrID;
   vector<TVector3> *SwrDirection;
   vector<TVector3> *SwrDirectionErr;
   vector<TVector3> *SwrShowerStart;
   vector<TVector3> *SwrShowerStartErr;
   vector<double>  *PandoraNuIDs;
   vector<int>     *Mode;
   vector<int>     *InteractionType;
   vector<TVector3> *DaughterStartPoint;
   vector<TVector3> *DaughterEndPoint;
   vector<TVector3> *DaughterStartDirection;
   vector<vector<double> > *SwrEnergy;
   TVector3        *TotalMomEvent;
   vector<TVector3> *SunDirectionFromTrueBDM;
   vector<int>     *Swrbest_plane;
   vector<vector<float> > *DaughterTrackdEdx;
   vector<vector<float> > *DaughterTrackResidualRange;
   vector<int>     *best_plane_pid;
   vector<int>     *nTrk_Cal;
   vector<int>     *nTrk_Pid;
   vector<vector<double> > *chi2proton;
   vector<vector<int> > *track_PID_pdg;
   vector<bool>    *track_isContained;
   vector<double>  *DaughterTrackKE;
   vector<double>  *DaughterTrackRange;
   vector<double>  *DaughterTrackPitch;
   vector<double>  *DaughterTrackMomentumIfMuon;
   vector<double>  *DaughterTrackMomentumIfProton;
   vector<double>  *DaughterMomentumMultiScatter;
   vector<TVector3> *DaughterMultiScatterStartingPoint;
   vector<TVector3> *PrimaryBDMVertex;
   vector<double>  *InDMMomentum;
   vector<double>  *InDMEnergy;
   vector<double>  *OutDMMomentum;
   vector<double>  *OutDMEnergy;

   // List of branches
   TBranch        *b_EventNo;   //!
   TBranch        *b_RunNo;   //!
   TBranch        *b_SubRunNo;   //!
   TBranch        *b_nPrimaries;   //!
   TBranch        *b_nDaughters;   //!
   TBranch        *b_PFP_PdgCode;   //!
   TBranch        *b_PFP_Parent;   //!
   TBranch        *b_PFParticleID;   //!
   TBranch        *b_nPFParticle;   //!
   TBranch        *b_nPFParticleVtxDaughters;   //!
   TBranch        *b_nPFParticleTrkDaughters;   //!
   TBranch        *b_nPFParticleSwrDaughters;   //!
   TBranch        *b_VtxStatus;   //!
   TBranch        *b_VtxID;   //!
   TBranch        *b_VtxXYZ;   //!
   TBranch        *b_IsVtxPrimary;   //!
   TBranch        *b_IsVtxDaughter;   //!
   TBranch        *b_DaughterTrackLengths;   //!
   TBranch        *b_DaughterVertexTrack;   //!
   TBranch        *b_DaughterStartMomentumTrack;   //!
   TBranch        *b_DaughterEndMomentumTrack;   //!
   TBranch        *b_intCCNC;   //!
   TBranch        *b_SwrID;   //!
   TBranch        *b_SwrDirection;   //!
   TBranch        *b_SwrDirectionErr;   //!
   TBranch        *b_SwrShowerStart;   //!
   TBranch        *b_SwrShowerStartErr;   //!
   TBranch        *b_PandoraNuIDs;   //!
   TBranch        *b_Mode;   //!
   TBranch        *b_InteractionType;   //!
   TBranch        *b_DaughterStartPoint;   //!
   TBranch        *b_DaughterEndPoint;   //!
   TBranch        *b_DaughterStartDirection;   //!
   TBranch        *b_SwrEnergy;   //!
   TBranch        *b_TotalMomEvent;   //!
   TBranch        *b_SunDirectionFromTrueBDM;   //!
   TBranch        *b_Swrbest_plane;   //!
   TBranch        *b_DaughterTrackdEdx;   //!
   TBranch        *b_DaughterTrackResidualRange;   //!
   TBranch        *b_best_plane_pid;   //!
   TBranch        *b_nTrk_Cal;   //!
   TBranch        *b_nTrk_Pid;   //!
   TBranch        *b_chi2proton;   //!
   TBranch        *b_track_PID_pdg;   //!
   TBranch        *b_track_isContained;   //!
   TBranch        *b_DaughterTrackKE;   //!
   TBranch        *b_DaughterTrackRange;   //!
   TBranch        *b_DaughterTrackPitch;   //!
   TBranch        *b_DaughterTrackMomentumIfMuon;   //!
   TBranch        *b_DaughterTrackMomentumIfProton;   //!
   TBranch        *b_DaughterMomentumMultiScatter;   //!
   TBranch        *b_DaughterMultiScatterStartingPoint;   //!
   TBranch        *b_PrimaryBDMVertex;   //!
   TBranch        *b_InDMMomentum;   //!
   TBranch        *b_InDMEnergy;   //!
   TBranch        *b_OutDMMomentum;   //!
   TBranch        *b_OutDMEnergy;   //!

   bdm(TTree *tree=0);
   virtual ~bdm();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual void     Analysis();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef bdm_cxx
bdm::bdm(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("RecoParticles/",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("RecoParticles/","");
      chain->Add("../data/BDM_RecoParticles.root/RecoParticles");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

bdm::~bdm()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t bdm::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t bdm::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void bdm::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   nDaughters = 0;
   PFP_PdgCode = 0;
   PFP_Parent = 0;
   PFParticleID = 0;
   VtxStatus = 0;
   VtxID = 0;
   VtxXYZ = 0;
   IsVtxPrimary = 0;
   IsVtxDaughter = 0;
   DaughterTrackLengths = 0;
   DaughterVertexTrack = 0;
   DaughterStartMomentumTrack = 0;
   DaughterEndMomentumTrack = 0;
   intCCNC = 0;
   SwrID = 0;
   SwrDirection = 0;
   SwrDirectionErr = 0;
   SwrShowerStart = 0;
   SwrShowerStartErr = 0;
   PandoraNuIDs = 0;
   Mode = 0;
   InteractionType = 0;
   DaughterStartPoint = 0;
   DaughterEndPoint = 0;
   DaughterStartDirection = 0;
   SwrEnergy = 0;
   TotalMomEvent = 0;
   SunDirectionFromTrueBDM = 0;
   Swrbest_plane = 0;
   DaughterTrackdEdx = 0;
   DaughterTrackResidualRange = 0;
   best_plane_pid = 0;
   nTrk_Cal = 0;
   nTrk_Pid = 0;
   chi2proton = 0;
   track_PID_pdg = 0;
   track_isContained = 0;
   DaughterTrackKE = 0;
   DaughterTrackRange = 0;
   DaughterTrackPitch = 0;
   DaughterTrackMomentumIfMuon = 0;
   DaughterTrackMomentumIfProton = 0;
   DaughterMomentumMultiScatter = 0;
   DaughterMultiScatterStartingPoint = 0;
   PrimaryBDMVertex = 0;
   InDMMomentum = 0;
   InDMEnergy = 0;
   OutDMMomentum = 0;
   OutDMEnergy = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EventNo", &EventNo, &b_EventNo);
   fChain->SetBranchAddress("RunNo", &RunNo, &b_RunNo);
   fChain->SetBranchAddress("SubRunNo", &SubRunNo, &b_SubRunNo);
   fChain->SetBranchAddress("nPrimaries", &nPrimaries, &b_nPrimaries);
   fChain->SetBranchAddress("nDaughters", &nDaughters, &b_nDaughters);
   fChain->SetBranchAddress("PFP_PdgCode", &PFP_PdgCode, &b_PFP_PdgCode);
   fChain->SetBranchAddress("PFP_Parent", &PFP_Parent, &b_PFP_Parent);
   fChain->SetBranchAddress("PFParticleID", &PFParticleID, &b_PFParticleID);
   fChain->SetBranchAddress("nPFParticle", &nPFParticle, &b_nPFParticle);
   fChain->SetBranchAddress("nPFParticleVtxDaughters", &nPFParticleVtxDaughters, &b_nPFParticleVtxDaughters);
   fChain->SetBranchAddress("nPFParticleTrkDaughters", &nPFParticleTrkDaughters, &b_nPFParticleTrkDaughters);
   fChain->SetBranchAddress("nPFParticleSwrDaughters", &nPFParticleSwrDaughters, &b_nPFParticleSwrDaughters);
   fChain->SetBranchAddress("VtxStatus", &VtxStatus, &b_VtxStatus);
   fChain->SetBranchAddress("VtxID", &VtxID, &b_VtxID);
   fChain->SetBranchAddress("VtxXYZ", &VtxXYZ, &b_VtxXYZ);
   fChain->SetBranchAddress("IsVtxPrimary", &IsVtxPrimary, &b_IsVtxPrimary);
   fChain->SetBranchAddress("IsVtxDaughter", &IsVtxDaughter, &b_IsVtxDaughter);
   fChain->SetBranchAddress("DaughterTrackLengths", &DaughterTrackLengths, &b_DaughterTrackLengths);
   fChain->SetBranchAddress("DaughterVertexTrack", &DaughterVertexTrack, &b_DaughterVertexTrack);
   fChain->SetBranchAddress("DaughterStartMomentumTrack", &DaughterStartMomentumTrack, &b_DaughterStartMomentumTrack);
   fChain->SetBranchAddress("DaughterEndMomentumTrack", &DaughterEndMomentumTrack, &b_DaughterEndMomentumTrack);
   fChain->SetBranchAddress("intCCNC", &intCCNC, &b_intCCNC);
   fChain->SetBranchAddress("SwrID", &SwrID, &b_SwrID);
   fChain->SetBranchAddress("SwrDirection", &SwrDirection, &b_SwrDirection);
   fChain->SetBranchAddress("SwrDirectionErr", &SwrDirectionErr, &b_SwrDirectionErr);
   fChain->SetBranchAddress("SwrShowerStart", &SwrShowerStart, &b_SwrShowerStart);
   fChain->SetBranchAddress("SwrShowerStartErr", &SwrShowerStartErr, &b_SwrShowerStartErr);
   fChain->SetBranchAddress("PandoraNuIDs", &PandoraNuIDs, &b_PandoraNuIDs);
   fChain->SetBranchAddress("Mode", &Mode, &b_Mode);
   fChain->SetBranchAddress("InteractionType", &InteractionType, &b_InteractionType);
   fChain->SetBranchAddress("DaughterStartPoint", &DaughterStartPoint, &b_DaughterStartPoint);
   fChain->SetBranchAddress("DaughterEndPoint", &DaughterEndPoint, &b_DaughterEndPoint);
   fChain->SetBranchAddress("DaughterStartDirection", &DaughterStartDirection, &b_DaughterStartDirection);
   fChain->SetBranchAddress("SwrEnergy", &SwrEnergy, &b_SwrEnergy);
   fChain->SetBranchAddress("TotalMomEvent", &TotalMomEvent, &b_TotalMomEvent);
   fChain->SetBranchAddress("SunDirectionFromTrueBDM", &SunDirectionFromTrueBDM, &b_SunDirectionFromTrueBDM);
   fChain->SetBranchAddress("Swrbest_plane", &Swrbest_plane, &b_Swrbest_plane);
   fChain->SetBranchAddress("DaughterTrackdEdx", &DaughterTrackdEdx, &b_DaughterTrackdEdx);
   fChain->SetBranchAddress("DaughterTrackResidualRange", &DaughterTrackResidualRange, &b_DaughterTrackResidualRange);
   fChain->SetBranchAddress("best_plane_pid", &best_plane_pid, &b_best_plane_pid);
   fChain->SetBranchAddress("nTrk_Cal", &nTrk_Cal, &b_nTrk_Cal);
   fChain->SetBranchAddress("nTrk_Pid", &nTrk_Pid, &b_nTrk_Pid);
   fChain->SetBranchAddress("chi2proton", &chi2proton, &b_chi2proton);
   fChain->SetBranchAddress("track_PID_pdg", &track_PID_pdg, &b_track_PID_pdg);
   fChain->SetBranchAddress("track_isContained", &track_isContained, &b_track_isContained);
   fChain->SetBranchAddress("DaughterTrackKE", &DaughterTrackKE, &b_DaughterTrackKE);
   fChain->SetBranchAddress("DaughterTrackRange", &DaughterTrackRange, &b_DaughterTrackRange);
   fChain->SetBranchAddress("DaughterTrackPitch", &DaughterTrackPitch, &b_DaughterTrackPitch);
   fChain->SetBranchAddress("DaughterTrackMomentumIfMuon", &DaughterTrackMomentumIfMuon, &b_DaughterTrackMomentumIfMuon);
   fChain->SetBranchAddress("DaughterTrackMomentumIfProton", &DaughterTrackMomentumIfProton, &b_DaughterTrackMomentumIfProton);
   fChain->SetBranchAddress("DaughterMomentumMultiScatter", &DaughterMomentumMultiScatter, &b_DaughterMomentumMultiScatter);
   fChain->SetBranchAddress("DaughterMultiScatterStartingPoint", &DaughterMultiScatterStartingPoint, &b_DaughterMultiScatterStartingPoint);
   fChain->SetBranchAddress("PrimaryBDMVertex", &PrimaryBDMVertex, &b_PrimaryBDMVertex);
   fChain->SetBranchAddress("InDMMomentum", &InDMMomentum, &b_InDMMomentum);
   fChain->SetBranchAddress("InDMEnergy", &InDMEnergy, &b_InDMEnergy);
   fChain->SetBranchAddress("OutDMMomentum", &OutDMMomentum, &b_OutDMMomentum);
   fChain->SetBranchAddress("OutDMEnergy", &OutDMEnergy, &b_OutDMEnergy);
   Notify();
}

Bool_t bdm::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void bdm::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t bdm::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef bdm_cxx
