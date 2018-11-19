#!/bin/bash

# For generate the thesis.
sudo apt-get install texlive-full inkscape
sudo apt-get install build-essential cmake
sudo apt-get install libegl1-mesa-dev libgles2-mesa-dev freeglut3-dev

# Install 'compare'
mkdir -p 3rdparty
cd 3rdparty
if [ ! -f ImageMagick.tar.gz ]; then
  wget https://www.imagemagick.org/download/ImageMagick.tar.gz
fi
tar xf ImageMagick.tar.gz
cd ImageMagick-7*
_INSTALL_PREFIX=$PWD/../ImageMagick7
./configure --prefix=$_INSTALL_PREFIX
make
make install

if [[ ${1} == "--dev" ]] ; then
  echo "Install packages for developing..."
  sudo apt-get install geany-plugin-spellcheck hunspell-hu
fi

echo "Done!"
