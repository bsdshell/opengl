#!/bin/bash
echo "run OpenGL"

#g++ -v -o  draw_point draw_point.cpp -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL 

g++ -v -o drawline drawline.cpp -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL
