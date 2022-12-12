#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>
const double NXB = 15;
const double NX = NXB * 3 + 1;
const double NYB = 12;
const double NY = NYB * 3 + 1;
const double REP = 3000;
const double EPSL = 1.e-5;
const double LL = 1.7f;
const double TEM1 = 5.0f;
const double TEM2 = 15.0f;
const double HX = 0.2f;
const double HY = 0.3f;

using namespace std;

void maxpvr(double *t1, double *del, double *maxdel)
{
	double d = fabs(*del) / fabs(*t1);
	if (d > *maxdel) *maxdel = d;
}

int main(int argc, char **argv)
{
	ofstream foutT("D:/”чЄба/„ислаки лаб 6/dT.dat", ios_base::out | ios_base::trunc | ios_base::binary);
	int i1, i2, j1, j2, i3, j3, rp, i, j, k = 0;
	double T1 = TEM1, T2 = TEM2, h = HX, r = HY, tx, t0, t1, del, maxdel = 0.0f;
	double** T = new double*[NY];
	for (int i0 = 0; i0 < NY; i0++)
		T[i0] = new double[NX];
	double lam = LL;
	double eps = EPSL;
	int prz = 1;
	int nT = 0;
	double alf_1 = -h / r;
	double alf_2 = -r / h;
	double alf_3 = alf_2 * 0.5f;
	double alf_4 = alf_1 * 0.5f;
	double gam_1 = -2.f * (alf_1 + alf_2);
	double gam_2 = -1.5f * (alf_1 + alf_2);
	double gam_3 = -(alf_1 + alf_2);
	double gam_4 = -(alf_3 + alf_4);
	i1 = NXB;  i2 = i1 + NXB; i3 = i2 + NXB;
	j1 = NYB; j2 = j1 + NYB; j3 = j2 + NYB;
	rp = REP;
	for (j = 0; j <= j3; j++)
		for (i = 0; i <= i3; i++)
			T[j][i] = 0.0f;

	for (j = 0; j <= j1; j++) T[j][0] = T1;
	for (i = 0; i <= i1; i++) T[0][i] = T1;
	for (j = j2; j <= j3; j++) T[j][i3] = T2;
	for (i = i2; i <= i3; i++) T[j3][i] = T2;

	while (k < rp && prz == 1) {
		k++;
		for (i = 0; i <= i3; i++) {
			for (j = 0; j <= j3; j++) {
				t0 = T[j][i];
				if (i == 0 && j > j1 && j < j3) { //CD
					tx = -(alf_4*(T[j - 1][i] + T[j + 1][i]) + alf_2 * T[j][i + 1]) / gam_3;
					del = lam * (tx - t0); t1 = t0 + del; T[j][i] = t1;
					maxpvr(&t1, &del, &maxdel);
				}
				else if (j == j3 && i > 0 && i < i2) { //DE
					tx = -(alf_3*(T[j][i - 1] + T[j][i + 1]) + alf_1 * T[j - 1][i]) / gam_3;
					del = lam * (tx - t0); t1 = t0 + del; T[j][i] = t1;
					maxpvr(&t1, &del, &maxdel);
				}
				else if (i == i3 && j > 0 && j < j2) { //GH
					tx = -(alf_4*(T[j - 1][i] + T[j + 1][i]) + alf_2 * T[j][i - 1]) / gam_3;
					del = lam * (tx - t0); t1 = t0 + del; T[j][i] = t1;
					maxpvr(&t1, &del, &maxdel);
				}
				else if (j == 0 && i > i2 && i < i3) { //HI
					tx = -(alf_3*(T[j][i - 1] + T[j][i + 1]) + alf_1 * T[j + 1][i]) / gam_3;
					del = lam * (tx - t0); t1 = t0 + del; T[j][i] = t1;
					maxpvr(&t1, &del, &maxdel);
				}
				else if (i == i2 && j > 0 && j < j1) { //IJ
					tx = -(alf_4*(T[j - 1][i] + T[j + 1][i]) + alf_2 * T[j][i + 1]) / gam_3;
					del = lam * (tx - t0); t1 = t0 + del; T[j][i] = t1;
					maxpvr(&t1, &del, &maxdel);
				}
				else if (j == j1 && i > i1 && i < i2) { //JK
					tx = -(alf_3*(T[j][i - 1] + T[j][i + 1]) + alf_1 * T[j + 1][i]) / gam_3;
					del = lam * (tx - t0); t1 = t0 + del; T[j][i] = t1;
					maxpvr(&t1, &del, &maxdel);
				}
				else if (i == i1 && j > 0 && j < j1) { //KA
					tx = -(alf_4*(T[j - 1][i] + T[j + 1][i]) + alf_2 * T[j][i - 1]) / gam_3;
					del = lam * (tx - t0); t1 = t0 + del; T[j][i] = t1;
					maxpvr(&t1, &del, &maxdel);
				}
				else if (i == 0 && j == j3) { //D
					tx = -(alf_3*T[j][i + 1] + alf_4 * T[j - 1][i]) / gam_4;
					del = lam * (tx - t0); t1 = t0 + del; T[j][i] = t1;
					maxpvr(&t1, &del, &maxdel);
				}
				else if (i == i3 && j == 0) { //H
					tx = -(alf_3*T[j][i - 1] + alf_4 * T[j + 1][i]) / gam_4;
					del = lam * (tx - t0); t1 = t0 + del; T[j][i] = t1;
					maxpvr(&t1, &del, &maxdel);
				}
				else if (i == i2 && j == 0) { //I
					tx = -(alf_3*T[j][i + 1] + alf_4 * T[j + 1][i]) / gam_4;
					del = lam * (tx - t0); t1 = t0 + del; T[j][i] = t1;
					maxpvr(&t1, &del, &maxdel);
				}
				else if (i == i2 && j == j1) {//J
					tx = -(alf_4*T[j - 1][i] + alf_3 * T[j][i + 1] + alf_2 * T[j][i - 1] + alf_1 * T[j + 1][i]) / gam_2;
					del = lam * (tx - t0); t1 = t0 + del; T[j][i] = t1;
					maxpvr(&t1, &del, &maxdel);
				}
				else if (i == i1 && j == j1) {//K
					tx = -(alf_4*T[j - 1][i] + alf_3 * T[j][i - 1] + alf_2 * T[j][i + 1] + alf_1 * T[j + 1][i]) / gam_2;
					del = lam * (tx - t0); t1 = t0 + del; T[j][i] = t1;
					maxpvr(&t1, &del, &maxdel);
				}
				else if (i > 0 && i < i1 && j > 0 && j < j3) { //1
					tx = -(alf_1*(T[j - 1][i] + T[j + 1][i]) + alf_2 * (T[j][i - 1] + T[j][i + 1])) / gam_1;
					del = lam * (tx - t0); t1 = t0 + del; T[j][i] = t1;
					maxpvr(&t1, &del, &maxdel);
				}
				else if (i >= i1 && i <= i2 && j > j1 && j < j3) { //2
					tx = -(alf_1*(T[j - 1][i] + T[j + 1][i]) + alf_2 * (T[j][i - 1] + T[j][i + 1])) / gam_1;
					del = lam * (tx - t0); t1 = t0 + del; T[j][i] = t1;
					maxpvr(&t1, &del, &maxdel);
				}
				else if (i > i2 && i < i3 && j > 0 && j < j3) { //3
					tx = -(alf_1*(T[j - 1][i] + T[j + 1][i]) + alf_2 * (T[j][i - 1] + T[j][i + 1])) / gam_1;
					del = lam * (tx - t0); t1 = t0 + del; T[j][i] = t1;
					maxpvr(&t1, &del, &maxdel);
				}
			}
		}
		nT++; double w = maxdel;
		foutT.write((char*)&w, sizeof w);
		//		cout << w << " ";
		if (maxdel < eps) prz = 0; maxdel = 0.0f;
	}

	foutT.close();
	ofstream fouT("D:/”чЄба/„ислаки лаб 6/nT.dat", ios_base::out | ios_base::trunc | ios_base::binary);
	fouT.write((char*)&nT, sizeof nT);
	cout << "nT = " << nT << endl;
	fouT.close();
	ofstream fout("D:/”чЄба/„ислаки лаб 6/Pole.dat", ios_base::out | ios_base::trunc | ios_base::binary);
	for (j = 0; j < NY; j++) {
		for (i = 0; i < NX; i++) {
			double w = T[j][i];
			fout.write((char*)&w, sizeof w);
		}
	}
	fout.close();
	int n_x = NX; int n_y = NY;
	ofstream fou("D:/”чЄба/„ислаки лаб 6/Param.dat", ios_base::out | ios_base::trunc | ios_base::binary);
	fou.write((char*)&n_x, sizeof n_x);
	fou.write((char*)&n_y, sizeof n_y);
	cout << "NX = " << n_x << endl;
	cout << "NY = " << n_y << endl;
	fou.close();
}