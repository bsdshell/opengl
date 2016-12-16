#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>  /* Header File For The GLut Library*/

int arr[1];
int fun(int* p){
    if(*p < 4){
        *p = *p + 1;
        printf("*p=[%d]\n", *p);
        fun(p);
    }
}
void fun2(){
    arr[0] = 100;
}

int main(int argc, char** argv) {
    int p = 5;
    fun(&p);
    printf("p=[%d]\n", p);
    fun2();
    printf("arr[0]=[%d]\n", arr[0]);
    return 0;
}
