# Este codigo corre toyMC para diferentes parametros de entrada a y b

import os,sys

command = ""
for N in range(200,201):
	for iDC in range(1,20):
		DC=iDC*10
		for A in [120, 150, 180, 210, 240]: 
			for B in [0.0010, 0.0020, 0.0030, 0.0040]: 
				for R in range(1,2):  # Este loop determina cuantas veces se repite el MC con los mismos parametros
					command += "./toyMC.exe "+str(N)+" "+str(DC)+" "+str(A)+" "+str(B)+" "+str(R)+" && "
command = command[:-2]     
print command
os.system(command)
