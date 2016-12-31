/**
 * @file process.h
 * @date 30 Dec 2016
 *
 * Functions to process image and video
 */

#ifndef PROCESS_H
#define PROCESS_H

#include "core.h"

/**
 * Process and image writing a frame.
 *
 * @param p pointer to the frame
 * @param size size of the frame
 * @param frame_number number of the frame
 * @param type type of the capture
 * @param format format of the frame
 * @pram vp descriptor to de video file
 */
void process_image(const char *p, int size, int frame_number, enum type type, 
enum format format, int vp);

/**
 * Reads a frame
 *
 * @param fp pointer to dev
 * @param buffers pointer to buffers
 * @param io method to capture image
 * @param n_buffers pointer to number of buffers
 * @param frame_number number of the frame
 * @param type type of the capture
 * @param format format of the frame
 * @param vp descriptor to de video file
 * @return 0 if a frame has been read properly. 1 in other case
 */
int read_frame(int fd, struct buffer *buffers, enum io_method io, 
unsigned int *n_buffers, unsigned int frame_number, enum type type, 
enum format format, int vp);

/**
 * Loop to read all the frames
 *
 * @param fd pointer to dev
 * @param frame_count number of frames to read
 * @param io method to capture image
 * @param buffers pointer to buffers
 * @param n_buffers pointer to number of buffers
 * @param type type of the capture
 * @param format format of the frame
 * @param vp descriptor to de video file
 */
void mainloop(int fd, int frame_count, enum io_method io, struct buffer *buffers, 
unsigned int *n_buffers, enum type type, enum format format, int vp);

#endif /* PROCESS_H */