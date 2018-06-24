#include <iostream>
#include <vector>
#include <iomanip>

#include "TFile.h"
#include "TObject.h"
#include "TKey.h"
#include "TF1.h"
#include "TString.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraphAsymmErrors.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TLine.h"
#include "TLegend.h"
#include <TROOT.h>

#include "TSystem.h"
#include "TGaxis.h"

#include <cstdlib>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TObjString.h"
#include "TH2D.h"

using namespace std;

void prueba(){

int xmin=0;
int xmax=20;
int nbins=xmax-xmin+1;


TH1D *h2 = new TH1D("ohdu2", "Prueba", nbins, xmin, xmax);
TH1D *h3 = new TH1D("ohdu3", "Prueba", nbins, xmin, xmax);
TH1D *h4 = new TH1D("ohdu4", "Prueba", nbins, xmin, xmax);
TH1D *h5 = new TH1D("ohdu5", "Prueba", nbins, xmin, xmax);

// Open the file containing the tree.
TFile *myFile = TFile::Open("/home/mariano/Desktop/toyMontecarlo/55Fe_exp.root");

// Create a TTreeReader for the tree, for instance by passing the
// TTree's name and the TDirectory / TFile it is in.
TTreeReader myReader("hitSumm", myFile);
// The branch "px" contains floats; access them as myPx.
TTreeReaderValue<Float_t> n(myReader, "n");
TTreeReaderValue<Int_t> runID(myReader, "runID");
TTreeReaderValue<Int_t> ohdu(myReader, "ohdu");
TTreeReaderValue<Int_t> expoStart(myReader, "expoStart");
TTreeReaderValue<Int_t> nSat(myReader, "nSat");
TTreeReaderValue<Int_t> flag(myReader, "flag");
TTreeReaderValue<Int_t> xMin(myReader, "xMin");
TTreeReaderValue<Int_t> xMax(myReader, "xMax");
TTreeReaderValue<Int_t> yMin(myReader, "yMin");
TTreeReaderValue<Int_t> yMax(myReader, "yMax");
TTreeReaderValue<Float_t> e(myReader, "e");
TTreeReaderValue<Float_t> xBary(myReader, "xBary");
TTreeReaderValue<Float_t> yBary(myReader, "yBary");
TTreeReaderValue<Float_t> xVar(myReader, "xVar");
TTreeReaderValue<Float_t> yVar(myReader, "yVar");
TTreeReaderValue<Int_t> nSavedPix(myReader, "nSavedPix");
TTreeReaderValue<Int_t> xPix(myReader, "xPix");
TTreeReaderValue<Int_t> yPix(myReader, "yPix");
TTreeReaderValue<Float_t> ePix(myReader, "ePix");


   // Loop over all entries of the TTree or TChain.
   while (myReader.Next()) {
      // Just access the data as if myPx and myPy were iterators (note the '*'
      // in front of them):
      if (*e>4 && *ohdu==4){
        h2->Fill(*n);
      }
      if (*e>4 && *ohdu==4){
        h3->Fill(*n);
      }
      if (*e>4 && *ohdu==4){
        h4->Fill(*n);
      }
      if (*e>4 && *ohdu==5){
        h5->Fill(*n);
      }
    }
TCanvas *ch2p2 = new TCanvas("ch2p2","ch2p2",1000,1000);

h2-> Sumw2(); h3-> Sumw2(); h4-> Sumw2(); h5-> Sumw2();
ch2p2->Divide(2,2);
ch2p2->cd(1);
h2->Draw("hist e"); // Interactions
ch2p2->cd(2);
h3->Draw("hist e"); // Dark Current
ch2p2->cd(3);
h4->Draw("hist e"); // Interactions + Dark Current
ch2p2->cd(4);
h5->Draw("hist e"); // Interactions + Dark Current






}
