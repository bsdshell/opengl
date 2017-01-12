#!/bin/bash
echo "run OpenGL"

#g++ -v -o  draw_point draw_point.cpp -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL 

g++ -g -v -o drawtriangle drawtriangle.cpp -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL
