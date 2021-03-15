# Syntax for an if statement
# All red text is syntax
# NOTE: WHITESPACE IS IMPORTANT!
# if[] will not run!
# if [$1 -gt 1] will not run!

#!/bin/bash
if [ $# -gt 0 ]
then
	if [ $1 -eq 1 ]
	then
		echo "The first parameter was '1'!"
	else
		echo "The first parameter was not '1'"
	fi

	# We can also have mathematical equations define whether an if statement runs using double round brackets
	# For example we want this statement to run when: The first and second parameter sum to < 5
	if (($1 + $2 < 5))
	then
		echo "$1 + $2 is less than 5"
	fi
else
	echo "No parameters were given"
fi