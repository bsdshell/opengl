#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ReadTeapot.h"

int main() {
    char fname[] = "teacup";
    float arrf[26][4][4][3];

    ReadTeapot readteapot(fname);
    readteapot.loadbatch(arrf);
}

