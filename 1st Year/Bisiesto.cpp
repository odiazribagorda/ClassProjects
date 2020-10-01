// DG05 Oscar Diaz Ribagorda

#include <iostream>
using namespace std;

// Programa que te dice si un año entre 1582 y 10000 es bisiesto.
int main() {
	// Declaración de variables.
	int year = 0, numVeces = 0;

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) {
		cin >> year;
		// Si es divisible entre 4 dice si.
		if (year % 4 == 0) {
			// Si además es divisible entre 100 dice no.
			if (year % 100 == 0) {
				// Si además de entre 100 es divisible entre 400 dice si.
				if (year % 400 == 0)
					cout << "SI" << '\n';
				else
					cout << "NO" << '\n';
			}
			else
				cout << "SI" << '\n';
		}
		// Si no es divisible entre 4.
		else
			cout << "NO" << '\n';
	}
	return 0;
}