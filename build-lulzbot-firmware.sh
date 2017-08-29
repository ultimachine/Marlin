#!/bin/sh

####
# Copyright (C) 2017  AlephObjects, Inc.
#
#
# The bash script in this page is free software: you can
# redistribute it and/or modify it under the terms of the GNU Affero
# General Public License (GNU AGPL) as published by the Free Software
# Foundation, either version 3 of the License, or (at your option)
# any later version.  The code is distributed WITHOUT ANY WARRANTY;
# without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU AGPL for more details.
#

####
# The following variables list the models and toolheads to build for:

MINI_MODELS="Gladiola_Mini Hibiscus_Mini2 Gladiola_MiniLCD Hibiscus_Mini2LCD"
MINI_TOOLHEADS="Gladiola_SingleExtruder Albatross_Flexystruder Finch_Aero"

TAZ_MODELS="Juniper_TAZ5 Oliveoil_TAZ6 Quiver_TAZ7"
TAZ_TOOLHEADS="Tilapia_SingleExtruder Kanyu_Flexystruder Opah_Moarstruder Javelin_DualExtruderV2 Longfin_FlexyDually Yellowfin_DualExtruderV3 Angelfish_Aero"

####
# usage
#
# Prints out a usage summary
#
usage() {
  echo "Usage: $0 [--no-timestamps] [printer_model toolhead_name]"
  exit
}

####
# build_firmware <printer> <toolhead>
#
# Compiles firmware for the specified printer and toolhead
#
build_firmware() {
  printer=$1
  toolhead=$2
  echo
  echo Building for ${printer} and ${toolhead}
  echo
  (cd Marlin; make clean; make $MAKEOPTS AVR_TOOLS_PATH=${AVR_TOOLS_PATH}/ MODEL=${printer} TOOLHEAD=${toolhead}) || exit
  mv Marlin/applet/*.hex build
}

####
# check_tool <exec_name>
#
# Checks whether a tool exists in the AVR_TOOLS_PATH
#
check_tool() {
  if [ ! -x "$AVR_TOOLS_PATH/$1" ]; then
    echo Cannot locate $1 in $AVR_TOOLS_PATH.
    exit 1
  fi
}

####
# locate_avr_tools
#
# Attempts to locate the avr tools, otherwise prompts
# the user for a location.
#
locate_avr_tools() {
  AVR_OBJCOPY=`which avr-objcopy`
  if [ $? -eq 0 ]; then
    AVR_TOOLS_PATH=`dirname $AVR_OBJCOPY`
  fi
  while [ ! -x $AVR_TOOLS_PATH/avr-gcc ]
  do
    echo
    echo avr-gcc tools not found!
    echo
    read -p "Type path to avr-gcc tools: " AVR_TOOLS_PATH
    if [ -z $AVR_TOOLS_PATH ]; then
      echo Aborting.
      exit
    fi
  done
}

####
# check_avr_tools
#
# Verify that all the AVR tools we need exist in the located
# directory.
#
check_avr_tools() {
  echo
  echo Using $AVR_TOOLS_PATH for avr-gcc tools.
  echo

  check_tool avr-gcc
  check_tool avr-objcopy
  check_tool avr-g++
  check_tool avr-objdump
  check_tool avr-ar
  check_tool avr-size
}

####
# build_for_mini
#
# Build all the toolhead variants for the mini
#
build_for_mini() {
  for model in $MINI_MODELS
  do
    for toolhead in $MINI_TOOLHEADS
    do
      build_firmware ${model} ${toolhead}
    done
  done
}

####
# build_for_taz
#
# Build all the toolhead variants for the TAZ
#
build_for_taz() {
  for model in $TAZ_MODELS
  do
    for toolhead in $TAZ_TOOLHEADS
    do
      build_firmware ${model} ${toolhead}
    done
  done
}

####
# build_summary
#
# Print out a summary of hex files that were created
#
build_summary() {
  echo
  echo
  echo
  echo Firmware hex files built in "`pwd`/build":
  echo
  ls build
  echo
}

############################################
# MAIN SCRIPT
############################################

while true
do
  case $1 in
    --no-timestamps)
      MAKEOPTS="NO_TIMESTAMP=1"
      shift
      ;;
    --*)
      usage
      ;;
    *)
      break
      ;;
  esac
done

locate_avr_tools
check_avr_tools

rm -rf build
mkdir build

if [ $# -eq 2 ]
then
  build_firmware $1 $2
else
  build_for_mini
  build_for_taz
fi

build_summary
