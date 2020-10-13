/* TIME-LIMIT Hay que buscar la manera de guardar los elementos en una matriz para
	aprovechar bien la programación dinámica, además se puede intentar buscar una
	condicion de parada segun las respuestas anteriores (una cota). */

// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

const long int INF = LONG_MAX;

struct cordel {
	int longitud;
	int precio;
};

struct tManeras {
	bool sePuede = false;
	long int minPrecio = INF;
	long int numFormas = 0;
	long int minCor = INF;
};


int main() {
	int numCor = 0, longitud = 0;
	while (cin >> numCor >> longitud) {
		vector<cordel> cordeles(numCor + 1);
		for (int i = 1; i <= numCor; ++i) {
			cin >> cordeles[i].longitud >> cordeles[i].precio;
		}
		vector<vector<tManeras>> formas(numCor + 1, vector<tManeras>(longitud + 1));
		formas[0][longitud].sePuede = true;
		formas[0][longitud].numFormas = 1;
		formas[0][longitud].minPrecio = 0;
		formas[0][longitud].minCor = 0;

		for (int i = 1; i <= numCor; ++i) {
			for (int j = 0; j <= longitud; ++j) {
				if (j + cordeles[i].longitud <= longitud) {
					formas[i][j].sePuede = formas[i - 1][j + cordeles[i].longitud].sePuede || formas[i - 1][j].sePuede;
					if (formas[i][j].sePuede) {
						formas[i][j].numFormas = formas[i - 1][j + cordeles[i].longitud].numFormas + formas[i - 1][j].numFormas;
						formas[i][j].minCor = min(formas[i - 1][j + cordeles[i].longitud].minCor, formas[i - 1][j].minCor) + 1;
						formas[i][j].minPrecio = min(formas[i - 1][j + cordeles[i].longitud].minPrecio +
							cordeles[i].precio, formas[i - 1][j].minPrecio);
					}
				}
				else {
					formas[i][j].sePuede = formas[i - 1][j].sePuede;
					formas[i][j].numFormas = formas[i - 1][j].numFormas;
					formas[i][j].minCor = formas[i - 1][j].minCor;
					formas[i][j].minPrecio = formas[i - 1][j].minPrecio;
				}
			}
		}

		if (formas[numCor][0].sePuede) {
			cout << "SI " << formas[numCor][0].numFormas << ' '
				 << formas[numCor][0].minCor << ' ' << formas[numCor][0].minPrecio << '\n';
		}
		else {
			cout << "NO\n";
		}
	}

	return 0;
}