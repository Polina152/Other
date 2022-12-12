#include <iostream>
#include <iomanip>

using namespace std;

const double de = 1e-9;
const int itr_max = 100;

bool gauss(double **u, int n)
{
	for (int k = 0; k < n; k++)
	{
		int max = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(u[i][k]) > abs(u[max][k])) max = i;
		}

		if (abs(u[max][k]) <= 1e-10) return 1;

		swap(u[max], u[k]);

		for (int j = k + 1; j < n + 1; j++)
			u[k][j] = u[k][j] / u[k][k];
		u[k][k] = 1;

		for (int i = k + 1; i < n; i++)
		{
			for (int j = k + 1; j < n + 1; j++)
			{
				u[i][j] -= u[i][k] * u[k][j];
			}
			u[i][k] = 0;
		}

	}

	return 0;
}
bool Re(double** u, double* x, int n)
{
	for (int k = n - 1; k >= 0; k--)
	{
		x[k] = u[k][n];
		if (abs(x[k]) <= 0.000000000001) x[k] = 0;
		for (int i = k - 1; i >= 0; i--)
		{
			u[i][n] -= x[k] * u[i][k];
		}
	}
	return 1;
}
double f1(double x1, double x2) 
{
	//return log(1 + (x1 + x2) / 5) - sin(x2 / 3) - x1 + 1.1;
	return x1 - x2 - 6 * log10(x1) - 1;
	//return x1*x1*x2*x2 - 3 * x1*x1 - 6 * x2*x2*x2 + 8;
	//return sin(x1) - x2 - 1.32;

}
double f2(double x1, double x2) 
{
	//return cos(x1*x2 / 6) - x2 + 0.5;
	return x1 - 3 * x2 - 6 * log10(x2) - 2;
	//return x1*x1*x1*x1 - 9 * x2 + 2;
	//return cos(x2) - x1 + 0.85;
}

double Diff(double (*f)(double, double), double x1, double x2, int x)
{
	if (x == 1)
		return (f(x1 + de, x2) - f(x1, x2)) / de;
	else
		return (f(x1, x2 + de) - f(x1, x2)) / de;
}

double TochDiff(double x1, double x2, int var)
{
	switch (var)
	{
	case 1: return 1 - 6 / x1 / log(10);
	case 2: return -1;
	case 3: return 1;
	case 4: return -3 - 6 / x2 / log(10);
	}
}

bool Newton(double *Answer, int n)
{
	double **J = new double*[n];
	for (int i = 0; i < n; i++)
		J[i] = new double[n + 1];

	double b1 = 0, b2 = 0;

	cout << endl << "k" << setw(15) << "   b1   " << setw(15) << "   b2   " << endl << endl;
	int itr = 0;

	do
	{
	/*	J[1][0] = Diff(f2, Answer[0], Answer[1], 1);
		J[1][1] = Diff(f2, Answer[0], Answer[1], 2);*/
		J[1][0] = TochDiff(Answer[0], Answer[1], 3);
		J[1][1] = TochDiff(Answer[0], Answer[1], 4);
		J[1][2] = -f2(Answer[0], Answer[1]);
		/*J[0][0] = Diff(f1, Answer[0], Answer[1], 1);
		J[0][1] = Diff(f1, Answer[0], Answer[1], 2);*/
		J[0][0] = TochDiff(Answer[0], Answer[1], 1);
		J[0][1] = TochDiff(Answer[0], Answer[1], 2);
		J[0][2] = -f1(Answer[0], Answer[1]);

		double *An = new double[n];	
		if (gauss(J, n))
			return 0;
		Re(J, An, n);

		Answer[0] += An[0];
		Answer[1] += An[1];

		if (abs(f1(Answer[0], Answer[1])) > abs(f2(Answer[0], Answer[1])))
			b1 = abs(f1(Answer[0], Answer[1]));
		else
			b1 = abs(f2(Answer[0], Answer[1]));

		for (int i = 0; i < n; i++)	
		{
			if (abs(An[i]) < 1)
				b2 = abs(An[i]);
			else if (abs(An[i]) >= 1)
				b2 = abs(An[i] / Answer[i]);
		}

		cout << itr + 1 << setw(15) << b1 << setw(15) << b2 << endl;

		itr++;
		if (itr == itr_max) 
			return 0;
	} while (b1 > de || b2 > de);

	return 1;
}

void main()
{
	const int n = 2;
	double *Answer = new double[n];
	Answer[0] = 0.5; Answer[1] = 0.2;

	if (Newton(Answer, n))
	{
		cout << "\nAnswer: ";
		for (int i = 0; i < n; i++)
			cout << Answer[i] << "; ";
		cout << "\n\n";
	}
	else
		cout << "\n\n   ***Error***\n\n";
	system("pause");
}