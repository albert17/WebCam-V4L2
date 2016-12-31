/**
 * @file device.c
 * @date 30 Dec 2016
 *
 * Immplements device.h
 */

#include "method.h"
#include "device.h"

int open_device(char *dev_name) {
        struct stat st;

        if (-1 == stat(dev_name, &st)) {
                fprintf(stderr, "Cannot identify '%s': %d, %s\n",
                         dev_name, errno, strerror(errno));
                exit(EXIT_FAILURE);
        }

        if (!S_ISCHR(st.st_mode)) {
                fprintf(stderr, "%s is no device\n", dev_name);
                exit(EXIT_FAILURE);
        }

        int fd = open(dev_name, O_RDWR /* required */ | O_NONBLOCK, 0);

        if ( fd == -1 ) {
                fprintf(stderr, "Cannot open '%s': %d, %s\n",
                         dev_name, errno, strerror(errno));
                exit(EXIT_FAILURE);
        }
        return fd;
}

void close_device(int fd) {
        if (-1 == close(fd))
                errno_exit("close");

        fd = -1;
}

struct buffer* init_device(int fd, char *dev_name, enum io_method io, int width, int height, enum format format, unsigned int *n_buffers) {
        struct v4l2_capability cap;
        struct v4l2_cropcap cropcap;
        struct v4l2_crop crop;
        struct v4l2_format fmt;
        unsigned int min;

        if (-1 == xioctl(fd, VIDIOC_QUERYCAP, &cap)) {
                if (EINVAL == errno) {
                        fprintf(stderr, "%s is no V4L2 device\n",
                                 dev_name);
                        exit(EXIT_FAILURE);
                } else {
                        errno_exit("VIDIOC_QUERYCAP");
                }
        }

        if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
                fprintf(stderr, "%s is no video capture device\n",
                         dev_name);
                exit(EXIT_FAILURE);
        }

        switch (io) {
        case IO_METHOD_READ:
                if (!(cap.capabilities & V4L2_CAP_READWRITE)) {
                        fprintf(stderr, "%s does not support read i/o\n",
                                 dev_name);
                        exit(EXIT_FAILURE);
                }
                break;

        case IO_METHOD_MMAP:
        case IO_METHOD_USERPTR:
                if (!(cap.capabilities & V4L2_CAP_STREAMING)) {
                        fprintf(stderr, "%s does not support streaming i/o\n",
                                 dev_name);
                        exit(EXIT_FAILURE);
                }
                break;
        }


        /* Select video input, video standard and tune here. */


        CLEAR(cropcap);

        cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

        if (0 == xioctl(fd, VIDIOC_CROPCAP, &cropcap)) {
                crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                crop.c = cropcap.defrect; /* reset to default */

                if (-1 == xioctl(fd, VIDIOC_S_CROP, &crop)) {
                        switch (errno) {
                        case EINVAL:
                                /* Cropping not supported. */
                                break;
                        default:
                                /* Errors ignored. */
                                break;
                        }
                }
        } else {
                /* Errors ignored. */
        }


        CLEAR(fmt);

        fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        fmt.fmt.pix.width = width;
        fmt.fmt.pix.height = height;
        switch (format) {
                case JPEG:
                        fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
                        break;
                default:
                        fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
                        break;
        }
        fmt.fmt.pix.field = V4L2_FIELD_ANY;

        if (-1 == xioctl(fd, VIDIOC_S_FMT, &fmt))
                errno_exit("VIDIOC_S_FMT");

        /* Buggy driver paranoia. */
        min = fmt.fmt.pix.width * 2;
        if (fmt.fmt.pix.bytesperline < min)
                fmt.fmt.pix.bytesperline = min;
        min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
        if (fmt.fmt.pix.sizeimage < min)
                fmt.fmt.pix.sizeimage = min;

        struct buffer *buffers;
        switch (io) {
        case IO_METHOD_READ:
                buffers = init_read(fmt.fmt.pix.sizeimage);
                break;

        case IO_METHOD_MMAP:
                buffers =  init_mmap(dev_name, fd, n_buffers);
                break;

        case IO_METHOD_USERPTR:
                buffers = init_userp(dev_name, fd, fmt.fmt.pix.sizeimage, n_buffers);
                break;
        }
        return buffers;
}

void term_device(enum io_method io, struct buffer *buffers, unsigned int *n_buffers) {
        unsigned int i;

        switch (io) {
        case IO_METHOD_READ:
                free(buffers[0].start);
                break;

        case IO_METHOD_MMAP:
                for (i = 0; i < *n_buffers; ++i){
                        if (-1 == munmap(buffers[i].start, buffers[i].length)){
                                errno_exit("munmap");
                        }
                }
                break;

        case IO_METHOD_USERPTR:
                for (i = 0; i < *n_buffers; ++i)
                        free(buffers[i].start);
                break;
        }
        free(buffers);
}
        