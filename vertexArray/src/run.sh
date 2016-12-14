#!/bin/bash
g++ -o trymain trymain.cpp -I /opt/X11/include/GL/glext.h -framework GLUT -framework OpenGL -framework Cocoa
