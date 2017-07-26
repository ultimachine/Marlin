#!/bin/sh

build_firmware() {
  printer=$1
  toolhead=$2
  echo
  echo Building for ${printer} and ${toolhead}
  echo
  (cd Marlin; make clean; make $MAKEOPTS MODEL=${printer} TOOLHEAD=${toolhead}) || exit
  mv Marlin/applet/*.hex build
}

rm -rf build
mkdir build

MINI_MODELS="Gladiola_Mini Huerfano_Mini Gladiola_GLCD"
TAZ_MODELS="Oliveoil_TAZ_6 Huerfano_TAZ_7"

MINI_TOOLHEADS="Gladiola_SingleExtruder Albatross_Flexystruder Heather_Aero"
TAZ_TOOLHEADS="Oliveoil_SingleExtruder Kanyu_Flexystruder Opah_Moarstruder Javelin_DualExtruder Longfin_FlexyDually Yellowfin_DualExtruder Angelfish_Aero"

for model in $MINI_MODELS
do
  for toolhead in $MINI_TOOLHEADS
  do
    build_firmware ${model} ${toolhead}
  done
done

for model in $TAZ_MODELS
do
  for toolhead in $TAZ_TOOLHEADS
  do
    build_firmware ${model} ${toolhead}
  done
done

echo
echo
echo
echo Firmware hex files built in "`pwd`/build":
echo
ls build
echo