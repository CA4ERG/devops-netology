#include <stdio.h>
#include <math.h>
#include <locale.h>
int main() {
	setlocale (LC_ALL, "RUSSIAN");
    double a, b, c;
    double D, x1, x2;
    a = 1.0;
    b = 3.0;
    c = 2.0;
    printf("Óðàâíåíèå: %.2f*x^2+%.2f*x+%.2f=0\n", a, b, c);
    D = pow(b, 2)-4*a*c;
    printf("Äèñêðèìèíàíò: D= %.2f\n", D);

    if (D>0) {
        x1=(-b+sqrt(D))/(2*a);
        x2=(-b-sqrt(D))/(2*a);
        printf("Äâà êîðíÿ:\n");
        printf("x1= %.4f\n",x1);
        printf("x2= %.4f",x2);
    }
    else if (D==0) {
        x1=-b/(2*a);
        printf("Êîðåíü: x1= %.4f\n",x1);
    }
    else {
        printf("Êîðíåé íåò");
    }
    return 0;
}

