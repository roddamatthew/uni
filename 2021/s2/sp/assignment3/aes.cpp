// plaintext ciphertext accesstime
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define OUTLIER 300

using namespace std ;

struct s {
    string byte ;
    int index ;
    int accesses[64] ;
    int n ;
} ;

// Stolen from https://www.delftstack.com/howto/cpp/find-most-frequent-element-in-an-array-cpp/
int getMostFrequentElement(vector<int> &arr)
{
    if (arr.empty())
        return -1;

    sort(arr.begin(), arr.end());

    auto last_int = arr.front();
    auto most_freq_int = arr.front();
    int max_freq = 0, current_freq = 0;

    for (const auto &i : arr) {
        if (i == last_int)
            ++current_freq;
        else {
            if (current_freq > max_freq) {
                max_freq = current_freq;
                most_freq_int = last_int;
            }

            last_int = i;
            current_freq = 1;
        }
    }

    if (current_freq > max_freq) {
        max_freq = current_freq;
        most_freq_int = last_int;
    }

    return most_freq_int;
}

int hex2int(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
    return -1;
}

int find( vector<s>* v, string byte, int index ) {
    for( int i = 0 ; i < v -> size() ; i++ ) {
        if( v -> at( i ).byte == byte && v -> at( i ).index == index ) return i ;
    }
    return -1 ;
}

// Normalise the accesses array and return the slowest index
int analyse( int accesses[64], float normalise[64] ) {
    float max = 0 ;
    int maxIndex = -1 ;
    
    for( int i = 0 ; i < 64 ; i++ ) {
        float weighted_access = accesses[i] / normalise[i] ;
        if( weighted_access >= max ) {
            max = weighted_access ;
            maxIndex = i ;
        }
    }
    return maxIndex ;
}

bool doubleSort( s a, s b ) {
    if( a.index != b.index ) return a.index < b.index ;
    else return a.byte < b.byte ;
}

int main() {
    string plaintext, ciphertext, accesstime ; // Strings to store input
    vector<s> v ; // Store accesses associated with a given byte at given position
    int total[64] ; // Store all accesses for normalisation
    int totalLines = 0 ;

    // Initialize the total array to zeroes
    for( int i = 0 ; i < 64 ; i++ )
        total[i] = 0 ;

    // Read input of the form: plaintext ciphertext access0 access1 ... access63
    while( cin >> plaintext ) {
        cin >> ciphertext ;
        totalLines ++ ;
        
        int temp[64], flag = 0 ;
        for( int i = 0 ; i < 64 ; i++ ) {
            cin >> accesstime ;
            temp[i] = stoi( accesstime ) ;
            if( stoi( accesstime ) > OUTLIER ) flag++ ; // Skip outliers
        }

        if( flag == 0 ) {
            // Add the accesses of this line to the total
            for( int i = 0 ; i < 64 ; i++ )
                total[i] += temp[i] ;
            totalLines++ ;

            for( int j = 0 ; j < 16 ; j++ ) {
                // Check if the same byte in the same position has been stored before
                int index = find( &v, plaintext.substr( j * 2, 2 ), j ) ;

                // Not in vector, create a new element
                if( index == -1 ) {
                    s newAccess ;
                    newAccess.index = j ;
                    newAccess.byte = plaintext.substr( j * 2, 2 ) ;
                    newAccess.n = 1 ;
                    for( int i = 0 ; i < 64 ; i++ )
                        newAccess.accesses[i] = temp[i] ;
                    v.push_back( newAccess ) ;
                } else {
                    // In vector, add to the running total
                    v.at( index ).n++ ;
                    for( int i = 0 ; i < 64 ; i++ )
                        v.at(index).accesses[i] += temp[i] ;
                }
            }
        }
    }

    // Calculate the normalisation array
    float normalise[64] ;
    float average = 0 ;
    float one = 1 ;
    for( int i = 0 ; i < 64 ; i++ ) {
        normalise[i] = (float)total[i] / totalLines ;
        average += normalise[i] ;
    }
    average /= 64 ;

    for( int i = 0 ; i < 64 ; i++ ) {
        normalise[i] /= average ;
    }

    sort( v.begin(), v.end(), doubleSort ) ;

    vector<int> trials ; 
    for( int i = 0 ; i < v.size() ; i++ ){
        trials.push_back( analyse( v.at( i ).accesses, normalise ) ) ;
        if( i % 16 == 15 ) {
            cout << "byte: " << v.at( i ).byte[0] << " at index " << v.at( i ).index << " had slowest cache set: " ;
            cout << getMostFrequentElement( trials ) ;
            int P = hex2int( v.at( i ).byte[0] ) ;
            int i = getMostFrequentElement( trials ) % 16 - 1 ;
            int k = P ^ i ;
            cout << " key byte = " << k ;
            cout << endl ;
            trials.clear() ;
        }
    }

    return 0 ;
}
