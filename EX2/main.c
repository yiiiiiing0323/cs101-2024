#include <stdio.h>
#include <stdlib.h>
int main()
{
    FILE* fp;
    int a[3]={0,1,2};
    char b[3]="ABC";
    float c[3]={1.1,1.2,1.3};
    int ra[3];
    char rb[3];
    float rc[3];
    
    
    fp=fopen("a.bin","wb+");
    fwrite(a,sizeof(int),3,fp);
    fwrite(b,sizeof(char),3,fp);
    fwrite(c,sizeof(float),3,fp);
    fseek(fp,0,SEEK_SET);
    fread(ra,sizeof(int),3,fp);
    
    //fseek(fp,0,SEEK_SET);
    fread(rb,sizeof(char),3,fp);
    
    //fseek(fp,0,SEEK_SET);
    fread(rc,sizeof(float),3,fp);
    for (int i=0;i<3;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
    for (int j=0;j<3;j++){
        printf("%c ",b[j]);
    }
    printf("\n");
    for (int k=0;k<3;k++){
        printf("%f ",c[k]);
    }
    printf("\n");
    return 0;
}
    printf("\n");
    return 0;
}
