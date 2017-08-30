#include <chaos/enc.h>
#include <stdio.h>

#define MSG_LEN 22

int main(void)
{
        uint32_t i;
        uint8_t msg[MSG_LEN] = {
                180,  27, 146, 108, 
                221,  49, 231, 201,
                 73, 235, 214,  98, 
                154,  50,  78,  13, 
                 24, 127,  98,  42, 
                107, 234
        };
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
