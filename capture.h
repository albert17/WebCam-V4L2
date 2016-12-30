#ifndef CAPTURE_H
#define CAPTURE_H

#include "core.h"

void start_capturing(int fd, enum io_method io, struct buffer *buffers, unsigned int *n_buffers);
void stop_capturing(int fd, enum io_method io);

#endif /* CAPTURE_H */