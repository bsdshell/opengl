#!/bin/bash
echo "run OpenGL"

gcc -o wireframe wireframe.c -framework GLUT -framework OpenGL
