#!/bin/bash

# For generate the thesis.
sudo apt-get install texlive-full

if [[ ${1} == "--dev" ]] ; then
  echo "Install packages for developing..."
  sudo apt-get install okular geany-plugin-spellcheck hunspell-hu
fi

# For compile the gepard lib and examples bin
# TODO: use the gepard.git project own dependencies updater.

echo "Done!"
