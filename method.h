#ifndef METHOD_H
#define METHOD_H

#include "core.h"

void init_read(unsigned int buffer_size,struct buffer *buffers);
void init_mmap(char *dev_name, int fd, struct buffer *buffers, unsigned int n_buffers);
void init_userp(char *dev_name, int fd, unsigned int buffer_size, struct buffer *buffers, unsigned int n_buffers);

#endif /* CORE_H */