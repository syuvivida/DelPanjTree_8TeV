### To check out

git clone git@github.com:syuvivida/DelPanjTree_8TeV.git

cd DelPanjTree_8TeV

git checkout v0.00

#### To commit

git remote add upstream git@github.com:syuvivida/DM.git

git add xxxx

git commit -m "remove lines"

git pull --rebase upstream v0.02

git push origin v0.02


#### To run

cmsrel CMSSW_5_3_20

cd CMSSW_5_3_20

rm -rf src

tar xvzf /afs/cern.ch/work/s/syu/public/forStudents/src.tgz

cd src

rm -rf DelPanj

git clone git@github.com:syuvivida/DelPanjTree_8TeV.git DelPanj

cd DelPanj

git checkout v0.00

cd -

scramv1 b clean

bsub -q2nd $PWD/runJob.sh $PWD
