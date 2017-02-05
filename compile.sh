#!/bin/bash
# Author: A.Alvarez
# Date: 31/01/2017
# Description: Compiles the code for Beaglebone and ubuntu

if [ "$1" == "beaglebone" ]
then
    if [ -z $LINARO ]; then
        echo "Export variable 'LINARO'" >&2
        exit 1
    fi
    export CC="$LINARO/bin/arm-linux-gnueabihf-gcc"
    export INC="-I$LINARO/arm-linux-gnueabihf/libc/usr/include"
    export LIBS="-static -L$LINARO/arm-linux-gnueabihf/libc/lib/arm-linux-gnueabihf -L$LINARO/arm-linux-gnueabihf/libc/usr/lib/arm-linux-gnueabihf"
    make -C ./src  clean &>2
    make -C ./src #&>2
elif [ "$1" == "ubuntu" ]
then
    export CC="gcc"
    make -C ./src  clean &>2
    make -C ./src #&>2
else
    echo "Usage: ./compile [ beaglebone | ubuntu ]" >&2
fi