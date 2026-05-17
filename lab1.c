#include <stdio.h>   // printf
#include <math.h>    // sqrt, pow

int main() {
    double a = 1, b = -5, c = 6;                 // коэффициенты
    double D = pow(b, 2) - 4 * a * c;            // дискриминант
    double x1, x2;                               // корни

    if (D > 0) {                                 // если 2 корня
        x1 = (-b + sqrt(D)) / (2 * a);           // первый корень
        x2 = (-b - sqrt(D)) / (2 * a);           // второй корень
        printf("x1 = %.2lf\nx2 = %.2lf", x1, x2); // вывод корней
    }
    else if (D == 0) {                           // если 1 корень
        x1 = -b / (2 * a);                       // вычисление корня
        printf("x = %.2lf", x1);                 // вывод корня
    }
    else                                         // если корней нет
        printf("Корней нет");                    // вывод сообщения

    return 0;                                    // конец программы
}

