#!/bin/bash
# (C) 2018. Szilárd Ledán <szledan@gmail.com>

# Steps of resource building
resource_list()
{
  step "SVGs2EPS" "Convert all SVG to EPS." "./scripts/svg-to-eps.sh --export-margin=3mm --svg=./paper/src/svg --eps=./paper/src/img"
  step "Convert2Gray" "Convert the article in to grayscale." "./scripts/convert-grayscale.sh"
  step "Triangle" "Run 'triangle' example" "./build/paper/examples/triangle/triangle"
  step "Erdely" "Run 'erdely' example" "./build/paper/examples/erdely/erdely"
}

#### Main and util functions ####

main()
{
  echo "*** Build resources ***"
  parse_arguments $@
  if [ $# == "0" ]; then echo "Please select an 'index' from the list."; fi

  echo "List:"
  echo " 0: All steps"
  resource_list

  if [ "$g_selected" != "0" ]; then
    _done_pc=$((g_done * 100 / g_selected))
    _fail_pc=$((g_done * 100 / g_selected))
    echo
    echo "  DONE: $g_done / $g_selected ($_done_pc%)"
    echo "  FAIL: $g_fail / $g_selected ($_fail_pc%)"
    echo
  fi
}

print_name()
{
  _indx=$1; _brief=$2; _descript=$3
  printf "%2d: %-20s: %s\n" "$_indx" "$_brief" "$_descript";
}

step()
{
  _indx=$((++g_index)); _brief=$1; _description=$2; _cmd=$3
  print_name "$_indx" "$_brief" "$_description"
    if [ "$g_help" == "0" ] && contains "$_indx"; then
      ((g_selected++))
      echo "  SELECTED COMMAND: $_cmd"
      $_cmd
      if [ "$?" == "0" ]; then
        ((g_done++))
        echo "  DONE.";
      else
        ((g_fail++))
        echo "  FAIL!!!";
      fi
    fi
}

contains()
{
  _pattern=" $1 "; _list=" ${BASH_ARGV[*]} "
  [ -z "${_list##*$_pattern*}" ] || [ -z "${_list##*0*}" ]
}

parse_arguments()
{
  # Include argument parser.
  . ./scripts/arg-parser.sh

  # Check help arguments
  if [[ $(getFlag "--help -h --usage" $@) ]] ; then
    echo "usage: "`basename $0`" index [index...]"
    echo
    g_help=1;
  fi
}

#### Start point ####

g_help=0;
g_selected=0
g_done=0
g_fail=0
g_index=0

main $@
exit 0
