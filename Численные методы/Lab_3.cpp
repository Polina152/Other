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
double f_yavn(double* u, double t, int n)
{
	if (n == 0)
	{
//		return u[1] - (2 * u[0] + 0.25*u[1]) * u[0];

		double a = sin(t) / t;
		if (abs(t) < de)
			a = 0;
		return a - u[0] * u[1];
	}
	else if (n == 1)
	{
//		return exp(u[0]) - (u[0] + 2 * u[1]) * u[0];

		return 3.125*t / (1 + t * t) - u[1] * u[1];
	}
	return 0;
}
double f1(double *uk1, double *uk, double t, double Tau)
{
	return uk1[0] - uk[0] - Tau * (f_yavn(uk1, t, 0));
}
double f2(double *uk1, double *uk, double t, double Tau)
{
	return uk1[1] - uk[1] - Tau * (f_yavn(uk1, t, 1));
}
double Diff(double f(double*, double*, double, double), double *uk1, double *uk, double t, double Tau, int n)
{
	double dx = 1e-9;
	double* D = new double[2];
	for (int i = 0; i < 2; i++)
	{
		if (i == n - 1)
		{
			D[i] = uk1[i] + dx;
			i++;
		}
		D[i] = uk1[i];
	}

	double F = f(uk1, uk, t, Tau);
	double dF = f(D, uk, t, Tau);

	return (dF - F) / dx;
}
double Newton(double *yk1, double *yk, double tk, double Tau, int n)
{
	double **F = new double*[n];
	for (int i = 0; i < n; i++)
		F[i] = new double[n + 1];
	double *An = new double[n];
	double e = 1e-9, b1 = 0, b2 = 0;

	int itr = 1;

	do {
		F[0][0] = Diff(f1, yk1, yk, tk, Tau, 1);
		F[0][1] = Diff(f1, yk1, yk, tk, Tau, 2);
		F[0][2] = -f1(yk1, yk, tk, Tau);
		F[1][0] = Diff(f2, yk1, yk, tk, Tau, 1);
		F[1][1] = Diff(f2, yk1, yk, tk, Tau, 2);
		F[1][2] = -f2(yk1, yk, tk, Tau);
		
		if (gauss(F, n))
		{
			return 0;
		}
		Re(F, An, n);

		yk1[0] += An[0];
		yk1[1] += An[1];

		if (abs(f1(yk1, yk, tk, Tau)) > abs(f2(yk1, yk, tk, Tau)))
			b1 = abs(f1(yk1, yk, tk, Tau));
		else
			b1 = abs(f2(yk1, yk, tk, Tau));

		for (int i = 0; i < n; i++)							
		{
			if (abs(An[i]) < 1)
				b2 = abs(An[i]);
			else if (abs(An[i]) >= 1)
				b2 = abs(An[i] / yk1[i]);
		}

		itr++;
	} while ((b1 > e || b2 > e) && (itr < itr_max));

	return 1;
}
void Eiler_Yav(double* u, int n)
{
	double Tau = 0;
	double Eps = 0.001, T = 1, TauMax = 0.1;
	double tk = 0;
	double* yk = new double[n];

	for (int i = 0; i < n; i++)
		yk[i] = u[i];

	cout << "    t" << setw(15)  << "    u1" << setw(14) << "    u2\n";

	int kol = 0;
	do {

		double *tmp = new double[n];
		for (int i = 0; i < n; i++)
			tmp[i] = f_yavn(yk, tk, i);

		if (Eps / (abs(tmp[0]) + Eps / TauMax) > Eps / (abs(tmp[1]) + Eps / TauMax))
			Tau = Eps / (abs(tmp[1]) + Eps / TauMax);
		else
			Tau = Eps / (abs(tmp[0]) + Eps / TauMax);

		for (int i = 0; i < n; i++)
			yk[i] += Tau * tmp[i];
		tk += Tau;

		cout << tk << setw(15);
		for (int i = 0; i < n; i++)
		{
			cout << setw(15) << yk[i];
		}
		cout << endl;

		kol++;
	} while (tk < T && kol < 10000);

	cout << endl << "Number of iterations is " << kol << endl;
}
void Eiler_Neyav(double* u, int n)
{
	double Tau, Tau_pred, Tau_sled;
	double Eps = 0.001, T = 1, TauMax = 0.1, TauMin = 0.0001;
	double tk = 0, tk_sled = 0;
	double* ek = new double[n];
	double* yk = new double[n];                
	double* yk_pred = new double[n];              
	double* yk_sled = new double[n];               
	Tau = Tau_pred = TauMin;

	for (int i = 0; i < n; i++) 
		yk[i] = yk_pred[i] = yk_sled[i] = u[i];

	cout << "     t" << setw(15);
	for (int i = 0; i < n; i++)
	{
		cout << "     u" << i + 1 << setw(14);
	}
	cout << endl;

	int kol = 1;
	while (tk <= T)
	{
		tk_sled = tk + Tau;

		Newton(yk_sled, yk, tk, Tau, n); 

		for (int k = 0; k < n; k++)
			ek[k] = -(Tau*Tau)*((yk_sled[k] - yk[k]) / Tau - (yk[k] - yk_pred[k]) / Tau_pred) / (Tau + Tau_pred);
		bool fl = false;
		for (int k = 0; k < n; k++)
			if (abs(ek[k]) > Eps && !fl)
			{
				Tau /= 2;
				tk_sled = tk;
				for (int j = 0; j < n; j++)
					yk_sled[j] = yk[j];
				fl = true;
			}
		if (fl) continue;


		double *tmp = new double[n];
		for (int i = 0; i < n; i++)
		{
			if (abs(ek[i]) > Eps)
				tmp[i] = Tau / 2;
			if (abs(ek[i]) > Eps / 4  && abs(ek[i]) <= Eps)
				tmp[i] = Tau;
			if (abs(ek[i]) <= Eps / 4)
				tmp[i] = 2 * Tau;
		}

		for (int i = 0; i < n - 1; i++)
		{
			if (tmp[i] > tmp[i + 1])
				Tau_sled = tmp[i + 1];
			else Tau_sled = tmp[i];
		}

		if (Tau_sled > TauMax)
			Tau_sled = TauMax;

		for (int i = 0; i < n; i++)
		{
			if (i == 0)
				cout << tk << setw(15);
			cout << setw(15) << yk[i];
			if (i == n - 1)
				cout << endl;
		}

		for (int i = 0; i < n; i++)
		{
			yk_pred[i] = yk[i];
			yk[i] = yk_sled[i];
		}
		Tau_pred = Tau;
		Tau = Tau_sled;
		tk = tk_sled;

		kol++;
	}

	cout << endl << "Number of iterations is " << kol << endl;
}

void main()
{
	int n = 2;
	double* y = new double[n];

	cout << "Start value of U[1] = 1.0   U[2] = 0.0 " << endl;
	y[0] = 1.0;
	y[1] = -0.0;

	cout << endl << "Yavni Method\n";
//	Eiler_Yav(y, n);

//	cout << "Neyavni Method\n";
	Eiler_Neyav(y, n);
	system("pause");
}