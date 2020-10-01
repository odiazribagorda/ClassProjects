// Oscar Diaz Ribagorda (DG05)

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct tPalabra {
	string palabra;
	vector<int> lineas;
};

ostream & operator<<(ostream & archSal, vector<int> lineas) {
	archSal << lineas[0];
	for (int i = 1; i < lineas.size(); i++) {
		archSal << ' ' << lineas[i];
	}
	return archSal;
}

ostream & operator<<(ostream & archSal, vector<tPalabra> texto) {
	for (int i = 0; i < texto.size(); i++) {
		archSal << texto[i].palabra << ' ' << texto[i].lineas << '\n';
	}
	archSal << "----\n";

	return archSal;
}

string tolower(string palabra) {
	string palabraAux = "";

	for (int i = 0; i < palabra.size(); ++i)
		palabraAux.push_back(tolower(palabra[i]));

	return palabraAux;
}

/*void insertarInsercion(vector<tPalabra> & texto, tPalabra palabra) {
	tPalabra palabraAux;

	texto.push_back(palabra);
	palabraAux = palabra;
	int i = texto.size() - 1;
	while (i > 0 && texto[i - 1] > palabraAux) {
		texto[i] = texto[i - 1];
		--i;
	}
	texto[i] = palabraAux;
} */

void insertarBinaria(vector<tPalabra> & array, tPalabra palabra, int linea) {
	int ini = 0, fin = array.size(), mitad;
	bool encontrado = false;
	while (ini < fin && !encontrado) {
		mitad = (ini + fin - 1) / 2;
		if (array[mitad].palabra > palabra.palabra) fin = mitad;
		else if (palabra.palabra > array[mitad].palabra) ini = mitad + 1;
		else encontrado = true;
	}
	if (encontrado) ini = mitad;

	if (ini < array.size() && array[ini].palabra == palabra.palabra) {
		if (array[ini].lineas[array[ini].lineas.size() - 1] != linea)
			array[ini].lineas.push_back(linea);
	} else {
		palabra.lineas.push_back(linea);
		array.push_back(palabra);
		for (int i = array.size() - 1; i > ini; --i)
			array[i] = array[i - 1];
		array[ini] = palabra;
	}
}


void leer(vector<tPalabra> & texto, int numLineas) {
	char letra = ' ';
	tPalabra palabraAux;

	for (int i = 0; i < numLineas; ++i) {
		cin >> palabraAux.palabra;
		palabraAux.palabra = tolower(palabraAux.palabra);
		cin.get(letra);

		while (letra != '\n') {
			if (palabraAux.palabra.size() > 2)
				insertarBinaria(texto, palabraAux, i + 1);

			cin >> palabraAux.palabra;
			palabraAux.palabra = tolower(palabraAux.palabra);
			cin.get(letra);
		}
		if (palabraAux.palabra.size() > 2)
			insertarBinaria(texto, palabraAux, i + 1);
	}
}

int main() {
	int numLineas = 0;
	char aux = ' ';

	cin >> numLineas;
	cin.get(aux);

	while (numLineas != 0) {
		vector<tPalabra> texto;
		leer(texto, numLineas);
		cout << texto;

		cin >> numLineas;
		cin.get(aux);
	}

	return 0;
}