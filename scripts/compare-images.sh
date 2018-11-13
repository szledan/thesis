#!/bin/bash

_cmd_nmbr=$1
_all_cmd=0
_no_cmd=""
_cmd_ndx=0

_rootDir=$PWD
_srcDir="$2"
_imgDir=$_srcDir/img
_builtDir=$_imgDir/built
_refDir=$_imgDir
_diffDir=$_builtDir
_diffPrefix=$_diffDir/diff

_img=$_builtDir/tiger.png

_ref_chrome=$_refDir/tiger-chrome-70_0_3538_77.png
#_ref_chrome=$3
_ref_edge=$_refDir/tiger-edge-42_17134_1_0.png
_ref_firefox=$_refDir/tiger-firefox-63_0.png
_ref_safari=$_refDir/tiger-safari-12_0-14606_1_36_1_9.png

_ssim=$_srcDir/res/ssim.txt
_ssim_psnr=$_srcDir/res/ssim-psnr.txt

function channel_table {
  _result_ssim=$(compare -verbose -metric SSIM -compose src -lowlight-color white $_img $_ref_chrome ${_diffPrefix}.png 2>&1)
  for _c in red green blue all; do
    if [ "$_c" == "all" ] ; then echo "\\hline"; fi
    echo "$(echo $_result_ssim | grep -oP "($_c): [\d.]+" | sed "s/red:/vörös \&/; s/green:/zöld \&/; s/blue:/kék \&/; s/alpha:/alpha \&/; s/all:/összesen \&/") \\\\"
  done
}

function compare_results {
  _row_ssim="$1 & SSIM"
  _row_psnr="   & PSNR [dB]"
  _i=$2
  for _f in "${@:3}"; do
    _d=$_diffPrefix-$(basename $_i .png)-$(basename $_f)
    #echo $_d
    _result_ssim=$(compare -verbose -metric SSIM -compose src -lowlight-color white $_i $_f $_d 2>&1)
    _result_psnr="$(compare -verbose -metric PSNR -compose src -lowlight-color white $_i $_f $_d 2>&1)"
    _a_ssim=()
    _a_psnr=()
    for _c in red green blue alpha all; do
      _a_ssim+=("$(echo $_result_ssim | grep -oP "($_c): \K[\d.]+")")
      _a_psnr+=("$(echo $_result_psnr | grep -oP "($_c): \K([\d.]+|(inf))" | sed "s/inf/\$\\\infty\$/")")
    done
    _row_ssim="$_row_ssim & ${_a_ssim[4]}"
    _row_ssim=$(echo $_row_ssim | sed "s/ 1 / \\\multicolumn\{1\}\{\|c\|\}\{1\} /")
    _row_psnr="$_row_psnr & ${_a_psnr[4]}"
  done
  echo "$_row_ssim \\\\"
  echo "$_row_psnr \\\\"
}

# Create over diff
let "_cmd_ndx++";
echo -n "[$_cmd_ndx] Create over diff"
if [[ "$_cmd_nmbr" == "$_cmd_ndx" || "$_cmd_nmbr" == "$_all_cmd" ]]; then
  echo -n "  run..."
  compare -metric SSIM -compose over $_img $_ref_chrome ${_diffPrefix}over.png
  echo "  done!";
else
  echo "  off"
fi

# Create SSIM color channel table
let "_cmd_ndx++";
echo -n "[$_cmd_ndx] Create SSIM color channel table"
if [[ "$_cmd_nmbr" == "$_cmd_ndx" || "$_cmd_nmbr" == "$_all_cmd" ]]; then
  echo -n "  run..."
  channel_table > $_ssim
  echo "  done!"
else
  echo "  off"
fi

# Create SSIM and PSNR table
let "_cmd_ndx++";
echo -n "[$_cmd_ndx] Create SSIM and PSNR table"
if [[ "$_cmd_nmbr" == "$_cmd_ndx" || "$_cmd_nmbr" == "$_all_cmd" ]]; then
  echo -n "  run..."
  echo -n "" > $_ssim_psnr
  compare_results "\\multirow{2}{*}{Gepard}" $_img $_ref_chrome $_ref_safari $_ref_edge >> $_ssim_psnr
  echo "\\hline" >> $_ssim_psnr
  compare_results "\\multirow{2}{*}{Skia}" $_ref_chrome $_ref_chrome $_ref_safari $_ref_edge >> $_ssim_psnr
  echo "  done!"
else
  echo "  off"
fi
