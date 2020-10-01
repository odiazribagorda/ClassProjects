// DG05 Oscar Diaz Ribagorda.

#include <iostream>
#include <string>

using namespace std;

int main() {
	// Declaración de varibles:
	int numVeces = 0, cont = 0, aux = 0;
	string str = "", sub = "", strAux = "";
	char c = ' ';

	cin >> numVeces;
	getline(cin, str); // sirve para leer el último retorno

	for (int i = 0; i < numVeces; ++i) {
		// A veces es necesario leerlo dos veces porque como es un getline, tambien lee el cambio de linea anterior(que no se habia borrado)
		getline(cin, str);
		c = str.at(0);
		strAux = tolower(c);
		for (int j = 1; j < str.size(); ++j) {
			c = str.at(j);
			c = tolower(c);
			strAux += c;
		}
		str = strAux;

		getline(cin, sub);
		c = sub.at(0);
		strAux = tolower(c);
		for (int j = 1; j < sub.size(); ++j) {
			c = sub.at(j);
			c = tolower(c);
			strAux += c;
		}
		sub = strAux;
		// Busca si hay una cadena dentro de str que coincide con sub.
		if (sub == "") aux = string::npos;
		else aux = str.find(sub);

		// Bucle while que suma uno si encuentra resultado con el find y busca el siguiente.
		while (aux != string::npos) {
			++cont;
			aux = str.find(sub, ++aux);
		}
		cout << cont << '\n';
		cont = 0;
	}
	return 0;
}