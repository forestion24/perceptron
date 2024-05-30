#!/bin/bash

# align weights and put them in a separate file so they look nice for reasons
cat weights.txt | tr -s ' ' '\n' | fold -w 5 | awk '{printf "%6s", $1} NR%800==0 {print ""}' > aligned_weights.txt