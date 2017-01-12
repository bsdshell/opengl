#!/bin/bash
echo "run OpenGL"

g++ -Wno-deprecated -std=c++11 -v -o viewport viewport.cpp -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL 

