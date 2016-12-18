#!/bin/bash
echo "run OpenGL"

g++ -v -o beziercurve_test beziercurve_test.cpp -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL 

