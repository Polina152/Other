#pragma once

#include <iostream>
#include <iomanip>

void zapoln(char* mas, int dlina, int sposob)
{
	srand(time(0));
	for (int i = 0; i < dlina; i++)
	{
		int j = i;
		if (i > 'z' - 'a') j = i - 'z' + 'a' - 1;
		switch (sposob)
		{
		case (0): mas[i] = j + 'a';  break;
		case (1): mas[i] = 'z' - j; break;
		case (2): mas[i] = rand() % ('z' - 'a' + 1) + 'a'; break;
		}
	}
}

void zapoln(char** mas, int dlina, int sposob)
{

	srand(time(0));
	for (int i = 0; i < dlina; i++)
	{
		int i2 = 0;
		for (i2; i2 < dlina - 1; i2++)
		{
			int j = i;
			if (i > 'z' - 'a') j = i - 'z' + 'a' - 1;
			switch (sposob)
			{
			case (0): mas[i][i2] = j + 'a';  break;
			case (1): mas[i][i2] = 'z' - j; break;
			case (2): mas[i][i2] = rand() % ('z' - 'a' + 1) + 'a'; break;
			}
		}
		mas[i][i2] = '\0';
	}
}

void zapoln(int* mas, int dlina, int sposob)
{
	srand(time(0));
	for (int i = 0; i < dlina; i++)
	{
		switch (sposob)
		{
		case (0): mas[i] = i;  break;
		case (1): mas[i] = dlina - i; break;
		case (2): mas[i] = rand() % (21); break;
		}
	}
}
void zapoln(float* mas, int dlina, int sposob)
{
	int toch = 100;
	srand(time(0));
	for (int i = 0; i < dlina; i++)
	{
		float a = i;
		switch (sposob)
		{
		case (0): mas[i] = a / toch;  break;
		case (1): mas[i] = (dlina - a) / toch; break;
		case (2): mas[i] = float(rand() % (toch * 10)) / toch; break;
		}
	}
}
