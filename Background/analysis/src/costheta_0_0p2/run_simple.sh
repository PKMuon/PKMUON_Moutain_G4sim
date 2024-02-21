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
echo $2

source ~/.bashrc
source /data/bond/yuxd/root/install/bin/thisroot.sh

cd /home/pku/yuxd/bond/PKMUON_Moutain_G4sim/Background/analysis/src/costheta_0_0p2

root -b -q -l draw_mountain_sea.cc > $1
