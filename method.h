#ifndef METHOD_H
#define METHOD_H

#include "core.h"

struct buffer* init_read(unsigned int buffer_size);
struct buffer* init_mmap(char *dev_name, int fd, unsigned int *n_buffers);
struct buffer* init_userp(char *dev_name, int fd, unsigned int buffer_size, unsigned int *n_buffers);

#endif /* CORE_H */