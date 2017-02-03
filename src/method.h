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
 */
void init_read(unsigned int buffer_size);

/**
 * Init the device to capture using mmap method
 */
void init_mmap();

/**
 * Init the device to capture using user method
 *
 * @param dev_name name of dev
 * @param fd dev descriptor
 * @param buffer_size size of the buffer
 * @param n_buffers pointer to number of buffers
 * @return pointer to buffers
 */
void init_userp(unsigned int buffer_size);

#endif /* CORE_H */