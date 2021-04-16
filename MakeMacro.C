#include <iostream>
#include <fstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

void MakeMacro()
{
    TChain * chain = new TChain("RecoParticles/","");
    
    chain->Add("../data/BDM_RecoParticles.root/RecoParticles");

    chain->MakeClass("bdm");
}