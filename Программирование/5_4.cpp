#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
using namespace std;

const bool  bo = 1;
const int n = 1000;

void zapoln(int A[], int razmer, bool random)
{
	srand(time(0));
	if (random)
		for (int i = 0; i < razmer; i++)
		{
			A[i] = rand() % 10;
			cout << A[i] << ", ";
		}
	else
	{
		cout << "Enter numbers: ";
		for (int i = 0; i < razmer; i++)
			cin >> A[i];
	}
}

int& find_min(int Mas[], int razmer)
{
	bool flag = false;
	int min_povtor = 0, min = 0;
	for (int i = 0; i < razmer - 1; i++)
	{
		for (int j = i+1; j < razmer; j++)
		{
			if (Mas[i] == Mas[j]) 
			{ 
				if (flag == false) min_povtor = i;
				flag = true; 
				if (Mas[min_povtor] > Mas[i]) min_povtor = i;
			}
			else if (Mas[j] < Mas[min]) min = j;
		}
	}
	if (flag) return(Mas[min_povtor]);
	else return(Mas[min]);

}

void main()
{
	int Mas[n];
	int razm;
	cout << "Enter a number of numbers:  ";
	cin >> razm;
	zapoln(Mas, razm, bo);
	find_min(Mas, razm) = 100;
	cout << endl;
	for (int i = 0; i < razm; i++)
	{
		cout << Mas[i] << ", ";
	}

	system("pause");
}