#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GLUT/glut.h>  /* Header File For The GLut Library*/
#include "BezierCurve.h"
#include "Utility.h"

void test0(){
    Vector3 v0(0, 1, 0);
    Vector3 v1(1, 1, 0);
    Vector3 v2(1, 0, 0);
    int level = 10;
    DDLinkedList<Vector3>* ddl = new DDLinkedList<Vector3>();
    beziercurve(v0, v1, v2, ddl, level);
    fl();    
    print(ddl);
}
int main(int argc, char** argv) {
    test0();
    return 0;
}
