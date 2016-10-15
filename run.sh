#!/bin/bash
echo "run OpenGL"

g++ -o first first.c -framework GLUT -framework OpenGL
    -L"/System/Library/Frameworks/OpenGL.framework/Libraries"
    -lGL -lGLU -lm -lobjc -lstdc++
