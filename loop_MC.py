# Este codigo corre toyMC para diferentes parametros de entrada
# R es una etiqueta para el numero de run pero no juega ningun rol dentro de toyMC

import os,sys

command = ""
for N in range(1000,1001):
	for iDC in range(0,2):
		DC=iDC*1000
		for A in [2500]: 
			for B in [30]: 
				for R in range(10,13):
					command += "./toyMC.exe "+str(N)+" "+str(DC)+" "+str(A)+" "+str(B)+" "+str(R)+" && "
command = command[:-3]
print (command)
os.system(command)
