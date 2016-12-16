#!/bin/bash
echo "run OpenGL"

gcc -o cube cube.c -framework GLUT -framework OpenGL
