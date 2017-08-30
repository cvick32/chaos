#ifndef GEN_H 
#define GEN_H

#include "../src/attractor.h"
#include "../src/seed.h"

/* removes initial noise */
#define DISCARD 64 

#define ROL(x,n) ((x = ((x << n) | (x >> (32 - n)))))

struct gen {
        struct attractor a;
};

void gen_init(struct gen *g, uint64_t k[3]);
uint32_t gen32(struct gen *g);
uint64_t gen64(struct gen *g);
void gen96(struct gen *g, uint32_t out[3]);
void gen128(struct gen *g, uint32_t out[4]);

#endif
