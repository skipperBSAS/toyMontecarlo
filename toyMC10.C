/*
Código escrito para simular:

- Coordenada (xx,yy) donde tuvo lugar la interacción del foton X
- Profundidad zz donde tuvo lugar la interacción del foton X
- Número de cargas generadas en cada interacción
- Distribución de cargas que llega a la superficie del CCD
- Numero de cargas por pixel
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
#include "TH2Poly.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TRandom2.h"
#include "TRandom3.h"
#include "TStopwatch.h"
using namespace std;


int main() {

// contador
TStopwatch t;
t.Start();

int N0=5;
//N0 represents the number of X-rays that interact with the CCD ////////

int emeannumber = 1000;
// emeannumber: mean number of electrons generates by a X-ray //////////

// To check distributions run N0=100000, emeannumber = 10.

// Skin depth //////////////////////////////////////////////////////////
int tau=50; 

// CCD size. Real dimension: 4126 x 866.
int nx = 400;            // Number of pixels in x-direction
int ny = 100;            // Number of pixels in y-direction
int pixSize= 15;        // Pixel size side in microns
int xSize = nx*pixSize; // x CCD size in microns
int ySize = ny*pixSize; // y CCD size in microns
int sizeArray =nx*ny; // tamaño en pixeles de la CCD
long fpixel[2] = {1,1};



int pix[sizeArray]; //vector de pixeles
int pix_dc[sizeArray]; //vector de pixeles con eventos DC
//int xpix[xSize]; //array de los pixeles en x
//int ypix[ySize]; //array de los pixeles en y

//int pix[xSize][ySize]; //matriz de xSize x ySize de pixeles
//int pix_dc[xSize][ySize]; //matriz de xSize x ySize de pixeles con DC (es redundante porque array es lo mismo pero le da un poco mas de coherencia al codigo)



//lleno de 0 a pi

for (int i = 0; i < sizeArray; ++i) pix[i]=0;

// array de 0's y 1's donde va a estar la DC
// X e Y son la posición de cada DC
// darkC es la cantidad de eventos

// int array[sizeArray];
int X; //posicion en pixeles
int Y;
int XX; //posicion en micrones
int YY;
int darkC = 10;


//lleno de 0 a array
for (int i = 0; i < sizeArray; ++i) pix_dc[i]=0;





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



// CCD con interacciones solamente
	TCanvas *ch2p2 = new TCanvas("ch2p2","ch2p2",30*nx,30*ny);
	TH2F *h2p = new TH2F("h2p","",nx,-0,xSize,ny,0,ySize); //este es el histograma 2D. xbins, xmin, xmax y luego y idem.
	h2p->SetName("Pixels");
	h2p->SetTitle("CCD_Interacciones");
	// gStyle->SetPalette(1); // ????? porque gStyle? como se da cuenta qeu habla de h2p? 
 
// CCD solo DC
	TH2F *h2p_DC = new TH2F("h2p","",nx,-0,xSize,ny,0,ySize); //este es el histograma 2D. xbins, xmin, xmax y luego y idem.
	h2p_DC->SetName("Pixels");
	h2p_DC->SetTitle("CCD_DC");
	// gStyle->SetPalette(1); // ????
 
// CCD con interacciones y DC
	TH2F *h2p_TOTAL = new TH2F("h2p","",nx,-0,xSize,ny,0,ySize); //este es el histograma 2D. xbins, xmin, xmax y luego y idem.
	h2p_TOTAL->SetName("Pixels");
	h2p_TOTAL->SetTitle("CCD_TOTAL");
	// gStyle->SetPalette(1); // ????



// Print TCanvas into pdf
   
   // ch2p2 ->cd();
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
    BB[j]=1;
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
	 h2p->Fill(chargex[i], chargey[i]);
	 
	 
	 h2p_TOTAL->Fill(chargex[i], chargey[i]); //hasta ahora ambos histogramas tienen lo mismo, pero no sé copiarlos sin romperlos
	 
 }

}   // End loop over x-rays interactions

 for (int i = 0; i < darkC; ++i)
    {
        X =  (rand() % (nx-1)) +1;
        Y =  (rand() % (ny-1)) +1;
        
        cout << "X " << X << " " << "Y " << Y << endl;
        
        XX=X*pixSize;
        YY=Y*pixSize;
		
        cout << "XX " << XX << " " << "YY " << YY << endl;

		
        pix_dc[nx*Y+X]+=  1;
                
        h2p_DC->Fill(XX,YY);
		h2p_TOTAL->Fill(XX,YY);
    }



// Show CCD 2D plot ////////////////////////////////////////////////////
	ch2p2->Divide(2,2);
	ch2p2->cd(1);
	h2p->Draw("COLZ"); // CCD interacciones
	
	ch2p2->cd(2);
	h2p_DC->Draw("COLZ"); // CCD DC
	
	ch2p2->cd(3);
	h2p_TOTAL->Draw("COLZ"); // CCD interacciones+DC

	ch2p2->Print(ps);
	ch2p2->Print(ps+"]");
   
////////////////////////////////////////////////////////////////////////
	double*  array = new double[sizeArray];
    
    int naxis = 2;
    int status = 0;
    
	for (int i = 0; i < sizeArray; ++i) array[i] = 0;
       
// Save the content of each bin into the variable pix[i][j] ////////////
	for (int i = 0; i < nx; ++i) {	
		for (int j = 0; j < ny; ++j) {
		
		   int bin = h2p->FindBin(i*pixSize+pixSize/2,j*pixSize+pixSize/2,0);
		   int content = h2p->GetBinContent(bin);
		   //pix[i][j]=content;
		   array[i*nx+j]=content;
		   //pix[nx*j+i]=+content+pix_dc[nx*j+i];
		   //cout<<array[bin]<<endl;
		   cout<<"i: "<<i<<" j: "<<j<<" bin "<<bin<<" content: "<<content<<endl;
		   //getchar();		   
		}
	}
	
//le agrego DC a pix


	
/////////////////////////////  CARGAS DE INTERACCIONES  ///////////////////////////////////////////
	
	cout<< "CERO ";
	    
	std::string outMeanFitsFile1 = "interacciones.fits";
    
    fitsfile *outClusterptr1;
    
    fits_create_file(&outClusterptr1, outMeanFitsFile1.c_str(), &status);

    long naxesOut[9] = {nx, ny, 1, 1, 1, 1, 1, 1, 1};
   
    

	fits_create_img(outClusterptr1, -32, naxis, naxesOut, &status);
    
    fits_write_pix(outClusterptr1, TDOUBLE, fpixel, sizeArray, array, &status);
    
    fits_close_file(outClusterptr1,  &status);
    
    cout<< "UNO ";

/////////////////////////////  CARGAS DE DC  ///////////////////////////////////////////
	std::string outMeanFitsFile2 = "dc.fits";
    
    fitsfile *outClusterptr2;
    
    fits_create_file(&outClusterptr2, outMeanFitsFile2.c_str(), &status);


	fits_create_img(outClusterptr2, -32, naxis, naxesOut, &status);
    
    fits_write_pix(outClusterptr2, TDOUBLE, fpixel, sizeArray, pix_dc, &status);
    
    fits_close_file(outClusterptr2,  &status);
    
    cout<< "DOS ";
   
/////////////////////////////  CARGAS DE INTERACCIONES+DC  ///////////////////////////////////////////
	std::string outMeanFitsFile3 = "interacciones+dc.fits";
    
    fitsfile *outClusterptr3;
    
    fits_create_file(&outClusterptr3, outMeanFitsFile3.c_str(), &status); 



	fits_create_img(outClusterptr3, -32, naxis, naxesOut, &status);
    
    fits_write_pix(outClusterptr3, TDOUBLE, fpixel, sizeArray, pix, &status);
    
    fits_close_file(outClusterptr3,  &status);
    
    cout<< "TRES ";
 
    
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
