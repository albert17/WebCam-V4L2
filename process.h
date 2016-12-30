#ifndef PROCESS_H
#define PROCESS_H

#include "core.h"

void process_image(const char *p, int size, int frame_number, enum type type, enum format format, int vp);
int read_frame(int fd, struct buffer *buffers, enum io_method io, unsigned int *n_buffers, unsigned int frame_number, enum type type, enum format format, int vp);
void mainloop(int fd, int frame_count, enum io_method io, struct buffer *buffers, unsigned int *n_buffers, enum type type, enum format format, int vp);

#endif /* PROCESS_H */