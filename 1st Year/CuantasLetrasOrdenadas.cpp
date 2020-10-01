//DG05 Oscar Diaz Ribagorda

#include <iostream>
#include <string>

using namespace std;

int main() {
	//Declaración de variables.
	int letras = 0, cont = 0, aux = 0;
	string str = "";

	cin >> str;

	while (str != "XXX") {
		if (str.size() > 1) {
			for (int i = 0; i < str.size() - 1; ++i) {

				// Si la letra es mayor suma en un contador y si el contador es mayor que lo guardado guarda ese nuevo número.
				if (str.at(i) < str.at(i + 1)) {
					++cont;
					if (cont + 1 >= aux) aux = cont + 1;
				}
				// Cuando deja de ser una letra mayor que la anterior el contador pasa a ser 0.
				else cont = 0;

				++letras;
			}
		}
		else aux = 1;
		cout << letras + 1 << ' ' << aux << '\n';

		aux = 0;
		letras = 0;
		cont = 0;

		cin >> str;
	}
	return 0;
}