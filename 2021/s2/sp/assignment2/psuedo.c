r = ( 2bsi-1 - 4B ) / n
while( true ) {
    s_min = ( 2B + rn ) / b ;
    s_max = ( 3B + rn ) / a ;

    while( valid_range( s_min, s_max ) ) {
        ci = c0(s_min)^e modN ;
        if( oracle( ci ) )
            return ;
    }
    num_inc( r ) ;
}



void s_min( num_t s, num_t r, num_t b, const num_t B, const num_t n ) {
    num_mul( product, r, n ) ;
    num_add( product, product, twoB ) ;
    num_div( s, remainder, product, b ) ;
}
