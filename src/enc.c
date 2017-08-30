#include <chaos/enc.h>

void cipher(struct gen *g, uint8_t *buf, uint32_t len)
{
        uint32_t stream_pos[4];
        uint32_t ncalls = len >> 4;
        uint8_t left = len & 15;
        uint8_t *tmp = (uint8_t *)&stream_pos;

        for(uint32_t i = 0; i < ncalls; ++i) {
                gen128(g, stream_pos);

                buf[(i<<4)] ^= tmp[0];
                buf[(i<<4)+1] ^= tmp[1];
                buf[(i<<4)+2] ^= tmp[2];
                buf[(i<<4)+3] ^= tmp[3];

                buf[(i<<4)+4] ^= tmp[4];
                buf[(i<<4)+5] ^= tmp[5];
                buf[(i<<4)+6] ^= tmp[6];
                buf[(i<<4)+7] ^= tmp[7];

                buf[(i<<4)+8] ^= tmp[8];
                buf[(i<<4)+9] ^= tmp[9];
                buf[(i<<4)+10] ^= tmp[10];
                buf[(i<<4)+11] ^= tmp[11];

                buf[(i<<4)+12] ^= tmp[12];
                buf[(i<<4)+13] ^= tmp[13];
                buf[(i<<4)+14] ^= tmp[14];
                buf[(i<<4)+15] ^= tmp[15];
        }

        if(left == 0) {
                return;
        } else {
                gen128(g, stream_pos);
                for(uint8_t i = 0; i < left; ++i)
                        buf[(ncalls<<4)+i] ^= tmp[i];
        }
}
