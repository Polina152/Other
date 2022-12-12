#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>
const double NXB = 15;
const double NYB = 12;
const double NX = NXB * 3 + 1;
const double NY = NYB * 3 + 1;
const double NYK2 = NYB * 2;
const double REP = 10000;
const double DEL = 100;
const double AMAT = 1.1;
const double TEM1 = 5.0;
const double TEM2 = 15.0;
const double HX = 0.2;
const double HY = 0.3;

using namespace std;

int main(int argc, char **argv)
{
	int i, j, k;
	int idt = 0;
	int ndt = 0;
	double T1 = TEM1, T2 = TEM2, h = HX, r = HY, a = AMAT, t0;
	double** T = new double*[NY];
	double** TT = new double*[NY];
	for (int i = 0; i < NY; i++)
	{
		T[i] = new double[NX];
		TT[i] = new double[NX];
	}
	double rr = r < h ? r : h;
	double tau = 0.25f*rr*rr / a;
	double alf_1 = -h / r;
	double alf_2 = -r / h;
	double alf_3 = 0.5f * alf_2;
	double alf_4 = 0.5f * alf_1;
	double bet_1 = a*tau / (h*r);
	double bet_2 = 2.0f*bet_1;
	double bet_3 = 4.0f*bet_1;
	double bet_4 = bet_3 / 3;
	double gam_1 = -2.f*(alf_1 + alf_2);
	double gam_2 = -1.5f*(alf_1 + alf_2);
	double gam_3 = -(alf_1 + alf_2);
	double gam_4 = -(alf_3 + alf_4);

	int i1 = NXB;
	int i2 = i1*2;
	int i3 = i1*3;
	int j1 = NYB;
	int j2 = j1*2;
	int j3 = j1*3;

	char filename[128];
	for (j = 0; j<NY; j++) {
		for (i = 0; i<NX; i++) {
			T[j][i] = 0.0;
			TT[j][i] = 0.0;
		}
	}
	for (j = 0; j <= j1; j++)
	{
		T[j][0] = T1; TT[j][0] = T1; //AE
	}
	for (i = 0; i <= i1; i++)
	{
		T[0][i] = T1; TT[0][i] = T1; //AE
	}
	for (j = j2; j<=j3; j++)
	{
		T[j][i3] = T2; TT[j][i3] = T2; //CF
	}
	for (i = i2; i <= i3; i++)
	{
		T[j3][i] = T2; TT[j3][i] = T2; //CF
	}

	ofstream fout("D:/”чЄба/„ислаки лаб 7/T1.dat", ios_base::out | ios_base::trunc | ios_base::binary);
	for (j = 0; j < NY; j++) {
		for (i = 0; i < NX; i++) {
			double w = T[j][i];
			fout.write((char*)&w, sizeof w);
		}
	}
	fout.close();
	for (k = 0; k<REP; k++) {
		for (j = 0; j<NY; j++) {
			for (i = 0; i<NX; i++) {
				t0 = T[j][i];
				if (i == 0 && j > j1 && j < j3) { //CD
					TT[j][i] = t0 - bet_2*(alf_4*(T[j - 1][i] + T[j + 1][i]) + alf_2*T[j][i + 1] + gam_3*t0);//6
				}
				else if (j == j3 && i > 0 && i < i2) { //DE
					TT[j][i] = t0 - bet_2*(alf_3*(T[j][i - 1] + T[j][i + 1]) + alf_1*T[j - 1][i] + gam_3*t0);//8
				}
				else if (i == i3 && j > 0 && j < j2) { //GH
					TT[j][i] = t0 - bet_2*(alf_4*(T[j - 1][i] + T[j + 1][i]) + alf_2*T[j][i - 1] + gam_3*t0);//7
				}
				else if (j == 0 && i > i2 && i < i3) { //HI
					TT[j][i] = t0 - bet_2*(alf_3*(T[j][i - 1] + T[j][i + 1]) + alf_1*T[j + 1][i] + gam_3*t0); //9
				}
				else if (i == i2 && j > 0 && j < j1) { //IJ
					TT[j][i] = t0 - bet_2*(alf_4*(T[j - 1][i] + T[j + 1][i]) + alf_2*T[j][i + 1] + gam_3*t0);//6
				}
				else if (j == j1 && i > i1 && i < i2) { //JK
					TT[j][i] = t0 - bet_2*(alf_3*(T[j][i - 1] + T[j][i + 1]) + alf_1*T[j + 1][i] + gam_3*t0); //9
				}
				else if (i == i1 && j > 0 && j < j1) { //KA
					TT[j][i] = t0 - bet_2*(alf_4*(T[j - 1][i] + T[j + 1][i]) + alf_2*T[j][i - 1] + gam_3*t0);//7
				}
				else if (i == 0 && j == j3) { //D
					TT[j][i] = t0 - bet_3*(alf_3*T[j][i + 1] + alf_4*T[j - 1][i] + gam_4*t0);//10
				}
				else if (i == i3 && j == 0) { //H
					TT[j][i] = t0 - bet_3*(alf_3*T[j][i - 1] + alf_4*T[j + 1][i] + gam_4*t0);//13
				}
				else if (i == i2 && j == 0) { //I
					TT[j][i] = t0 - bet_3*(alf_3*T[j][i + 1] + alf_4*T[j + 1][i] + gam_4*t0);//12
				}
				else if (i == i2 && j == j1) {//J
					TT[j][i] = t0 - bet_4*(alf_4*T[j - 1][i] + alf_3*T[j][i - 1] + alf_2*T[j][i+1] + alf_1*T[j + 1][i] + gam_2*t0);//4
				}
				else if (i == i1 && j == j1) {//K
					TT[j][i] = t0 - bet_4*(alf_4*T[j - 1][i] + alf_2*T[j][i - 1] + alf_3*T[j][i+1] + alf_1*T[j + 1][i] + gam_2*t0);//5
				}
				else if (i > 0 && i < i1 && j > 0 && j < j3) { //1
					TT[j][i] = t0 - bet_1*(alf_1*(T[j][i - 1] + T[j][i + 1]) + alf_2*(T[j - 1][i] + T[j + 1][i]) + gam_1*t0);//1
				}
				else if(i >= i1 && i <= i2 && j > j1 && j < j3) { //2
					TT[j][i] = t0 - bet_1*(alf_1*(T[j][i - 1] + T[j][i + 1]) + alf_2*(T[j - 1][i] + T[j + 1][i]) + gam_1*t0);//1
				}
				else if (i > i2 && i < i3 && j > 0 && j < j3) { //3
					TT[j][i] = t0 - bet_1*(alf_1*(T[j][i - 1] + T[j][i + 1]) + alf_2*(T[j - 1][i] + T[j + 1][i]) + gam_1*t0);//1
				}
			}
		}
		for (j = 0; j < NY; j++) {
			for (i = 0; i < NX; i++) {
				T[j][i] = TT[j][i];
			}
		}
		idt++;
		if (idt == DEL) {
			idt = 0; ndt++;
			sprintf_s(filename, sizeof(filename), "D:/”чЄба/„ислаки лаб 7/T%d.dat", ndt + 1);
			ofstream fout(filename, ios_base::out | ios_base::trunc | ios_base::binary);
			for (j = 0; j < NY; j++) {
				for (i = 0; i < NX; i++) {
					double w = T[j][i];
					fout.write((char*)&w, sizeof w);
				}
			}
			fout.close();
		}
	}
	int n_x = NX; int n_y = NY; int n_k = ndt;
	ofstream fou("D:/”чЄба/„ислаки лаб 7/Param.dat", ios_base::out | ios_base::trunc | ios_base::binary);
	fou.write((char*)&n_x, sizeof n_x);
	fou.write((char*)&n_y, sizeof n_y);
	fou.write((char*)&n_k, sizeof n_y);
	fou.close();
}
