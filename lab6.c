#include <stdio.h>   // стандартный ввод-вывод (файлы, printf, scanf)
#include <locale.h> // Ћокализаци€ €зыка (наример на –усский)
int main() // главна€ функци€ программы
{
	setlocale (LC_ALL, "RUSSIAN");
    FILE *in, *out;   // указатели на файлы (входной и выходной)

    char surname[30]; // фамили€
    char name[30];    // им€
    char patronymic[30]; // отчество
    int year;         // год рождени€

    in = fopen("input.txt", "r"); // открываем файл дл€ чтени€

    if (in == NULL) // проверка: открылс€ ли файл
    {
        printf("ќшибка открыти€ файла input.txt\n");
        return 1; // завершение программы с ошибкой
    }

    out = fopen("output.txt", "w"); // открываем файл дл€ записи

    if (out == NULL) // проверка файла на запись
    {
        printf("ќшибка создани€ output.txt\n");
        return 1;
    }

    while (fscanf(in, "%s %s %s %d", // читаем данные из файла пока есть строки
                  surname, name, patronymic, &year) == 4)
    {
        if (year > 1980) // провер€ем условие: родилс€ после 1980 года
        {
            fprintf(out, "%s %s %s %d\n", // записываем в новый файл
                    surname, name, patronymic, year);
        }
    }

    fclose(in); // закрываем файлы (ќЅя«ј“≈Ћ№Ќќ)
    fclose(out);

    printf("‘айл успешно обработан!\n"); // сообщение об успехе

    return 0; // конец программы
}
