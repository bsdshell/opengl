#!/bin/bash
echo "run OpenGL"

g++ -Wno-deprecated -std=c++11 -v -o simple_surface simple_surface.cpp -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL 

