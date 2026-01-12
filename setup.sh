#!/bin/bash

headear_flag = "false"
arm_flag = "false"
sensekit_flag = "false"
tamale_flag= "false"

while getopts ':ahst:' flag; do
  case "${flag}" in
    a) arm_flag="true" ;;
    h) headear_flag="true" ;;
	s) sensekit_flag="true" ;;
	t) tamale_flag="true" ;;
  esac
done 

if [  ]; then # for each optoin, chnage what gets moved or deleted
    echo "Remaining positional arguments: $@"
fi
