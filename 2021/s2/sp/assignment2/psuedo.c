// https://link.springer.com/content/pdf/10.1007%2F3-540-36400-5_6.pdf
void modinv( num_t r, num_t a, const num_t p ) {
    num_t u, v, s, k ;
    u := p, v := a, r := 0, s := 1

    while( v > 0 ) {
        if( is_even( u ) ) {
            if( is_even( r ) ) {
                u = u / 2 ;
                r = r / 2
                inc( k ) ;
            } else {
                u = u / 2 ;
                r = (r + p)/2
                inc( k ) ;
            }
        } else if( is_even( v ) ) {
            if( is_even( s ) ) {
                v = v / 2 ;
                s = s / 2 ;
                inc( k ) ;
            }
        } else if(  )
    }
}

num_div(bignum_t quotient, num_t remainder, const bignum_t numerator, const num_t denominator) 