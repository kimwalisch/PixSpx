#!/bin/bash
E12=00000000000

for j in 0 00 000 0000 00000 000000
do
    for i in 1 2 3 4 5 6 7 8 9
    do
	sump64 2>/dev/null $i$E12$j >> sums_12_19 
    done
done
