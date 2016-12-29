#ifndef CORE_H
#define CORE_H

#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <linux/videodev2.h>
#include <unistd.h>
#include <assert.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>


#define CLEAR(x) memset(&(x), 0, sizeof(x))

enum io_method {
        IO_METHOD_READ,
        IO_METHOD_MMAP,
        IO_METHOD_USERPTR,
};

enum type {
        VIDEO,
        FRAMES,
};

enum format {
        YUYV,
        JPEG,
};

struct buffer {
        void   *start;
        size_t  length;
};

void errno_exit(const char *s);
int xioctl(int fh, int request, void *arg);

#endif /* CORE_H */