#/bin/bash
cd "$(dirname "$0")"
#gcc MicroFramework/__core.cpp -o program -lGLU -lglut -std=c++11
clang MicroFramework/__core.cpp -o program -lGLU -lglut -lc++ #-std=c++11
# -std=c++17
#./program
