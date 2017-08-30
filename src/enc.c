#include <chaos/enc.h>

void cipher(struct gen *g, uint8_t *buf, uint32_t len)
{
        uint32_t cpos = 0;
        uint32_t ncalls = len >> 2;
        uint8_t left = len & 3;
        uint8_t *tmp = (uint8_t *)&cpos;

        for(uint32_t i = 0; i < ncalls; ++i) {
                cpos = gen32(g);
                buf[(i<<2)] ^= tmp[0];
                buf[(i<<2)+1] ^= tmp[1];
                buf[(i<<2)+2] ^= tmp[2];
                buf[(i<<2)+3] ^= tmp[3];
        }

        if(left == 0) {
                return;
        } else {
                cpos = gen32(g);
                for(uint8_t i = 0; i < left; ++i)
                        buf[(ncalls<<2)+i] ^= tmp[i];
        }
}
