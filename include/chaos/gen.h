#ifndef GEN_H 
#define GEN_H

#include "../src/attractor.h"
#include "../src/seed.h"

/* removes initial noise - controls number of initial iterations before numbers are given out */
#define DISCARD 64 
#define ROL(x,n) ((x = ((x << n) | (x >> (32 - n)))))
#define P(w,x,y,z) ((w ^= x ^ y ^ z))  

struct gen {
        struct attractor as[2];
};

void gen_init(struct gen *k);
uint32_t gen32(struct gen *k);

#endif
