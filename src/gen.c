#include <chaos/gen.h>

void gen_init(struct gen *k)
{
        ainit(&k->as[0], gen_seed);
        ainit(&k->as[1], gen_seed);
        for(uint8_t i = 0; i < DISCARD - 1; ++i) {
                anext(&k->as[0]);
                anext(&k->as[1]);
        }
}

static void extract(struct gen *k, uint32_t out[12])
{
        out[0] = (uint32_t)(k->as[0].x.p.mant >> 32);
        out[1] = (uint32_t)(k->as[0].x.p.mant);
        out[2] = (uint32_t)(k->as[0].y.p.mant >> 32);
        out[3] = (uint32_t)(k->as[0].y.p.mant);
        out[4] = (uint32_t)(k->as[0].z.p.mant >> 32);
        out[5] = (uint32_t)(k->as[0].z.p.mant);
        out[6] = (uint32_t)(k->as[1].x.p.mant >> 32);
        out[7] = (uint32_t)(k->as[1].x.p.mant);
        out[8] = (uint32_t)(k->as[1].y.p.mant >> 32);
        out[9] = (uint32_t)(k->as[1].y.p.mant);
        out[10] = (uint32_t)(k->as[1].z.p.mant >> 32);
        out[11] = (uint32_t)(k->as[1].z.p.mant);
}

uint32_t gen32(struct gen *k)
{
        static uint32_t m[12];
        extract(k, m);
        anext(&k->as[0]);
        anext(&k->as[1]);

        m[0]  += m[1];
        m[2]  += m[3];
        m[4]  += m[5];
        m[6]  += m[7];
        m[8]  += m[9];
        m[10] += m[11];
        for(uint8_t i = 0; i < 24; ++i) {
                m[3] += m[5];
                m[7] += m[9];
                m[11] += m[1];
                ROL(m[0],7);
                ROL(m[4],13);
                ROL(m[2],7);
                ROL(m[6],13);
                ROL(m[8],7);
                ROL(m[10],13);
                P(m[1],m[0],m[4],m[3]);
                P(m[5],m[2],m[6],m[7]);
                P(m[9],m[8],m[10],m[11]);
        }
        m[1] ^= (m[5] ^ m[9]);
        return m[1];
}
