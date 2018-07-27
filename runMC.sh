#!/bin/bash
clear
echo "Entro al directorio /home/dario/CCD/toy"
cd /home/dario/CCD/toy
echo "Paso a ROOT 6 "
. /home/dario/root6/bin/thisroot.sh
echo "Compilo toyMC "
make &&
echo "Corro loop_MC "
echo ""
python loop_MC.py 
echo ""
echo "Termine el loop de Monte Carlo " 
echo "Paso a ROOT 5" 
. /home/dario/root5/bin/thisroot.sh 
echo "Entro al directorio /home/dario/CCD/toy/fis" 
cd fits 
echo "Corro loop_clustering " 
echo ""
python loop_clustering.py 
echo ""
echo "Sumo usando hadd los diferentes RUNs hechos con toyMC" 
python hadd.py 
echo ""
echo "Muevo los Out* a la carpeta compare"
mv Out* /home/dario/CCD/toy/compare
echo "Entro al directorio /home/dario/CCD/toy/compare" 
cd /home/dario/CCD/toy/compare 
echo "Paso a ROOT 6" 
. /home/dario/root6/bin/thisroot.sh 
echo "Ejecuto MakePlots para comparar el Montecarlo con el experimento"
#root -l MakePlots3.C
root -l p1to2.C
