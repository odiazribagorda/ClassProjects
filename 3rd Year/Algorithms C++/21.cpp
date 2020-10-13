// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int pesoMax = 0, numPersonas = 0;
	while (cin >> pesoMax >> numPersonas) {
		int numSillas = 0;
		vector<int> pesos(numPersonas);
		for (int i = 0; i < numPersonas; ++i) cin >> pesos[i];
		sort(pesos.begin(), pesos.end());
		int i = 0, j = numPersonas - 1;
		while (i < j) {
			if (pesos[i] + pesos[j] > pesoMax) {
				--j;
				++numSillas;
			}
			else {
				++i; --j;
				++numSillas;
			}
		}
		if (i == j) ++numSillas;
		
		cout << numSillas << '\n';
	}

	return 0;
}