# Variables for Beaglebone
LINARO = /opt/gcc-linaro-arm-linux-gnueabihf-4.8-2013.06_linux
CC = $(LINARO)/bin/arm-linux-gnueabihf-gcc
INC = -I$(LINARO)/arm-linux-gnueabihf/libc/usr/include
LIBS = -static -L$(LINARO)/arm-linux-gnueabihf/libc/lib/arm-linux-gnueabihf -L$(LINARO)/arm-linux-gnueabihf/libc/usr/lib/arm-linux-gnueabihf

# Variable for Ubuntu
CFLAGS = -std=c99

#Variable for all
BIN = main 
main: core.o method.o device.o capture.o process.o
		$(CC) $(CFLAGS) $(LIBS) -o $(BIN) main.c core.o method.o device.o capture.o process.o

core.o: core.c core.h
		$(CC) -c $(INC) $(CFLAGS) core.c
method.o: method.c method.h core.h
		$(CC) -c $(INC) $(CFLAGS) method.c core.h
device.o: device.c device.h method.h core.h
		$(CC) -c $(INC) $(CFLAGS) device.c
capture.o: capture.c capture.h core.h
		$(CC) -c $(INC) $(CFLAGS) capture.c
process.o: process.c process.h core.h
		$(CC) -c $(INC) $(CFLAGS) process.c

clean:
		rm -rf $(BIN) *.o *.gch
#modprobe ucvvideo
vb2: dqbuf of buffer 0, with state 0
