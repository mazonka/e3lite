#!/bin/bash
# Copyright 2022 MoMA Lab, NYU Abu Dhabi (wp.nyu.edu/momalab/)
# cases=( fact fib matrix pir sieve )
cases=( fact fib matrix sieve )
dir=`pwd`
for case in ${cases[@]}; do
    cd ${case}
    python3 test.py
    cd ${dir}
done
