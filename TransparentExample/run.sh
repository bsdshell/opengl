#!/bin/bash
echo "run OpenGL"

g++ -Wno-deprecated -std=c++11 -g -v -o transparent transparent.cpp -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL 


