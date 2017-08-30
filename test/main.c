#include <chaos/enc.h>
#include <stdio.h>

const uint64_t MSG_LEN = 100;

int main(void) 
{
        struct gen g;
        uint64_t key[3] = {sbytes(), sbytes(), sbytes()};
        uint8_t msg[MSG_LEN];

        /* fill msg with 1s */
        for(uint64_t i = 0; i < MSG_LEN; ++i)
                msg[i] = 1;

        /* enc */
        gen_init(&g, key);
        cipher(&g, msg, MSG_LEN);
        for(uint64_t i = 0; i < MSG_LEN; ++i)
                printf("enc byte #%" PRIu64 ": %" PRIu8 "\n", i, msg[i]);

        /* dec */
        gen_init(&g, key);
        cipher(&g, msg, MSG_LEN);
        for(uint64_t i = 0; i < MSG_LEN; ++i)
                printf("dec byte #%" PRIu64 ": %" PRIu8 "\n", i, msg[i]);
}
