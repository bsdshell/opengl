#!/bin/bash
echo "run OpenGL"

g++ -v -o bender bender.cpp -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL 

