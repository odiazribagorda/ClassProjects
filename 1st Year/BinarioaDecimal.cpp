//DG05 Oscar Diaz Ribagorda

#include <iostream>
#include <string>

using namespace std;

int main() {
	long long unsigned int total = 0, numVeces = 0, potencia = 1;
	string num = "";

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) {
		cin >> num;
		for (int j = num.size() - 1; j >= 0; --j) {
			if (num.at(j) == '1') total += potencia;
			potencia *= 2;
		}
		cout << total << '\n';
		total = 0;
		potencia = 1;
	}
	return 0;
}