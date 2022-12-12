#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
using namespace std;


double funk(double x)
{

	double a = x * x * x - 3;

	return (a);
}


float PolovinDel(double (*funk)(double), bool* er, int* it, float a = 1, float b = 4, double e = 0.000001)
{
	int iter = 0;
	float sered;
	do
	{
		sered = (a + b) / 2;
		iter++;
		if (funk(b)*funk(sered) <= 0) a = sered;
		else if (funk(a)*funk(sered) <= 0) b = sered;
	} while (abs(a - b) > e && (a == sered || b == sered));
	*it = iter;
	if (a != sered && b != sered)
		*er = 0;
	else *er = 1;
	return sered;
}

void main()
{
	bool error = true;
	bool *er;
	er = &error;
	int K_iter = 0;
	int *it;
	it = &K_iter;

	float a = 1, b = 4;
	
	double x = PolovinDel(funk, er, it);
	if (error)
		cout << "X = " << x << setw(15) << "F(X) = " << funk(x) << setw(20) << "K_iter = " << K_iter << endl;
	else cout << "   ***   Error   ***   " << endl;
	cout << endl;

	system("pause");
}