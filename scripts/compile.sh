#!/bin/bash

rootDir=$PWD
srcDir="$rootDir/paper/src"
outDir="$rootDir/build"

mkdir -p $outDir

fileName="ledanszilard"
if [ "${1}" != "" ] ; then
  fileName=${1}
fi

processIndex=0
processNumber=6
echo $rootDir $srcDir $outDir $fileName

echo [$((++processIndex))/$processNumber]
cd $srcDir
latex -output-directory=$outDir $fileName
if [ "$?" != "0" ] ; then exit; fi

echo [$((++processIndex))/$processNumber]
cp $srcDir/cites.bib $outDir/
cp $srcDir/huplain.bst $outDir/
cd $outDir
bibtex $fileName
if [ "$?" != "0" ] ; then exit; fi

echo [$((++processIndex))/$processNumber]
cd $srcDir
latex -output-directory=$outDir $fileName
if [ "$?" != "0" ] ; then exit; fi

echo [$((++processIndex))/$processNumber]
latex -output-directory=$outDir $fileName
if [ "$?" != "0" ] ; then exit; fi

echo [$((++processIndex))/$processNumber]
dvips $outDir/$fileName -o $outDir/$fileName.ps
if [ "$?" != "0" ] ; then exit; fi

echo [$((++processIndex))/$processNumber]
cd $outDir
ps2pdf $fileName.ps $fileName.pdf
if [ "$?" != "0" ] ; then exit; fi

echo Done!
