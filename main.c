
#include <getopt.h>

#include "core.h"
#include "method.h"
#include "device.h"
#include "capture.h"
#include "process.h"

static void usage(FILE *fp, int argc, char **argv)
{
        fprintf(fp,
                 "Usage: ./main [options]\n\n"
                 "Options:\n"
                 "-d | --device name   Video device name [ /dev/videoN ]\n"
                 "-t | --type          Capture type [ video | frames ]\n"
                 "-f | --format        Image format [ YUYV | JPEG ] (only applicable for type: frames)\n"
                 "-h | --height        Image height\n"
                 "-w | --width         Image width\n"
                 "-m | --method        Capture method [ mmap | read | userp ]\n"
                 "-n | --number        Number of frames to capture\n"
                 "-r | --fps           Frames per second to capture\n"
                 "");
}

static const char short_options[] = "d:t:f:h:w:m:n:r:";

static const struct option
long_options[] = {
        { "device", required_argument, NULL, 'd' },
        { "type", required_argument, NULL, 't' },
        { "format", required_argument, NULL, 'f' },
        { "height", required_argument, NULL, 'h' },
        { "width", required_argument, NULL, 'w' },
        { "method", required_argument, NULL, 'm' },
        { "num", required_argument, NULL, 'n' },
        { "fps", required_argument, NULL, 'r' },
        { 0, 0, 0, 0 }
};

char *dev_name;
enum type type;
enum format format;
int height;
int width;
enum io_method io;
int frame_count;
int fps;
unsigned int tmp = 0;
unsigned int *n_buffers = &tmp;

int main(int argc, char *argv[]) {
        for (;;) {
                int idx;
                int c;

                c = getopt_long(argc, argv,
                                short_options, long_options, &idx);

                if (-1 == c) { break;}

                switch (c) {
                case 0: /* getopt_long() flag */
                        break;

                case 'd':
                        dev_name = optarg;
                        break;
                case 't':
                        if (strcmp(optarg, "video") == 0) {
                            type = VIDEO;
                        } 

                        else if (strcmp(optarg, "frames") == 0) {
                            type = FRAMES;
                        } 
                        else {
                            errno_exit(optarg);
                        }
                        break;
                case 'f':
                        if (strcmp(optarg, "YUYV") == 0) {
                            type = YUYV;
                        } 

                        else if (strcmp(optarg, "JPEG") == 0) {
                            type = JPEG;
                        } 

                        else {
                            errno_exit(optarg);
                        }
                        break;
                case 'h':
                        errno = 0;
                        height = strtol(optarg, NULL, 0);
                        if (errno)
                                errno_exit(optarg);
                        break;
                case 'w':
                        errno = 0;
                        width = strtol(optarg, NULL, 0);
                        if (errno)
                                errno_exit(optarg);
                        break;
                case 'm':
                        if (strcmp(optarg, "mmap") == 0) {
                            io = IO_METHOD_MMAP;
                        } 

                        else if (strcmp(optarg, "read") == 0) {
                            io = IO_METHOD_READ;
                        }
                        else if (strcmp(optarg, "userp") == 0) {
                            io = IO_METHOD_USERPTR;
                        } 
                        else {
                            errno_exit(optarg);
                        }
                        break;

                case 'n':
                        errno = 0;
                        frame_count = strtol(optarg, NULL, 0);
                        if (errno)
                                errno_exit(optarg);
                        break;

                case 'r':
                        errno = 0;
                        fps = strtol(optarg, NULL, 0);
                        if (errno)
                                errno_exit(optarg);
                        break;

                default:
                        usage(stderr, argc, argv);
                        exit(EXIT_FAILURE);
                }
        }
        int fd = open_device(dev_name);
        struct buffer *buffers;
        buffers = init_device(fd, dev_name, io, height, width, format, n_buffers);
        start_capturing(fd, io, buffers, n_buffers);
        mainloop(fd, frame_count, io, buffers, n_buffers);
        stop_capturing(fd, io);
        term_device(io, buffers, n_buffers);
        close_device(fd);
        return 0;
}
