#!/bin/bash
g++ -o cube cube.cpp -I /opt/X11/include/GL/glext.h -framework GLUT -framework OpenGL -framework Cocoa
