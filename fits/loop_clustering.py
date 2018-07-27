# Este codigo corre skExtract.exe para diferentes outputs con parametros de entrada N0, DC, A y B
# y para cada run R

import os,sys

command = ""
for N in range(100,101):
	for iDC in range(21,30):
		DC=iDC*100
		for A in [2500]: 
			for B in [30]:   
				for R in range(51,128):
					command += "./skExtract.exe -c extractConfig.xml MC_N0="+str(N)+"_DC="+str(DC)+"_A="+str(A)+"_B="+str(B)+"_R="+str(R)+".fits -o output_N0="+str(N)+"_DC="+str(DC)+"_A="+str(A)+"_B="+str(B)+"_R="+str(R)+".root"+" && "
command = command[:-3]     
print (command)
os.system(command)
