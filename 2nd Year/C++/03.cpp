// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include <cmath>
#include "03.h"

using namespace std;

bool mandlebrotiano(complejo z, complejo const& c, int n) {
	if (z.mod() > 2) return false;
	else if (n < 0) return true;
	else return mandlebrotiano(z * z + c, c, n - 1);
}

int main() {
	int numVeces = 0;
	cin >> numVeces;
	for (int i = 0; i < numVeces; ++i) {
		float a = 0.0, b = 0.0;
		int n = 0;
		cin >> a >> b >> n;
		complejo c(a, b), z(0,0);
		if (mandlebrotiano(z, c, n)) cout << "SI\n";
		else cout << "NO\n";
	}

	return 0;
}