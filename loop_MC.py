# Este codigo corre toyMC para diferentes parametros de entrada a y b
# y para cada uno de ellos corre luego skExtract (clustering) generando la salida output_a_b.root
import os,sys
command = "thisroot6"
os.system(command)

command = ""
for a in range(1,2):
	for b in range(1,2):
		command += "./toyMC.exe 10 5 "+str(a)+" "+str(b)+" && "
		command += "switchROOT &&"
		command += "./skExtract.exe -c extractConfig.xml procNT_A="+str(a)+"_B="+str(b)+".fits -o output_"+str(a)+"_"+str(b)+".root"+" && "
		command += "switchROOT &&"
command = command[:-2]     
print command
os.system(command)
