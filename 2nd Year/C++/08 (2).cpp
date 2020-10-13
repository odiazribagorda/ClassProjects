// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include <string>

using namespace std;


/* Esta funcion recorre una vez el vector linea (tamaño n) y en el peor caso una vez
	por cada elemento el vector de patron (tamaño m). Por tanto el algoritmo tiene complejidad (n * m).
	*/
int contadorDePatron(string const& linea, string const& patron) {
	int cont = 0;

	for (int i = 0; i < linea.size() - patron.size() + 1; ++i) {
		if (linea[i] == patron[0]) {
			int j = 1;
			while (j < patron.size() && linea[i + j] == patron[j])
				++j;
			if (j == patron.size())
				++cont;
		}
	}

	return cont;
}

int main() {
	string linea = "", patron = "";

	while (getline(cin, linea)) {
		getline(cin, patron);
		cout << contadorDePatron(linea, patron) << '\n';
	}


	return 0;
}