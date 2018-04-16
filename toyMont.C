#include <TRandom>
#include <ctime>
#include <cstdlib>
// #include <array>

// Inputs
int bCluster = 5;
int xSizeArray = 10;
int ySizeArray = 20;
int numClusters2 = 1;
int darkC = 10;

// int auxRand = 10000;


int sizeArray = xSizeArray*ySizeArray;

	void clustCreator(int numClust, int sizeClust, int array[]){
		int* clArray = new int[2*sizeClust*2*sizeClust];

		for (int i = 0; i < numClust; ++i)
		{

			for (int l = 0; l < 2*sizeClust*2*sizeClust; ++l) clArray[l] = 0;
			// srand( time( NULL ) );
			int xMin = 2*sizeClust;
			int xMax = 0;
			int yMin = 2*sizeClust;
			int yMax = 0;

			

			// 	for (int h = 0; h <2*sizeClust; ++h)
			// {
			// 	cout << "\n"  << endl	;
			// 	for (int j = 0; j < 2*sizeClust; ++j)
			// 	{
			// 		cout<< "|" << clArray[2*sizeClust*h + j]<< "|";
			// 	}
			// }

			// int rand = 10000;
			int auxRand = 10000;
			int sumRand = 0;
			int rest = 0;
			int azzardo = 0;

			int X = sizeClust-1;
			int Y = sizeClust;

			if (sizeClust!=1){	
			
				auxRand = (rand() % (auxRand/2 + auxRand%2));
				rest = 10000 - auxRand;
				
			}

			// cout << auxRand << endl;

			sumRand +=  auxRand;
			
			clArray[2*sizeClust*Y+ X] += auxRand;

			// 	for (int h = 0; h <2*sizeClust; ++h)
			// {
			// 	cout << "\n"  << endl	;
			// 	for (int j = 0; j < 2*sizeClust; ++j)
			// 	{
			// 		// cout<< "|" << 2*sizeClust*h + j << "|";
				
			// 		cout<< "|" << clArray[2*sizeClust*h + j]<< "|";
			// 	}
			// }
	

			for (int j = 1; j < sizeClust; ++j)
			{
				
						
				azzardo = (rand() % 4) + 1 ;

				// cout << "azzardo: " << azzardo << endl;

				if (azzardo == 1)
				{
					int auxX = X-1;
					int auxY = Y;
				
				}else if(azzardo == 2){
				
					int auxX = X;
					int auxY = Y+1;

				}else if(azzardo == 3){
				
					int auxX = X+1;
					int auxY = Y;
				
				}else if(azzardo == 4){
					
					int auxX = X;
					int auxY = Y-1;
				
				}

				// cout << j << endl;

				if (clArray[2*sizeClust*auxY+ auxX]!=0)
				{
					j-=1	;
					continue;
				}else{

					X = auxX;
					Y = auxY;
					
					if(j==sizeClust-1){
						clArray[2*sizeClust*Y+ X]+= 10000 - sumRand ;
					}else{

						// cout << "rest" << rest << endl;
						auxRand = (rand() % (rest/2 + rest%2));
						// cout << "auxRand" << auxRand << endl ;
						sumRand += auxRand;
						rest -= auxRand;
						clArray[2*sizeClust*Y+ X]+= auxRand;

						// cout << auxRand << endl;
					}
				}

				
					// cout << j << endl;		


			}

	// cout << "i:" << i << endl;

		// for (int i1 = 0; i1 <2*sizeClust; ++i1)
		// 	{
		// 		cout << "\n"  << endl	;
		// 		for (int j = 0; j < 2*sizeClust; ++j)
		// 		{
		// 			cout<< "|" << clArray[2*sizeClust*i1 + j]<< "|";
		// 		}
		// 	}

			// Find xMin , ...

			for (int iy = 0; iy < 2*sizeClust; ++iy)
			{
				for (int ix = 0; ix < 2*sizeClust; ++ix)
				{
					if (clArray[2*sizeClust*iy + ix]==0)
					{
						continue;
					
					}else{
						if (yMin>iy)
						{

						yMin = iy;
						break;
							
						}
					}

				}
			}

			// cout << "yMin:" << yMin << endl;

			for (int ix = 0; ix < 2*sizeClust; ++ix)
			{
				for (int iy = 0; iy < 2*sizeClust; ++iy)
				{
					if (clArray[2*sizeClust*iy + ix]==0)
					{
						continue;
					
					}else{
						if (xMin>ix)
						{
						xMin = ix;
						break;
						}

					}

				}
			}


			// cout << "xMin:" << xMin << endl;

			for (int ix = 2*sizeClust -1; ix >=0 ; --ix)
			{
				// cout << ix << endl;
				for (int iy = 2*sizeClust -1; iy >=0 ; --iy)
				{

					// cout << iy << endl;
			
					if (clArray[(2*sizeClust )*iy +  ix]==0)
					{
						continue;
					
					}else{
						if (ix>xMax){
						xMax = ix;
						break;
						}
					}

				}
			}


			// cout << "xMax:" << xMax << endl;

			for (int iy = 2*sizeClust-1; iy >=0 ; --iy)
			{
				for (int ix = 2*sizeClust-1; ix >=0; --ix)
				{
					if (clArray[2*sizeClust*iy + ix]==0)
					{
						continue;
					
					}else{
						if (iy>yMax)
						{
							
						yMax = iy;
						break;
						}
					}

				}
			}

			// cout << endl;
			// cout << endl;
			// cout << "xMin: " << xMin << " " << "xMax: " << xMax << endl;
			// cout << "yMin: " << yMin << " " <<"yMax: " << yMax << endl;
			// cout << endl;


		// // cout << "i:" << i << endl;

		// for (int i1 = yMin; i1 <yMax+1; ++i1)
		// 	{
		// 		cout << "\n"  << endl	;
		// 		for (int j = xMin; j < xMax+1; ++j)
		// 		{
		// 			cout<< "|" << clArray[2*sizeClust*i1 + j]<< "|";
		// 		}
		// 	}

		int X = (rand() % (xSizeArray-(xMax-xMin)-1)) + 1;
		int Y = (rand() % (ySizeArray-(yMax-yMin)-1)) + 1 ;

		// cout << "X:" << X << " " << "Y:" << Y << endl;

		for (int i1 = yMin ; i1 < yMax+1; ++i1)
			{
				cout << "\n"  << endl	;
				for (int j = xMin; j < xMax+1; ++j)
				{
					array[xSizeArray*(Y+i1-yMin) + X+j-xMin] += clArray[2*sizeClust*i1 + j];
				}
			}

		


	// 	cout << "i:" << i << endl;
	// 	for (int i1 = 0; i1 <2*sizeClust; ++i1)
	// 		{
	// 			cout << "\n"  << endl	;
	// 			for (int j = 0; j < 2*sizeClust; ++j)
	// 			{
	// 				cout<< "|" << clArray[2*sizeClust*i1 + j]<< "|";
	// 			}
	// 		}

		}
	}

void measureCCD(int array[]){

int* cluster = new int[sizeArray];
std::vector<int> labelVec;

int label = 0;

// Creates a new array with labels to the clusters

for (int i = 0; i < sizeArray; ++i) cluster[i] = 0 ;

for (int i = 1; i < ySizeArray; ++i)
{
	for (int j = 1; j < xSizeArray; ++j)
	{	
		if (array[xSizeArray*i + j]!=0)
		{
			if (array[xSizeArray*(i-1) + j]==0 && array[xSizeArray*i + (j-1)]==0)
			{
				label++;
				cluster[xSizeArray*i + j] = label;
			}else if(array[xSizeArray*(i-1) + j]!=0 && array[xSizeArray*i + (j-1)]==0)
			{
				cluster[xSizeArray*i + j] = cluster[xSizeArray*(i-1) + j];

			}else if(array[xSizeArray*(i-1) + j]==0 && array[xSizeArray*i + (j-1)]!=0)
			{
				cluster[xSizeArray*i + j] = cluster[xSizeArray*i + (j-1)];
			}else{
				
				if(cluster[xSizeArray*(i-1) + j]<=cluster[xSizeArray*i + (j-1)]){
					labelVec.push_back(cluster[xSizeArray*i + (j-1)]);
					labelVec.push_back(cluster[xSizeArray*(i-1) + j]);
					cluster[xSizeArray*i + j] = cluster[xSizeArray*(i-1) + (j)];
				}else{
					labelVec.push_back(cluster[xSizeArray*(i-1) + j]);
					labelVec.push_back(cluster[xSizeArray*i + (j-1)]);	
					cluster[xSizeArray*i + j] = cluster[xSizeArray*(i) + (j-1)];
				
				}
			}
		}

	}


}

// for (int i = 0; i < labelVec.size(); ++i){


// if (i%2==0 && i!=0)
// 	{
// 		cout<<endl;
// 	}


//  cout<<labelVec[i]<<" ";
// }
// Correct mistakes in "labelVec" 

cout<<endl;

for (int i = 0; i < labelVec.size()/2 ; ++i)
{
	for (int j = 0; j < labelVec.size()/2; ++j)
	{
		if (labelVec[2*i]==labelVec[2*j + 1] &&  labelVec[2*j + 1] > labelVec[2*i + 1])
		{
			labelVec[2*j + 1] = labelVec[2*i + 1];	
		}
	}
}

// Correct mistakes in "cluster"

// cout<<endl;
// for (int i = 0; i < labelVec.size(); ++i){

// 	if (i%2==0 && i!=0)
// 		{
// 			cout<<endl;
// 		}

// 	cout<<labelVec[i]<<" " ;  
	
// }
	for (int i = 0; i < labelVec.size()/2; ++i)
	{
		for (int j = 0; j < ySizeArray; ++j)
		{
			for (int h = 0; h < xSizeArray; ++h)
			{
				if (cluster[xSizeArray*j + h]==labelVec[2*i ] )
				{
					cluster[xSizeArray*j + h]=labelVec[2*i + 1];	
				}
			}
		}
	}


for (int i = 0; i <ySizeArray; ++i)
{
	cout << "\n"  << endl	;
	for (int j = 0; j < xSizeArray; ++j)
	{
		if (cluster[xSizeArray*i + j]<10)
		{
			cout<< "|" << "0"<<cluster[xSizeArray*i + j]<< "|";
	
		}else{
		cout<< "|" << cluster[xSizeArray*i + j]<< "|";
		}
	}
}


// Output: Number of clusters, Starting Clusters, Ending Clusters, # clusters of 1, 2, 3, .. 

// Create a vector with number of clusters

std::vector<int>  vecClust;

for (int i = 0; i <ySizeArray; ++i)
{
	for (int j = 0; j < xSizeArray; ++j)
	{
		if (cluster[xSizeArray*i + j] !=0)
		{
			if (vecClust.size()==0)
			{

				vecClust.push_back(cluster[xSizeArray*i + j]);

			}else{

			for (int h = 0; h < vecClust.size(); ++h)
			{
				
				if (cluster[xSizeArray*i + j]==vecClust[h])
				{
					break;
				}

				if (h==vecClust.size()-1)
				{

					vecClust.push_back(cluster[xSizeArray*i + j]);	

				}

			}

			}
		}
	}
}


cout<<endl;
// for (int i = 0; i < vecClust.size(); ++i) cout << vecClust[i] << endl;

// Get info of every cluster

int biggestClust = 50;
int*   clustSize = new double[biggestClust];
int*   clustFE = new double[biggestClust];
int*   clustFEPlus = new double[biggestClust];
int*   clustDC = new double[biggestClust];
int*   clustBoth = new double[biggestClust];



for (int i = 0; i < biggestClust; ++i) clustSize[i] = 0 ;
for (int i = 0; i < biggestClust; ++i) clustFE[i] = 0 ;
for (int i = 0; i < biggestClust; ++i) clustFEPlus[i] = 0 ;
for (int i = 0; i < biggestClust; ++i) clustDC[i] = 0 ;
for (int i = 0; i < biggestClust; ++i) clustBoth[i] = 0 ;


for (int h = 0; h < vecClust.size(); ++h)
{
	int auxCountSize = 0;
	int auxCountRatio = 0;
	for (int i = 0; i < ySizeArray; ++i)
	{
		for (int j = 0; j < xSizeArray; ++j)
		{
			if (cluster[xSizeArray*i + j]==vecClust[h])
			{
				auxCountSize++;
				auxCountRatio += array[xSizeArray*i + j]; 
			}
		
		}
	}

if (auxCountSize!=0)
{
	clustSize[auxCountSize]++;
	
}

cout<<endl;

// cout << auxCountSize << " " << auxCountRatio << endl;


cout<<endl;




	if (auxCountRatio % 10000 == 0 &&  auxCountRatio>10000)
	{
		clustFEPlus[auxCountSize]++;
	}else if(auxCountRatio==10000)
	{
		clustFE[auxCountSize]++;
	}else if(auxCountRatio % 10000 != 0 &&  auxCountRatio>=10000){

		clustBoth[auxCountSize]++;

	}else if (auxCountRatio % 10000 != 0 &&  auxCountRatio<10000)
	{
		clustDC[auxCountSize]++;
	}

	

// cout<<clustFE[auxCountSize]<<endl;

}



// for (int i = 1; i < biggestClust; ++i) cout << clustSize[i] << endl;


cout << "||| Clusters Results |||\n "<< endl;

for (int i = 1; i < biggestClust; ++i){

	if (clustFE[i] != 0 || clustDC[i] != 0 || clustBoth[i] != 0 || clustFEPlus[i] != 0)
	{
		
	
	// cout<<endl;
	cout << "Clust Size:" << i << " " <<"FE:" <<clustFE[i]<<" " << "DC:" << clustDC[i] << " " << "BOTH:" << clustBoth[i] << " " << "FE_Plus:" <<clustFEPlus[i]<<" " << endl ;  
	cout<<endl;
	
	}
	
}


cout << "||| Help |||\n "<< endl;

cout << "FE: It's the number of clusters composed only of Fe55 \n" << endl;

cout << "DC: It's the number of clusters composed only of DarkCurrent \n" << endl;

cout << "BOTH: It's the number of clusters composed FE && DC \n" << endl;

cout << "FE_Plus: It's the number of clusters composed more than one FE interactions \n" << endl;

}

void addDC(int array[]){

	for (int i = 0; i < darkC; ++i)
	{

		int X =  (rand() % (xSizeArray-1)) +1;;
		int Y =  (rand() % (ySizeArray-1)) +1;;
		
		// cout << X << " " << Y << endl;

		array[xSizeArray*Y+X]+=  1;
	}



}

void toyMont(){

srand( time( NULL ) );
int*   array = new int[sizeArray];

for (int i = 0; i < sizeArray; ++i) array[i] = 0 ;

for (int i = 0; i < bCluster; ++i)
{

	clustCreator(numClusters2,2,array);
	
}


	addDC(array);
	measureCCD(array);



}	//End

