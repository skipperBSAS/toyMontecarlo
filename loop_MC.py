# Este codigo corre toyMC para diferentes parametros de entrada
# R es una etiqueta para el numero de run pero no juega ningun rol dentro de toyMC

import os,sys

command = ""
for N in range(100,101):
	for iDC in range(21,30):
		DC=iDC*100
		for A in [2500]: 
			for B in [30]: 
				for R in range(51,128):
					command += "./toyMC.exe "+str(N)+" "+str(DC)+" "+str(A)+" "+str(B)+" "+str(R)+" && "
command = command[:-3]
print (command)
os.system(command)
