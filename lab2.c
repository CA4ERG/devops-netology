#include <stdio.h>
#include <stdlib.h>
#include <windows.h> //кодировка русского в VSCode
int main()
{
    SetConsoleOutputCP(CP_UTF8); //кодировка русского в VSCode
    int m,n;
    printf("Введите кол-во строк и столбцов матрицы(через пробел):\n");
    scanf("%d %d",&m,&n);
    double **mat = (double**)malloc(m * sizeof(double*));
        for(int i = 0; i<m; i++){
            mat[i] = (double*)malloc(n * sizeof(double));
        }
    printf("Введите элементы матрицы (через пробел) размер - %dх%d:\n",m,n);
    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
        scanf("%lf",&mat[i][j]);
        }  
    }

    double sumg=0,sump=0;
    for(int i=0;i<m;++i)
        sumg+=mat[i][i],sump+=mat[i][m-1-i];
    printf("Сумма главной = %.2lf, Сумма побочной = %.2lf\n",sumg,sump);
    
    if(m==n){
        double **kvad = (double**)malloc(m * sizeof(double*));
        for (int i = 0; i<m;++i){
            kvad[i]=(double*)malloc(n*sizeof(double));
        }
    
    for(int i=0;i<m;++i){
        for(int j=0;j<m;++j){
            for(int k=0;k<m;++k)
                kvad[i][j]+=mat[i][k]*mat[k][j];
            }
        }

    printf("Квадрат матрицы:\n");
    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            printf(" %3.0lf",kvad[i][j]);
        }
    printf("\n");
    }
    for(int i=0;i<m;++i){
        free(kvad[i]);
    
    }
    free(kvad);
    }
    else{
        printf("!!!Матрица не квадаратная!!!\n");
    }
   


    
    return 0;
}   