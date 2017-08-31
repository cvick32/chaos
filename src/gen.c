#include <chaos/gen.h>

static void init(struct gen *g, double ix, double iy, double iz)
{
        g->x.d = ix;
        g->y.d = iy;
        g->z.d = iz;
}

static void iterate(struct gen *g)
{
        g->x.d = g->x.d + H * (-g->y.d - g->z.d);
        g->y.d = g->y.d + H * (g->x.d + A * g->y.d); 
        g->z.d = g->z.d + H * (B + g->z.d * (g->x.d - C));
}

void gen_init(struct gen *g, uint64_t k[3])
{
        init(g,
                (double)k[0] / UINT64_MAX, 
                (double)k[1] / UINT64_MAX, 
                (double)k[2] / UINT64_MAX);
        for(uint8_t i = 0; i < DISCARD - 1; ++i)
                iterate(g);
}

uint32_t gen32(struct gen *g)
{
        uint32_t m[6];
        m[0] = (uint32_t)(g->x.p.mant >> 32);
        m[1] = (uint32_t)(g->x.p.mant);
        m[2] = (uint32_t)(g->y.p.mant >> 32);
        m[3] = (uint32_t)(g->y.p.mant);
        m[4] = (uint32_t)(g->z.p.mant >> 32);
        m[5] = (uint32_t)(g->z.p.mant);
        iterate(g);

        m[0] += m[1];
        m[2] += m[3];
        m[4] += m[5];
        for(uint8_t i = 0; i < 4; ++i) {
                ROL(m[0],7); ROL(m[3],13);
                m[5] ^= (m[4] + m[3]);
                m[1] ^= (m[2] + m[0]);
                m[2] = m[2] ^ m[0] ^ m[5];
                m[4] = m[4] ^ m[3] ^ m[1];
        }
        m[2] += m[4];
        return m[2];
}
