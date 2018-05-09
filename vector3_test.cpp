#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GLUT/glut.h>  /* Header File For The GLut Library*/
#include "MyLib.h"
using namespace SpaceTest;

void test0(){
    Complex c1;
    Test::t(c1.x == 0.0);
    Test::t(c1.y == 0.0);
}

int main(int argc, char** argv) {
    return 0;
}
