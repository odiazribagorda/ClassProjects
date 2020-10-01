//DG05 Oscar Diaz Ribagorda

#include <iostream>

using namespace std;

int main() {
	int ins = 0, arac = 0, crus = 0, escal = 0, numAnillos = 0, total = 0, numVeces = 0;

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) {
		cin >> ins >> arac >> crus >> escal >> numAnillos;
		total = ins * 6 + arac * 8 + crus * 10 + escal * numAnillos * 2;
		cout << total << '\n';
	}

	return 0;
}