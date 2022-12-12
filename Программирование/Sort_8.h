#pragma once
#include "Sravn_str.h"

using namespace std;

template<typename T>
void sort(T* mas, int size)
{
	if (size > 1)
	{

		int size_1 = size / 2;
		int size_2 = size - size_1;
		sort(mas, size_1);
		sort(&mas[size_1], size_2);


		T mas_cp[1000] = { 0 };
		if (bolshe(mas[0], mas[size_1]))
		{
			copy(mas, &mas[size_1], mas_cp);
			copy(&mas[size_1], &mas[size], mas);
			copy(mas_cp, &mas_cp[size_1], &mas[size_2]);
		}
	}
}
