#include <stdio.h>
#include <stdlib.h>
#include <math.h>


perimetrik (int a, int b, int c) { // функци€ периметра треугольника

		return a + b + c;
	} 
double ploshadik (int a, int b, int c) { //функци€ площади треугольника а - основание треугольника (нижн€€ сторона) h - высота треугольника
		
		double poluperimetr = (a + b + c)/2;
		
		
		return sqrt(poluperimetr*(poluperimetr - a)*(poluperimetr - b)*(poluperimetr - c)); //‘ормула √ерона дл€ нахождени€ площади по трЄм сторонам
}
