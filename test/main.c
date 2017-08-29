#include <chaos/gen.h>
#include <stdio.h>

#include "unif01.h"
#include "bbattery.h"

struct gen g;

unsigned int wrapper(void)
{
        return gen32(&g);
}

int hamming_test(uint32_t a, uint32_t b)
{
        int dist = 0;
        uint32_t val = a ^ b;
        while (val != 0) {
                dist++;
                val &= val - 1;
        }
        return dist;
}

int main(void)
{
        gen_init(&g);

        float avg = 0.0;
        for(uint32_t i = 1; i <= 1000000; i+=2)
                avg += hamming_test((i ^ gen32(&g)), ((i + 1) ^ gen32(&g)));
        printf("avg hamming distance over consecutive pairs: %f\n", 
                avg / 500000);

        unif01_Gen *gen;
        gen = unif01_CreateExternGenBits("chaos", wrapper); 
        bbattery_Crush(gen);
        unif01_DeleteExternGenBits(gen);
}
