// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Nodo {
	vector<int> solucion;
	int k;
	vector<bool> marcados;
	int sumaTotal;
	int minimoEstimado;
};

bool operator<(Nodo const& a, Nodo const& b) {
	return a.minimoEstimado > b.minimoEstimado;
}

void calcularMinimos(vector<vector<int>> const& trabajos, vector<int> & minimos){
	for (int i = 1; i < trabajos.size(); ++i) {
		minimos[i] = trabajos[i][1];
		for (int j = 2; j < trabajos.size(); ++j)
			if (trabajos[i][j] < minimos[i]) minimos[i] = trabajos[i][j];
	}
}

int calcularOptimista(int actual, int k, vector<int> const& minimos){
	int suma = actual;
	for (int i = k + 1; i < minimos.size(); ++i) {
		suma += minimos[i];
	}
	return suma;
}

int calcularPesimista(vector<vector<int>> const& trabajos) {
	int suma = 0;
	for (int i = 1; i < trabajos[0].size(); ++i){
		suma += trabajos[i][i];
	}
	return suma;
}

int main() {
	int N = 0;
	cin >> N;
	while (N != 0) {
		vector<vector<int>> trabajos(N + 1, vector<int>(N + 1));
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				cin >> trabajos[i][j];
			}
		}
		vector<int> minimos(N + 1);
		calcularMinimos(trabajos, minimos);
		Nodo Y, X;
		priority_queue<Nodo> pq;
		// Creamos la raiz
		Y.solucion = vector<int>(N + 1, 0);
		Y.k = 0;
		Y.marcados = vector<bool>(N + 1, false);
		Y.sumaTotal = 0;
		Y.minimoEstimado = calcularOptimista(Y.sumaTotal, Y.k, minimos);
		pq.push(Y);
		int tiempoMinimo = calcularPesimista(trabajos);
		
		while (!pq.empty() && pq.top().minimoEstimado < tiempoMinimo) {
			Y = pq.top(); pq.pop();
			X.solucion = Y.solucion; X.k = Y.k + 1; X.marcados = Y.marcados;
			for (int i = 1; i <= N; ++i) {
				if (!Y.marcados[i]) {
					X.solucion[X.k] = i;
					X.marcados[i] = true;
					X.sumaTotal = Y.sumaTotal + trabajos[X.k][i];
					X.minimoEstimado = calcularOptimista(X.sumaTotal, X.k, minimos);
					if (X.minimoEstimado < tiempoMinimo) {
						if (X.k == N) {
							tiempoMinimo = X.sumaTotal;
						}
						else {
							pq.push(X);
						}
					}
					X.marcados[i] = false;
				}
			}
		}
		cout << tiempoMinimo << '\n';

		cin >> N;
	}

	return 0;
}