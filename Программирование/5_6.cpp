#include <iostream>
#include <iomanip>
#include <stdio.h>
using namespace std;

double e = 0.000001;

double funk(float x, float s, float t)
{
	/*s = 1 / s;
	double a = t + x * x * x;
	a = pow(a, s);

	return a;*/
	return 1;
}

double integral(double(*funk)(float, float, float), int* it, float a, float b, int n, float s, float t);
double toch_integral(double(*funk)(float, float, float), int* it, float a, float b, float s, float t);


void main()
{
	
	int K_iter = 0;
	int *it;
	it = &K_iter;

	float a = 0, b = 1;
	float s0 = 1.5, s_max =2.5, ds = 0.5;
	float t0 = 0, t_max = 4, dt = 1;

	cout << "S" <<  setw(15) << "T" << setw(15) << "Int" << setw(20) << "K_iter" << endl;
	for (float s = s0; s <= s_max; s += ds)
		for (float t = t0; t <= t_max; t += dt)
		{
			double x = toch_integral(funk, it, a, b, s, t);
			cout << s << setw(15) << t << setw(15) << x << setw(17) << K_iter << endl;
			K_iter = 0;
		}

	cout << endl;

	system("pause");
}

double toch_integral(double(*funk)(float, float, float), int* it, float a, float b, float s, float t)
{
	int n = 5;
	double integ2, integ1 = integral(funk, it, a, b, n, s, t);
	do
	{
		(*it)++;

		n *= 2;
		integ2 = integ1;
		integ1 = integral(funk, it, a, b, n, s, t);
	} while (abs(integ1 - integ2) > e);
	
	return (integ1);
}

double integral(double(*funk)(float, float, float), int* it, float a, float b, int n, float s, float t)
{
	double integ = 0;

	float h = (b - a) / n;
	float x = a;
	for (int i = 0; i < n; i++)
	{
		integ += funk(x + i * h, s, t);
		//		(*it)++;
	}
	integ *= h;
	return integ;
}
