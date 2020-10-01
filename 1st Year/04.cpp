// Oscar Diaz Ribagorda (DG05)


#include <iostream>
#include <vector>

using namespace std;

struct tCelda {
	bool descubierta;
	bool bomba;
	int numBombas;
};

struct tPos {
	int fila;
	int columna;
};

const int DIM = 300;

void sumarBombas(tCelda tablero[DIM][DIM], int f, int c, int posBombaY, int posBombaX) {
	if (posBombaY != 0) {
		++tablero[posBombaY - 1][posBombaX].numBombas;
		if (posBombaX != 0)
			++tablero[posBombaY - 1][posBombaX - 1].numBombas;
		if (posBombaX != c - 1)
			++tablero[posBombaY - 1][posBombaX + 1].numBombas;
	}
	if (posBombaY != f - 1) {
		++tablero[posBombaY + 1][posBombaX].numBombas;
		if (posBombaX != 0)
			++tablero[posBombaY + 1][posBombaX - 1].numBombas;
		if (posBombaX != c - 1)
			++tablero[posBombaY + 1][posBombaX + 1].numBombas;
	}
	if (posBombaX != 0)
		++tablero[posBombaY][posBombaX - 1].numBombas;
	if (posBombaX != c - 1)
		++tablero[posBombaY][posBombaX + 1].numBombas;
}

bool leer(tCelda tablero[DIM][DIM], int & f, int & c) {
	bool ok = true;
	char aux = ' ';

	cin >> f >> c;
	if (!cin) ok = false;

	for (int i = 0; i < f; ++i)
		for (int j = 0; j < c; ++j) {
			tablero[i][j].numBombas = 0;
			tablero[i][j].descubierta = false;
			tablero[i][j].bomba = false;
		}

	for (int i = 0; i < f; ++i)
		for (int j = 0; j < c; ++j) {
			cin >> aux;
			if (aux == '*') {
				tablero[i][j].bomba = true;
				sumarBombas(tablero, f, c, i, j);
			}
		}

	return ok;
}

bool destaparCeldas(tCelda tablero[DIM][DIM], tPos pos, int f, int c) {
	bool gameOver = false;
	vector<tPos> horno;
	tPos posAux;

	if (tablero[pos.fila][pos.columna].bomba)
		gameOver = true;
	else if (!tablero[pos.fila][pos.columna].descubierta) {
		horno.push_back(pos);

		while (horno.size() > 0) {
			pos.fila = horno[horno.size() - 1].fila;
			pos.columna = horno[horno.size() - 1].columna;
			horno.pop_back();

			tablero[pos.fila][pos.columna].descubierta = true;
			if (tablero[pos.fila][pos.columna].numBombas == 0) {
				if (pos.fila != 0) {
					if (!tablero[pos.fila - 1][pos.columna].descubierta) {
						posAux.fila = pos.fila - 1;
						posAux.columna = pos.columna;
						horno.push_back(posAux);
					}
					if (pos.columna != 0 && !tablero[pos.fila - 1][pos.columna - 1].descubierta) {
						posAux.fila = pos.fila - 1;
						posAux.columna = pos.columna - 1;
						horno.push_back(posAux);
					}
					if (pos.columna != c - 1 && !tablero[pos.fila - 1][pos.columna + 1].descubierta) {
						posAux.fila = pos.fila - 1;
						posAux.columna = pos.columna + 1;
						horno.push_back(posAux);
					}
				}
				if (pos.fila != f - 1) {
					if (!tablero[pos.fila + 1][pos.columna].descubierta) {
						posAux.fila = pos.fila + 1;
						posAux.columna = pos.columna;
						horno.push_back(posAux);
					}
					if (pos.columna != 0 && !tablero[pos.fila + 1][pos.columna - 1].descubierta) {
						posAux.fila = pos.fila + 1;
						posAux.columna = pos.columna - 1;
						horno.push_back(posAux);
					}
					if (pos.columna != c - 1 && !tablero[pos.fila + 1][pos.columna + 1].descubierta) {
						posAux.fila = pos.fila + 1;
						posAux.columna = pos.columna + 1;
						horno.push_back(posAux);
					}
				}
				if (pos.columna != 0 && !tablero[pos.fila][pos.columna - 1].descubierta) {
					posAux.fila = pos.fila;
					posAux.columna = pos.columna - 1;
					horno.push_back(posAux);
				}
				if (pos.columna != c - 1 && !tablero[pos.fila][pos.columna + 1].descubierta) {
					posAux.fila = pos.fila;
					posAux.columna = pos.columna + 1;
					horno.push_back(posAux);
				}
			}
		}
	}

	return gameOver;
}

void mostrar(const tCelda tablero[DIM][DIM], int f, int c) {
	for (int i = 0; i < f; ++i) {
		for (int j = 0; j < c; ++j)
			if (tablero[i][j].descubierta)
				if (tablero[i][j].numBombas == 0)
					cout << '-';
				else cout << tablero[i][j].numBombas;
			else cout << 'X';
			cout << '\n';
	}
}

int main() {
	tCelda tablero[DIM][DIM];
	int f = 0, c = 0, numVeces = 0;
	tPos pos;
	bool gameOver = false;

	while (leer(tablero, f, c)) {
		cin >> numVeces;
		for (int i = 0; i < numVeces && !gameOver; ++i) {
			cin >> pos.fila >> pos.columna;
			--pos.fila; --pos.columna;
			gameOver = destaparCeldas(tablero, pos, f, c);
		}

		if (gameOver) cout << "GAME OVER\n";
		else mostrar(tablero, f, c);

		gameOver = false;
	}
	

	return 0;
}