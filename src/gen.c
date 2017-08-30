#include <chaos/gen.h>

void gen_init(struct gen *g, uint64_t k[3])
{
        ainit(&g->a,
                (double)k[0] / UINT64_MAX, 
                (double)k[1] / UINT64_MAX, 
                (double)k[2] / UINT64_MAX);
        for(uint8_t i = 0; i < DISCARD - 1; ++i)
                anext(&g->a);
}

uint32_t gen32(struct gen *g)
{
        static uint32_t m[6];
        m[0] = (uint32_t)(g->a.x.p.mant >> 32);
        m[1] = (uint32_t)(g->a.x.p.mant);
        m[2] = (uint32_t)(g->a.y.p.mant >> 32);
        m[3] = (uint32_t)(g->a.y.p.mant);
        m[4] = (uint32_t)(g->a.z.p.mant >> 32);
        m[5] = (uint32_t)(g->a.z.p.mant);
        anext(&g->a);

        m[0] += m[1];
        m[2] += m[3];
        m[4] += m[5];
        for(uint8_t i = 0; i < 4; ++i) {
                m[5] ^= (m[4] + m[3]);
                m[1] ^= (m[2] + m[0]);
                ROL(m[0],7); ROL(m[3],13);
                m[2] = m[2] ^ m[0] ^ m[5];
                m[4] = m[4] ^ m[3] ^ m[1];
        }
        m[2] += m[4];
        return m[2];
}

uint64_t gen64(struct gen *g)
{
        uint32_t a = gen32(g);
        uint32_t b = gen32(g);
        uint64_t ret = (uint64_t)a << 32 | b;
        return ret;
}

void gen96(struct gen *g, uint32_t out[3])
{
        out[0] = gen32(g); 
        out[1] = gen32(g); 
        out[2] = gen32(g);
}

void gen128(struct gen *g, uint32_t out[4])
{
        out[0] = gen32(g); 
        out[1] = gen32(g); 
        out[2] = gen32(g);
        out[3] = gen32(g); 
}
