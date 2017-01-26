#!/bin/bash

rootDir=$PWD
srcDir="$rootDir/paper/src"
outDir="$rootDir/build"
fileName="szakdolgozat"
outputFileName="$fileName"

mkdir -p $outDir

if [ "${1}" != "" ] ; then
  outputFileName=${1}
fi

cd $srcDir
latex -output-directory=$outDir $fileName
if [ "$?" != "0" ] ; then exit $?; fi

cp -R $srcDir/bib $outDir/
cd $outDir
bibtex $fileName
if [ "$?" != "0" ] ; then exit $?; fi

cd $srcDir
latex -output-directory=$outDir $fileName
if [ "$?" != "0" ] ; then exit $?; fi

latex -output-directory=$outDir $fileName
if [ "$?" != "0" ] ; then exit $?; fi

dvips $outDir/$fileName -o $outDir/$fileName.ps
if [ "$?" != "0" ] ; then exit $?; fi

cd $outDir
ps2pdf $fileName.ps $fileName.pdf
if [ "$?" != "0" ] ; then exit $?; fi


echo " --- "
echo "root=$rootDir src=$srcDir out=$outDir"
echo "input=$fileName output=$outputFileName"
echo "Done!"
