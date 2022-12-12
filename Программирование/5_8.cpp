#include <iostream>
#include <iomanip>
#include "Zapolnenie_8.h"
#include "Sort_8.h"
using namespace std;

template <typename T>
void vyvod(T*mas, int r)
{
	for (int i = 0; i < r; i++) cout << mas[i] << ' ';
	cout << endl;
}
void vyvod(char**mas, int r)
{
	for (int i = 0; i < r; i++) 
		for (int j = 0; j < r; j++)
		{
			cout << mas[i][j];
		}
	cout << endl;
}


void main()
{
	const int r = 10;	
	const int s = 2;				

	int prisv = 0; int sravn = 0;

	int a[r];
	zapoln(a, r, s); int a2[r];


	vyvod(a, r);
	sort(a, r);
	cout << endl;
	vyvod(a, r); 
	cout << endl;

	system("pause");
}
