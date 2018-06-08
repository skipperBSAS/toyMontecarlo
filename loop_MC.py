# Este codigo corre toyMC para diferentes parametros de entrada a y b

import os,sys

command = ""
for a in range(1,2):
	for b in range(1,10):
		command += "./toyMC.exe 1000 0 "+str(a)+" "+str(b)+" && "
command = command[:-2]     
print command
os.system(command)
