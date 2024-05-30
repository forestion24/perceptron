#!/bin/bash

# generate 600*800 zeros separated by spaces and save them to weights.txt
for ((i = 0; i < 480000; i++)); do
    echo -n "0 "
done > weights.txt

# update aigned weights file
cat weights.txt | tr -s ' ' '\n' | fold -w 5 | awk '{printf "%6s", $1} NR%800==0 {print ""}' > aligned_weights.txt