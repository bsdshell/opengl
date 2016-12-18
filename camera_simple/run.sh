#!/bin/bash
echo "run OpenGL"

g++ -v -o camera_simple camera_simple.cpp -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL 

