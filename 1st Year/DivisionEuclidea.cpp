//DG05 Oscar Diaz Ribagorda

#include <iostream>

using namespace std;

int main() {
	int divisor = 0, dividendo = 0, numVeces = 0;

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) {
		cin >> dividendo >> divisor;

		if (divisor == 0)
			cout << "DIV0\n";
		else if (dividendo > 0 || dividendo % divisor == 0)
			cout << dividendo / divisor << ' ' << dividendo % divisor << '\n';
		else if (divisor > 0)
			cout << dividendo / divisor - 1 << ' ' << divisor + dividendo % divisor << '\n';
		else
			cout << dividendo / divisor + 1 << ' ' << -divisor + dividendo % divisor << '\n';
	}
	return 0;
}