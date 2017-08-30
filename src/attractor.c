#include "attractor.h"

void ainit(struct attractor *a, double ix, double iy, double iz)
{
        a->x.d = ix;
        a->y.d = iy;
        a->z.d = iz;
}
