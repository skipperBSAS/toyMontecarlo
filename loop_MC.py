# Este codigo corre toyMC para diferentes parametros de entrada a y b

import os,sys

command = ""
for N in range(200,201):
	for DC in range(0,201):
		for A in range(1,2): 
			for B in range(1,21): 
				command += "./toyMC.exe "+str(N)+" "+str(DC)+" "+str(A)+" "+str(B)+" && "
command = command[:-2]     
print command
os.system(command)
