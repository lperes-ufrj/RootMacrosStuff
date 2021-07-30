#define bdm_cxx
#include "bdm.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <fstream>
#include <TVector3.h>
#include <iostream>
#include <TLorentzVector.h>

#define PROTON_MASS 0.9382
#define MUON_MASS 0.1056

void bdm::Loop()
{
   //   In a ROOT session, you can do:
   //      root> .L bdm.C
   //      root> bdm t
   //      root> t.GetEntry(12); // Fill t data members with entry number 12
   //      root> t.Show();       // Show values of entry 12
   //      root> t.Show(16);     // Read and show values of entry 16
   //      root> t.Loop();       // Loop on all entries
   //

   //     This is the loop skeleton where:
   //    jentry is the global entry number in the chain
   //    ientry is the entry number in the current Tree
   //  Note that the argument to GetEntry must be:
   //    jentry for TChain::GetEntry
   //    ientry for TTree::GetEntry and TBranch::GetEntry
   //
   //       To read only selected branches, Insert statements like:
   // METHOD1:
   //    fChain->SetBranchStatus("*",0);  // disable all branches
   //    fChain->SetBranchStatus("branchname",1);  // activate branchname
   // METHOD2: replace line
   //    fChain->GetEntry(jentry);       //read all branches
   //by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0)
      return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry = 0; jentry < nentries; jentry++)
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0)
         break;
      nb = fChain->GetEntry(jentry);
      nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}

bool IsVisibleParticle(int Pdg)
{

   bool condition = false;

   if (Pdg == 130 || Pdg == 130 || Pdg == 211 || (Pdg > 300 && Pdg < 400) || Pdg == 2212 || (Pdg > 3000 && Pdg < 4000))
   {
      condition = true;
   }

   return condition;
}

void bdm::Analysis()
{
   if (fChain == 0)
      return;
   Long64_t nbytes = 0, nb = 0;
   ofstream MomentumTrue, EnergyTrue, PdgTrue, TotalMomentumTrue, PtTotalMomentumTrue, CosSunTotalMomentumTrue, PrimaryVtxXTrue, PrimaryVtxYTrue, PrimaryVtxZTrue;
   ofstream MomentumReco, EnergyReco, PdgReco, TotalMomentumReco, PtTotalMomentumReco, CosSunTotalMomentumReco, PrimaryVtxXReco, PrimaryVtxYReco, PrimaryVtxZReco;
   ofstream fileinevTrue, fileinevReco, fileTrue, fileReco, AngleDiffFile;
   ofstream RecoTrueProton, RecoTruePionMu, RecoTruePartTracks, RecoTrueAngleDiff, CosSunRecoAndTrue;

   ofstream nTracksFlippedPerEvFile, nTotalTracksPerEvFile;

   fileinevReco.open("fileinevReco.dat");
   fileinevTrue.open("fileinevTrue.dat");
   fileTrue.open("fileTrue.dat");
   fileReco.open("fileReco.dat");

   MomentumTrue.open("MomentumTrue.dat");
   EnergyTrue.open("EnergyTrue.dat");
   PdgTrue.open("PdgTrue.dat");
   TotalMomentumTrue.open("TotalMomentumTrue.dat");
   PtTotalMomentumTrue.open("PtTotalMomentumTrue.dat");
   CosSunTotalMomentumTrue.open("CosSunTotalMomentumTrue.dat");
   PrimaryVtxXTrue.open("PrimaryVtxXTrue.dat");
   PrimaryVtxYTrue.open("PrimaryVtxYTrue.dat");
   PrimaryVtxZTrue.open("PrimaryVtxZTrue.dat");

   MomentumReco.open("MomentumReco.dat");
   EnergyReco.open("EnergyReco.dat");
   PdgReco.open("PdgReco.dat");
   TotalMomentumReco.open("TotalMomentumReco.dat");
   PtTotalMomentumReco.open("PtTotalMomentumReco.dat");
   CosSunTotalMomentumReco.open("CosSunTotalMomentumReco.dat");
   PrimaryVtxXReco.open("PrimaryVtxXReco.dat");
   PrimaryVtxYReco.open("PrimaryVtxYReco.dat");
   PrimaryVtxZReco.open("PrimaryVtxZReco.dat");

   RecoTrueProton.open("RecoTrueProtonSignal.dat");
   RecoTruePionMu.open("RecoTruePionMuSignal.dat");
   RecoTruePartTracks.open("RecoTruePartTracksSignal.dat");
   RecoTrueAngleDiff.open("RecoTrueAngleDiff.dat");
   AngleDiffFile.open("AngleDiffFile.dat");
   CosSunRecoAndTrue.open("CosSunRecoAndTrue.dat");

   nTracksFlippedPerEvFile.open("nTracksFlippedPerEvFile.dat");
   nTotalTracksPerEvFile.open("nTotalTracksPerEvFile.dat");

   Long64_t nentries = fChain->GetEntriesFast();
   int nTracksFlipped = 0;
   for (Long64_t jentry = 0; jentry < nentries; jentry++)
   {

      int nRecoMuons = 0, nRecoProtons = 0, nTruePions = 0, nTrueProtons = 0;
      int nRecoTracks = 0, nTrueParticle = 0;
      int nTracksFlippedPerEv = 0;
      int nTotalTracksPerEv = 0;
      

      double AngleTotalMomentumDiff = -9999;

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0)
         break;
      nb = fChain->GetEntry(jentry);
      nbytes += nb;

      TLorentzVector Total4MomentumTrue;
      // std::cout << EventNo << jentry << "\t" << nGeantParticles << "\t" << IsVtxPrimary->size() << "\t" << DaughterStartDirection->size() << "\t" << std::endl;

      for (size_t i = 0; i < nGeantParticles; i++)
      {
         //std::cout << "oi" <<std::endl;
         if (!IsVisibleParticle(MC_PdgCode->at(i)))
         {
            continue;
         }
         if (!isMCinside)
            continue;

         if (MC_Momentum->at(i).Mag() != 0)
         {

            TLorentzVector True4Momentum(MC_Momentum->at(i), MC_StartEnergy->at(i));
            std::cout << i << " X: " << MC_Momentum->at(i).X() << " Y: " << MC_Momentum->at(i).Y() << " Z: " << MC_Momentum->at(i).Z() << std::endl;
            std::cout << MC_Momentum->at(i).Mag() << std::endl;
            std::cout << sqrt(MC_Momentum->at(i).X() * MC_Momentum->at(i).X() + MC_Momentum->at(i).Y() * MC_Momentum->at(i).Y() + MC_Momentum->at(i).Z() * MC_Momentum->at(i).Z()) << std::endl;
            MomentumTrue << MC_Momentum->at(i).Mag() << std::endl;
            EnergyTrue << MC_StartEnergy->at(i) << std::endl;
            PdgTrue << std::abs(MC_PdgCode->at(i)) << std::endl;
            fileTrue << fChain->GetCurrentFile()->GetName() << std::endl;
            if (MC_StartEnergy->at(i) - True4Momentum.Mag() > 0.05)
            {
               nTrueParticle++;
               if (std::abs(MC_PdgCode->at(i)) == 2212)
                  nTrueProtons++;
               if (std::abs(MC_PdgCode->at(i)) == 211)
                  nTruePions++;
            }
            Total4MomentumTrue += True4Momentum;
         }
      }

      if (Total4MomentumTrue.Vect().Mag() != 0)
      {
         TotalMomentumTrue << Total4MomentumTrue.Vect().Mag() << std::endl;
         CosSunTotalMomentumTrue << cos(Total4MomentumTrue.Angle(SunDirectionFromTrueBDM->at(0))) << std::endl;
         PtTotalMomentumTrue << sin(Total4MomentumTrue.Angle(SunDirectionFromTrueBDM->at(0))) * Total4MomentumTrue.Vect().Mag() << std::endl;
         fileinevTrue << fChain->GetCurrentFile()->GetName() << std::endl;

         PrimaryVtxXTrue << PrimaryBDMVertex->at(0).X() << std::endl;
         PrimaryVtxYTrue << PrimaryBDMVertex->at(0).Y() << std::endl;
         PrimaryVtxZTrue << PrimaryBDMVertex->at(0).Z() << std::endl;
      }

      TVector3 VtxPrimary;
      bool VtxFlag = false;

      for (size_t i = 0; i < IsVtxPrimary->size(); i++)
      {
         // std::cout << "IsVtxPrimary = " << (*IsVtxPrimary).at(i) << std::endl;
         if (IsVtxPrimary->size() != VtxXYZ->size())
         {
            VtxFlag = true;
            continue;
         }
         if ((*IsVtxPrimary).at(i) == 1)
            VtxPrimary = (*VtxXYZ).at(i);
      }
      
      TVector3 P_Vector, TotalMomTrackReco;
      for (int p = 0; p < DaughterStartDirection->size(); p++)
      {

         P_Vector.SetXYZ(0, 0, 0);
         P_Vector.SetXYZ((*DaughterStartDirection).at(p).X(), (*DaughterStartDirection).at(p).Y(), (*DaughterStartDirection).at(p).Z());

         int best_plane = (*best_plane_pid).at(p);
         std::vector<int> IsProton1 = (*track_PID_pdg).at(p);
         int IsProton = IsProton1[best_plane];

         if (!(*track_isContained).at(p))
            continue;

         double Pmodulus = 0;
         if (IsProton == 2212)
         {
            Pmodulus = (*DaughterTrackMomentumIfProton).at(p);
            if (Pmodulus != 0)
            {
               PdgReco << "Proton" << std::endl;
               EnergyReco << sqrt(Pmodulus * Pmodulus + PROTON_MASS * PROTON_MASS) << std::endl;
               nRecoProtons++;
            }
         }
         else
         {
            Pmodulus = (*DaughterTrackMomentumIfMuon).at(p);
            if (Pmodulus != 0)
            {
               PdgReco << "Muon" << std::endl;
               EnergyReco << sqrt(Pmodulus * Pmodulus + MUON_MASS * MUON_MASS) << std::endl;
               nRecoMuons++;
            }
         }

         if (Pmodulus != 0)
         {
            double distVtxStart = (PrimaryBDMVertex->at(0) - (*DaughterStartPoint).at(p)).Mag();
            double distVtxEnd = (PrimaryBDMVertex->at(0) - (*DaughterEndPoint).at(p)).Mag();
            MomentumReco << Pmodulus << std::endl;
            
            if ((distVtxEnd < distVtxStart && !VtxFlag) || (*DaughterMultiScatterStartingPoint).at(p) != (*DaughterStartPoint).at(p))
            {
               P_Vector = -P_Vector;
               nTracksFlipped++;
               nTracksFlippedPerEv++;
          
            }
            nTotalTracksPerEv++;
            P_Vector = Pmodulus * P_Vector.Unit();
            TotalMomTrackReco += P_Vector;
            fileReco << fChain->GetCurrentFile()->GetName() << std::endl;
         }
      }
      nTracksFlippedPerEvFile << nTracksFlippedPerEv << std::endl;
      nTotalTracksPerEvFile << nTotalTracksPerEv << std::endl;

      if (TotalMomTrackReco.Mag() != 0)
      {

         TotalMomentumReco << TotalMomTrackReco.Mag() << std::endl;
         PtTotalMomentumReco << sin(TotalMomTrackReco.Angle(SunDirectionFromTrueBDM->at(0))) * TotalMomTrackReco.Mag() << std::endl;
         CosSunTotalMomentumReco << TotalMomTrackReco.Unit() * SunDirectionFromTrueBDM->at(0) << std::endl;
         fileinevReco << fChain->GetCurrentFile()->GetName() << std::endl;
         PrimaryVtxXReco << VtxPrimary.X() << std::endl;
         PrimaryVtxYReco << VtxPrimary.Y() << std::endl;
         PrimaryVtxZReco << VtxPrimary.Z() << std::endl;
      }

      if (Total4MomentumTrue.Vect().Mag() != 0 && TotalMomTrackReco.Mag() != 0){

         RecoTrueAngleDiff << std::abs(Total4MomentumTrue.Angle(SunDirectionFromTrueBDM->at(0)) - acos(TotalMomTrackReco.Unit() * SunDirectionFromTrueBDM->at(0))) << std::endl;
         AngleDiffFile << fChain->GetCurrentFile()->GetName() << std::endl;
         CosSunRecoAndTrue << TotalMomTrackReco.Unit() * SunDirectionFromTrueBDM->at(0)<< "\t"<< cos(Total4MomentumTrue.Angle(SunDirectionFromTrueBDM->at(0)))  << std::endl;

      }

      RecoTruePionMu << nTruePions - nRecoMuons << std::endl;
      RecoTruePartTracks << nTrueParticle - nRecoTracks << std::endl;
      RecoTrueProton << nTrueProtons - nRecoProtons << std::endl;
   }
   std::cout << "nTracksFlipped = " << nTracksFlipped << std::endl;
   MomentumTrue.close();
   EnergyTrue.close();
   PdgTrue.close();
   TotalMomentumTrue.close();
   PtTotalMomentumTrue.close();
   CosSunTotalMomentumTrue.close();
   PrimaryVtxXTrue.close();
   PrimaryVtxYTrue.close();
   PrimaryVtxZTrue.close();

   MomentumReco.close();
   EnergyReco.close();
   PdgReco.close();
   TotalMomentumReco.close();
   PtTotalMomentumReco.close();
   CosSunTotalMomentumReco.close();
   PrimaryVtxXReco.close();
   PrimaryVtxYReco.close();
   PrimaryVtxZReco.close();

   fileReco.close();
   fileTrue.close();
   fileinevTrue.close();
   fileinevReco.close();

   RecoTrueProton.close();
   RecoTruePionMu.close();
   RecoTruePartTracks.close();
   RecoTrueAngleDiff.close();
   AngleDiffFile.close();
   CosSunRecoAndTrue.close();

   nTracksFlippedPerEvFile.close();
   nTotalTracksPerEvFile.close();
}
