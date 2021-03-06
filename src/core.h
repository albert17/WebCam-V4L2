/**
 * @file core.h
 * @date 30 Dec 2016
 *
 * Basic structures and functions
 */

#ifndef CORE_H
#define CORE_H

#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <linux/videodev2.h>
#include <unistd.h>
#include <assert.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>


#define CLEAR(x) memset(&(x), 0, sizeof(x))

/**
 * Enumeration of methods
 */
enum io_method {
        IO_METHOD_READ, /** Read method */
        IO_METHOD_MMAP, /** MMAP method*/
        IO_METHOD_USERPTR, /** USER method */
};

/**
 * Enumeration of types
 */
enum type {
        VIDEO, /** Video */
        FRAMES, /** Frames */
};

/**
 * Enumeration of formats
 */
enum format {
        YUYV, /** YUYV */
        JPEG, /** JPEG */
};

/**
 * Buffer struct
 */
struct buffer {
        void   *start; /** Pointer to the buffer*/
        size_t  length; /** Length of the buffer*/
};

// Define shared structs
extern char *dev_name; // dev name 
extern enum type type; // type of data
extern enum format format; // format fo data
extern int height; // height of images
extern int width; // width of images
extern int fd; // Device descriptor
extern enum io_method io; // method to capture
extern int frame_count; // number of frames
extern unsigned int n_buffers; // Pointer to number of buffer
extern struct buffer *buffers; // Pointer to buffer
extern int vp; // video file pointer



/**
 * Exit the application with an error message
 * 
 * @param s error message
 */
void errno_exit(const char *s);

/**
 * Configure de camera
 *
 * @param fh descriptor device
 * @param request request to the device
 * @param pointer to arguments
 */
int xioctl(int fh, int request, void *arg);

#endif /* CORE_H */