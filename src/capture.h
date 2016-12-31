/**
 * @file capture.h
 * @date 30 Dec 2016
 *
 * Functions to set capture options
 */

#ifndef CAPTURE_H
#define CAPTURE_H

#include "core.h"

/**
 * Start the device options to capture images
 *
 * @param fd device descriptor
 * @param io method to capture
 * @param buffers pointer to buffers to allocate images
 * @param pointer to number of buffers
 */
void start_capturing(int fd, enum io_method io, struct buffer *buffers, 
unsigned int *n_buffers);

/**
 * Stop the device options to capture images
 *
 * @param fd device descriptor
 * @param io method to capture
 */
void stop_capturing(int fd, enum io_method io);

#endif /* CAPTURE_H */