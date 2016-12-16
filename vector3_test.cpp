#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GLUT/glut.h>  /* Header File For The GLut Library*/
#include "MyLib.h"

void test0(){
    Vector3 v1(2, 3, 4);
    Vector3 v2(1, 2, 3);
    Vector3 v3 = v1.dot(v2);
    v3.print();
}

void test1(){
    Vector3 v1(2, 3, 4);
    Vector3 v2(1, 2, 3);
    Vector3 v3 = v1 + v2; 
    v3.print();
}

void test2(){
    Vector3 v1(2, 3, 4);
    Vector3 v2(1, 2, 3);
    Vector3 v3 = v1 - v2; 
    v3.print();
}

void test3(){
    Vector3 v1(2, 3, 4);
    Vector3 v3 = v1/2.0; 
    v3.print();
}
int main(int argc, char** argv) {
    test0();
    test1();
    test2();
    test3();
    return 0;
}
