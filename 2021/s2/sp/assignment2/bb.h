#ifndef __BB_H__
#define __BB_H__ 1

int bb_blind(num_t c0, num_t s0, const num_t c, const num_t e, const num_t n);
int bb_step0(num_t low, num_t high, num_t si, const num_t c0, const num_t e, const num_t n);
int bb_step0test(const num_t n);

// Linked list to store range of num_t
typedef struct range{
    num_t low ;
    num_t high ;
    struct range* next ;
} range_t ;

int range_push( range_t* ptr, num_t low, num_t high ) ;

// Bonus function
void bleichenbacher(num_t m, const num_t c, const num_t e, const num_t n);


#endif 
