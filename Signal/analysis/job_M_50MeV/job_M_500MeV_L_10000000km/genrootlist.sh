#!/bin/bash

currentpath=$PWD

if [ -f "root.list" ]; then
    echo exit root.list and rm root.list
    rm root.list
else
    echo root.list do not exist, make a new one
fi


for i in {0..99}
do

  echo $currentpath muCry_${i}.root muCry_${i}.root
  echo $currentpath muCry_${i}.root muCry_${i}.root >> root.list

done
