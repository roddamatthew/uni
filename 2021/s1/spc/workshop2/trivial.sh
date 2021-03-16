#!/bin/bash
# Solution 2:
array=( "$@" )
for ((i=0;i<10;i++))
	do
		echo "$(( i + 1 ))= ${array[$i]}"
done

# Solution 1:
for ((i=1;i<10;i++))
	do
		echo "$i=" $1
		shift 
done

