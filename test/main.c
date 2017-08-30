#include <chaos/enc.h>
#include <stdio.h>
#include <time.h>

#define MSG_LEN 64 

int main(void)
{
        srand(time(NULL));
        uint32_t i;

        /* fill msg with rand bytes */
        uint8_t msg[MSG_LEN];
        for(i = 0; i < MSG_LEN; ++i)
                msg[i] = rand();

        uint64_t key[6] = {
                sbytes(), sbytes(), sbytes(), 
                sbytes(), sbytes(), sbytes()
        };
        struct gen g;

        /* original */
        printf("msg:     ");
        for(i = 0; i < sizeof msg; ++i)
                printf("%" PRIu8 "", msg[i]);
        putchar('\n');

        /* enc */
        gen_init(&g, key);
        cipher(&g, msg, sizeof msg);

        printf("msg enc: ");
        for(i = 0; i < sizeof msg; ++i)
                printf("%" PRIu8 "", msg[i]);
        putchar('\n');

        /* dec */
        gen_init(&g, key);
        cipher(&g, msg, sizeof msg);

        printf("msg dec: ");
        for(i = 0; i < sizeof msg; ++i)
                printf("%" PRIu8 "", msg[i]);
        putchar('\n');
}
