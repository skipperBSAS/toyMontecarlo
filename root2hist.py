# Este codigo abre los output_A_B.root
# cuenta cuantos eventos tiene y los muestra en pantalla
# y ademas guarda en out_A_B.dat el histograma de tamanio de clusters.

import ROOT
import os,sys

# Book histogram
Hist = ROOT.TH1D("SizeClusterDist","",20,0,20)

TreeName = "hitSumm"

for i in range(1,2):
	for j in range(1,10):
		FileName = "output_"+str(i)+"_"+str(j)+".root"
		OutFile  = "out_"+str(i)+"_"+str(j)+".dat"
		# Open TFile
		File = ROOT.TFile.Open(FileName)
		if not File:
			print "File not found, exiting"
			sys.exit(0)

		# Get tree
		tree = File.Get(TreeName)
		if not tree:
			print "TTree not found, exiting"
			sys.exit(0)

		# Loop over tree
		print "nEntries: "+str(tree.GetEntries())

		counter = 0
		#for event in tree:
		for event in tree:
			counter += 1
			# Loop over passed triggers
			# if tree.ohdu == 4 and tree.e>500 and tree.e<1700:
			if tree.ohdu == 4:
				# Fill histogram
				Hist.Fill(tree.n) 

		Outputs = []
		for i in range(0,Hist.GetNbinsX()):
		  Outputs.append(str(Hist.GetBinContent(i)))

		outFile = open(OutFile,"w") 
		for text in Outputs:
		  outFile.write(text+"\n")
		outFile.close()
