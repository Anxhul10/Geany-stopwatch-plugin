#!/usr/bin/env bash
set -e

gcc -fPIC -c main.c $(pkg-config --cflags geany)
gcc -shared -o main.so main.o $(pkg-config --libs geany)
mkdir -p ~/.config/geany/plugins
cp main.so ~/.config/geany/plugins
