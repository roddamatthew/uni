#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#define INFINITE 100000000 /* define a constant for infinity */
#define NO_LINK -1 /* define a constant for no link */

using namespace std ;

static int TRACE = 0 ;

/* Data structure to store a link between two routers */
struct link {
	std::string start ;
	std::string end ;
	int distance ;

	/* defualt constructor if no distance is entered, assume infinite */
	link( std::string s, std::string e ) {
		start = s ;
		end = e ;
		distance = INFINITE ;
	}

	/* constructor for a given distance */
	link( std::string s, std::string e, int d ) {
		start = s ;
		end = e ;
		distance = d ;
	}
} ;

int main() {
	vector<string> names ;
	string input ;

	while( getline( cin, input ) ) {
		names.push_back( input ) ;
	}


	return 0 ;
}
