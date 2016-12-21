#!/bin/bash
#g++ -o cube cube.cpp -I /opt/X11/include/GL/glext.h -framework GLUT -framework OpenGL -framework Cocoa

g++ -std=c++11 -v -o cube cube.cpp -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL 

