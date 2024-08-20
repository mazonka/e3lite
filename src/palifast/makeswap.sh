#!/bin/bash
# Copyright 2022 MoMA Lab, NYU Abu Dhabi (wp.nyu.edu/momalab/)

# use swap to swap files

if [ "$1" = "" ]; then
arr=(`cat amalgam.sh | grep "ciphertext-ser.h"`)
ech=${arr[0]}
  if [ "$ech" = "echo" ]; then
  echo "palifast are inplace (not originals) - do not checkin" 
  exit 1
  elif [ "$ech" = "#echo" ]; then
  echo "original is inplace - safe to check-in" 
  else
  echo "error in finding swap" 
  fi
exit
fi

if [ "$1" != "swap" ]; then
echo Use swap to swap
exit
fi

echo "Swapping files"

swap(){
file=$2
dir=$1
echo "$file <=> $dir/$file"
mv $file $file.tmp
mv $dir/$file ./
mv $file.tmp $dir/$file
}

swap .. amalgam.sh
swap .. mak_mod_ek.mak
swap .. mak_cgt.mak
swap .. mak_bob.mak
swap .. mak_alice.mak
swap .. mak_mod_dev.mak

