/**
 * @file core.c
 * @date 30 Dec 2016
 *
 * Immplements core.h
 */

#include "core.h"

void errno_exit(const char *s) {
        fprintf(stderr, "%s error %d, %s\n", s, errno, strerror(errno));
        exit(EXIT_FAILURE);
}

int xioctl(int fh, int request, void *arg) {
        int r;

        do {
                r = ioctl(fh, request, arg);
        } while (-1 == r && EINTR == errno);

        return r;
}