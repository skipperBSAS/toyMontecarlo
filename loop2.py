# Este codigo hace el clustering de los archivos de andre

import os,sys

command = ""
for a in range(73,88):



		command += " \n ./skExtract.exe -c extractConfig.xml proc_fe552018-04-12_00"+str(a)+".fits -o output_"+str(a)+".root"
		#command += "./skExtract.exe -c extractConfig.xml interactions+dc_A="+str(a)+"_B="+str(b)+".fits -o output_"+str(a)+"_"+str(b)+".root"+" && "

command = command[:-2]

print command
os.system(command)
command = ""

for a in range(87,101):
		command += " \n ./skExtract.exe -c extractConfig.xml proc_fe552018-04-13_00"+str(a)+".fits -o output_"+str(a)+".root"
		##command += "\n scp monsoon@estela:/home/monsoon/andre/macros/datos/tracer/newSetup/fe55/dataApril12/proc_fe552018-04-13_00"+str(a)+".fits /home/mariano/Desktop/caca/"
		##command += "./skExtract.exe -c extractConfig.xml interactions+dc_A="+str(a)+"_B="+str(b)+".fits -o output_"+str(a)+"_"+str(b)+".root"+" && "


command = command[:-2]

print command
os.system(command)
command = ""

for a in range(100,118):

		command += " \n ./skExtract.exe -c extractConfig.xml proc_fe552018-04-13_0"+str(a)+".fits -o output_"+str(a)+".root"

		##command += "\n scp monsoon@estela:/home/monsoon/andre/macros/datos/tracer/newSetup/fe55/dataApril12/proc_fe552018-04-13_0"+str(a)+".fits /home/mariano/Desktop/caca/"
		##command += "./skExtract.exe -c extractConfig.xml interactions+dc_A="+str(a)+"_B="+str(b)+".fits -o output_"+str(a)+"_"+str(b)+".root"+" && "


command = command[:-2]

print command
os.system(command)
command = ""

for a in range(117,268):

		command += " \n ./skExtract.exe -c extractConfig.xml proc_fe552018-04-14_0"+str(a)+".fits -o output_"+str(a)+".root"

		##command += "\n scp monsoon@estela:/home/monsoon/andre/macros/datos/tracer/newSetup/fe55/dataApril12/proc_fe552018-04-14_0"+str(a)+".fits /home/mariano/Desktop/caca/"
		##command += "./skExtract.exe -c extractConfig.xml interactions+dc_A="+str(a)+"_B="+str(b)+".fits -o output_"+str(a)+"_"+str(b)+".root"+" && "


command = command[:-2]

print command
os.system(command)
