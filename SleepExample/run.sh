#!/bin/bash
echo "run OpenGL"

g++ -v -o sleepexample sleepexample.cpp -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL 

