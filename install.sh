gcc -fPIC -c main.c `pkg-config --cflags geany`
gcc -shared -o main.so main.o `pkg-config --libs geany`
cp -r main.so ~/.config/geany/plugins
