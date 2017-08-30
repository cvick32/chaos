#include <chaos/enc.h>

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

const size_t MSG_LEN = 1000000000;

uint64_t sbytes() {
        int fd = 0; 
        ssize_t res = 0;
        uint64_t buf = 0;
        if((fd = open("/dev/urandom", O_RDONLY)) == -1)
                exit(-1);
        if((res = read(fd, &buf, sizeof buf)) < 0)
                exit(-1);
        close (fd);
        return buf;
}

int main(void) 
{
        struct gen g;
        uint64_t key[3] = {sbytes(), sbytes(), sbytes()};
        uint8_t *msg = malloc(MSG_LEN);

        /* fill msg with 1s */
        memset(msg, 1, MSG_LEN);

        /* enc */
        gen_init(&g, key);
        gen32(&g);
        clock_t s = clock();
        cipher(&g, msg, MSG_LEN);
        clock_t e = clock();
        double spent = (double)(e - s) / CLOCKS_PER_SEC;
        printf("enc time 1GiB: %lf\n", spent); 

        free(msg);
}
