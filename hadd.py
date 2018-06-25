# Este codigo suma usando hadd todas las salidas de skExtract.exe que correspondan a iguales parametros fisicos de entrada

import os,sys

command = ""
for N in range(200,201):
	for DC in range(0,51):
		for A in range(1,2): 
			for B in range(1,21): 
				command += "hadd Out_N0="+str(N)+"_DC="+str(DC)+".root output_N0="+str(N)+"_DC="+str(DC)+"_A="+str(A)+"_B=* && "
command = command[:-2]     
print command
os.system(command)
