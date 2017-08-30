#ifndef GEN_H 
#define GEN_H

#include <inttypes.h>

/* removes initial noise */
#define DISCARD 32 

/* attractor constants */
#define A 0.4263
#define B 2
#define C 4

/* integral approximation step size */
#define H 0.01

#define ROL(x,n) ((x = ((x << n) | (x >> (32 - n)))))

union dbits {
        double d;
        struct {
                uint64_t mant: 52;
                uint64_t exp: 11;
                uint64_t sign: 1;
        } p;
};

struct gen {
        union dbits x, y, z; 
};

void gen_init(struct gen *g, uint64_t k[3]);
uint32_t gen32(struct gen *g);

#endif
