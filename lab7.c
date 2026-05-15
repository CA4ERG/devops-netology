#include <stdio.h>      // библиотека ввода и вывода 
#include <stdlib.h>     // библиотека дл€ malloc 
#include <locale.h>     // локализаци€

int main() {
	setlocale (LC_ALL, "RUSSIAN");
    int n;                          // число n 
    int p;                          // текущее простое число 
    int i;                          // счетчик 

    printf("¬ведите n: ");
    scanf("%d", &n);                // ввод числа 

    // создание битового массива 
    char *prime = (char*)malloc((n + 1) * sizeof(char));

    // все числа считаем простыми 
    for(i = 0; i <= n; i++)
    {
        prime[i] = 1;
    }

    // 0 и 1 не €вл€ютс€ простыми 
    prime[0] = 0;
    prime[1] = 0;

    // алгоритм Ёратосфена 
    for(p = 2; p * p <= n; p++)
    {
        // если число простое 
        if(prime[p] == 1)
        {
            // вычеркиваем кратные начина€ с p? 
            for(i = p * p; i <= n; i += p)
            {
                prime[i] = 0;
            }
        }
    }

    printf("\nѕростые числа:\n");

    // вывод простых чисел 
    for(i = 2; i <= n; i++)
    {
        if(prime[i] == 1)
        {
            printf("%d ", i);
        }
    }

    free(prime);                    // освобождение пам€ти 
    return 0;                       // завершение программы
}
