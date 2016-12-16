#!/bin/bash
#g++ -o surface surface.c -framework GLUT -framework OpenGL -framework Cocoa
gcc -o beziercurve beziercurve.cpp -framework GLUT -framework OpenGL -framework Cocoa &> output.txt
