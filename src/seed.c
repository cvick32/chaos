#include "seed.h"

double gen_seed() {
        int fd = 0; 
        ssize_t res = 0;
        uint64_t buf = 0;
        if((fd = open("/dev/urandom", O_RDONLY)) == -1)
                exit(-1);
        if((res = read(fd, &buf, sizeof(buf))) < 0)
                exit(-1);
        close (fd);
        return (double)buf / UINT64_MAX;
}