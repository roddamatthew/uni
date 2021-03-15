# Creating an array and looping over the elements

#!/bin/bash
choices=( A B C D E )

# Now we can loop over each element
# choices[@] indexes each element in the array, starting at 0 like C++
# var is a variable
for var in "${choices[@]}"
do
	echo "$var"
done

# We can also make a for loop that looks familiar to most other languages
# This loop prints every integer from 0 to 5
for (( i=0; i<6; i++))
do
	echo "$i"
done