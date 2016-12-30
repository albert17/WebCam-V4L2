#ifndef DEVICE_H
#define DEVICE_H

#include "core.h"

int open_device(char *dev_name);
void close_device(int fd);
struct buffer* init_device(int fd, char *dev_name, enum io_method io, int height, int width, enum format format, unsigned int *n_buffers);
void term_device(enum io_method io, struct buffer *buffers, unsigned int *n_buffers);

#endif /* DEVICE_H */