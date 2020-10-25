#include <iostream>
#include <vector>
#include <string>

using namespace std ;

// Global vectors to store numbers and operators
vector<int> numbers ;
string operators ;

void getInput()
{
	int k ;
	string currentNumber ;

	string input ;
	getline( cin, input ) ;

	// Add all non white space characters to operators until a number is read
	while( input[k] < '0' )
	{
		if( input[k] != ' ' ) operators = input[k] + operators ;
		k++ ;
	}

	// Add all input numbers to vector until reaching the end of input
	for( int i = k ; i < input.length() ; i++ )
	{
		if( input[i] != ' ' ) currentNumber += input[i] ; else
		if( input[i] == ' ' )
		{
			int n = stoi( currentNumber ) ;
			numbers.push_back( n ) ;
			currentNumber = "" ;
		}
	}

	int n = stoi( currentNumber ) ;
	numbers.push_back( n ) ;
}

int calculateResult()
{
	int result ;

	// Calculate result
	if( ( numbers.size() - 1 ) != operators.size() ) std::cout << "Error" << std::endl ;
	else
	{
		result = numbers[0] ;

		for( int i = 0 ; i < operators.length() ; i++ )
		{
			switch( operators[i] )
			{
				case '+':
					result = result + numbers[i+1] ;
					break ;

				case '-':
					result = result - numbers[i+1] ;
					break ;

				case '*':
					result = result * numbers[i+1] ;
					break ;

				case '/':
					result = result / numbers[i+1] ;
					break ;

				default:
					std::cout << "Error with result" << std::endl ;
					break ;
			}
		}
	}
}

void printEquation()
{
	string equation ;

	// Add all the numbers to the string

	equation += " = " ;
	equation += to_string( calculateResult() ) ;

}

int main()
{
	getInput() ;
	printEquation() ;

	return 0 ;
}