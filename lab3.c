#include <stdio.h>
#include <locale.h>

int main() {
	setlocale (LC_ALL, "RUSSIAN");
    // ===== 1. Работа со строкой =====
    char str[81];

    printf("Введите строку (до 80 символов):\n");
    fgets(str, 81, stdin);

    // Замена 'a' и 'b' на 'A' и 'B'
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == 'a') str[i] = 'A';
        if (str[i] == 'b') str[i] = 'B';
    }

    printf("Результат:\n%s\n", str);

    // ===== 2. Работа с матрицей =====
    int n;
    printf("\nВведите размер квадратной матрицы: ");
    scanf("%d", &n);

    int matrix[100][100]; // запас до 100x100

    printf("Введите элементы матрицы:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Суммы диагоналей
    int mainSum = 0;
    int sideSum = 0;

    for (int i = 0; i < n; i++) {
        mainSum += matrix[i][i];
        sideSum += matrix[i][n - i - 1];
    }

    printf("Сумма главной диагонали: %d\n", mainSum);
    printf("Сумма побочной диагонали: %d\n", sideSum);

    // ===== Проверка магического квадрата =====
    int isMagic = 1;

    // сумма первой строки
    int targetSum = 0;
    for (int j = 0; j < n; j++) {
        targetSum += matrix[0][j];
    }

    // проверка строк
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++) {
            sum += matrix[i][j];
        }
        if (sum != targetSum) {
            isMagic = 0;
        }
    }

    // проверка столбцов
    for (int j = 0; j < n; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += matrix[i][j];
        }
        if (sum != targetSum) {
            isMagic = 0;
        }
    }

    // диагонали
    if (mainSum != targetSum || sideSum != targetSum) {
        isMagic = 0;
    }

    // результат
    if (isMagic)
        printf("Матрица является магическим квадратом\n");
    else
        printf("Матрица НЕ является магическим квадратом\n");

    return 0;
}
