#!/bin/bash

OS_NAME=`uname -o 2>/dev/null || uname -s`

if [ $OS_NAME == "Msys" ]; then
    GLFLAG="-lopengl32"
elif [ $OS_NAME == "Darwin" ]; then
    GLFLAG="-framework OpenGL"
else
    GLFLAG="-lGL"
fi

CFLAGS="-I../gui -Wall -std=c11 -pedantic `sdl2-config --libs` $GLFLAG -lm -O3 -g"

gcc main.c -Igui gui/renderer.c -Igui gui/microui.c -o KanjoTux $CFLAGS

