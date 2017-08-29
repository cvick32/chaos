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
        uint64_t k[6] = {
                sbytes(), sbytes(), sbytes(), 
                sbytes(), sbytes(), sbytes()
        };
        gen_init(&g, k);

        uint32_t i;
        uint32_t avg = 0;
        for(i = 1; i <= 1000000; i+=2)
                avg += hamming_test((i ^ gen32(&g)), ((i + 1) ^ gen32(&g)));
        printf("avg hamming distance over consecutive pairs: %f\n", 
                        (float)avg / 500000);

        for(i = 1; i <= 10; ++i)
                printf("%d enc: %" PRIu32 "\n", i, i ^ gen32(&g));
        for(i = 1; i <= 10; ++i)
                printf("%d enc: %" PRIu32 "\n", i, i ^ gen32(&g));
}
