# Este codigo suma usando hadd todas las salidas de skExtract.exe que correspondan a iguales parametros fisicos de entrada


import os,sys

command = ""
for N in range(100,101):
	for iDC in range(21,30):
		DC=iDC*100
		for A in [2500]: 
			for B in [30]:  
				command += "hadd Out_N0="+str(N)+"_DC="+str(DC)+"_A="+str(A)+"_B="+str(B)+".root output_N0="+str(N)+"_DC="+str(DC)+"_A="+str(A)+"_B="+str(B)+"_R=* && "
command = command[:-3]     
print (command)
os.system(command)
