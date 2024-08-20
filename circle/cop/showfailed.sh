#!/bin/sh

ls -1 *.gold.tmp 2> /dev/null
ls -1 */*.gold.tmp 2> /dev/null
ls -1 */*/*.gold.tmp  2> /dev/null
ls -1 */*/*/*.gold.tmp  2> /dev/null
ls -1 */*/*/*/*.gold.tmp 2> /dev/null
