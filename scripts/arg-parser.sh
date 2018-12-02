#!/bin/bash

_args_file=/tmp/.__${BASHPID}__args__.text
echo "$@" > $_args_file

function getFlag()
{
  _args=($(cat $_args_file))
  local flags=${1};
  for _i in "${!_args[@]}"; do
    if [[ " ${flags[@]} " =~ " ${_args[$_i]} " ]]; then
      unset _args[${_i}]; echo "${_args[@]}" > $_args_file
      echo "${_i}";
      exit
    fi
  done
}

function getValue()
{
  _args=($(cat $_args_file))
  if [[ ${_args[0]} ]]; then
    echo ${_args[0]}
    unset _args[0]; echo "${_args[@]}" > $_args_file
  else
    echo $1
  fi
}

function getFlagValue()
{
  local _i=$(getFlag "${1}")
  if [[ $_i ]]; then
    _args=($(cat $_args_file))
    if [[ ${_args[$_i]} ]]; then
      echo ${_args[$_i]}
      unset _args[$_i]; echo "${_args[@]}" > $_args_file
    else
      echo $2
    fi
    exit 1
  fi
  exit 0
}
