#!/bin/bash
g++ -o highlight highlight.c -framework GLUT -framework OpenGL -framework Cocoa

g++ -Wno-deprecated -std=c++11 -v -o select_model select_model.cpp -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL 
