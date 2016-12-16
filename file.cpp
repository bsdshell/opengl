#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GLUT/glut.h>  /* Header File For The GLut Library*/
#include "MyLib.h"

int main(int argc, char** argv) {
    printf("dog\n");
    Vector3* v = new Vector3();
    Vector3 v1(2, 3, 4);
    Vector3 v2(1, 2, 3);
    Vector3 v3 = v1.dot(v2);
    v3.print();
    return 0;
}
