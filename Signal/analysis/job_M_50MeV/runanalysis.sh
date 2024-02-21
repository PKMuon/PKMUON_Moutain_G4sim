#!/bin/bash

currentpath=$PWD

MassName=("500MeV")
FreePathName=("100" "1000" "10000" "100000" "1000000" "10000000")

for (( i=0; i<${#MassName[@]}; i++ ))
do
  for (( j=0; j<${#FreePathName[@]}; j++ ))
  do
    jobpath=job_M_${MassName[$i]}_L_${FreePathName[$j]}km
    echo $currentpath/$jobpath
    cd $currentpath/$jobpath
    sh genrootlist.sh
    condor_submit submit_analysis.jdl
    #root -b -q -l analysis.cc'('\"${jobpath}\"')'
  done
done

