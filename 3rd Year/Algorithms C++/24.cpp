// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Sesion {
	int comienzo;
	int duracion;
	bool operator<(Sesion s) {
		return comienzo < s.comienzo;
	}
};

int main() {
	int numSesiones = 0;
	cin >> numSesiones;
	while (numSesiones != 0) {
		int numPelis = 0;
		vector<Sesion> peliculas(numSesiones);
		for (int i = 0; i < numSesiones; ++i) {
			char aux = ' ';
			int hora, min;
			cin >> hora >> aux >> min;
			peliculas[i].comienzo = hora * 60 + min;
			cin >> peliculas[i].duracion;
		}
		sort(peliculas.begin(), peliculas.end());

		int dur = peliculas[0].duracion;
		++numPelis;
		for (int i = 1; i < numSesiones; ++i) {
			dur -= peliculas[i].comienzo - peliculas[i - 1].comienzo;
			if (dur > peliculas[i].duracion) {
				dur = peliculas[i].duracion;
			}
			else if (dur <= -10) {
				++numPelis;
				dur = peliculas[i].duracion;
			}
		}
		cout << numPelis << '\n';
		cin >> numSesiones;
	}

	return 0;
}