#!/bin/bash
cd "$(dirname "$0")"
#clang++ MicroFramework/__core.cpp -I/Volumes/tool/microframework/libs/libremidi/include -o program -std=c++17 -framework GLUT -framework OPENGL -framework CoreMIDI -target arm64-apple-macos11 
clang++ MicroFramework/__core.cpp -Ilibs/libremidi/include -o program -std=c++17 -framework GLUT -framework OPENGL -framework CoreMIDI -framework CoreAudio -framework CoreFoundation -target arm64-apple-macos11 
# -std=c++17
./program
