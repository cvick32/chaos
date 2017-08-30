#include <chaos/gen.h>

void gen_init(struct gen *g, uint64_t k[6])
{
        ainit(&g->as[0], 
                (double)k[0] / UINT64_MAX, 
                (double)k[1] / UINT64_MAX, 
                (double)k[2] / UINT64_MAX);
        ainit(&g->as[1], 
                (double)k[3] / UINT64_MAX, 
                (double)k[4] / UINT64_MAX, 
                (double)k[5] / UINT64_MAX);

        for(uint8_t i = 0; i < DISCARD - 1; ++i) {
                anext(&g->as[0]);
                anext(&g->as[1]);
        }
}

uint32_t gen32(struct gen *g)
{
        static uint32_t m[12];
        m[0] = (uint32_t)(g->as[0].x.p.mant >> 32);
        m[1] = (uint32_t)(g->as[0].x.p.mant);
        m[2] = (uint32_t)(g->as[0].y.p.mant >> 32);
        m[3] = (uint32_t)(g->as[0].y.p.mant);
        m[4] = (uint32_t)(g->as[0].z.p.mant >> 32);
        m[5] = (uint32_t)(g->as[0].z.p.mant);
        m[6] = (uint32_t)(g->as[1].x.p.mant >> 32);
        m[7] = (uint32_t)(g->as[1].x.p.mant);
        m[8] = (uint32_t)(g->as[1].y.p.mant >> 32);
        m[9] = (uint32_t)(g->as[1].y.p.mant);
        m[10] = (uint32_t)(g->as[1].z.p.mant >> 32);
        m[11] = (uint32_t)(g->as[1].z.p.mant);
        anext(&g->as[0]);
        anext(&g->as[1]);

        m[0] += m[1];
        m[2] += m[3];
        m[4] += m[5];
        m[6] += m[7];
        m[8] += m[9];
        m[10] += m[11];
        for(uint8_t i = 0; i < 14; ++i) {
                m[11] ^= m[5];
                m[3] ^= m[9];
                m[7] ^= m[1];
                ROL(m[4],7); ROL(m[6],13);
                ROL(m[8],7); ROL(m[10],13);
                ROL(m[0],7); ROL(m[2],13);
                m[5] = m[5] ^ m[8] ^ m[10] ^ m[7];
                m[9] = m[9] ^ m[0] ^ m[2] ^ m[11];
                m[1] = m[1] ^ m[4] ^ m[6] ^ m[3];
        }
        m[1] = m[1] ^ m[5] ^ m[9];
        return m[1];
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
