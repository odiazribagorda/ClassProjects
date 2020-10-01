// Grupo 5 - Oscar Diaz Ribagorda y Rafael Herrera Troca

#include "juegoPeg.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <Windows.h>

using namespace std;


void color(int colorFondo, int colorLetra) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, colorLetra | (colorFondo << 4));
}

bool cargar(tJuegoPeg & juego, string const& nombre) {
	bool OK = true;
	int aux = 0;
	ifstream archEnt;

	archEnt.open(nombre);
	if (!archEnt.is_open())
		OK = false;
	else {
		archEnt >> juego.numFilas >> juego.numCols;
		if (juego.numFilas > DIM || juego.numCols > DIM)
			OK = false;
		else {
			for (int i = 0; i < juego.numFilas; ++i)
				for (int j = 0; j < juego.numCols; ++j) {
					archEnt >> aux;
					juego.tablero[i][j] = tCelda(aux);
				}
			archEnt >> juego.meta.fila >> juego.meta.col;
			archEnt >> juego.numBolas;
		}
		archEnt.close();
	}
	return OK;
}
void mostrar(tJuegoPeg const& juego, tCasilla cas, tPosibles posibles) {
	int fExtra = 0, cExtra = 0, num = 0, colorFondo = 0, colorLetra = 0, numero = 0;
	vector< tCasilla > destinos;

	crearDestinos(cas, posibles, destinos);
	cout << '\n';
	if (juego.numFilas >= 10)
		cExtra = trunc(log10(juego.numFilas));
	if (juego.numCols >= 10) {
		fExtra = trunc(log10(juego.numCols));
		for (int i = 0; i < fExtra; ++i) {
			cout << setw(cExtra + 4) << ' ';
			for (int j = 2; j < juego.numCols + 1; ++j) {
				num = trunc(j / pow(10, fExtra - i));
				if (num == 0)
					cout << "  ";
				else
					cout << ' ' << num % 10;
			}
			cout << '\n';
		}
	}
	cout << setw(cExtra + 4) << 1;
	for (int i = 1; i < juego.numCols; ++i) {
		cout << ' ' << (i + 1) % 10;
	}
	cout << "\n\n";
	for (int i = 0; i < juego.numFilas; ++i) {
		cout << setw(cExtra + 2) << i + 1;
		for (int j = 0; j < juego.numCols; ++j) {
			cout << ' ';
			if (cas != tCasilla{ -1, -1 } && tCasilla{ i, j } == cas)
				colorFondo = ROSA;
			else
				colorFondo = int(juego.tablero[i][j]);

			if (juego.meta == tCasilla{i, j})
				colorLetra = BLANCO;
			else
				colorLetra = ROJO;

			color(colorFondo, colorLetra);
			numero = calcNumero(destinos, i, j);

			if (juego.meta == tCasilla{i, j})
				cout << char(254);
			else if (numero != -1)
				cout << numero;
			else
				cout << ' ';

			color(int(NULA), BLANCO);
		}
		cout << "\n\n";
	}
}
void guardar(tJuegoPeg const& juego, string nombre) {
	ofstream archSal;

	archSal.open(nombre);
	archSal << juego.numFilas << ' ' << juego.numCols << '\n';
	for (int i = 0; i < juego.numFilas; ++i) {
		archSal << juego.tablero[i][0];
		for (int j = 1; j < juego.numCols; ++j)
			archSal << ' ' << juego.tablero[i][j];
		archSal << '\n';
	}
	archSal << juego.meta.fila << ' ' << juego.meta.col << '\n' << juego.numBolas;
	
	archSal.close();
}

bool dentroRango(tCasilla cas, int numFilas, int numCol, int f, int c) {
	return cas.fila >= f && cas.col >= c && cas.fila < numFilas && cas.col < numCol;
}
bool sePuedeMover(tJuegoPeg const& juego, tCasilla cas) {
	bool puede = false;
	tCasilla siguiente, siguiente2;
	int dir = 0;

	while (!puede && dir < NUM_DIRS) {
		siguiente = cas + MOVER[dir];
		siguiente2 = cas + 2 * MOVER[dir];
		if (dentroRango(siguiente, juego.numFilas, juego.numCols)
			&& juego.tablero[siguiente.fila][siguiente.col] == FICHA
			&& dentroRango(siguiente2, juego.numFilas, juego.numCols)
			&& juego.tablero[siguiente2.fila][siguiente2.col] == VACIA)
			puede = true;
		else
			++dir;
	}

	return puede;
}
bool posiblesMovimientos(tJuegoPeg const& juego, tCasilla cas, tPosibles posibles) {
	bool hayPosibles = false;
	tCasilla siguiente, siguiente2;

	for (int i = 0; i < NUM_DIRS; ++i)
	{
		siguiente = cas + MOVER[i];
		siguiente2 = cas + 2 * MOVER[i];
		if (dentroRango(siguiente, juego.numFilas, juego.numCols) && juego.tablero[siguiente.fila][siguiente.col] == FICHA
			&& dentroRango(siguiente2, juego.numFilas, juego.numCols) && juego.tablero[siguiente2.fila][siguiente2.col] == VACIA)
			posibles[i] = hayPosibles = true;
		else
			posibles[i] = false;
	}

	return hayPosibles;
}
bool ejecutarMovimiento(tJuegoPeg & juego, tMovimiento const& mov) {
	bool OK = true;
	tCasilla siguiente = mov.origen + MOVER[int(mov.dir)];
	tCasilla siguiente2 = mov.origen + 2 * MOVER[int(mov.dir)];

	OK = !(!dentroRango(mov.origen, juego.numFilas, juego.numCols) || !dentroRango(siguiente2, juego.numFilas, juego.numCols) ||
		juego.tablero[mov.origen.fila][mov.origen.col] != FICHA || juego.tablero[siguiente.fila][siguiente.col] != FICHA ||
		juego.tablero[siguiente2.fila][siguiente2.col] != VACIA);

	if (OK)
	{
		juego.tablero[mov.origen.fila][mov.origen.col] = VACIA;
		juego.tablero[siguiente.fila][siguiente.col] = VACIA;
		juego.tablero[siguiente2.fila][siguiente2.col] = FICHA;
	}

	return OK;
}
tEstado revisarEstado(tJuegoPeg const& juego) {
	tEstado estado = BLOQUEO;
	bool primera = true;
	tCasilla cas;
	
	int fila = 0, col = 0;
	while (estado != JUGANDO && fila < juego.numFilas) {
		while (estado != JUGANDO && col < juego.numCols) {
			cas.fila = fila;
			cas.col = col;
			if (juego.tablero[fila][col] == FICHA && sePuedeMover(juego, cas)) {
				estado = JUGANDO;
				primera = false;
			}
			else if (juego.tablero[fila][col] == FICHA && primera && juego.meta.fila == fila && juego.meta.col == col) {
				estado = GANADOR;
				primera = false;
			}
			else if (juego.tablero[fila][col] == FICHA) {
				estado = BLOQUEO;
				primera = false;
			}
			++col;
		}
		col = 0;
		++fila;
	}

		return estado;
}

void pushDCola(tDobleCola & dCola, tMovimiento mov) {
	dCola.vector[dCola.ini] = mov;
	++dCola.ini;
	if (dCola.ini >= (NUM_DESHACER + 1))
		dCola.ini -= NUM_DESHACER + 1;
	if (dCola.ini == dCola.fin) {
		++dCola.fin;
		if (dCola.fin >= (NUM_DESHACER + 1))
			dCola.fin -= NUM_DESHACER + 1;
	}
}
tMovimiento popDCola(tDobleCola & dCola) {
	tMovimiento mov;

	if (dCola.ini == dCola.fin)
		mov.origen = { -1, -1 };
	else {
		--dCola.ini;
		if (dCola.ini < 0)
			dCola.ini += (NUM_DESHACER + 1);
		mov = dCola.vector[dCola.ini];
	}

	return mov;
}

void crearDestinos(tCasilla cas, tPosibles posibles, vector< tCasilla > & destinos) {
	tCasilla destino;

	if (cas != tCasilla{ -1, -1 })
	for (int i = 0; i < NUM_DIRS; ++i) {
		destino = cas + 2 * MOVER[i];
		if (posibles[i])
			destinos.push_back(destino);
		else
			destinos.push_back({ -1, -1 });
	}
}
int calcNumero(vector< tCasilla > const& destinos, int i, int j) {
	int numero = -1;

	for (int k = 0; k < destinos.size() && numero == -1; ++k)
		if (destinos[k] == tCasilla{ i, j })
			numero = k + 1;

	return numero;
}

bool sustituir(tJuegoPeg & juego, tBolas & colocadas, int puntero) {
	bool sustituida = false;
	int dirIni = rand() % NUM_DIRS;
	int dir = dirIni;
	tCasilla siguiente, siguiente2;

	do {
		siguiente = colocadas[puntero] + MOVER[dir];
		siguiente2 = colocadas[puntero] + 2 * MOVER[dir];
		if (dentroRango(siguiente, juego.numFilas, juego.numCols)
			&& dentroRango(siguiente2, juego.numFilas, juego.numCols)
			&& juego.tablero[siguiente.fila][siguiente.col] != FICHA
			&& juego.tablero[siguiente2.fila][siguiente2.col] != FICHA) {

			juego.tablero[colocadas[puntero].fila][colocadas[puntero].col] = VACIA;
			juego.tablero[siguiente.fila][siguiente.col] = FICHA;
			colocadas[puntero].fila = siguiente.fila;
			colocadas[puntero].col = siguiente.col;
			juego.tablero[siguiente2.fila][siguiente2.col] = FICHA;
			colocadas.push_back(siguiente2);
			++juego.numBolas;
			sustituida = true;
		}
		else dir = (dir + 1) % NUM_DIRS;
	} while (!sustituida && dir != dirIni);

	return sustituida;
}

tCasilla & operator+(tCasilla cas, tCasilla cas2) {
	tCasilla resultado = { cas.fila + cas2.fila, cas.col + cas2.col };	
	return resultado;
}
tCasilla & operator-(tCasilla cas, tCasilla cas2) {
	tCasilla resultado = { cas.fila - cas2.fila, cas.col - cas2.col };
	return resultado;
}
tCasilla & operator*(int mult, tCasilla cas) {
	tCasilla resultado = { cas.fila * mult, cas.col * mult };
	return resultado;
}
bool & operator==(tCasilla cas2, tCasilla cas) {
	bool igual = ((cas2.fila == cas.fila) && (cas2.col == cas.col));
	return igual;
}
bool & operator!=(tCasilla cas2, tCasilla cas) {
	bool igual = ((cas2.fila != cas.fila) || (cas2.col != cas.col));
	return igual;
}