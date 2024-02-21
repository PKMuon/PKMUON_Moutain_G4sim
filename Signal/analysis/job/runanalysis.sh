#!/bin/bash

currentpath=$PWD

MassName=("5MeV" "50MeV" "100MeV" "200MeV" "500MeV" "1GeV" "10GeV" "100GeV")
FreePathName=("10" "100" "10000")

for (( i=0; i<${#MassName[@]}; i++ ))
do
  for (( j=0; j<${#FreePathName[@]}; j++ ))
  do
    jobpath=job_M_${MassName[$i]}_L_${FreePathName[$j]}m
    echo $jobpath
    root -b -q -l analysis.cc'('\"${jobpath}\"')'
  done
done

