// Grupo 5 - Oscar Diaz Ribagorda y Rafael Herrera Troca
																			
#include "juegoPeg.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;


// Redefinicion de operador
ostream & operator<<(ostream & salida, tDireccion dir);
// Pide un nombre de archivo y lo devuelve (añade ".txt" si el nombre no lo llevaba)
string bienvenida();
// Muestra el menu y devuelve la opcion elegida
int menu();
// Inicia el juego sobre un tablero ya dado
void jugar(tJuegoPeg & juego);
// Carga un tablero con un nombre dado y devuelve un mensaje de error si no se pudo cargar
bool cargaTablero(tJuegoPeg & juego);
// Desarrolla una partida y devuelve un booleano indicando si se ha querido guardar el juego a la mitad o se ha jugado hasta el final
bool partida(tJuegoPeg & juego);
// Lee un movimiento y controla que se pueda realizar. Devuelve un booleano indicando si se desea guardar la partida
bool leerMovimiento(tJuegoPeg const& juego, tMovimiento & mov, bool & deshacer);
// Deshace un movimiento (si es posible)
void deshacerMov(tJuegoPeg & juego);

// Pide las opciones para generar un tablero con ellas (numero de filas, de columnas y de bolas)
void pedirOpciones(tJuegoPeg & juego, int & numBolas);
// Genera un tablero aleatorio
void generarTablero(tJuegoPeg & juego);

int main() {
	srand(time(NULL));
	int opcion = 0;
	tJuegoPeg juego;

	opcion = menu();
	while (opcion != 0) {
		if (opcion == 1) {
			if(cargaTablero(juego))
				jugar(juego);
		}
		else {
			generarTablero(juego);
			jugar(juego);
		}
		opcion = menu();
	}
	
	return 0;
}

int menu() {
	int opcion = 0;

	system("CLS");
	cout << "Elige una opcion:\n";
	cout << " 1 - Jugar partida\n";
	cout << " 2 - Generar tablero aleatorio\n";
	cout << " 0 - Salir\n";
	cout << "Opcion: ";
	cin >> opcion;
	cin.sync();
	while (cin.fail() || opcion < 0 || opcion > 2) {
		if (cin.fail())
			cin.clear();
		cout << "Opcion no valida. Elige una opcion: ";
		cin >> opcion;
		cin.sync();
	}

	return opcion;
}
bool cargaTablero(tJuegoPeg & juego) {
	string nombre = "";
	bool OK = true;
	nombre = bienvenida();
	if (!cargar(juego, nombre)) {
		cout << "Error al cargar tablero\n";
		OK = false;
	}
	return OK;
}
void jugar(tJuegoPeg & juego) {
	string nombre = "";

	juego.estado = JUGANDO;
	if (partida(juego)) {
		system("CLS");
		mostrar(juego);
		if (juego.estado == GANADOR)
			cout << "Enhorabuena !!! Has ganado.\n";
		else
			cout << "Lo siento, has perdido. Vuelvelo a intentar.\n";
		system("PAUSE");
	}
	else {
		cout << "Introduce el nombre para guardar el fichero.\n",
			cin >> nombre;
		if (nombre.size() < 4 || nombre.substr(nombre.size() - 4, 4) != ".txt")
			nombre += ".txt";
		guardar(juego, nombre);
	}
}
string bienvenida() {
	string nombre = "";

	system("CLS");
	cout << "Bienvenido. Introduce el nombre del fichero con el tablero que quieres jugar.\n\n ";
	cin >> nombre;
	if (nombre.size() < 4 || nombre.substr(nombre.size() - 4, 4) != ".txt")
		nombre += ".txt";
	system("CLS");

	return nombre;
}
bool partida(tJuegoPeg & juego) {
	bool guardar = false, deshacer = false;
	tMovimiento mov;

	while (juego.estado == JUGANDO && !guardar) {
		guardar = !leerMovimiento(juego, mov, deshacer);
		if (!deshacer && !guardar) {
			if (!ejecutarMovimiento(juego, mov))
				cout << "Error al ejecutar el movimiento.\n";
			else
				pushDCola(juego.ultimos, mov);
		}
		else if (deshacer) {
			deshacerMov(juego);
			deshacer = false;
		}
		juego.estado = revisarEstado(juego);
	}
	
	return !guardar;
}
bool leerMovimiento(tJuegoPeg const& juego, tMovimiento & mov, bool & deshacer) {
	tCasilla cas;
	tPosibles posibles;
	int dir = 0;
	bool guardar = false, hayPosibles = true;

	do {
		do {
			system("CLS");
			mostrar(juego);
			if (!hayPosibles)
				cout << "No hay movimientos posibles con esa ficha\n";
			cout << "Selecciona la ficha a mover (fila y columna),\n o 0 para guardar y salir: ";
			cin >> cas.fila;
			if (!cin.fail()) {
				if (cas.fila == 0)
					guardar = true;
				else if (cas.fila == -1)
					deshacer = true;
				else
					cin >> cas.col;
			}
			cas = cas - tCasilla{ 1, 1 };
			cin.sync();
			while (!deshacer && !guardar && (cin.fail() || !dentroRango(cas, juego.numFilas, juego.numCols, 0, 0) 
				|| juego.tablero[cas.fila][cas.col] != FICHA)) {
				cout << "No hay una ficha en esa posicion\nSelecciona la ficha a mover (fila y columna),\n o 0 para guardar y salir: ";
				if (cin.fail())
					cin.clear();
				cin >> cas.fila;
				if (!cin.fail()) {
					if (cas.fila == 0)
						guardar = true;
					else if (cas.fila == -1)
						deshacer = true;
					else
						cin >> cas.col;
				}
				cin.sync();
				cas = cas - tCasilla{ 1, 1 };
			}
			if (!guardar && !deshacer)
				hayPosibles = posiblesMovimientos(juego, cas, posibles);

		} while (!guardar && !deshacer && !hayPosibles);

		if (!guardar && !deshacer) {
			system("CLS");
			mostrar(juego, cas, posibles);
			cout << "Selecciona una direccion:\n";
			for (int i = 0; i < NUM_DIRS; ++i) {
				if (posibles[i])
					cout << ' ' << i + 1 << " - " << tDireccion(i) << '\n';
			}
			cout << " 0 - Seleccionar otra ficha\n";
			cin >> dir;
			cin.sync();
			while (cin.fail() || dir < 0 || dir > 8 || !posibles[dir - 1]) {
				if (cin.fail())
					cin.clear();
				cout << "Esa direccion no existe. Elige una direccion valida.\n";
				cin >> dir;
				cin.sync();
			}
		}
	} while (dir == 0 && !guardar && !deshacer);

	mov.origen = cas;
	mov.dir = tDireccion(dir - 1);

	return !guardar;
}
void deshacerMov(tJuegoPeg & juego) {
	tMovimiento mov;
	tCasilla siguiente, siguiente2;

	mov = popDCola(juego.ultimos);
	if (mov.origen == tCasilla{ -1, -1 }) {
		cout << "No se pueden deshacer mas movimientos\n";
		system("PAUSE");
	}
	else {
		siguiente = mov.origen + MOVER[int(mov.dir)];
		siguiente2 = mov.origen + 2 * MOVER[int(mov.dir)];
		juego.tablero[mov.origen.fila][mov.origen.col] = FICHA;
		juego.tablero[siguiente.fila][siguiente.col] = FICHA;
		juego.tablero[siguiente2.fila][siguiente2.col] = VACIA;
	}
}

void pedirOpciones(tJuegoPeg & juego, int & numBolas) {
	system("CLS");
	cout << "\nSelecciona el numero de filas del tablero: ";
	cin >> juego.numFilas;
	cin.sync();
	while (cin.fail() || juego.numFilas < 1 || juego.numFilas > DIM) {
		if (cin.fail())
			cin.clear();
		cout << "Selecciona un numero de filas correcto: ";
		cin >> juego.numFilas;
		cin.sync();
	}

	cout << "\nSelecciona el numero de columnas del tablero: ";
	cin >> juego.numCols;
	cin.sync();
	while (cin.fail() || juego.numCols < 1 || juego.numCols > DIM) {
		if (cin.fail())
			cin.clear();
		cout << "Selecciona un numero de filas correcto: ";
		cin >> juego.numCols;
		cin.sync();
	}

	cout << "\nSelecciona el numero de bolas: ";
	cin >> numBolas;
	cin.sync();
	while (cin.fail() || numBolas < 1 || numBolas >= juego.numFilas * juego.numCols) {
		if (cin.fail())
			cin.clear();
		cout << "Selecciona un numero de bolas correcto: ";
		cin >> numBolas;
		cin.sync();
	}
}
void generarTablero(tJuegoPeg & juego) {
	int numBolas = 0, puntero = 0, bIni = 0;
	tBolas colocadas;
	bool hayMovimientos = true;

	pedirOpciones(juego, numBolas);

	for (int i = 0; i < juego.numFilas; ++i)
	for (int j = 0; j < juego.numCols; ++j)
		juego.tablero[i][j] = NULA;
	juego.numBolas = 0;

	juego.meta.fila = rand() % juego.numFilas;
	juego.meta.col = rand() % juego.numCols;
	juego.tablero[juego.meta.fila][juego.meta.col] = FICHA;
	++juego.numBolas;
	colocadas.push_back(juego.meta);

	hayMovimientos = !((juego.numFilas < 3 && juego.numCols < 3) ||
		(juego.numFilas == 3 && juego.numCols == 3 && juego.meta.fila == 1 && juego.meta.col == 1));

	while (juego.numBolas < numBolas && hayMovimientos) {
		bIni = rand() % colocadas.size();
		puntero = bIni;
		bool sustituida = false;
		do {
			sustituida = sustituir(juego, colocadas, puntero);
			if (!sustituida)
				puntero = (puntero + 1) % colocadas.size();
		} while (!sustituida && puntero != bIni);
		if (!sustituida) hayMovimientos = false;
	}
}

ostream & operator<<(ostream & salida, tDireccion dir) {
	switch (dir)
	{
		case N: salida << "Norte"; break;
		case NE: salida << "Noreste"; break;
		case E: salida << "Este"; break;
		case SE: salida << "Sureste"; break;
		case S: salida << "Sur"; break;
		case SO: salida << "Suroeste"; break;
		case O: salida << "Oeste"; break;
		case NO: salida << "Noroeste"; break;
	};
	return salida;
}