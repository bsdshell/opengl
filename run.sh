#!/bin/bash
echo "run OpenGL"

g++ -o draw_polygon  draw_polygon.c -framework GLUT -framework OpenGL
