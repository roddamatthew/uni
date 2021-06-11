#define INFINITE 1073741823 /* define a constant for infinity (this is INT_MAX / 2) */
#define NO_LINK -1 /* define a constant for no link */

static int TRACE = 0 ;

using namespace std ;

struct link {
	string start ;
	string end ;
	int distance ;

	/* defualt constructor if no distance is entered, assume infinite */
	link( string s, string e ) {
		start = s ;
		end = e ;
		distance = INFINITE ;
	}

	/* constructor for a given distance */
	link( string s, string e, int d ) {
		start = s ;
		end = e ;
		distance = d ;
	}
} ;

/* Data structure to represent a routing table */
/* Has the name of the router with a vector for its links */
struct routingTable {
	string name ;
	vector<struct link> routes ;
} ;

int updateBroadcast( vector<routingTable>*, vector<routingTable>* ) ;
int distance( vector<routingTable>*, string, string, string ) ;
int distance( vector<routingTable>*, string, string ) ;
void addNeighbour( vector<routingTable>*, string, string, int ) ;
void calculateDVs( vector<routingTable>*, vector<routingTable>*, vector<routingTable>* ) ;
void printDVs( vector<routingTable>*, int ) ;
void calculateRTs( vector<routingTable>*, vector<routingTable>* ) ;
void printRoutingTableArray( vector<routingTable>* ) ;
void printBroadcast( vector<routingTable>* ) ;
vector<string> sortAlphabetically( vector<string> list ) ;
