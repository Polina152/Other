#include <iostream>
#include <iomanip>
#include "Zapolnenie.h"
#include "Sort.h"
using namespace std;

template <typename T>
void vyvod(T*mas, int r)
{
	for (int i = 0; i < r; i++) cout << mas[i] << ' ';
	cout << endl;
}




void main()
{
	const int r = 100;				// размер
	const int s = 2;				// 0 - возрастание, 1 - убывание, 2 - случайные

	int prisv = 0; int sravn = 0;

	int a[r];
	zapoln(a, r, s); int a2[r]; for (int i = 0; i < r; i++) a2[i] = a[i];
	
	
	vyvod(a, r);
	sort_vybor(a, r, &prisv, &sravn); cout << endl << "Сортировка выбором" << endl;
	vyvod(a, r); cout << "Кол-во обменов " << prisv << "; Кол-во сравнений " << sravn << endl << endl;
	prisv = 0; sravn = 0;
	sort_vstav(a2, r, &prisv, &sravn); cout << "Сортировка вставками" << endl;
	vyvod(a, r); cout << "Кол-во обменов " << prisv << "; Кол-во сравнений " << sravn << endl << endl;
	prisv = 0; sravn = 0;

	
	

	

	cout << endl;


	system("pause");
}
