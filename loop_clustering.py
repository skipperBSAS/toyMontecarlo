# Este codigo corre skExtract.exe para diferentes outputs con parametros de entrada a y b

import os,sys

command = ""
for a in range(1,2):
	for b in range(1,100):
		command += "./skExtract.exe -c extractConfig.xml interactions+dc_A="+str(a)+"_B="+str(b)+".fits -o output_"+str(a)+"_"+str(b)+".root"+" && "
command = command[:-2]     
print command
os.system(command)
