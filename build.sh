#/bin/bash
rm -rf build
mkdir build
cc src/main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o build/main
