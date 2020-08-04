#/bin/bash
cd "$(dirname "$0")"
gcc _mf.cpp -o program -lGL -lGLU -lglut
./program
