// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;

struct Nodo {
	int k; int puntuacion;
	pair<int, int> capacidad;
	float maximoEstimado;

	bool operator<(Nodo const& other) const {
		return maximoEstimado < other.maximoEstimado;
	}
};

struct cancion{
	int duracion;
	int puntuacion;
	float densidad;
};

bool comparacion(cancion & a, cancion & b) {
	return (a.densidad > b.densidad);
}


float calcularOptimista(Nodo const& Y, vector<cancion> const& canciones){
	float suma = Y.puntuacion;
	int capacidad = Y.capacidad.first + Y.capacidad.second;
	int i = Y.k + 1;
	while (i < canciones.size() && capacidad > canciones[i].duracion) {
		suma += canciones[i].puntuacion;
		capacidad -= canciones[i].duracion;
		++i;
	}
	if (i < canciones.size()) {
		suma += capacidad * canciones[i].densidad;
	}
	return suma;
}

int calcularPesimista(int puntuacion, int k, vector<cancion> const& canciones, pair<int, int> capacidad) {
	int suma = puntuacion;
	int capacidad1 = capacidad.first, capacidad2 = capacidad.second;
	int i = k + 1;
	while (i < canciones.size() && (capacidad1 >= canciones[i].duracion || capacidad2 >= canciones[i].duracion)) {
		if (capacidad1 >= canciones[i].duracion) {
			suma += canciones[i].puntuacion;
			capacidad1 -= canciones[i].duracion;
		}
		else {
			suma += canciones[i].puntuacion;
			capacidad2 -= canciones[i].duracion;
		}
		++i;
	}
	return suma;
}

int main() {
	int N = 0;
	cin >> N;
	while (N != 0) {
		int cintaDur;
		cin >> cintaDur;
		vector<cancion> canciones(N + 1);
		for (int i = 1; i <= N; ++i) {
			cin >> canciones[i].duracion >> canciones[i].puntuacion;
			canciones[i].densidad = float(canciones[i].puntuacion) / float(canciones[i].duracion);
		}
		sort(canciones.begin() + 1, canciones.end(), comparacion);
		Nodo Y, X;
		priority_queue<Nodo> pq;
		// Creamos la raiz
		Y.k = 0;
		Y.capacidad.first = cintaDur;
		Y.capacidad.second = cintaDur;
		Y.puntuacion = 0;
		Y.maximoEstimado = calcularOptimista(Y, canciones);
		pq.push(Y);
		int puntuacionMaxima = calcularPesimista(Y.puntuacion, Y.k, canciones, Y.capacidad);

		while (!pq.empty() && pq.top().maximoEstimado >= puntuacionMaxima) {
			Y = pq.top(); pq.pop();
			X.k = Y.k + 1; X.capacidad = Y.capacidad;
			if (Y.capacidad.first >= canciones[X.k].duracion) { // La metemos en la primera cara.
				X.puntuacion = Y.puntuacion + canciones[X.k].puntuacion;
				X.capacidad.first = Y.capacidad.first - canciones[X.k].duracion;
				X.maximoEstimado = calcularOptimista(X, canciones); // Seguramente esto no haga falta, porque si la hemos podido meter, la cotaOptimista no varia.
				if (X.maximoEstimado > puntuacionMaxima) {
					if (X.k == N) {
						puntuacionMaxima = X.puntuacion;
					}
					else {
						pq.push(X);
					}
				}
				X.capacidad.first = Y.capacidad.first;
			}
			if (Y.capacidad.first != Y.capacidad.second) {
				if (Y.capacidad.second >= canciones[X.k].duracion) { // La metemos en la segunda cara.
					X.puntuacion = Y.puntuacion + canciones[X.k].puntuacion;
					X.capacidad.second = Y.capacidad.second - canciones[X.k].duracion;
					X.maximoEstimado = calcularOptimista(X, canciones); // Tampoco haria falta este.
					if (X.maximoEstimado > puntuacionMaxima) {
						if (X.k == N) {
							puntuacionMaxima = X.puntuacion;
						}
						else {
							pq.push(X);
							puntuacionMaxima = max(puntuacionMaxima, calcularPesimista(X.puntuacion, X.k, canciones, X.capacidad));
						}
					}
					X.capacidad.second = Y.capacidad.second;
				}
			}
			// Por ultimo, no meterla siempre es posible.
			X.puntuacion = Y.puntuacion;
			X.maximoEstimado = calcularOptimista(X, canciones); // Este si que cambiara.
			if (X.maximoEstimado > puntuacionMaxima) {
				if (X.k == N) {
					puntuacionMaxima = X.puntuacion;
				}
				else {
					pq.push(X);
					puntuacionMaxima = max(puntuacionMaxima, calcularPesimista(X.puntuacion, X.k, canciones, X.capacidad));
				}
			}
		}
		cout << puntuacionMaxima << '\n';

		cin >> N;
	}

	return 0;
}