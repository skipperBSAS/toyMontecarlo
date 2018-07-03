# Este codigo suma usando hadd todas las salidas de skExtract.exe que correspondan a iguales parametros fisicos de entrada


import os,sys

command = ""
for N in range(200,201):
	for iDC in range(0,1):
		DC=iDC
		for A in [120, 150, 180, 210, 240]: 
			for B in [10, 20, 30, 40]: 
				command += "hadd Out_N0="+str(N)+"_DC="+str(DC)+"_A="+str(A)+"_B="+str(B)+".root output_N0="+str(N)+"_DC="+str(DC)+"_A="+str(A)+"_B="+str(B)+"_R=* && "
command = command[:-2]     
print command
os.system(command)
