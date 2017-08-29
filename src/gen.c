#include <chaos/gen.h>

void gen_init(struct gen *g)
{
        ainit(&g->as[0], gen_seed);
        ainit(&g->as[1], gen_seed);
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
        for(uint8_t i = 0; i < 18; ++i) {
                m[11] += m[5];
                m[3] += m[9];
                m[7] += m[1];
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
