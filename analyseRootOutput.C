#include <TFile.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

#include <iostream>
#include <vector>

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
