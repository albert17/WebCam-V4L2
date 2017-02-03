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
 */
void open_device();

/**
 * Close the device
 *
 * @param fd device descriptor
 */
void close_device();

/**
 * Init the device
 *
 */
void init_device();

/**
 * Terminates the device
 */
void term_device();

#endif /* DEVICE_H */