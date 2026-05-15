#include <stdio.h>
#include "triangle.h"
#include <locale.h>

int main() {
	setlocale (LC_ALL, "RUSSIAN");
    double a, b, c;

    printf("Введите стороны треугольника: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    // проверка существования треугольника
    if (a + b > c && a + c > b && b + c > a) {
        printf("Периметр: %.2lf\n", perimeter(a, b, c));
        printf("Площадь: %.2lf\n", area(a, b, c));
    } else {
        printf("Треугольник не существует!\n");
    }

    return 0;
}
