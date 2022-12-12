#pragma once

using namespace std;

template <typename T>
void sort_vybor(T* mas, int dlina, int* prisv, int* sravn)
{
	for (int i = 0; i < dlina - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < dlina; j++)
		{
			(*sravn)++;
			if (mas[j] < mas[min])
			{
				min = j;
			}
		}
		if (min != i)
		{
			swap(mas[i], mas[min]); (*prisv)+=3;
			min = i;
		}
	}
}

template <typename T>
void sort_vstav(T* mas, int dlina, int* prisv, int* sravn)
{
	for (int i = 1; i < dlina; i++)
	{
		T x = mas[i];
		(*prisv)++;
		int j = i;
		while ((*sravn)++, j > 0 && mas[j - 1] > x)
		{
			mas[j] = mas[j - 1];
			j--;
			(*prisv)++;
		}
		if (i != j)
		{
			mas[j] = x;
			(*prisv)++;
		}
	}

}
