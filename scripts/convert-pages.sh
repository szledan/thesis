#!/bin/bash

# Include argument parser.
. ./scripts/arg-parser.sh

# Set default values.
inDir=./build/paper/src
outDir=$inDir
inFile=szakdolgozat.pdf
outFile=grayscaled-$inFile

# Check help flags.
if [[ "$#" == "0" ]] || [[ $(getFlag "--help -h --usage") ]] ; then
  echo "usage: "`basename $0`" [options] input.pdf [out.pdf=$outDir/$outFile]"
  echo ""
  echo "Options:"
  echo "  -c, --convert-gray        Convert input file to grayscaled output file"
  echo "  -cp, --color-pages        Get list of colored pages"
  echo "  -gp, --gray-pages         Get list of grayscaled pages"
  echo "  -p, --to-printer [SEP=,]  List of pages is printer friendly with SEP char"
  exit 0;
fi

# Parse flags.
_c_isOn=$(getFlag "--convert-gray -c")
_cp_isOn=$(getFlag "--color-pages -cp")
_gp_isOn=$(getFlag "--gray-pages -gp")
_sep_char=$(getFlagValue "--to-printer -p" ",")
_p_isOn=$?
# Get working directories.
inFile=$(getValue "./$inDir/$inFile")
outFile=$(getValue "./$outDir/$outFile")

# Check dependencies.
if ! which gs > /dev/null; then
  echo "need to be installed: 'sudo apt install gs'"
  exit 1
fi

# Convert page numbers to printer friendly list
function printable_list()
{
  local _gray_arr=($1)
  local _ln=${_gray_arr[@]:0:1}
  local _gray_list="$_ln"
  local _mode=2

  for _ln in ${_gray_arr[@]}; do
    _gray_arr=(${_gray_arr[@]:1})
    _cn=${_gray_arr[0]}
    if [[ ! $_cn ]]; then _mode=3; fi
    if [[ "$_mode" != "3" ]] && (($_ln + 1 == $_cn)); then
      _mode=1
    else
      _ch1=$3
      _ch2=$2
      _n=$_ln
      case $_mode in
      0) ;&
      2) _n="";_ch1="";;
      3) _ch2="";;
      esac
      _gray_list="$_gray_list$_ch1$_n$_ch2$_cn"
      _mode=0
    fi
    _ln=$_cn
  done
  echo "$_gray_list"
}

# Print grayscaled OR colored pages.
if [[ $_gp_isOn ]] ||  [[ $_cp_isOn ]]; then
  _group="?="
  if [[ $_cp_isOn ]]; then _group="?!"; fi
  _list="$(gs -o - -sDEVICE=inkcov $inFile | grep -Pzo "Page\K [0-9]+\n($_group 0.00000  0.00000  0.00000)")"
  if [ "$_p_isOn" != "0" ]; then
    _list=$(printable_list "$_list" $_sep_char "-")
  fi
  echo $_list
fi

# Convert colored pdf to grayscaled one.
if [[ $_c_isOn ]]; then
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
fi
