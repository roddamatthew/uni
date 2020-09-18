// Helper function:
// Complete tail recursion using an accumulator
int squareHelper( int n, int acc )
{
	// Base case: n <= 1
	// Now we return the accumulator instead of 1
	if( n == 0 ) return acc ;

	// Increase accumulator
	acc+= 2 * n - 1 ;

	// Recursive call with n - 1
	return squareHelper( n - 1, acc ) ;
}

int square( int n )
{
	// Hide accumulator from user using a helper function
	return squareHelper( n, 0 ) ;
}