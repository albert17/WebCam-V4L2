#ifndef PROCESS_H
#define PROCESS_H

#include "core.h"

void process_image(const char *p, int size, int frame_number);
int read_frame(int fd, struct buffer *buffers, enum io_method io, unsigned int n_buffers, unsigned int frame_number);
void mainloop(int fd, int frame_count, enum io_method io, struct buffer *buffers, unsigned int n_buffers);

#endif /* PROCESS_H */