#!/bin/bash
echo "run OpenGL"

g++ -std=c++11 -v -o lookat lookat.cpp -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL 

