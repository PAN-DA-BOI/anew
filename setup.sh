#!/bin/bash

headgear_flag="false"
arm_flag="false"
sensekit_flag="false"
tamale_flag="false"
controller_flag="false"

while getopts ':ahstc' flag; do
  case "${flag}"
    a) arm_flag="true" ;;
    h) headgear_flag="true" ;;
    s) sensekit_flag="true" ;;
    t) tamale_flag="true" ;;
    c) controller_flag="true" ;;
  esac
done



if [ "$arm_flag" = "true" ]; then
    mv /home/pi/arm.sh /home/pi/boot
fi

if [ "$headgear_flag" = "true" ]; then
    mv /home/pi/headgear.sh /home/pi/boot
fi

if [ "$sensekit_flag" = "true" ]; then
    mv /home/pi/sensekit.sh /home/pi/boot
fi

if [ "$tamale_flag" = "true" ]; then
    mv /home/pi/tamale.sh /home/pi/boot
fi

if [ "$controller_flag" = "true" ]; then
    mv /home/pi/controller.sh /home/pi/boot
fi