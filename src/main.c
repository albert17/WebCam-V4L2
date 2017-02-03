/**
 * @file main.c
 * @date 30 Dec 2016
 *
 * Executes the application with several options
 */

#include <getopt.h>

#include "core.h"
#include "method.h"
#include "device.h"
#include "capture.h"
#include "process.h"

/**
 * Print the instructions
 *
 * @param fp file pointer to write the message
 */
static void usage(FILE *fp)
{
        fprintf(fp,
                 "Usage: ./main [options]\n\n"
                 "Options:\n"
                 "-d | --device name   Video device name [ /dev/videoN ]\n"
                 "-t | --type          Capture type [ video | frames ]\n"
                 "-f | --format        Image format [ YUYV | JPEG ] (only applicable for type: frames)\n"
                 "-w | --width         Image width\n"
                 "-h | --height        Image height\n"
                 "-m | --method        Capture method [ mmap | read | userp ]\n"
                 "-n | --number        Number of frames to capture\n"
                 "-r | --fps           Frames per second to capture\n"
                 "");
}

/**
 * List of short options
 */
static const char short_options[] = "d:t:f:h:w:m:n:";

/**
 * List of large options
 */
static const struct option
long_options[] = {
        { "device", required_argument, NULL, 'd' },
        { "type", required_argument, NULL, 't' },
        { "format", required_argument, NULL, 'f' },
        { "width", required_argument, NULL, 'w' },
        { "height", required_argument, NULL, 'h' },
        { "method", required_argument, NULL, 'm' },
        { "num", required_argument, NULL, 'n' },
        { 0, 0, 0, 0 }
};

char *dev_name = "/dev/video0"; // dev name 
enum type type = FRAMES; // type of data
enum format format = JPEG; // format fo data
int height = 480; // height of images
int width = 640; // width of images
int fd = -1; // Device descriptor
enum io_method io = IO_METHOD_MMAP; // method to capture
int frame_count = 10; // number of frames
unsigned int n_buffers = 0; // Pointer to number of buffer
struct buffer *buffers; // Pointer to buffer
int vp = -1; // video file pointer

/**
 * Executes de application
 * @param argc number of params
 * @param argv pointer to params
 */
int main(int argc, char *argv[]) {
        for (;;) {
                int idx;
                int c;

                // get options
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
                            format = YUYV;
                        } 

                        else if (strcmp(optarg, "JPEG") == 0) {
                            format = JPEG;
                        } 

                        else {
                            errno_exit(optarg);
                        }
                        break;
                case 'w':
                        errno = 0;
                        width = strtol(optarg, NULL, 0);
                        if (errno)
                                errno_exit(optarg);
                        break;
                case 'h':
                        errno = 0;
                        height = strtol(optarg, NULL, 0);
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

                default:
                        usage(stderr);
                        exit(EXIT_FAILURE);
                }
        }
        // Open device
        open_device(dev_name);
        
        // Init the devide
        init_device();
        
        // Init the capturing options
        start_capturing();
        
        char videoname[15];
        switch (type)
        {
        case VIDEO:
                sprintf(videoname, "video.mjpeg");
                vp=open(videoname, O_CREAT | O_RDWR | O_APPEND, 0666);
        default:
                break;
        }
        
        // Capture
        mainloop(vp);
        
        // Close video file
        switch (type)
        {
        case VIDEO:
                close(vp);
                break;
        default:
                break;
        }
        
        // Stop capture
        stop_capturing();
        
        // Term device
        term_device();
        
        // Close devie
        close_device();
        
        return 0;
}
