
#include "process.h"

void process_image(const char *p, int size, int frame_number) {
        char filename[15];
        sprintf(filename, "frame-%d.raw", frame_number);
        FILE *fp=fopen(filename,"wb");
        fwrite(p, size, 1, fp);
        //write(1,p,size);
        fflush(fp);
        fclose(fp);
}

int read_frame(int fd, struct buffer *buffers, enum io_method io, unsigned int *n_buffers, unsigned int frame_number) {
        struct v4l2_buffer buf;
        unsigned int i;
       // printf("read_frame: Frame %d\n", frame_number);
        switch (io) {
        case IO_METHOD_READ:
                if (-1 == read(fd, buffers[0].start, buffers[0].length)) {
                        switch (errno) {
                        case EAGAIN:
                                return 0;

                        case EIO:
                                /* Could ignore EIO, see spec. */

                                /* fall through */

                        default:
                                errno_exit("read");
                        }
                }

                process_image(buffers[0].start, buffers[0].length, frame_number);
                break;

        case IO_METHOD_MMAP:
                CLEAR(buf);
                buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                buf.memory = V4L2_MEMORY_MMAP;

                if (-1 == xioctl(fd, VIDIOC_DQBUF, &buf)) {
                        switch (errno) {
                        case EAGAIN:
                                printf("ERROR\n");
                                return 0;

                        case EIO:
                                /* Could ignore EIO, see spec. */

                                /* fall through */

                        default:
                                errno_exit("VIDIOC_DQBUF");
                        }
                }
                assert(buf.index < *n_buffers);
                process_image(buffers[buf.index].start, buf.bytesused, frame_number);
                if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
                        errno_exit("VIDIOC_QBUF");
                break;

        case IO_METHOD_USERPTR:
                CLEAR(buf);

                buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                buf.memory = V4L2_MEMORY_USERPTR;

                if (-1 == xioctl(fd, VIDIOC_DQBUF, &buf)) {
                        switch (errno) {
                        case EAGAIN:
                                return 0;

                        case EIO:
                                /* Could ignore EIO, see spec. */

                                /* fall through */

                        default:
                                errno_exit("VIDIOC_DQBUF");
                        }
                }

                for (i = 0; i < *n_buffers; ++i)
                        if (buf.m.userptr == (unsigned long)buffers[i].start
                            && buf.length == buffers[i].length)
                                break;

                assert(i < *n_buffers);

                process_image((void *)buf.m.userptr, buf.bytesused, frame_number);

                if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
                        errno_exit("VIDIOC_QBUF");
                break;
        }

        return 1;
}

void mainloop(int fd, int frame_count, enum io_method io, struct buffer *buffers, unsigned int *n_buffers) {
        for(unsigned int count = 0; count < frame_count; count++) {
                for (;;) {
                        fd_set fds;
                        struct timeval tv;
                        int r;

                        FD_ZERO(&fds);
                        FD_SET(fd, &fds);

                        /* Timeout. */
                        tv.tv_sec = 2;
                        tv.tv_usec = 0;

                        r = select(fd + 1, &fds, NULL, NULL, &tv);

                        if (-1 == r) {
                                if (EINTR == errno)
                                        continue;
                                errno_exit("select");
                        }

                        if (0 == r) {
                                fprintf(stderr, "select timeout\n");
                                exit(EXIT_FAILURE);
                        }

                        if (read_frame(fd, buffers, io, n_buffers, count))
                                break;
                        /* EAGAIN - continue select loop. */
                }
        }
}