# WebCam-V4L2
WEBCAM-V4L2 is a software which allows to capture images and video from USB cameras using the V4L2 API.
[![Build Status](https://travis-ci.org/albert17/WebCam-V4L2.svg)](https://travis-ci.org/albert17/WebCam-V4L2
)
## Usage
### Compile
```sh
$ make
```
### Execute

```
$ ./main

Usage: ./main [options]

Options:
-d | --device name   Video device name [ /dev/videoN ]
-t | --type          Capture type [ video | frames ]
-f | --format        Image format [ YUYV | JPEG ] (only applicable for type: frames)
-w | --width         Image width
-h | --height        Image height
-m | --method        Capture method [ mmap | read | userp ]
-n | --number        Number of frames to capture
-r | --fps           Frames per second to capture
```
## Enviroment
### Platform
This software has been tested is the following platforms:
* Ubuntu 16.04 - Linux kernel: 4.4.0-57
* Beaglebone - Linux kernel: 3.8.13

### Webcam
This software has been tested with the following cameras:
* Logitech c170

## Disclaimer

This software has been based on the example provided in the [V4L2 API](https://linuxtv.org/downloads/v4l-dvb-apis-new/uapi/v4l/v4l2.html).