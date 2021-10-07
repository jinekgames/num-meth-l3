// main.cpp
//
// Numerical methods
// lab 3 (Kalinin, Pimenova, Smirnova)
// interpolate using newton forward interpolation



#pragma warning (disable : 4996)

#include <windows.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include "conio.h"
#include "additionalMaths.h"
#include "constants.h"

using namespace std;


#define DISPLAY
#define INTER_MOD


// calculating u mentioned in the formula
DOUBLE u_cal(DOUBLE u, int n)
{
	DOUBLE temp = u;
	for (int i = 1; i < n; i++)
		temp = temp * (u - i);
	return temp;
}


#define ISTREAM *inputStream

int main(int argc, char* argv[]) {

	istream* inputStream;
	ifstream fin;
	BOOL file = false;

	try {

		if (argc > 1) {
			fin.open(argv[1]);
			if (!fin.is_open()) {
				throw "FILE OPENING ERROR\n";
			}
			file = true;
			inputStream = &fin;
			cout << "Input from file \"" << argv[1] << "\"";
		} else {
			inputStream = &cin;
		}

		// function table size
		ULONG vecLen;
		if (!file)	cout << "Input table size -> ";
		ISTREAM >> vecLen;

		// X vector values
		vector<DOUBLE> Xvec(vecLen, 0);
		// Y vector values & difference matrix
		vector<vector<DOUBLE>> Ymtrx(vecLen, vector<DOUBLE>(vecLen, 0));

		// Input table of function values
		if (!file)	cout << "Input " << vecLen << " X vector values:\n";
		for (auto i = 0ul; i < vecLen; i++) {
			ISTREAM >> Xvec[i];
		}
		if (!file)	cout << "Input " << vecLen << " appropriate Y vector values:\n";
		for (auto i = 0ul; i < vecLen; i++) {
			ISTREAM >> Ymtrx[i][0ul];
		}


		// Filling differece matrix
		for (auto i = 1ul; i < vecLen; i++) {
			for (auto j = 0ul; j < vecLen - i; j++) {

				Ymtrx[j][i] = DOUBLE(Ymtrx[j + 1ul][i - 1ul]) - Ymtrx[j][i - 1ul];

			}
		}


#ifdef DISPLAY

		// max i coord in table
		ULONG i_max = vecLen * 2ul - 1ul;
		// max k coord in table
		ULONG k_max = vecLen + 1;

		// Output differece matrix
		cout << "\n\nDifferece table:\n\n" << setw(DIF_TBL_COL_WDTH) << "X    " << setw(DIF_TBL_COL_WDTH) << "Y = f(X)" << "\n\n";

		for (auto i = 0ul; i < i_max; i++) {
			for (auto k = 0ul; k < k_max; k++) {

				if ((k == i + 1) || (i_max - i == k)) {
					cout << '\n';
					break;
				}
				else if (((i % 2) * (k % 2) == 0) && ((k % 2) + (i % 2) == 1)) {
					cout << setw(DIF_TBL_COL_WDTH) << ' ';
				}
				else {
					cout << setw(DIF_TBL_COL_WDTH) << fixed << Ymtrx[(i-k) / 2][k];
				}

			}
		}

		cout << "\n\n";

#endif // DISPLAY


		// X value for interpolation
		DOUBLE Xinterp;
		cout << "Input X value u need to interpolate -> ";
		cin >> Xinterp;

		auto starttime = GetTickCount64();

		// Interpolation
#ifdef INTER_MOD
		DOUBLE sum = Ymtrx[0ul][0ul];
		DOUBLE u = (Xinterp - Xvec[0ul]) / (Xvec[1ul] - Xvec[0ul]);
		DOUBLE fact = 1.0;
		DOUBLE poly = u;
		for (auto i = 1ul; i < vecLen; i++) {
			fact *= i;
			sum += (poly * Ymtrx[0ul][i]) / fact;
			poly *= u - i;
		}
#else // INTER_MOD
		DOUBLE value = 52;
		DOUBLE sum = Ymtrx[0][0];
		DOUBLE u = (value - Xvec[0]) / (Xvec[1] - Xvec[0]);
		for (int i = 1; i < vecLen; i++) {
			sum = sum + (u_cal(u, i) * Ymtrx[0][i]) /
				jnkMath::factorial(i);
		}
#endif // INTER_MOD

		cout << "Interpolated value: " << sum;

		cout << "\nInterpolation time: " << starttime - GetTickCount64() << "\n";








	} catch (const CHAR* e) {
		cout << "\n\n" << e << "\n\n";
	} catch (const CHAR& e) {
		cout << "\n\n" << e << "\n\n";
	}


	// Exit msg
	cout << EXIT_MSG;
	_getch();

	// Bye
	system("cls");
	cout << BYE_MSG;
	Sleep(1000);



	if (file) {
		fin.close();
	}

	return 0;

}
