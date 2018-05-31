/*
Código escrito para simular:

- Coordenada (xx,yy) donde tuvo lugar la interacción del foton X
- Profundidad zz donde tuvo lugar la interacción del foton X
- Número de cargas generadas en cada interacción
- Distribución de cargas que llega a la superficie del CCD
- Numero de cargas por pixel.
- Pixeles generador por corriente oscura
- Distribucion de los pixeles que conforman cada cluster

*/    

#include <random>
#include <ctime>
#include <cstdlib>
#include "fitsio.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <chrono>
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TRandom3.h"
#include "TStopwatch.h"
using namespace std;


int main() {

// time counter
TStopwatch t;
t.Start();

int N0=3;
//N0 represents the number of X-rays that interact with the CCD ////////

int emeannumber = 1000;
// emeannumber: mean number of electrons generates by a X-ray //////////

// To check distributions run N0=100000, emeannumber = 10.

int darkC = 5; // Dark Current total events

// Skin depth //////////////////////////////////////////////////////////
int tau=50; 

// CCD size. Real dimension: 4126 x 866.
int nx = 20;            // Number of pixels in x-direction
int ny = 20;            // Number of pixels in y-direction
int pixSize= 15;        // Pixel size side in microns
int xSize = nx*pixSize; // x CCD size in microns
int ySize = ny*pixSize; // y CCD size in microns
int sizeArray =nx*ny;   // Total number of pixels in the CCD

long fpixel[2] = {1,1};

double*  pix_int = new double[sizeArray];
double*  pix_dc = new double[sizeArray];
double*  pix_total = new double[sizeArray];

/*
int pix_int[sizeArray]; // pixels array with real interactions
int pix_dc[sizeArray];  // pixels array with dark current
int pix_total[sizeArray];     // pixels array with all information
*/

// Initialization 
for (int i = 0; i < sizeArray; ++i) pix_int[i]=0; 
for (int i = 0; i < sizeArray; ++i) pix_dc[i]=0; 
for (int i = 0; i < sizeArray; ++i) pix_total[i]=0; 

// Variables for random numbers ////////////////////////////////////////
	vector<double> xx(N0);                                               
	vector<double> yy(N0);
	vector<double> zz(N0);                                               

	vector<double> AA(N0); //constante 1 formula sigma cuadrado = 2D/a1*nu
	vector<double> BB(N0); //constante 2 formula sigma cuadrado a1/E(y_w)
	
	vector<double> electrons(N0);
    vector<double> sigma(N0);
    
// Book 1D-histograms //////////////////////////////////////////////////
	int binnumber = N0/5;
	
	auto h1 = new TH1D("h1","x-coordinate",binnumber,-xSize/4,1.25*xSize);
	auto h2 = new TH1D("h2","y-coordinate",binnumber,-ySize/4,1.25*ySize);
	auto h3 = new TH1D("h3","z-coordinate",binnumber,-tau/5,5*tau);
	
	double esigma= pow(emeannumber,0.5); //raiz de emeannumber
	auto h4 = new TH1D("h4","number of electrons",binnumber,emeannumber-5*esigma,emeannumber+5*esigma);
	auto h5 = new TH1D("h5","sigma",binnumber,-tau/10,tau/2);
	auto h6 = new TH1D("h6","spot x",binnumber,-xSize/2,3*xSize/2);
	auto h7 = new TH1D("h7","spot y",binnumber,-ySize/2,3*ySize/2);

// CCD - Interactions Only
	TCanvas *ch2p2 = new TCanvas("ch2p2","ch2p2",30*nx,30*ny);
	
	TH2F *h2p_int = new TH2F("h2p_int","",nx,-0,xSize,ny,0,ySize); //este es el histograma 2D. xbins, xmin, xmax y luego y idem.
	h2p_int->SetName("Pixels");
	h2p_int->SetTitle("CCD Interactions");
	 
// CCD - Dark Current Only
	TH2F *h2p_DC = new TH2F("h2p_DC","",nx,-0,xSize,ny,0,ySize); //este es el histograma 2D. xbins, xmin, xmax y luego y idem.
	h2p_DC->SetName("Pixels");
	h2p_DC->SetTitle("CCD Dark Current");
	 
// CCD - Interactions + Dark Current
	TH2F *h2p_TOTAL = new TH2F("h2p_TOTAL","",nx,-0,xSize,ny,0,ySize); //este es el histograma 2D. xbins, xmin, xmax y luego y idem.
	h2p_TOTAL->SetName("Pixels");
	h2p_TOTAL->SetTitle("CCD Interactions + Dark Current");
	
// Print TCanvas into pdf
   TString ps = "CCD.pdf";
   ch2p2->Print(ps+"[");

////////////////////////////////////////////////////////////////////////	
// This loop runs over each X-ray interaction //////////////////////////

for (int j = 0; j < N0; ++j){ 

	// Generate a pair (xx, yy) of uniform random numbers //////////////
	// (xx,yy) represents the coordinates of interaction in the CCD ////
		
    TRandom3 rx(0); //  seed=0  ->  different numbers every time         
    h1->Fill(xx[j]=rx.Uniform(0,xSize)); 
	                                               
    TRandom3 ry(0); //  seed=0  ->  different numbers every time         
    h2->Fill(yy[j]=ry.Uniform(0,ySize)); 
           
	////////////////////////////////////////////////////////////////////
	// Generate zz: depth in the CCD
	// An exponential random number with coefficient tau 
    
    TRandom3 rz(0); //  seed=0  ->  different numbers every time         
    h3->Fill(zz[j] = rz.Exp(tau));                    

	//cout << endl;
	//cout << "x = "<< xx[j] << " , " << "y = "<< yy[j] << " , " << "z = "<< zz[j] << endl;
    
    ////////////////////////////////////////////////////////////////////
    // emeannumber is the mean number of electrons generated by the primary electron.
    // Primary electron here is who carries the energy released 
    // by the x-ray after photoelectric interaction.
   
	// Generate a Poisson random number with mu = emeannumber //////////
	
	TRandom3 re(0); //seed=0  ->  different numbers every time
	h4->Fill(electrons[j] = re.Poisson(emeannumber)); 
	//cout << "#e = "<< electrons[j] << endl;		
	
	////////////////////////////////////////////////////////////////////
    // sigma of charge distribution on the CCD surface in microns
    // proportional to the square root of zz depth
    // AA y BB son variables medibles sacadas del trabajo que nos paso Javier T
    
    AA[j]=1;
    BB[j]=1; //This parameter could depend on the energy
    h5->Fill(sigma[j] = pow(AA[j]*log(BB[j]*zz[j]+1),0.5)); 
    //cout << "sigma = "<< sigma[j] << endl;	
    
    ////////////////////////////////////////////////////////////////////
    // charge distribution on the CCD surface
    // It generates electrons[j] random numbers with
    // bivariate multinormal distribution
    
    // Coordinates x and y of each charge colected /////////////////////
    vector<double> chargex(electrons[j]);
    vector<double> chargey(electrons[j]);
    
    for (int i = 0; i < electrons[j]; ++i) {
		
		////////////////////////////////////////////////////////////////
		// rcx is the number of excited electrons after difussion     
		// Generate a gaussian random number with mean xx[j]
		TRandom3 rcx(0); //seed=0  ->  different numbers every time
		h6->Fill(chargex[i] = rcx.Gaus(xx[j],sigma[j])); 
		//cout << endl;
		//cout << "x on CCD = "<< chargex[i] << endl;	
						
		////////////////////////////////////////////////////////////////
		// rcy is the number of excited electrons after difussion     
		// Generate a gaussian random number with mean yy[j]
		TRandom3 rcy(0); //seed=0  ->  different numbers every time
		h7->Fill(chargey[i] = rcy.Gaus(yy[j],sigma[j]));
		//cout << "y on CCD = "<< chargey[j] << endl;	
	}

for (int i = 0; i < electrons[j]; ++i){
	
	 h2p_int->Fill(chargex[i], chargey[i]); //Only interactions
	 h2p_TOTAL->Fill(chargex[i], chargey[i]); // Only interactions, up to now ...
	 	 
 }

}   // End loop over x-rays interactions

// Add dark Current ////////////////////////////////////////////////////
for (int i = 0; i < darkC; ++i) {
        double xdc =  rand() % xSize;
        double ydc =  rand() % ySize;
                              
        h2p_DC->Fill(xdc,ydc);
		h2p_TOTAL->Fill(xdc,ydc);
}
 
cout<< "MC simulations finished. "<<endl;
    
// Show CCD 2D plot ////////////////////////////////////////////////////
	ch2p2->Divide(1,3);
	ch2p2->cd(1);
	h2p_int->Draw("COLZ"); // Interactions
	
	ch2p2->cd(2);
	h2p_DC->Draw("COLZ"); // Dark Current
	
	ch2p2->cd(3);
	h2p_TOTAL->Draw("COLZ"); // Interactions + Dark Current

	ch2p2->Print(ps);
	ch2p2->Print(ps+"]");

////////////////////////////////////////////////////////////////////////
// Save the content of each histogram into pix variables ///////////////

for (int i = 0; i < nx; ++i) {	
		for (int j = 0; j < ny; ++j) {
				   
		   pix_int[(i)*(nx)+(j)]= h2p_int->GetBinContent(i*nx+j+23); 
		   //pix_int[i*nx+j]= 10*(i*nx+j); 
		   cout<<"bin: "<<i*nx+j<<" Interactions: "<<pix_int[i*nx+j]<<endl;
		   
		   pix_dc[i*nx+j]= h2p_DC->GetBinContent(i*nx+j); 
		   cout<<"bin: "<<i*nx+j<<" Dark Current: "<<pix_dc[i*nx+j]<<endl;
		   
		   pix_total[i*nx+j]= h2p_TOTAL->GetBinContent(i*nx+j); 
		   cout<<"bin: "<<i*nx+j<<" Interac + DC: "<<pix_total[i*nx+j]<<endl;
		   cout<<endl;
		   
		}
	}

cout<< "Starting to save fits files ..."<<endl;

////////////////////////////////////////////////////////////////////////   
// Save histograms as .fits files //////////////////////////////////////

	int naxis = 2;
    int status = 0;
    long naxesOut[9] = {nx, ny, 1, 1, 1, 1, 1, 1, 1};

///////////////////////Real Interactions ///////////////////////////////	
        
	std::string outMeanFitsFile1 = "real_interactions.fits";
    
    fitsfile *outClusterptr1;
    
    fits_create_file(&outClusterptr1, outMeanFitsFile1.c_str(), &status);
 
	fits_create_img(outClusterptr1, -32, naxis, naxesOut, &status);
    
    fits_write_pix(outClusterptr1, TDOUBLE, fpixel, sizeArray, pix_int, &status);
    
    fits_close_file(outClusterptr1,  &status);
    
    cout<< "real_interactions.fits saved "<<endl;
    
	
/* 
////////////////////////// Dark Current ////////////////////////////////
		
	std::string outMeanFitsFile2 = "dc.fits";
    
    fitsfile *outClusterptr2;
    
    fits_create_file(&outClusterptr2, outMeanFitsFile2.c_str(), &status);

	fits_create_img(outClusterptr2, -32, naxis, naxesOut, &status);
    
    fits_write_pix(outClusterptr2, TDOUBLE, fpixel, sizeArray, pix_dc, &status);
    
    fits_close_file(outClusterptr2,  &status);
    
    cout<< "dc.fits saved "<<endl;
    
    
    
///////////////  Real Interactions + Dark Current///////////////////////
	
	std::string outMeanFitsFile3 = "real_interactions+dc.fits";
    
    fitsfile *outClusterptr3;
    
    fits_create_file(&outClusterptr3, outMeanFitsFile3.c_str(), &status); 

	fits_create_img(outClusterptr3, -32, naxis, naxesOut, &status);
    
    fits_write_pix(outClusterptr3, TDOUBLE, fpixel, sizeArray, pix_total, &status);
    
    fits_close_file(outClusterptr3,  &status);
    
    cout<< "real_interactions+dc.fits saved "<<endl;
    
	
	

////////////////////////////////////////////////////////////////////////
	*/
	
	
	
	
	
	
	
	
	
	
	
	
	    
// Plot histograms /////////////////////////////////////////////////////
/*
if (N0>99){
	TCanvas* canvas = new TCanvas("canvas","canvas",10,10,700,800);
	canvas->Divide(3,3);
	
	canvas->cd(1);
	gStyle->SetOptStat(10);
	h1->Draw(""); // xx 
	
	canvas->cd(2);
	gStyle->SetOptStat(10); 
	h2->Draw(""); // yy
	
	canvas->cd(3);
	gStyle->SetOptStat(10); 
	h3->Draw(""); // zz
	
	canvas->cd(4);
	gStyle->SetOptStat(10); 
	h4->Draw(""); // #e
	
	canvas->cd(5);
	gStyle->SetOptStat(10); 
	h5->Draw(""); // sigma
	
	canvas->cd(6);
	gStyle->SetOptStat(10); 
	h6->Draw(""); // x
	
	canvas->cd(7);
	gStyle->SetOptStat(10); 
	h7->Draw(""); // y
}
*/
t.Stop();
t.Print(); 
return 0;
}
