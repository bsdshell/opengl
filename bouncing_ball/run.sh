#!/bin/bash
echo "run OpenGL"

g++ -v -o torus torus.cpp  -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL 

