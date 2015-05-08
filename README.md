cmsrel CMSSW_5_3_20

cd CMSSW_5_3_20

rm -rf src

tar xvzf /afs/cern.ch/work/s/syu/public/forStudents/src.tgz

cd src

rm -rf DelPanj

git clone git@github.com:syuvivida/DelPanjTree_8TeV.git 

cd DelPanjTree

git checkout v0.00


cd -

mv DelPanjTree_8TeV/DelPanj .

rm -rf DelPanjTree_8TeV

scramv1 b clean

bsub -q2nd $PWD/runJob.sh $PWD
