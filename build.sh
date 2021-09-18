#!/bin/sh

gcc src/main.c -Wall \
 -I include \
 -L ./ \
 -l glfw.3 \
 -o main.bin \
 -rpath ./