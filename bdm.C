#define bdm_cxx
#include "bdm.h"
#include <TH2.h>
#include <TH3.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <fstream>
#include <TVector3.h>
#include <iostream>
#include <TLorentzVector.h>

#define MUON_MASS 0.1056
#define PION_MASS 0.1396
#define PROTON_MASS 0.9382

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

void bdm::Analysis()
{

   TVector3 P_Vector;
   TVector3 P_Vector_unit;

   TH1F *CosThetaSun = new TH1F("CosThetaSun", "Total Momentum Track (#theta_{Sun})", 70, -1.2, 1.2);
   TH1F *MomPDist = new TH1F("MomPDist", "Momentum Distribution of Tracks", 70, 0, 2);

   TH1F *CosThetaDetShowerDir = new TH1F("CosThetaDetShowerDir", "Incident DM (#theta_{det})", 40, 0, M_PI + 0.00001);
   TH1F *CosPhiDetShowerDir = new TH1F("CosPhiDetShowerDir", "Incident DM (#phi_{det})", 40, -M_PI, M_PI + 0.000001);
   TH2D *Contour = new TH2D("Contour", "Contour Plot Showers Direction", 50, 0, M_PI, 50, -M_PI, M_PI);

   TH1F *CosThetaDetTrackDir = new TH1F("CosThetaDetTrackDir", "CosThetaDetTrackDir (#theta_{det})", 40, 0, M_PI + 0.00001);
   TH1F *CosPhiDetTrackDir = new TH1F("CosPhiDetTrackDir", "CosPhiDetTrackDir (#phi_{det})", 40, -M_PI, M_PI + 0.000001);
   TH2D *ContourTrack = new TH2D("ContourTrack", "ContourTrack Plot Direction", 50, 0, M_PI, 50, -M_PI, M_PI);

   TH2D *TotalMomvsCos = new TH2D("TotalMomvsCos", "Total Momentum vs cos(#theta_{Sun})", 40, -1.1, 1.1, 40, 0, 6);
   TotalMomvsCos->GetXaxis()->SetTitle("Cos(#theta_{Sun})");
   TotalMomvsCos->GetYaxis()->SetTitle("Total Momentum Mag/ Event [GeV/c]");

   TH2D *DistVtxZReco = new TH2D("DistVtxZReco", " ", 40, -1, 750, 40, 0, 2000);
   DistVtxZReco->GetXaxis()->SetTitle("Vtx Reco distance from Z axis [cm] ");
   DistVtxZReco->GetYaxis()->SetTitle("Primary Vertex distance |Reco-Truth| [cm]");

   TH2D *DistVtxCos = new TH2D("DistVtxCos", " ", 40, -1.1, 1.1, 40, 0, 5);
   DistVtxCos->GetXaxis()->SetTitle("Cos(#theta_{Sun})");
   DistVtxCos->GetYaxis()->SetTitle("Primary Vertex distance |Reco-Truth| [cm]");

   TH2D *DistVtxXReco = new TH2D("DistVtxXReco", " ", 40, -1, 2000, 40, 0, 2000);
   DistVtxXReco->GetXaxis()->SetTitle("Vtx Reco distance from X axis [cm] ");
   DistVtxXReco->GetYaxis()->SetTitle("Primary Vertex distance |Reco-Truth| [cm]");

   TH2D *DistVtxYReco = new TH2D("DistVtxYReco", " ", 40, -1, 2000, 40, 0, 2000);
   DistVtxYReco->GetXaxis()->SetTitle("Vtx Reco distance from Y axis [cm] ");
   DistVtxYReco->GetYaxis()->SetTitle("Primary Vertex distance |Reco-Truth| [cm]");

   TH1F *KE = new TH1F("KE Distribution", "KE Distribution of Daughters Tracks", 60, -0.0001, 2);

   // TH2D *dEdx = new TH2D("dEdx", "dEdx vs. Residual Range" )

   CosThetaDetShowerDir->GetXaxis()->SetTitle("#theta_{det}");
   CosPhiDetShowerDir->GetXaxis()->SetTitle("#phi_{det}");
   Contour->GetXaxis()->SetTitle("#theta_{det}");

   CosThetaDetShowerDir->GetYaxis()->SetTitle("Number of Showers");
   CosPhiDetShowerDir->GetYaxis()->SetTitle("Number of Showers");
   Contour->GetYaxis()->SetTitle("#phi_{det}");

   CosThetaSun->GetXaxis()->SetTitle("Cos(#theta_{Sun})");
   CosThetaSun->GetYaxis()->SetTitle("Number of Events");

   CosThetaDetTrackDir->GetXaxis()->SetTitle("#theta_{det}");
   CosPhiDetTrackDir->GetXaxis()->SetTitle("#phi_{det}");
   ContourTrack->GetXaxis()->SetTitle("#theta_{det}");

   CosThetaDetTrackDir->GetYaxis()->SetTitle("Number of Tracks");
   CosPhiDetTrackDir->GetYaxis()->SetTitle("Number of Tracks");
   ContourTrack->GetYaxis()->SetTitle("#phi_{det}");

   TH1F *VertexX = new TH1F("VertexX", "Vertex X  Daughters of 'Pandora Neutrinos Primaries' ", 100, -500, 500);
   TH1F *VertexY = new TH1F("VertexY", "Vertex Y  Daughters of 'Pandora Neutrinos Primaries' ", 100, -700, 700);
   TH1F *VertexZ = new TH1F("VertexZ", "Vertex Z  Daughters of 'Pandora Neutrinos Primaries' ", 100, 0, 1800);
   TH3D *DetecDistVertex = new TH3D("DetecDistVertex", "Detector distribution of vertexes", 200, -500, 500, 200, -700, 700, 200, 0, 1800);

   TH1F *ShowerStartX = new TH1F("ShowerStartX", "Shower Start X  Daughters of 'Pandora Neutrinos Primaries' ", 100, -500, 500);
   TH1F *ShowerStartY = new TH1F("ShowerStartY", "Shower Start Y  Daughters of 'Pandora Neutrinos Primaries' ", 100, -700, 700);
   TH1F *ShowerStartZ = new TH1F("ShowerStartZ", "Shower Start Z  Daughters of 'Pandora Neutrinos Primaries' ", 100, 0, 1800);
   TH3D *DetecDistShowerStart = new TH3D("DetecDistShowerStart", "Detector distribution of Showers Start", 200, -500, 500, 200, -700, 700, 200, 0, 1800);

   TH1F *TrackDaughterStartX = new TH1F("TrackDaughterStartX", "TrackDaughterStartX  Daughters of 'Pandora Neutrinos Primaries' ", 100, -500, 500);
   TH1F *TrackDaughterStartY = new TH1F("TrackDaughterStartY", "TrackDaughterStartY  Daughters of 'Pandora Neutrinos Primaries' ", 100, -700, 700);
   TH1F *TrackDaughterStartZ = new TH1F("TrackDaughterStartZ", "TrackDaughterStartZ Daughters of 'Pandora Neutrinos Primaries' ", 100, 0, 1800);
   TH3D *DetecDistTrackDaughterStart = new TH3D("DetecDistTrackDaughterStart", "Detector distribution of Tracks Start", 200, -500, 500, 200, -700, 700, 200, 0, 1800);

   TrackDaughterStartX->GetXaxis()->SetTitle("X [cm]");
   TrackDaughterStartY->GetXaxis()->SetTitle("Y [cm]");
   TrackDaughterStartZ->GetXaxis()->SetTitle("Z [cm]");

   TrackDaughterStartX->GetYaxis()->SetTitle("Number");
   TrackDaughterStartY->GetYaxis()->SetTitle("Number");
   TrackDaughterStartZ->GetYaxis()->SetTitle("Number");

   VertexX->GetXaxis()->SetTitle("X [cm]");
   VertexY->GetXaxis()->SetTitle("Y [cm]");
   VertexZ->GetXaxis()->SetTitle("Z [cm]");

   VertexX->GetYaxis()->SetTitle("Number");
   VertexY->GetYaxis()->SetTitle("Number");
   VertexZ->GetYaxis()->SetTitle("Number");

   ShowerStartX->GetXaxis()->SetTitle("X [cm]");
   ShowerStartY->GetXaxis()->SetTitle("Y [cm]");
   ShowerStartZ->GetXaxis()->SetTitle("Z [cm]");

   ShowerStartX->GetYaxis()->SetTitle("Number");
   ShowerStartY->GetYaxis()->SetTitle("Number");
   ShowerStartZ->GetYaxis()->SetTitle("Number");

   Long64_t nentries = fChain->GetEntriesFast();

   std::cout << "Hello, we are starting " << std::endl;

   Long64_t nbytes = 0, nb = 0;

   int nVertexes, nShowers, nShowersDir, nTracks;
   int nTotalVertexes = 0, nTotalShowers = 0, nTotalTracks = 0;
   int nCC_ev = 0, nNC_ev = 0;
   int nEvents = 0;
   int i = 0;
   int whichParticle = 0;

   int nTrkProtons = 0, nTrkMuons = 0;

   TVector3 TotalMomTrackEv;
   TVector3 TrueDMDir;

   ofstream events, evno;

   evno.open("evno.txt");

   events.open("events.txt");
   events << "nEvent"
          << "\t"
          << "nTrack"
          << "\t"
          << "TrackMomentumForMuon"
          << "\t"
          << "TrackMomentumForProton"
          << "\t"
          << "TrackParticle"
          << "\t"
          << "TrackStartDirectionX"
          << "\t"
          << "TrackStartDirectionY"
          << "\t"
          << "TrackStartDirectionZ"
          << "\t"
          << "P_MAG"
          << "\t"
          << "DMTrueDirectionX"
          << "\t"
          << "DMTrueDirectionY"
          << "\t"
          << "DMTrueDirectionZ" << std::endl;

   for (Long64_t jentry = 0; jentry < nentries; jentry++)
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0)
         break;
      nb = fChain->GetEntry(jentry);

      nbytes += nb;
      nEvents++;

      //std::cout << " InDMInitPosX->size() = " << InDMInitPosX->size() << std::endl;
      //std::cout << " (*InDMInitPosX).at(0) = " << (*InDMInitPosX).at(0) << std::endl;

      // 0=CC 1=NC
      //std::cout << " intCCNC.size() = " << intCCNC->size() << std::endl;

      nVertexes = VtxXYZ->size();
      nShowers = SwrShowerStart->size();
      nShowersDir = SwrDirection->size();
      nTracks = DaughterTrackLengths->size();

      nTotalTracks += nTracks;
      nTotalVertexes += nVertexes;
      nTotalShowers += nShowers;

      for (int p = 0; p < nVertexes; p++)
      {
         // std::cout << "p ="  << p << "InDMInitPosX = " << (*InDMInitPosX).at(p) << std::endl;
         VertexX->Fill((*VtxXYZ).at(p).X());
         VertexY->Fill((*VtxXYZ).at(p).Y());
         VertexZ->Fill((*VtxXYZ).at(p).Z());
         DetecDistVertex->Fill((*VtxXYZ).at(p).X(), (*VtxXYZ).at(p).Y(), (*VtxXYZ).at(p).Z());
      }

      for (int p = 0; p < nShowers; p++)
      {
         // std::cout << "p ="  << p << "InDMInitPosX = " << (*InDMInitPosX).at(p) << std::endl;
         ShowerStartX->Fill((*SwrShowerStart).at(p).X());
         ShowerStartY->Fill((*SwrShowerStart).at(p).Y());
         ShowerStartZ->Fill((*SwrShowerStart).at(p).Z());
         DetecDistShowerStart->Fill((*SwrShowerStart).at(p).X(), (*SwrShowerStart).at(p).Y(), (*SwrShowerStart).at(p).Z());
      }

      for (int p = 0; p < nShowersDir; p++)
      {
         // std::cout << "p ="  << p << "InDMInitPosX = " << (*InDMInitPosX).at(p) << std::endl;
         P_Vector.SetXYZ((*SwrDirection).at(p).X(), (*SwrDirection).at(p).Y(), (*SwrDirection).at(p).Z());
         P_Vector_unit = P_Vector.Unit();

         CosThetaDetShowerDir->Fill(P_Vector_unit.Theta());
         CosPhiDetShowerDir->Fill(P_Vector_unit.Phi());
         Contour->Fill(P_Vector_unit.Theta(), P_Vector_unit.Phi());
      }

      TVector3 VtxPrimary;
      bool VtxFlag = false;

      // std::cout << "PrimaryBDMVertex->size() = " << PrimaryBDMVertex->size() << std::endl;
      // std::cout << " IsVtxPrimary->size() = " <<  IsVtxPrimary->size() << std::endl;
      // std::cout << "VtxXYZ->size() = " << VtxXYZ->size() << std::endl;

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

      double VtxDistTrueReco = (VtxPrimary - PrimaryBDMVertex->at(0)).Mag();
      //std::cout << "VtxDistTrueReco = " << VtxDistTrueReco << std::endl;
      double VtxDistXReco = sqrt(VtxPrimary.Y() * VtxPrimary.Y() + VtxPrimary.Z() * VtxPrimary.Z());
      double VtxDistYReco = sqrt(VtxPrimary.X() * VtxPrimary.X() + VtxPrimary.Z() * VtxPrimary.Z());
      double VtxDistZReco = VtxPrimary.Mag() * sin(VtxPrimary.Theta());

      DistVtxXReco->Fill(VtxDistXReco, VtxDistTrueReco);
      DistVtxYReco->Fill(VtxDistYReco, VtxDistTrueReco);
      DistVtxZReco->Fill(VtxDistZReco, VtxDistTrueReco);


      if (SunDirectionFromTrueBDM->size() != 1)
         std::cout << " SunDirectionFromTrueBDM->size() " << SunDirectionFromTrueBDM->size() << std::endl;
      TrueDMDir.SetXYZ(0, 0, 0);
      TrueDMDir = (*SunDirectionFromTrueBDM).at(0);

      TotalMomTrackEv.SetXYZ(0, 0, 0);

      for (int p = 0; p < DaughterStartDirection->size(); p++)
      {
         P_Vector.SetXYZ(0, 0, 0);

         P_Vector.SetXYZ((*DaughterStartDirection).at(p).X(), (*DaughterStartDirection).at(p).Y(), (*DaughterStartDirection).at(p).Z());
         // std::cout << "(*DaughterStartDirection).at(p).X() = " << (*DaughterStartDirection).at(p).X() << std::endl;
         int best_plane = (*best_plane_pid).at(p);
         // std::cout << "(*best_plane_pid).at(p) = " << (*best_plane_pid).at(p) << std::endl;
         std::vector<int> IsProton1 = (*track_PID_pdg).at(p);

         int IsProton = IsProton1[best_plane];

         // std::cout << "IsProton = " << IsProton << std::endl;
         if (!(*track_isContained).at(p))
            continue;

         double Pmodulus = 0;
         if (IsProton == 2212)
         {
            Pmodulus = (*DaughterTrackMomentumIfProton).at(p);
            //std::cout << "IS A PROTON WITH MOMENTUM " << Pmodulus << std::endl;
            nTrkProtons++;
            whichParticle = 2212;
         }
         else
         {
            Pmodulus = (*DaughterTrackMomentumIfMuon).at(p);
            //std::cout << "IS A MUON WITH MOMENTUM " << Pmodulus  << std::endl;
            nTrkMuons++;
            whichParticle = 13;
         }

         double distVtxStart = (PrimaryBDMVertex->at(0) - (*DaughterStartPoint).at(p)).Mag();
         double distVtxEnd = (PrimaryBDMVertex->at(0) - (*DaughterEndPoint).at(p)).Mag();

         //std::cout << "distVtxStart = " << distVtxStart << std::endl;
         //std::cout << "distVtxEnd = " << distVtxEnd << std::endl;
         //std::cout << "Pmodulus = " << Pmodulus << std::endl;

         if ((distVtxEnd < distVtxStart && !VtxFlag) || (*DaughterMultiScatterStartingPoint).at(p) != (*DaughterStartPoint).at(p))
         {
            P_Vector = -P_Vector;
            evno << "Event No = " << EventNo << std::endl;
            if(EventNo == 41219){ std::cout << PrimaryBDMVertex->at(0).X() << "\t" << PrimaryBDMVertex->at(0).Y() << "\t" << PrimaryBDMVertex->at(0).Z() << std::endl;
            std::cout << VtxPrimary.X() << "\t" << VtxPrimary.Y() << "\t" << VtxPrimary.Z() << std::endl; }
            i++;
         }

         // std::cout << "P_Vector.Mag() = " << P_Vector.Mag() << std::endl;

         //std::cout << "Pmodulus = " << Pmodulus << std::endl;
         //std::cout << P_Vector.X()<< "\t" << P_Vector.Y()<< "\t" << P_Vector.Z()<< "\t" << Pmodulus << std::endl;

         double EnergyTrack = -999;
         if (whichParticle == 13)
         {

            EnergyTrack = sqrt(MUON_MASS * MUON_MASS + Pmodulus * Pmodulus);
            // Pmodulus = sqrt(EnergyTrack*EnergyTrack - PION_MASS*PION_MASS);
            // if((EnergyTrack*EnergyTrack - PION_MASS*PION_MASS) < 0.0 ) std::cout << "Pion Mom2 = " << EnergyTrack*EnergyTrack - PION_MASS*PION_MASS << std::endl;
         }
         else if (whichParticle == 2212)
         {
            EnergyTrack = sqrt(PROTON_MASS * PROTON_MASS + Pmodulus * Pmodulus);
         }

         P_Vector = Pmodulus * P_Vector.Unit();
         KE->Fill(EnergyTrack);
         MomPDist->Fill(Pmodulus);

         TotalMomTrackEv += P_Vector;

         events << jentry << "\t" << p << "\t" << (*DaughterTrackMomentumIfMuon).at(p) << "\t" << (*DaughterTrackMomentumIfProton).at(p) << "\t" << whichParticle << "\t" << (*DaughterStartDirection).at(p).X() << "\t" << (*DaughterStartDirection).at(p).Y() << "\t" << (*DaughterStartDirection).at(p).Z() << "\t" << Pmodulus << "\t" << TrueDMDir.X() << "\t" << TrueDMDir.Y() << "\t" << TrueDMDir.Z() << std::endl;

         //std::cout << "TotalMomTrackEv.CosTheta() = " << TotalMomTrackEv.CosTheta() << std::endl;
         //std::cout <<  "TotalMomTrackEv.Phi() = " << TotalMomTrackEv.Phi() << std::endl;
         //std::cout << "TotalMomTrackEv.Mag() = " << TotalMomTrackEv.Mag() << std::endl;
      }

      for (size_t i = 0; i < nTracks; i++)
      {
         TrackDaughterStartX->Fill((*DaughterStartPoint).at(i).X());
         TrackDaughterStartY->Fill((*DaughterStartPoint).at(i).Y());
         TrackDaughterStartZ->Fill((*DaughterStartPoint).at(i).Z());
         DetecDistTrackDaughterStart->Fill((*DaughterStartPoint).at(i).X(), (*DaughterStartPoint).at(i).Y(), (*DaughterStartPoint).at(i).Z());
      }

      //std::cout << "TotalMomTrackEv.Mag() = " << TotalMomTrackEv.Mag() <<std::endl;
      if (TotalMomTrackEv.Mag() == 0)
         continue;

      double TotalMom = TotalMomTrackEv.Mag();
      TotalMomTrackEv = TotalMomTrackEv.Unit();

      if (TrueDMDir * TotalMomTrackEv < -0.6)
      {
         //std::cout << "TotalMomTrackEv = " << TotalMomTrackEv.X() << "\t" << TotalMomTrackEv.Y() << "\t" << TotalMomTrackEv.Z() <<  std::endl;
         //std::cout << "TrueDMDir = " << TrueDMDir.X() << "\t" << TrueDMDir.Y() << "\t" << TrueDMDir.Z() <<  std::endl;
         //std::cout << "========================================" << std::endl;
      }

      TotalMomvsCos->Fill(TrueDMDir * TotalMomTrackEv, TotalMom);
      CosThetaSun->Fill(TrueDMDir * TotalMomTrackEv);
      DistVtxCos->Fill(TrueDMDir * TotalMomTrackEv, VtxDistTrueReco);
      //std::cout << "cos theta = " << TrueDMDir*TotalMomTrackEv << std::endl;

      CosThetaDetTrackDir->Fill(TotalMomTrackEv.Theta());
      CosPhiDetTrackDir->Fill(TotalMomTrackEv.Phi());
      ContourTrack->Fill(TotalMomTrackEv.Theta(), TotalMomTrackEv.Phi());
      //TotalMomTrackEv.SetXYZ(0, 0, 0);
   }

   TCanvas *InVertexX = new TCanvas;
   TCanvas *InVertexY = new TCanvas;
   TCanvas *InVertexZ = new TCanvas;
   TCanvas *InDet = new TCanvas;

   TCanvas *SwrStartX = new TCanvas;
   TCanvas *SwrStartY = new TCanvas;
   TCanvas *SwrStartZ = new TCanvas;
   TCanvas *DetSwr = new TCanvas;

   TCanvas *InCosTheta = new TCanvas;
   TCanvas *InCosPhi = new TCanvas;
   TCanvas *InContour = new TCanvas;

   TCanvas *TrkStartX = new TCanvas;
   TCanvas *TrkStartY = new TCanvas;
   TCanvas *TrkStartZ = new TCanvas;
   TCanvas *DetTrk = new TCanvas;
   TCanvas *InTrkCosTheta = new TCanvas;
   TCanvas *InTrkCosPhi = new TCanvas;
   TCanvas *InTrkContour = new TCanvas;

   TCanvas *CosSun = new TCanvas;
   TCanvas *KineticE = new TCanvas;
   TCanvas *PDist = new TCanvas;

   TCanvas *PCos = new TCanvas;
   TCanvas *Dist = new TCanvas;
   TCanvas *DistVtx = new TCanvas;
   TCanvas *DistVtxXReco_can = new TCanvas;
   TCanvas *DistVtxYReco_can = new TCanvas;

   InVertexX->cd();
   VertexX->Draw();
   //InVertexX->SaveAs("VertexX.pdf");
   InVertexY->cd();
   VertexY->Draw();
   //InVertexY->SaveAs("VertexY.pdf");
   InVertexZ->cd();
   VertexZ->Draw();
   //InVertexZ->SaveAs("VertexZ.pdf");
   InDet->cd();
   DetecDistVertex->Draw();
   //InDet->SaveAs("DetecDist.pdf");

   SwrStartX->cd();
   ShowerStartX->Draw();

   SwrStartY->cd();
   ShowerStartY->Draw();

   SwrStartZ->cd();
   ShowerStartZ->Draw();

   DetSwr->cd();
   DetecDistShowerStart->Draw();

   InCosTheta->cd();
   CosThetaDetShowerDir->Draw();

   InCosPhi->cd();
   CosPhiDetShowerDir->Draw();

   InContour->cd();
   Contour->Draw("colz");

   TrkStartX->cd();
   TrackDaughterStartX->Draw();
   TrkStartY->cd();
   TrackDaughterStartY->Draw();
   TrkStartZ->cd();
   TrackDaughterStartZ->Draw();
   DetTrk->cd();
   DetecDistTrackDaughterStart->Draw();
   
   InTrkCosTheta->cd();
   CosThetaDetTrackDir->Draw();
   InTrkCosPhi->cd();
   CosPhiDetTrackDir->Draw();
   InTrkContour->cd();
   ContourTrack->Draw("colz");

   KineticE->cd();
   KE->Draw();

   PDist->cd();
   MomPDist->Draw();

   CosSun->cd();
   CosThetaSun->Draw();

   PCos->cd();
   TotalMomvsCos->Draw("colz");

   Dist->cd();
   DistVtxCos->Draw("colz");

   DistVtx->cd();
   DistVtxZReco->Draw("colz");

   DistVtxXReco_can->cd();
   DistVtxXReco->Draw("colz");
   DistVtxYReco_can->cd();
   DistVtxYReco->Draw("colz");

   // std::cout << "------------------------- CCNC == 0 Events -----------------------" << std::endl;
   // std::cout << "nTotalTracks = " << nTotalTracks << std::endl;
   // std::cout << "nTotalVertexes = " << nTotalVertexes << std::endl;
   // std::cout << "nTotalShowers = " << nTotalShowers << std::endl;

   std::cout << "i =" << i << std::endl;

   std::cout << "The total number of events is " << nEvents << std::endl;
   std::cout << "nTrkProtons = " << nTrkProtons << std::endl;
   std::cout << "nTrkMuons = " << nTrkMuons << std::endl;
}
