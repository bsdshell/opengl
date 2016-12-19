#!/bin/bash
echo "run OpenGL"

clang -framework GLUT -framework OpenGL -framework Cocoa check_opengl.cpp -o check_opengl 

