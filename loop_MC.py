# Este codigo corre toyMC para diferentes parametros de entrada a y b

import os,sys

command = ""
for a in range(1,2): 
	for b in range(1,100): 
		command += "./toyMC.exe 100 0 "+str(a)+" "+str(b)+" && "
command = command[:-2]     
print command
os.system(command)
