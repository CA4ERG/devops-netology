#include <stdlib.h>
#include <windows.h> //Кодировка русского языка для VSCode
#include <stdio.h>
#include <string.h>
int main(){
SetConsoleOutputCP(CP_UTF8); //Кодировка русского языка для VSCode
printf("1)Замена строчных\n");
printf("Введите строку(до 80 значений на английском)\n");
char str[81];
fgets(str,sizeof(str),stdin);
for(int i=0;i<strlen(str);++i)
    if(str[i]=='a'){
        str[i]='A';
    }

    else if(str[i]=='b'){
        str[i]='B';
    }
printf("===Вывод===\n");
for(int i=0;i<strlen(str);++i){
    printf("%c",str[i]);
    }

printf("2)Магический квадрат\n");
int p = 0;
printf("Введите значение порядка матрицы:\n");
scanf("%d", &p);

if(p<=0){printf("*Ошибка* Порядок должен быть больше нуля\n");
return 1;
}

int **mat = (int**)malloc(p * sizeof(int*));//Выделение памяти и построение матрицы
for(int i=0;i<p;++i)
    mat[i] = (int*)malloc(p * sizeof(int));

printf("Введите переменные(%d шт)\n",p*p);
for(int i=0;i<p;++i){
    for(int j=0;j<p;++j){
    scanf("%d",&mat[i][j]);
    }
}
printf("Матрица:\n");
    for(int i=0;i<p;++i){
        for(int j=0;j<p;++j){
            printf(" %d",mat[i][j]);
        }
    printf("\n");
    }
int sg = 0,sp = 0,sumsrav = 0,check=1;
for(int i=0; i<p; ++i){
    sumsrav += mat[0][i];
}

for(int i=0;i<p;++i){
    int sumstr = 0;
    sg += mat[i][i], sp += mat[i][p-1-i];
    for(int j=0;j<p;++j){
        sumstr += mat[i][j];
    }
    if(sumstr != sumsrav ){
        check = 0;
    }
}

if(sg!=sumsrav || sp!=sumsrav){ //Сравнение диагоналей с тестовой суммой
    check = 0;}

for(int j=0;j<p;++j){
    int sumstr = 0;
    for(int i=0;i<p;++i){
        sumstr += mat[i][j];
    }
    if(sumstr != sumsrav){
        check=0;
    }
}
for(int i = 0;i<p;++i)
    free(mat[i]);
free(mat);
if(check == 1){printf("Наша матрица - магический квадрат.\n");}
else{printf("Наша матрица - никакой не магический квадрат\n");}
return 0;
}
/* Для проверки приведём данную матрицу 4го порядка: 
16  2  3 13 
5  11 10  8
9   7  6 12
4  14 15  1
Г.диагональ: 16+11+6+1=34
П.диагональ: 13+10+7+4=34
Стр:1)16+2+3+13=34;2)5+11+10+8=34;3)9+7+6+12=34;4)4+14+15+1=34
Стол:1)16+5+9+4=34;2)2+11+7+14=34;3)3+10+6+15=34;4)13+8+12+1=34
*/