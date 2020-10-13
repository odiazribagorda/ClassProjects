// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int numPartidos = 0;
	cin >> numPartidos;
	while (numPartidos != 0) {
		int margen = 0;
		vector<int> rivales(numPartidos);
		vector<int> broncos(numPartidos);
		for (int i = 0; i < numPartidos; ++i) cin >> rivales[i];
		for (int i = 0; i < numPartidos; ++i) cin >> broncos[i];
		sort(rivales.begin(), rivales.end());
		sort(broncos.begin(), broncos.end());
		int i = 0;
		while (i < numPartidos && broncos[numPartidos - 1 - i] - rivales[i] > 0) {
			margen += broncos[numPartidos - 1 - i] - rivales[i];
			++i;
		}
		cout << margen << '\n';

		cin >> numPartidos;
	}

	return 0;
}