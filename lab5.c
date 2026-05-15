#include <stdio.h>    // ввод и вывод
#include <stdlib.h>   // malloc и free
double** operate(double** A, double** B, int n, char op); // подключаем функцию из другого файла (модуля)

int main()
{
    int n;        // размер матрицы
    char op;      // операция + - *
    printf("Введите размер матрицы n: "); // ввод размера матрицы
    scanf("%d", &n);
    double** A = (double**)malloc(n * sizeof(double*)); // создаём матрицу A (указатель на указатели)
    double** B = (double**)malloc(n * sizeof(double*)); // создаём матрицу B

    for (int i = 0; i < n; i++) // выделяем память под строки матриц
    {
        A[i] = (double*)malloc(n * sizeof(double));
        B[i] = (double*)malloc(n * sizeof(double));
    }

    printf("Введите матрицу A:\n"); // ввод матрицы A
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%lf", &A[i][j]); // ввод числа типа double
        }
    }

    printf("Введите матрицу B:\n"); // ввод матрицы B
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%lf", &B[i][j]);
        }
    }

    printf("Введите операцию (+, -, *): "); // ввод операции
    scanf(" %c", &op); // пробел важен, чтобы убрать Enter
    double** C = operate(A, B, n, op); // вызываем функцию из другого файла
    printf("Результат:\n"); // вывод результата

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%.2lf ", C[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) // освобождение памяти матриц A
    {
        free(A[i]);
    }
    free(A);

    for (int i = 0; i < n; i++) // освобождение памяти матриц B
    {
        free(B[i]);
    }
    free(B);

    for (int i = 0; i < n; i++) // освобождение памяти результата C
    {
        free(C[i]);
    }
    free(C);

    return 0; // конец программы
}
