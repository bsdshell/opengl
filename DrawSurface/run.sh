#!/bin/bash
echo "run OpenGL"

g++ -Wno-deprecated -std=c++11 -v -o drawsurface drawsurface.cpp -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL 

