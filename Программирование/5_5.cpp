#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
using namespace std;

const double PI = 3.14159265358979323846;

double funk(double x, double s)
{
	s = 1/s;
	double a = pow(x, s);
	double b = PI * x / 2;
	b = cos(b);
	b = b * b * 2;
	a = a - b;

	return (a);
}



float PolovinDel(float s, bool* er, int* it, float a, float b, double e)
{
	int iter = 0;
	float sered;
	do
	{
		sered = (a + b) / 2;
		iter++;
		if (funk(b, s)*funk(sered, s) <= 0) a = sered;
		else if (funk(a, s)*funk(sered, s) <= 0) b = sered;
	} while (abs(a - b) > e && (a==sered || b==sered));
	*it = iter;
	if (a != sered && b != sered) 
		*er = 0;
	else *er = 1; 
	return sered;
}

float(*funk_1)(float s, bool* er, int* it, float a, float b, double e) = &PolovinDel;

void funk_o(float (*funk_ukaz)(float s, bool* er, int* it, float a, float b, double e))
{

	bool error = true;
	bool *er;
	er = &error;
	int K_iter = 0;
	int *it;
	it = &K_iter;

	float a = 0, b = 1;
	double e = 0.000001;

	float s = 0.5, smax = 2, ds = 0.5;
	for (s; s <= smax; s += ds)
	{
		double x = funk_ukaz(s, er, it, a, b, e);
		if (error)
			cout << "s = " << s << setw(10) << "X = " << x << setw(15) << "F(X) = " << funk(x, s) << setw(20) << "K_iter = " << K_iter << endl;
		else cout << "   ***   Error   ***   " << endl;
		error = true;
	}
	
}

void main()
{
	int M = 1;
	switch (M)
	{
	case (1): funk_o(funk_1); break;
	}
	
	cout << endl;

	system("pause");
}