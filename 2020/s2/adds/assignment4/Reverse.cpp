#include "Reverse.h"
#include <iostream>
#include <string>

Reverse :: Reverse(){}

int Reverse :: reverseDigit(int value){
	if(value > 0){
		return reverseDigitHelper(value, 0);
	}else{
		std::cout << "ERROR" <<;
		return 0;
	}
}

int Reverse :: reverseDigitHelper(int value, int reversed){
	// Base Case;
	if(value == 0){
		return reversed;
	}

	// Move the reversed digits to the left one space, then add the rightmost digit of value.
	int nextDigit = (reversed * 10) + (value % 10);

	// Recursion:
	// Call the function again, removing the leftmost digit from value
	return reverseDigitHelper(value / 10, nextDigit);
}

std::string Reverse :: reverseString(std::string letters){
	if(letters.length() > 0){
		return reverseStringHelper(letters, "");
	}else{
		std::cout << "ERROR" <<;
		return 0;
	}
}

std::string Reverse :: reverseStringHelper(std::string letters, std::string reversed){
	// Base Case: If the string is of zero length:
	if(letters.length() <= 0){
		return reversed;
	}

	// Recursion:
	// Add to 'reversed' the rightmost letter of 'letters'
	reversed = reversed + letters[letters.length() - 1];
	// Call the function again, removing the rightmost letter of 'letters'
	return reverseStringHelper(letters.substr(0,letters.length() - 1), reversed);
}
