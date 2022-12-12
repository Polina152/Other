#pragma once

using namespace std;

template<typename T>
bool bolshe(T a, T b)
{
	return a > b;
}
bool bolshe(char* a, char*b)
{
	int i = 0;
	while (a[i] != '\0' && b[i] != '\0')
		if (a[i] > b[i]) return true;
		else if (a[i] < b[i]) return false;
		else i++;
	return false;
}