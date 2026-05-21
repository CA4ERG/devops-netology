#include <stdio.h>
#include <stdlib.h>

void input_matrix(double **m, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            printf("m[%d][%d] = ", i, j);
            scanf("%lf", &m[i][j]);
        }
}

void input_matrix_int(int **m, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            printf("m[%d][%d] = ", i, j);
            scanf("%d", &m[i][j]);
        }
}

void print_matrix(double **m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%.2f ", m[i][j]);
        printf("\n");
    }
}

void print_matrix_int(int **m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", m[i][j]);
        printf("\n");
    }
}

int main() {
    /* Задача 1: матрица double 3x3 */
    printf("Матрица double 3x3:\n");
    double **a = (double **)malloc(3 * sizeof(double *));
    for (int i = 0; i < 3; i++)
        a[i] = (double *)malloc(3 * sizeof(double));
    
    input_matrix(a, 3);
    printf("\nМатрица:\n");
    print_matrix(a, 3);
    
    double diag1 = a[0][0] + a[1][1] + a[2][2];
    double diag2 = a[0][2] + a[1][1] + a[2][0];
    
    printf("Сумма главной диагонали: %.2f\n", diag1);
    printf("Сумма побочной диагонали: %.2f\n", diag2);
    
    for (int i = 0; i < 3; i++)
        free(a[i]);
    free(a);
    
    printf("\n");
    
    /* Задача 2: матрица int 2x2 */
    printf("Матрица int 2x2:\n");
    int **b = (int **)malloc(2 * sizeof(int *));
    for (int i = 0; i < 2; i++)
        b[i] = (int *)malloc(2 * sizeof(int));
    
    input_matrix_int(b, 2);
    printf("\nМатрица:\n");
    print_matrix_int(b, 2);
    
    int **c = (int **)malloc(2 * sizeof(int *));
    for (int i = 0; i < 2; i++)
        c[i] = (int *)malloc(2 * sizeof(int));
    
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++) {
            c[i][j] = 0;
            for (int k = 0; k < 2; k++)
                c[i][j] += b[i][k] * b[k][j];
        }
    
    printf("Квадрат матрицы:\n");
    print_matrix_int(c, 2);
    
    for (int i = 0; i < 2; i++) {
        free(b[i]);
        free(c[i]);
    }
    free(b);
    free(c);
    
    return 0;
}

