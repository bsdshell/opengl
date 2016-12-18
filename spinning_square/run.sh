#!/bin/bash
echo "run OpenGL"

g++ -v -o spinning_square spinning_square.cpp  -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL 

