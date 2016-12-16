#!/bin/bash
echo "run OpenGL"

gcc -o try try.c -framework GLUT -framework OpenGL
