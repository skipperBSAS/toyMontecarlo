// Este codigo fue escrito para contar cuantos clusters de tamanio n y n+1 hay en el archivo con datos experimentales
// y cuantos en la simulacion Montecarlo, para luego contar cuantos de tamaño n+1 quedan al imponer la condicion de que 
// ninguno de sus pixeles tenga un solo electron.
// Luego se calcula la probabilidad de que un cluster pierda un e en un pixel aledaño.

#include <iostream>
#include <vector>
#include <string>
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

void Enable_and_Set_Branches(TTree* & tree);

// Setting parameters //////////////////////////////////////////////////

// range for the number of electrons per cluster
  int emin = 0; int emax = 2;
  int ohdu_numer = 4;
      
////////////////////////////////////////////////////////////////////////

  int Entries_mc = 1;
  int Entries_exp = 1;
  int xmin = 0; // range for histograms of n
  int xmax =20; // range for histograms of n
  
  int nbins = xmax+1;
  const int maxClusterSize = 50000;
   
////////////////////////////////////////////////////////////////////////

  int runID; int ohdu; int expoStart; 
  int nSat; int flag; 
  int xMin; int xMax;
  int yMin; int yMax;
  Float_t e; Float_t n;
  Float_t xBary; Float_t yBary;
  Float_t xVar; Float_t yVar;
  int  nSavedPix;
  int xPix[maxClusterSize]; 
  int yPix[maxClusterSize];
  Float_t ePix[maxClusterSize];
  
////////////////////////////////////////////////////////////////////////
//  Older compilers
////////////////////////////////////////////////////////////////////////
string itos(const int i){
	ostringstream ossAux;
	ossAux << i;
	return ossAux.str();
}

int nnMax=2; // Maximum number of pixels in a cluster to be considerer
int mmMax=1; // Number of electrones excluded 0, 1, ... mmMax-1

int counter_exp[10][10];
int counter_mc[10][10];

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void p1to2(){  

bool FirstTime = true;
int point =0;

cout<<"e min: "<<emin<<endl;
cout<<"e max: "<<emax<<endl;

int tamanio=29;
double x[tamanio];
double pmc[tamanio];
double pdatos;

for(int N=1;N<2; N++){
//for(int N=100;N<101; N++){
	for(int DC=100;DC<2901; DC=DC+100){ 
		for(int A=2500;A<2501; A=A+100){
			for(int B=30;B<31; B=B+10){

	x[point] = DC;
	point += 1; // counter 

	cout<<"Interactions: "<<N<<endl;
	cout<<"Dark Current: "<<DC<<endl;
	cout<<"Parameter A : "<<A<<endl;
	cout<<"Parameter B : "<<B<<endl<<endl;

	for (int nn=1;nn<=nnMax;nn++){ 
	for (int mm=0;mm<=mmMax;mm++){
	
	float minePix = 1.5; // will be clasified as 1e-
	minePix=minePix*mm;

	if (FirstTime){

	// Experimental Data ///////////////////////////////////////////////////
	// Get input files//////////////////////////////////////////////////////

					TFile * f_exp = TFile::Open("55Fe_exp.root");
					if (!f_exp->IsOpen()) {std::cerr << "ERROR: cannot open the root file with experimental data" << std::endl;}
					TTree * texp = (TTree*) f_exp->Get("hitSumm");

					int Entries_exp = texp -> GetEntries();
					//cout<<"Entries in experimental data file: "<<Entries_exp<<endl;
					
					Enable_and_Set_Branches(texp); 

				// Get information from trees///////////////////////////////////////////

					for(int i_event=0;i_event<Entries_exp; i_event++){
				   
					texp->GetEntry(i_event);
					
						if (ohdu == ohdu_numer) {
							if (e>=emin && e<=emax){  // number of electrons
								//if (n==nn && xBary>255 && xBary<495 && yBary>5 && yBary<45){
								if (n==nn && xBary>5 && xBary<245 && yBary>5 && yBary<45){
									
									// Check if one of the pixels in the cluster is smaller that minePix
									bool noLowPixInCluster = true;
									for (int p = 0; p < nSavedPix; ++p){
										if(ePix[p]<minePix){
											noLowPixInCluster = false;
											break;
										}
									}

									if (noLowPixInCluster){
											counter_exp[nn][mm]+=1;
									}
								}	
							}
						}
					}									
	}
											
// Monte Carlo Data ////////////////////////////////////////////////////
// Get input files//////////////////////////////////////////////////////	
					
					TFile * f_mc = TFile::Open(("Out_N0="+itos(N)+"_DC="+itos(DC)+"_A="+itos(A)+"_B="+itos(B)+".root").c_str());
					
					if (!f_mc->IsOpen()) {std::cerr << "ERROR: cannot open the root file with MC data" << std::endl;}   
					TTree * tmc    = (TTree*) f_mc->Get("hitSumm");
					
					int Entries_mc = tmc -> GetEntries();
					//cout<<"Entries in MC file: "<<Entries_mc<<endl;

					Enable_and_Set_Branches(tmc);
					
				// Get information from trees///////////////////////////////////////////        
					
					for(int i_event=0;i_event<Entries_mc; i_event++){
					
					tmc->GetEntry(i_event);

						if (e>=emin && e<=emax){  // number of electrons
							if (n==nn && xBary>5 && xBary<245 && yBary>5 && yBary<45){
								
								// Check if one of the pixels in the cluster is smaller that minePix
								bool noLowPixInCluster = true;
								for (int p = 0; p < nSavedPix; ++p){
									if(ePix[p]<minePix){
										noLowPixInCluster = false;
										break;
									}
								}

								if (noLowPixInCluster){
										counter_mc[nn][mm]+=1;
								}
							}	
						}
					}
					/*
					cout<<"min ePix:                "<<minePix<<endl;
					cout<<"tamaño del cluster:      "<<nn<<endl;
					cout<<"Eventos en Experimental: "<<counter_exp[nn][mm]<<endl;
					cout<<"Eventos en Monte Carlo:  "<<counter_mc[nn][mm]<<endl;
					cout<<endl<<endl;
					*/
	} // ends loop for m, i.e. minePix=0 and minePix = 1
	} // ends loop for clustersize


double num1 = (counter_exp[2][0]-counter_exp[2][1]);
double deno1 = ((counter_exp[2][0]-counter_exp[2][1])+counter_exp[1][0]);
pdatos = num1/deno1;

double num2 = (counter_mc[2][0]-counter_mc[2][1]);
double deno2 = ((counter_mc[2][0]-counter_mc[2][1])+counter_mc[1][0]);
pmc[point] =num2/deno2;

cout<<"probabilidad de perdida de un e en un monocluster en los datos:            "<<pdatos<<endl;
cout<<"probabilidad de perdida de un e en un monocluster en la simulacion:        "<<pmc[point]<<endl;

cout<<endl;

//getchar();

FirstTime=false;	

			}
		}
	}
}

   TCanvas *c1 = new TCanvas("c1","Probabilidad de extension a dos pixeles",200,10,500,300);
   c1->SetGrid();
 
   TGraph* gr = new TGraph(tamanio,x,pmc);
   gr->Draw("A*");
   
   TLine *line = new TLine(0,pdatos,3000,pdatos);
   line->SetLineColor(kRed);
   line->Draw();
 
}

////////////////////////////////////////////////////////////////////////

void Enable_and_Set_Branches(TTree* & tree){

  tree->SetBranchStatus("*",1); //enable all branches
  tree->SetBranchAddress ("runID",&runID);
  tree->SetBranchAddress ("ohdu",&ohdu);
  tree->SetBranchAddress ("expoStart",&expoStart);
  tree->SetBranchAddress ("nSat",&nSat);
  tree->SetBranchAddress ("flag",&flag);
  tree->SetBranchAddress ("xMin",&xMin);
  tree->SetBranchAddress ("xMax",&xMax);
  tree->SetBranchAddress ("yMin",&yMin);
  tree->SetBranchAddress ("yMax",&yMax);
  tree->SetBranchAddress ("e",&e);
  tree->SetBranchAddress ("n",&n);
  tree->SetBranchAddress ("xBary",&xBary);
  tree->SetBranchAddress ("yBary",&yBary);
  tree->SetBranchAddress ("xVar",&xVar);
  tree->SetBranchAddress ("yVar",&yVar);
  tree->SetBranchAddress ("nSavedPix",&nSavedPix);
  tree->SetBranchAddress ("xPix",&xPix);
  tree->SetBranchAddress ("yPix",&yPix);
  tree->SetBranchAddress ("ePix",&ePix);
}
