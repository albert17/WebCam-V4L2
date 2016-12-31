/**
 * @file method.h
 * @date 30 Dec 2016
 *
 * Functions to init the method of capture
 */

#ifndef METHOD_H
#define METHOD_H

#include "core.h"

/**
 * Init the device to capture using read method
 *
 * @param buffer_size size of buffer
 * @return pointer to buffers
 */
struct buffer* init_read(unsigned int buffer_size);

/**
 * Init the device to capture using mmap method
 *
 * @param dev_name name of dev
 * @param fd dev descriptor
 * @param n_buffers pointer to number of buffers
 * @return pointer to buffers
 */
struct buffer* init_mmap(char *dev_name, int fd, unsigned int *n_buffers);

/**
 * Init the device to capture using user method
 *
 * @param dev_name name of dev
 * @param fd dev descriptor
 * @param buffer_size size of the buffer
 * @param n_buffers pointer to number of buffers
 * @return pointer to buffers
 */
struct buffer* init_userp(char *dev_name, int fd, unsigned int buffer_size, 
unsigned int *n_buffers);

#endif /* CORE_H */