#ifndef GEN_H 
#define GEN_H

#include "../src/attractor.h"
#include "../src/seed.h"

/* removes initial noise */
#define DISCARD 64 

#define ROL(x,n) ((x = ((x << n) | (x >> (32 - n)))))

struct gen {
        struct attractor as[2];
};

void gen_init(struct gen *g);
uint32_t gen32(struct gen *g);

#endif
