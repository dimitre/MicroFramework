#/bin/bash
cd "$(dirname "$0")"
gcc MicroFramework/__core.cpp -o program -lGL -lGLU -lglut
#./program
