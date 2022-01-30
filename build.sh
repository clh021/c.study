#/bin/bash
gcc -Wall -g hello.c -o hello -L/usr/X11R6/lib \
    -lglib -lgdk -lgtk -lX11 -lXext -lmgcc -o version version.c `pkg-config --libs --cflags gtk+-2.0`
gcc -o hello hello.c `pkg-config --libs --cflags gtk+-2.0`
