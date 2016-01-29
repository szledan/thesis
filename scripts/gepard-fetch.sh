#!/bin/bash

rootDir=$PWD
codeDir="$rootDir/code"
gepardDir="$codeDir/gepard.git"

mkdir -p $codeDir
cd $codeDir

if [ ! -d $gepardDir ] ; then
  git clone git@github.com:szledan/gepard.git $gepardDir
fi

cd $gepardDir
git checkout thesis-freeze

echo Done!
