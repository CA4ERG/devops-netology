#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main() {
    int n;
    char op;
    
    printf("Введите размер матрицы n: ");
    scanf("%d", &n);
    
    double **a = (double **)malloc(n * sizeof(double *));
    double **b = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        a[i] = (double *)malloc(n * sizeof(double));
        b[i] = (double *)malloc(n * sizeof(double));
    }
    
    printf("\nВведите элементы матрицы A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            printf("A[%d][%d] = ", i, j);
            scanf("%lf", &a[i][j]);
        }
    
    printf("\nВведите элементы матрицы B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            printf("B[%d][%d] = ", i, j);
            scanf("%lf", &b[i][j]);
        }
    
    printf("\nВыберите операцию (+, -, *): ");
    scanf(" %c", &op);
    
    double **result = matrix_operation(a, b, n, op);
    
    printf("\nРезультат:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%.2f ", result[i][j]);
        printf("\n");
    }
    
    for (int i = 0; i < n; i++) {
        free(a[i]);
        free(b[i]);
        free(result[i]);
    }
    free(a);
    free(b);
    free(result);
    
    return 0;
}


