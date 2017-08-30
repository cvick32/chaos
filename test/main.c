#include <chaos/enc.h>
#include <stdio.h>
#include <time.h>

#define MSG_LEN 100 

int main(void)
{
        srand(time(NULL));

        /* fill msg with rand bytes */
        uint8_t msg[MSG_LEN];
        uint32_t i;
        for(i = 0; i < MSG_LEN; ++i)
                msg[i] = rand();

        /* original */
        printf("msg: ");
        for(i = 0; i < sizeof msg; ++i)
                printf("%" PRIu8 "[%" PRIu32 "]", msg[i], i);
        putchar('\n');

        /* enc */
        struct gen g;
        uint64_t key[6] = {
                sbytes(), sbytes(), sbytes(), 
                sbytes(), sbytes(), sbytes()
        };
        gen_init(&g, key);
        cipher(&g, msg, sizeof msg);

        printf("msg enc: ");
        for(i = 0; i < sizeof msg; ++i)
                printf("%" PRIu8 "[%" PRIu32 "]", msg[i], i);
        putchar('\n');

        /* dec */
        gen_init(&g, key);
        cipher(&g, msg, sizeof msg);

        printf("msg dec: ");
        for(i = 0; i < sizeof msg; ++i)
                printf("%" PRIu8 "[%" PRIu32 "]", msg[i], i);
        putchar('\n');
}
