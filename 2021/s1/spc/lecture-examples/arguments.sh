# Some useful commands to do with arguments
# $#: returns the number of parameters given
# $n: returns the nth parameter
# $@: returns all parameters, in the order given, each seperated by one space
# shift: removes the first parameter from the list


#!/bin/bash
echo "Total Parameters: $#"
echo "First Parameter:  $1"
echo "Script Name: $0"
echo "All Parameters: $@"

echo ""
shift
echo "Shifting the parameters one time"
echo "All Parameters: $@"

echo ""
shift
echo "Shifting the parameters two times"
echo "All Parameters: $@"