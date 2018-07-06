# Este codigo corre toyMC para diferentes parametros de entrada
# R es una etiqueta para el numero de run pero no juega ningun rol dentro de toyMC

import os,sys

command = ""
for N in range(200,201):
	for iDC in range(0,1):
		DC=iDC
		for A in [240,270]: 
			for B in [11, 110]: # This number will be divided by 10.000 inside toyMC where must be measured in 1/um
				for R in range(1,11):  
					command += "./toyMC.exe "+str(N)+" "+str(DC)+" "+str(A)+" "+str(B)+" "+str(R)+" && "
command = command[:-2]     
print command
os.system(command)
