#ifndef ATTRACTOR_H
#define ATTRACTOR_H

#include <inttypes.h>

/* attractor constants */
#define A 0.4263
#define B 2
#define C 4

#define H 0.01

/* stores attractor point values to get mantissa later */
union dbits {
        double d;
        struct {
                uint64_t mant: 52;
                uint64_t exp: 11;
                uint64_t sign: 1;
        } p;
};

/* stores only current point */
struct attractor {
        union dbits x, y, z;
};

void ainit(struct attractor *a, double ix, double iy, double iz);
static inline void anext(struct attractor *a)
{
        a->x.d = a->x.d + H * (-a->y.d - a->z.d);
        a->y.d = a->y.d + H * (a->x.d + A * a->y.d); 
        a->z.d = a->z.d + H * (B + a->z.d * (a->x.d - C));
}

#endif
