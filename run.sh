#!/bin/bash
echo "run OpenGL"

g++ -v -o draw_polygon  draw_polygon.c -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL 

