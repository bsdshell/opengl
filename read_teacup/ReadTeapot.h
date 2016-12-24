class ReadTeapot{
    FILE *fp;
    public:
    char fname[100];
    ReadTeapot(char name[100]){
      strcpy(fname, name);

      printf("fnmae=[%s]\n", this->fname);

      if (!(fp = fopen(fname,"r"))) {
        fprintf(stderr,"loadbatch: Can't open %s\n", fname);
        exit(1);
      }
    }
    ~ReadTeapot(){
        if(fp) fclose(fp); 
    }
    void loadbatch(float arrf[26][4][4][3]) {
      int ii;
      float x,y,z;
      int a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p;
      int patches;
      int verticies;

      float vert[251][3];
      int   arr[26][4][4];

      fscanf(fp,"%i\n", &patches);
      for (ii = 0; ii < patches; ii++) {
        fscanf(fp,"%i, %i, %i, %i,",&a,&b,&c,&d);
        fscanf(fp,"%i, %i, %i, %i,",&e,&f,&g,&h);
        fscanf(fp,"%i, %i, %i, %i,",&i,&j,&k,&l);
        fscanf(fp,"%i, %i, %i, %i\n",&m,&n,&o,&p);
        oneBatch(ii, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, arr);
      }
      
      fscanf(fp,"%i\n", &verticies);
      for (ii = 1; ii <= verticies; ii++) {
        fscanf(fp,"%f, %f, %f\n",&x,&y,&z);
        onePoint(ii, x, y, z, vert);
      }
      fclose(fp);

      map(vert, arr, arrf);
    }

    private:
    void oneBatch(int ii, int a, int b, int c, int d, int e, int f, int g, int h,int i,
    int j, int k, int l, int m, int n, int o, int p, int arr[26][4][4]){
        arr[ii][0][0] = a;
        arr[ii][0][1] = b;
        arr[ii][0][2] = c;
        arr[ii][0][3] = d; 

        arr[ii][1][0] = e;
        arr[ii][1][1] = f; 
        arr[ii][1][2] = g; 
        arr[ii][1][3] = h; 

        arr[ii][2][0] = i; 
        arr[ii][2][1] = j; 
        arr[ii][2][2] = k; 
        arr[ii][2][3] = l; 

        arr[ii][3][0] = m; 
        arr[ii][3][1] = n; 
        arr[ii][3][2] = o; 
        arr[ii][3][3] = p; 
    
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                printf("[%i]", arr[ii][i][j]);
            } 
            printf("\n");
        } 
        printf("\n");

    }

    void map(float vert[251][3], int arr[26][4][4], float arrf[26][4][4][3]){
        for(int i=0; i<26; i++){
            for(int j=0; j<4; j++){
                for(int k=0; k<4; k++){
                    for(int x=0; x<3; x++){
                        arrf[i][j][k][x] = vert[arr[i][j][k]][x];
                        printf("[%f]", arrf[i][j][k][x]);
                    }
                    printf("\n");
                } 
                printf("\n");
            } 
            printf("\n");
        } 
    }

    void onePoint(int ii, float x, float y, float z, float vert[251][3]){
        vert[ii][0] = x;
        vert[ii][1] = y;
        vert[ii][2] = z;
    }
};


