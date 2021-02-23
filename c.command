#/bin/bash
cd "$(dirname "$0")"
#g++ MicroFramework/__core.cpp -o program -lGLU -lglut -std=c++11
#  -target arm64-apple-macos11
#g++ MicroFramework/__core.cpp -o program -Ilibs/glm -Ilibs/RtMidi17 -std=c++11 #-lc++  # 
#-lGLU -lglut 
#g++ MicroFramework/__core.cpp -o program -framework OpenGL -framework GLUT -Ilibs/glm -Ilibs/RtMidi17 -std=c++11 -target arm64-apple-macos11
clang++ MicroFramework/__core.cpp -o program -std=c++17 -framework GLUT -framework OPENGL -target arm64-apple-macos11 
# -std=c++17
./program
