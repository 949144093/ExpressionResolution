#include "FunCaculate.h"
#include<time.h>
#define _USE_MATH_DEFINES
#include <math.h>
int random(int a,int b) {
	srand((unsigned)time(NULL));
	int N = a + rand() % (b - a + 1);
	return N;
}

int max(int a, int b) {
	return (a > b ? a : b);
}

int min(int a, int b) {
	return (a > b ? b : a);
}

double sum(double a, double b) {
	return a + b;
}

double ift(bool a,double b,double c) {
	if ((bool)a)
	{
		return (double)b;
	}
	else
	{
		return (double)c;
	}
}

//方法名s1 参数数组s2
double FunCaculate::FuncCaculte(string s1, double* s2)
{
	if (s1 == "random()"||s1 == "RANDOM()") 
	{
		return random(s2[1],s2[0]);
	}
	else if (s1=="ift()"||s1=="IFT()")
	{
		return (double)ift((bool)s2[2], (double)s2[1], (double)s2[0]);
	}
	else if (s1=="ABS()"||s1=="abs()")
	{
		return abs(s2[0]);
	}
	else if (s1=="MAX()"||s1 == "max()")
	{
		return max(s2[1],s2[0]);
	}
	else if (s1 == "MIN()" || s1 == "min()")
	{
		return min(s2[1], s2[0]);
	}
	else if (s1 == "SUM()" || s1 == "sum()")
	{
		return sum(s2[1], s2[0]);
	}
	else if (s1 == "SIN()" || s1 == "sin()")
	{
		return sin(s2[0] * M_PI / 180);
	}
	else if (s1 == "COS()" || s1 == "cos()")
	{
		return cos(s2[0] * M_PI / 180);
	}
	else if (s1 == "TAN()" || s1 == "tan()")
	{
		return tan(s2[0] * M_PI / 180);
	}
	else if (s1 == "ASIN()" || s1 == "asin()")
	{
		return asin(s2[0]) * 180 / M_PI;
	}
	else if (s1 == "ACOS()" || s1 == "acos()")
	{
		return acos(s2[0]) * 180 / M_PI;
	}
	else if (s1 == "ATAN()" || s1 == "atan()")
	{
		return atan(s2[0]) * 180 / M_PI;
	}
	else if (s1 == "ATANT()" || s1 == "atant()")
	{
		return atan2(s2[1],s2[0]) * 180 / M_PI;
	}
	else if (s1 == "SQRT()" || s1 == "sqrt()")
	{
		return sqrt(s2[0]);
	}
	else if (s1=="POW()" || s1 == "pow()")
	{
		return pow(s2[1], s2[0]);
	}
	else if (s1 == "INT()" || s1 == "int()")
	{
		return int(s2[0]);
	}
	else if (s1 == "LOG()" || s1 == "log()")
	{
		return log(s2[0]);
	}
	else {
		return 0.0;
	}
}
