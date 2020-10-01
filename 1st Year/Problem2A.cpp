#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main() {
	int numVeces = 0;
	string mejor = "", palabraAux = "", palabraAux2 = "";

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) {
		cin >> palabraAux;
		mejor = "";
		mejor.push_back(palabraAux[0]);
		for (int j = 1; j < palabraAux.size(); ++j) {
			if (palabraAux[j] > mejor[0]) {
				palabraAux2 = palabraAux[j] + mejor;
				mejor = palabraAux2;
			}
			else mejor.push_back(palabraAux[j]);
		}

		cout << "Case #" << i + 1 << ": " << mejor << '\n';
	}

	return 0;
}