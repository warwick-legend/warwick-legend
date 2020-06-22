#include <TFile.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

std::vector<int> eventNetwork(int item, TTreeReaderValue<std::vector<int>> &tid,
                              TTreeReaderValue<std::vector<int>> &pid) {
  int idx = 0;
  int pidx = 0;
  std::vector<int> result;
  std::vector<int>::iterator it;

  it = std::find(tid->begin(), tid->end(), item);

  while (it != tid->end()) // find all links in the chain
  {
    idx = (it - tid->begin()); // location of id
    result.push_back(idx);

    pidx = pid->at(idx); // next to look for
    it = std::find(tid->begin(), tid->end(), pidx);
  }

  return result;
}

void PrintOut(int p, double vx, double vy, double vz, std::vector<double> tx,
              std::vector<double> ty, std::vector<double> tz) {
  std::cout << ">>> Event output: track by track" << std::endl;
  std::cout << ">> pdg:" << p << std::endl;
  std::cout << " vertex track x: " << vx << ", " << vy << ", " << vz
            << std::endl;
  std::cout << ">> track points: " << std::endl;
  for (auto i = 0; i < tx.size(); ++i)
    std::cout << "x=" << tx.at(i) << ", y=" << ty.at(i) << ", z=" << tz.at(i)
              << std::endl;
}

void analyse(TString inFile, TString outFile) {
  int counter = 0;
  int pdgcode = 0;
  double vtxX = 0.0;
  double vtxY = 0.0;
  double vtxZ = 0.0;

  std::vector<double> trjx;
  std::vector<double> trjy;
  std::vector<double> trjz;

  TFile *fout = new TFile(outFile.Data(), "RECREATE");
  TTree *tr = new TTree("scoreHistory", "Trajectories with Germanium Hit");
  tr->Branch("evID", &counter, "evID/I");
  tr->Branch("pdgCode", &pdgcode, "pdgCode/I");
  tr->Branch("Xvtx", &vtxX, "Xvtx/D");
  tr->Branch("Yvtx", &vtxY, "Yvtx/D");
  tr->Branch("Zvtx", &vtxZ, "Zvtx/D");
  tr->Branch("TrjX", &trjx);
  tr->Branch("TrjY", &trjy);
  tr->Branch("TrjZ", &trjz);
  tr->SetDirectory(fout);

  TFile *fdir = new TFile(inFile.Data(), "READ");
  TTreeReader myreader("Score", fdir);
  TTreeReaderValue<std::vector<int>> htrackid(myreader, "Htrid");
  TTreeReaderValue<std::vector<int>> trjtrackid(myreader, "Trjtid");
  TTreeReaderValue<std::vector<int>> trjparentid(myreader, "Trjpid");
  TTreeReaderValue<std::vector<int>> trjpdg(myreader, "Trjpdg");
  TTreeReaderValue<std::vector<int>> trjentries(myreader, "Trjentries");
  TTreeReaderValue<std::vector<double>> trjxvtx(myreader, "TrjXVtx");
  TTreeReaderValue<std::vector<double>> trjyvtx(myreader, "TrjYVtx");
  TTreeReaderValue<std::vector<double>> trjzvtx(myreader, "TrjZVtx");
  TTreeReaderValue<std::vector<double>> trjxpos(myreader, "TrjXPos");
  TTreeReaderValue<std::vector<double>> trjypos(myreader, "TrjYPos");
  TTreeReaderValue<std::vector<double>> trjzpos(myreader, "TrjZPos");

  // event loop
  while (myreader.Next()) {
    std::cout << " >> event " << counter
              << ", N hits in Ge: " << htrackid->size() << std::endl;
    for (const int &item : *htrackid) {
      std::vector<int> res = eventNetwork(item, trjtrackid, trjparentid);
      for (int &idx : res) {
        pdgcode = trjpdg->at(idx);
        vtxX = trjxvtx->at(idx);
        vtxY = trjyvtx->at(idx);
        vtxZ = trjzvtx->at(idx);
        int start =
            std::accumulate(trjentries->begin(), trjentries->begin() + idx, 0);
        for (int i = start; i < (start + trjentries->at(idx)); ++i) {
          trjx.push_back(trjxpos->at(i));
          trjy.push_back(trjypos->at(i));
          trjz.push_back(trjzpos->at(i));
        }
        tr->Fill();
        PrintOut(pdgcode, vtxX, vtxY, vtxZ, trjx, trjy, trjz);
        trjx.clear();
        trjy.clear();
        trjz.clear();
      }
    }
    counter++;
  } // end event loop
  fdir->Close();

  std::cout << "Total Hit events: " << counter << std::endl;
  fout->Write();
  fout->Close();
}

//  use output TTree for summary and TGraph2D
TGraph2D *graphics(TString fname) {
  TFile *fin = new TFile(fname.Data(), "READ");
  TTreeReader myreader("scoreHistory", fin);
  TTreeReaderValue<double> xvtx(myreader, "Xvtx");
  TTreeReaderValue<double> yvtx(myreader, "Yvtx");
  TTreeReaderValue<double> zvtx(myreader, "Zvtx");

  // event loop
  TGraph2D *gr = new TGraph2D(myreader.GetEntries());
  int npoint = 0;
  while (myreader.Next()) // vertex location graph in 3D
  {
    gr->SetPoint(npoint, *xvtx, *yvtx, *zvtx);
    npoint++;
  }
  gr->SetMarkerStyle(20);
  return gr;
}
