#! /bin/bash

ls -l /
echo "--------"
ls -l /usr
echo `pwd`
hostname
cat /etc/redhat-release
cat $_CONDOR_JOB_AD
sleep 2
echo "yeah"

par_path=$1
par_oldroot=$2
par_newroot=$3

source ~/.bashrc
source /data/bond/yuxd/root/install/bin/thisroot.sh

echo $1
cd $1

root -b -q -l analysis.cc'('\"${par_path}\"','\"${par_oldroot}\"','\"${par_newroot}\"')'
