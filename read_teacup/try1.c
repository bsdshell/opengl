#include <stdio.h>
#include <stdlib.h>

void B_patch(int ii, int a, int b, int c, int d, int e, int f, int g, int h,int i,
int j, int k, int l, int m, int n, int o, int p){
    printf("[%i]", a);
}

void B_point(int ii, float x, float y, float z){
    printf("[%f]", x);
}

void Load_patch(char *filename, int *patches, int* verticies) {
  int ii;
  float x,y,z;
  int a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p;

  FILE *fp;

  if (!(fp = fopen(filename,"r"))) {
    fprintf(stderr,"Load_patch: Can't open %s\n",filename);
  }else{
      for (ii = 0; ii < num; ii++) {
        fscanf(fp,"%i, %i, %i, %i,",&a,&b,&c,&d);
        fscanf(fp,"%i, %i, %i, %i,",&e,&f,&g,&h);
        fscanf(fp,"%i, %i, %i, %i,",&i,&j,&k,&l);
        fscanf(fp,"%i, %i, %i, %i\n",&m,&n,&o,&p);
//        B_patch(ii, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
      }
      if(verticies == NULL){
          printf("verticies is null");
      }
      
//      fscanf(fp,"%i\n", verticies);
//      printf("num=[%i] ii=[%i]", num, ii);
//      (void)fscanf(fp,"%i\n", vert);
//      (void)fscanf(fp,"%i\n",verticies);
//      if(verticies == NULL){
//          printf("verticies is null");
//      }
//      for (ii = 1; ii <= *verticies; ii++) {
//        (void)fscanf(fp,"%f, %f, %f\n",&x,&y,&z);
//        //B_point(ii, (double)x,(double)y,(double)z);
//      }
  }
}

int main() {
//    char filename[] = "teacup";
    char filename[] = "file.txt";
    int* patches;
    int* verticies;
    Load_patch(filename, patches, verticies);
    printf("dog");
}

