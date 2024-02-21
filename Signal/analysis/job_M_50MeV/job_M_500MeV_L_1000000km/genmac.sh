#!/bin/bash

currentpath=$PWD

# 循环运行Geant4模拟，传入不同的i值
for i in {0..99}
do

  echo "generate mac ${i}!!!"
  cp CryMu.mac mac/CryMu_${i}.mac
  ROOTNAME=$currentpath/root/muCry_${i}
  sed -i "s#OUTROOTNAME#${ROOTNAME}#g" mac/CryMu_${i}.mac

done

ls `pwd`/mac/*.mac > maclist.txt
