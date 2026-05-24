#FFFFFF#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int secret_number, guess, attempts = 0;
    char answer;
    
    srand(time(NULL));
    
    printf("====================================\n");
    printf("     Добро пожаловать в игру!\n");
    printf("     УГАДАЙ ЧИСЛО (1-100)\n");
    printf("====================================\n\n");
    
    do {
        secret_number = rand() % 100 + 1;
        attempts = 0;
        
        printf("Я загадал число от 1 до 100.\n");
        printf("Попробуй его угадать!\n\n");
        
        while (1) {
            printf("Введи свой вариант: ");
            scanf("%d", &guess);
            attempts++;
            
            if (guess < 1 || guess > 100) {
                printf("Пожалуйста, введи число от 1 до 100!\n\n");
                continue;
            }
            
            if (guess < secret_number) {
                printf("Число БОЛЬШЕ, чем %d\n\n", guess);
            } else if (guess > secret_number) {
                printf("Число МЕНЬШЕ, чем %d\n\n", guess);
            } else {
                printf("\nВЫ УГАДАЛИ! Число: %d\n", secret_number);
                printf("Попыток: %d\n\n", attempts);
                
                if (attempts <= 5) {
                    printf("Отличный результат!\n");
                } else if (attempts <= 10) {
                    printf("Хороший результат!\n");
                } else {
                    printf("Продолжай тренироваться!\n");
                }
                break;
            }
        }
        
        printf("\nХочешь сыграть еще? (y/n): ");
        scanf(" %c", &answer);
        printf("\n");
        
    } while (answer == 'y' || answer == 'Y');
    
    printf("Спасибо за игру! До встречи!\n");
    return 0;
}

