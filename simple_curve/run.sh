#!/bin/bash
echo "run OpenGL"

g++ -std=c++11 -v -o simple_curve simple_curve.cpp -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL 

