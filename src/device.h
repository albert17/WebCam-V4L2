/**
 * @file device.h
 * @date 30 Dec 2016
 *
 * Functions to open, close, init and term the device.
 */

#ifndef DEVICE_H
#define DEVICE_H

#include "core.h"

/**
 * Open the device
 *
 * @param dev_name name of the device
 * @return device descriptor
 */
int open_device(char *dev_name);

/**
 * Close the device
 *
 * @param fd device descriptor
 */
void close_device(int fd);

/**
 * Init the device
 *
 * @param fd device descriptor
 * @param dev_name device name
 * @param io method to capture images
 * @param width width of images
 * @param height height of images
 * @param format format of images
 * @param n_buffers number of buffers
 * @return pointer to buffer to store images
 */
struct buffer* init_device(int fd, char *dev_name, enum io_method io,  int width, 
int height, enum format format, unsigned int *n_buffers);

/**
 * Terminates the device
 *
 * @param io method to capture images
 * @param buffers pointer to buffer to store images
 * @param n_buffers number of buffers
 */
void term_device(enum io_method io, struct buffer *buffers, unsigned int *n_buffers);

#endif /* DEVICE_H */