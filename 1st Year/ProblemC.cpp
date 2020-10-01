#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

struct tComprobado {
	bool ok;
	long int cual;
};

const long int MAX_PRIM = 32000;

int main() {
	bool noPrimo[MAX_PRIM] = { false };
	int cont = 0, numVeces = 0, N, J;
	long long int sumas[9];
	vector<long int> primos;
	bool eano;
	tComprobado estabien[9];

	cin >> numVeces;

	for (int i = 2; i < MAX_PRIM; ++i) {
		if (!noPrimo[i])
			primos.push_back(i);
		for (int cont = 2; i * cont < MAX_PRIM; ++cont) {
			noPrimo[i * cont] = true;
		}
	}
	for (int i = 1; i <= numVeces; ++i) {
		cin >> N >> J;
		cout << "Case #" << i << ":\n";
		string number = "", copia = "";

		number.push_back('1');
		for (int i = 1; i < N - 1; ++i) {
			number.push_back('0');
		}
		number.push_back('1');

		cont = 0;
		while (cont < J) {
			for (short int j = 0; j < 9; ++j) {
				sumas[j] = 0;
				estabien[j].ok = false;
			}
			for (int k = 1; k <= N; ++k) {
				if (number[k - 1] == '1')
					for (int l = 2; l < 11; ++l)
						sumas[l - 2] += pow(l, (N - k));
			}

			eano = false;
			for (int b = 0; b < primos.size() && !eano; ++b) {
				for (int a = 0; a < 9; ++a)
					if (sumas[a] % primos[b] == 0) {
						estabien[a].ok = true;
						estabien[a].cual = primos[b];
					}
				eano = true;
				for (int a = 0; a < 9; ++a)
					if (!estabien[a].ok) eano = false;
			}
			if (eano) {
				++cont;
				cout << number;
				for (int z = 0; z < 9; ++z)
					cout << ' ' << estabien[z].cual;
				cout << '\n';
			}
			sumas[0] += 2;
			number = "";
			copia = "";
			int vueltas = 0;

			while (vueltas < N - 1) {
				number.push_back(char(sumas[0] % 2 + int('0')));
				sumas[0] = sumas[0] / 2;
				++vueltas;
			}
			number.push_back(char(sumas[0] + int('0')));
			for (int v = number.size() - 1; v >= 0; --v)
				copia.push_back(number[v]);

			number = copia;
		}
	}
	return 0;
}