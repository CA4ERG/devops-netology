#include <stdlib.h>
#include "matrix.h"

double** matrix_operation(double **a, double **b, int n, char op) {
    double **c = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
        c[i] = (double *)malloc(n * sizeof(double));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (op == '+')
                c[i][j] = a[i][j] + b[i][j];
            else if (op == '-')
                c[i][j] = a[i][j] - b[i][j];
            else if (op == '*') {
                c[i][j] = 0;
                for (int k = 0; k < n; k++)
                    c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    
    return c;
}
