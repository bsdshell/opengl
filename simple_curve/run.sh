#!/bin/bash
echo "run OpenGL"

g++ -v -o simple_curve simple_curve.cpp -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL 

