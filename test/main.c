#include <chaos/gen.h>
#include <stdio.h>

uint32_t hamming_test(uint32_t a, uint32_t b)
{
        uint32_t dist = 0;
        uint32_t val = a ^ b;
        while (val != 0) {
                dist++;
                val &= val - 1;
        }
        return dist;
}

int main(void)
{
        struct gen g;
        uint32_t avg = 0;

        gen_init(&g);
        for(uint32_t i = 1; i <= 1000000; i+=2)
                avg += hamming_test((i ^ gen32(&g)), ((i + 1) ^ gen32(&g)));
        printf("avg hamming distance over consecutive pairs: %f\n", 
                        (float)avg / 500000);
}
