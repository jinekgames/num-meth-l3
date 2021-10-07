// SAJOURA SALAH CODE HERE (not jnk)

// Таблица конечных разностей.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// CPP Program to interpolate using
// newton forward interpolation
#include <iostream>
#include <iomanip>
#include "conio.h"
using namespace std;

// calculating u mentioned in the formula
float u_cal(float u, int n)
{
	float temp = u;
	for (int i = 1; i < n; i++)
		temp = temp * (u - i);
	return temp;
}

// calculating factorial of given number n
int factorial(int n)
{
	int f = 1;
	for (int i = 2; i <= n; i++)
		f *= i;
	return f;
}

int main()
{
	// Number of values given
	const int n = 6;
	float x[] = { 45, 50, 55, 60, 65, 70 };

	// y[][] is used for difference table
	// with y[][0] used for input
	float y[n][n];
	y[0][0] = 0.7071;
	y[1][0] = 0.7660;
	y[2][0] = 0.8192;
	y[3][0] = 0.8660;
	y[4][0] = 0.8780;
	y[5][0] = 0.8905;

	// Calculating the forward difference
	// table
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++)
			y[j][i] = y[j + 1][i - 1] - y[j][i - 1];
	}

	// Displaying the forward difference table
	for (int i = 0; i < n; i++) {
		cout << setw(4) << x[i]
			<< "\t";
		for (int j = 0; j < n - i; j++)
			cout << setw(4) << y[i][j]
			<< "\t";
		cout << endl;
	}

	// Value to interpolate at
	float value = 52;

	// initializing u and sum
	float sum = y[0][0];
	float u = (value - x[0]) / (x[1] - x[0]);
	for (int i = 1; i < n; i++) {
		sum = sum + (u_cal(u, i) * y[0][i]) /
			factorial(i);
	}

	cout << "\n Value at " << value << " is "
		<< sum << endl;

	_getch();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
