#include <chaos/enc.h>

void cipher(struct gen *g, uint8_t *buf, size_t len)
{
        uint32_t stream_pos;
        size_t ncalls = len >> 2;
        uint8_t left = len & 3;
        uint8_t *tmp = (uint8_t *)&stream_pos;

        for(size_t i = 0; i < ncalls; ++i) {
                stream_pos = gen32(g);
                buf[(i<<2)] ^= tmp[0];
                buf[(i<<2)+1] ^= tmp[1];
                buf[(i<<2)+2] ^= tmp[2];
                buf[(i<<2)+3] ^= tmp[3];
        }
        if(left != 0) {
                stream_pos = gen32(g);
                for(uint8_t i = 0; i < left; ++i)
                        buf[(ncalls<<2)+i] ^= tmp[i];
        }
}
