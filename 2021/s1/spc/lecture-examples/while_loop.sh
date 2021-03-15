# While loop syntax example

#!/bin/bash
# assign some variale to 0
counter=0

# increment the variable and output it while it is less than 5
while [ $counter -lt 5 ]
do
	let counter=counter+1
	echo $counter
done

# we can also use an until loop
# until is essentially an inverse while loop
# note that we can create the exact some output by simply inverting the operator (in this case less than is the same as not( greater than or equal to ) )
echo ""
counter=0
until [ $counter -ge 5 ]
do
	let counter=counter+1
	echo $counter
done