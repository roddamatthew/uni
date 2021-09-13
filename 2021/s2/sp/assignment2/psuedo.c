s1 = 3B / n ;

ci = c0( s1 )^e mod N ;


while( !oracle( ci ) ) {
    increment( s1 ) ;
    ci = c0( s1 )^e mod N ;
}

// got s1, now find r
r = ceil( ( 2B * s1 - 3B + 1 ) / n )


num_mul( product, twoB, s1 ) ;
num_sub( product, product, p2 ) ;
num_div( r, dc, product, n ) ;


// r = floor( ( (3B -1)*s1 - 2B ) / n )

low = ( 2B + r*n ) / s1 ;
high = ( 3B-1 + r*n ) / s1 ;


num_mul()
num_add()
num_div()