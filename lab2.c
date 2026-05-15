#include <stdio.h>
#include <stdlib.h>
setlocale (LC_ALL, "RUSSIAN");
static int* allocIntMatrix(int n) {
    return (int*)malloc((size_t)n * n * sizeof(int));
}
static double* allocDoubleMatrix(int n) {
    return (double*)malloc((size_t)n * n * sizeof(double));
}
static long long* allocLongLongMatrix(int n) {
    return (long long*)calloc((size_t)n * n, sizeof(long long));
}
static void freeMatrix(void *p) {
    free(p);
}
static void inputDoubleMatrix(double *a, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("a[%d][%d] = ", i, j);
            scanf("%lf", &a[i*n + j]);
        }
    }
}
static void inputIntMatrix(int *b, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("b[%d][%d] = ", i, j);
            scanf("%d", &b[i*n + j]);
        }
    }
}
static double sumMainDiagonalDouble(const double *a, int n) {
    int i;
    double sum = 0.0;
    for (i = 0; i < n; i++) {
        sum += a[i*n + i];
    }
    return sum;
}
static double sumSecondaryDiagonalDouble(const double *a, int n) {
    int i;
    double sum = 0.0;
    for (i = 0; i < n; i++) {
        sum += a[i*n + (n - 1 - i)];
    }
    return sum;
}
static void squareIntMatrix(const int *b, long long *c, int n) {
    int i, j, k;
    /* c = b * b */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            long long s = 0;
            for (k = 0; k < n; k++) {
                s += (long long)b[i*n + k] * (long long)b[k*n + j];
            }
            c[i*n + j] = s;
        }
    }
}
static void printLongLongMatrix(const long long *m, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%lld ", m[i*n + j]);
        }
        printf("\n");
    }
}
int main(void) {
    int n1, n2;
    printf("Введите размер квадратной матрицы double (для условия 3x3 поставьте 3): ");
    scanf("%d", &n1);
    if (n1 <= 0) {
        printf("Некорректный размер.\n");
        return 1;
    }
    double *A = allocDoubleMatrix(n1);
    if (!A) {
        printf("Ошибка выделения памяти.\n");
        return 1;
    }
    printf("\nВвод матрицы A (double %dx%d):\n", n1, n1);
    inputDoubleMatrix(A, n1);
    printf("\nСумма главной диагонали: %.10g\n", sumMainDiagonalDouble(A, n1));
    printf("Сумма побочной диагонали: %.10g\n", sumSecondaryDiagonalDouble(A, n1));
    freeMatrix(A);
    printf("\nВведите размер квадратной матрицы int (для условия 2x2 поставьте 2): ");
    scanf("%d", &n2);
    if (n2 <= 0) {
        printf("Некорректный размер.\n");
        return 1;
    }
    int *B = allocIntMatrix(n2);
    long long *C = allocLongLongMatrix(n2);
    if (!B || !C) {
        printf("Ошибка выделения памяти.\n");
        freeMatrix(B);
        freeMatrix(C);
        return 1;
    }
    printf("\nВвод матрицы B (int %dx%d):\n", n2, n2);
    inputIntMatrix(B, n2);
    squareIntMatrix(B, C, n2);
    printf("\nКвадрат матрицы B (B*B):\n");
    printLongLongMatrix(C, n2);
    freeMatrix(B);
    freeMatrix(C);
    return 0;
}
