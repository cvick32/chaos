#include "attractor.h"

/* eulers method approximates integrals */
static inline double nx(struct attractor *a)
{
        return a->x.d + H * (-a->y.d - a->z.d);
}

static inline double ny(struct attractor *a)
{
        return a->y.d + H * (a->x.d + A * a->y.d);
}

static inline double nz(struct attractor *a)
{
        return a->z.d + H * (B + a->z.d * (a->x.d - C));
}

void ainit(struct attractor *a, double ix, double iy, double iz)
{
        a->x.d = ix;
        a->y.d = iy;
        a->z.d = iz;
}

void anext(struct attractor *a)
{
        a->x.d = nx(a);
        a->y.d = ny(a);
        a->z.d = nz(a);
}
