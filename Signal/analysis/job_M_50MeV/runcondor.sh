#!/bin/bash

currentpath=$PWD

#MassName=("5MeV" "50MeV" "100MeV" "200MeV" "500MeV" "1GeV" "10GeV" "100GeV")
#Mass=("5" "50" "100" "200" "500" "1000" "10000" "100000")
MassName=("500MeV")
Mass=("500")
FreePathName=("100" "1000" "10000" "100000" "1000000" "10000000")
XS=("0.01" "0.001" "0.0001" "0.00001" "0.000001" "0.0000001")

for (( i=0; i<${#MassName[@]}; i++ ))
do
  for (( j=0; j<${#FreePathName[@]}; j++ ))
  do
    cd $currentpath
    jobpath=job_M_${MassName[$i]}_L_${FreePathName[$j]}km
    echo $jobpath
    cp -r template $jobpath
    sed -i "s/DMMASSINMEV/${Mass[$i]}/g" $jobpath/CryMu.mac
    sed -i "s/DMXSINM/${XS[$j]}/g" $jobpath/CryMu.mac
    cd $jobpath
    sh genmac.sh
    condor_submit run_test.jdl
  done
done

