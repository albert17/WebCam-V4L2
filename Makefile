CC = gcc
CFLAGS = -O3
BIN = main 

main: core.o method.o device.o capture.o process.o
		$(CC) $(CFLAGS) -o $(BIN) main.c core.o method.o device.o capture.o process.o

core.o: core.c core.h
		$(CC) -c $(CFLAGS) core.c
method.o: method.c method.h core.h
		$(CC) -c $(CFLAGS) method.c core.h
device.o: device.c device.h method.h core.h
		$(CC) -c $(CFLAGS) device.c
capture.o: capture.c capture.h core.h
		$(CC) -c $(CFLAGS) capture.c
process.o: process.c process.h core.h
		$(CC) -c $(CFLAGS) process.c

clean:
		rm $(BIN) *.o *.gch
