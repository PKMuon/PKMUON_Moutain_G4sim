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
echo $3

index=$1
begin=$(expr \( $1 - 1 \) \* 1)
end=$(expr \( $1 \) \* 1)

source ~/.bashrc
source /data/bond/yuxd/root/install/bin/thisroot.sh

cd /home/pku/yuxd/bond/PKMUON_Moutain_G4sim/Background/analysis/job_opt2_100m/analysis

root -b -q -l "analysis.cc+(${index})" > $2
