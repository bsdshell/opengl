#!/bin/bash
#g++ -o surface surface.c -framework GLUT -framework OpenGL -framework Cocoa
gcc -o BezierSurface BezierSurface.c   -framework GLUT -framework OpenGL -framework Cocoa
