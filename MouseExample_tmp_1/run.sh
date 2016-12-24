#!/bin/bash
echo "run OpenGL"

#g++ -v -o  draw_point draw_point.cpp -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL 

g++ -Wno-deprecated -std=c++11 -g -v -o mouse_example mouse_example.cpp -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL 
