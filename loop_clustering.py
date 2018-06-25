# Este codigo corre skExtract.exe para diferentes outputs con parametros de entrada N0, DC, A y B

import os,sys

command = ""
for N in range(200,201):
	for DC in range(0,51):
		for A in range(1,2): 
			for B in range(1,21): 
				command += "./skExtract.exe -c extractConfig.xml interactions+dc_N0="+str(N)+"_DC="+str(DC)+"_A="+str(A)+"_B="+str(B)+".fits -o output_N0="+str(N)+"_DC="+str(DC)+"_A="+str(A)+"_B="+str(B)+".root"+" && "
command = command[:-2]     
print command
os.system(command)
