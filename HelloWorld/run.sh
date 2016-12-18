#!/bin/bash
echo "run OpenGL"

g++ -v -o hello_world hello_world.cpp -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL 

