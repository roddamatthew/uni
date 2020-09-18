int square( int n )
{
	// Base case: n == 0
	if( n == 0 ) return 0 ;

	// Recursive case: 
	return ( 2 * n - 1 ) + square( n - 1 ) ;
}