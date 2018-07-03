# Este codigo corre skExtract.exe para diferentes outputs con parametros de entrada N0, DC, A y B
# y para cada run R

import os,sys

command = ""
for N in range(200,201):
	for iDC in range(0,1):
		DC=iDC
		for A in [120, 150, 180, 210, 240]: 
			for B in [10, 20, 30, 40]: 
				for R in range(1,11):  
					command += "./skExtract.exe -c extractConfig.xml MC_N0="+str(N)+"_DC="+str(DC)+"_A="+str(A)+"_B="+str(B)+"_R="+str(R)+".fits -o output_N0="+str(N)+"_DC="+str(DC)+"_A="+str(A)+"_B="+str(B)+"_R="+str(R)+".root"+" && "
command = command[:-2]     
print command
os.system(command)
