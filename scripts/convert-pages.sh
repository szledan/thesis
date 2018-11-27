#!/bin/bash

_gray_list="$(gs -o - -sDEVICE=inkcov build/paper/src/szakdolgozat.pdf | grep -Pzo "Page\K [0-9]+\n(?= 0.00000  0.00000  0.00000)")"
_color_list="$(gs -o - -sDEVICE=inkcov build/paper/src/szakdolgozat.pdf | grep -Pzo "Page\K [0-9]+\n(?! 0.00000  0.00000  0.00000)")"

_gray_pdfs=""
for _i in $_gray_list; do
  _gray_pdf="build/gray_p$(printf "%04d" $_i).pdf"
  _gray_pdfs="$_gray_pdfs $_gray_pdf"
  pdfseparate -f $_i  -l $_i build/paper/src/szakdolgozat.pdf $_gray_pdf
  echo $_i;
done
gs -dNOPAUSE -sDEVICE=pdfwrite -sOUTPUTFILE=build/paper/src/print_gray_pages.pdf -dBATCH $_gray_pdfs

_color_pdfs=""
for _i in $_color_list; do
  _color_pdf="build/color_p$(printf "%04d" $_i).pdf"
  _color_pdfs="$_color_pdfs $_color_pdf"
  pdfseparate -f $_i  -l $_i build/paper/src/szakdolgozat.pdf $_color_pdf
  echo $_i;
done
gs -dNOPAUSE -sDEVICE=pdfwrite -sOUTPUTFILE=build/paper/src/print_color_pages.pdf -dBATCH $_color_pdfs

# Include argument parser.
. ./scripts/arg-parser.sh

# Set default values.
inDir=./build/paper/src
outDir=$inDir
inFile=szakdolgozat.pdf
outFile=grayscaled-$inFile
helpMsg="usage: "`basename $0`" input.pdf [out.pdf]"

# Check help flags.
if [[ $(getFlag "--help -h --usage" $@) ]] ; then
  echo $helpMsg;
  exit 0;
fi

# Get working directories.
inFile=$(getValue $1 "./$inDir/$inFile")
outFile=$(getValue $2 "./$outDir/$outFile")

# Check dependencies.
if ! which gs > /dev/null ; then
  echo "need to be installed: 'sudo apt install gs'"
  exit 1
fi

# Convert colored pdf to grayscaled one.
gs \
  -sOutputFile=$outFile \
  -sDEVICE=pdfwrite \
  -sColorConversionStrategy=Gray \
  -dProcessColorModel=/DeviceGray \
  -dCompatibilityLevel=1.4 \
  -dNOPAUSE \
  -dBATCH \
  $inFile

errorCode=$?

if [ "$errorCode" != "0" ] ; then
  echo "Error! (Code=$errorCode)"
else
  echo "Done!"
fi

exit $errorCode

# gs -o - -sDEVICE=inkcov build/paper/src/szakdolgozat.pdf |grep -Pzo "Page\K [0-9]+\n(?! 0.00000  0.00000  0.00000)"
# pdfseparate -f 8  -l 8 build/paper/src/szakdolgozat.pdf ez.pd
# pdfjam -o az.pdf ez.pdf ez.pdf ez.pdf
