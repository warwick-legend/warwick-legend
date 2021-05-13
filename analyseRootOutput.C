#include <TFile.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

#include <iostream>
#include <vector>

void summary(TString fname) {
  if (fname.IsNull()) fname = "lg.root";

  TFile *fin = new TFile(fname.Data(), "READ");
  TTreeReader myreader("Score", fin);
  TTreeReaderValue<std::vector<int>> hid(myreader, "HitID");
  TTreeReaderValue<std::vector<int>> tn(myreader, "Trjentries");
  TTreeReaderValue<std::vector<double>> edep(myreader, "Edep");
  TTreeReaderValue<std::vector<double>> time(myreader, "Time");
  TTreeReaderValue<std::vector<double>> we(myreader, "Weight");
  TTreeReaderValue<std::vector<double>> xpos(myreader, "Hitxloc");
  TTreeReaderValue<std::vector<double>> ypos(myreader, "Hityloc");
  TTreeReaderValue<std::vector<double>> zpos(myreader, "Hitzloc");
  
  // event loop
  while (myreader.Next())
  {
    for (size_t i=0; i<hid->size();++i) {
      std::cout << "<<< Hit Track ID " << hid->at(i) << std::endl;
      std::cout << "deposited energy [MeV]: " << edep->at(i) << std::endl;
      std::cout << "global time [ns]: " << time->at(i) << std::endl;
      std::cout << "track weight: " << we->at(i) << std::endl;
      std::cout << "pos x [m]: " << xpos->at(i) << std::endl;
      std::cout << "pos y [m]: " << ypos->at(i) << std::endl;
      std::cout << "pos z [m]: " << zpos->at(i) << std::endl;
    }
  }

}


//  use output TTree for summary and TGraph2D
TGraph2D *graphics(TString fname) {
  TFile *fin = new TFile(fname.Data(), "READ");
  TTreeReader myreader("Score", fin);
  TTreeReaderValue<std::vector<double>> xvtx(myreader, "TrjXVtx");
  TTreeReaderValue<std::vector<double>> yvtx(myreader, "TrjYVtx");
  TTreeReaderValue<std::vector<double>> zvtx(myreader, "TrjZVtx");

  // event loop
  TGraph2D *gr = new TGraph2D(myreader.GetEntries());
  int npoint = 0;
  while (myreader.Next()) // vertex location graph in 3D
  {
    for (size_t i=0; i<xvtx->size();++i) {
      gr->SetPoint(npoint, xvtx->at(i), yvtx->at(i), zvtx->at(i));
      npoint++;
    }
  }
  gr->SetMarkerStyle(20);
  return gr;
}
