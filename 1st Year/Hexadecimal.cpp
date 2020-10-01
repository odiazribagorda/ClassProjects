// DG05 Oscar Diaz Ribagorda

#include <iostream>
#include <cctype>

using namespace std;

// Programa que convierte un numero de dos cifras en hexadecimal a decimal.

int main() {
	
	// Declaración de variables.
	char c1 = ' ', c2 = ' ';
	int d1 = 0, d2 = 0, total = 0;

	cin >> c1 >> c2;

	// Bucle de repetición hasta que devuelva valor centinela 0.
	while (c1 != '0' || c2 != '0') {
		
		// Serie de if´s que resuelve las cuatro posibles combinaciones entre numeros y letras.
		if (isdigit(c1)) {
			d1 = (int(c1) - int('0')) * 16;
			if (isdigit(c2))
				d2 = int(c2) - int('0');
			else
				d2 = int(c2) - int('A') + 10;
		}
		else {
			d1 = (int(c1) - int('A') + 10) * 16;
			if (isdigit(c2))
				d2 = int(c2) - int('0');
			else
				d2 = int(c2) - int('A') + 10;
		}
		total = d1 + d2;
		cout << total << '\n';

		// Y se vuelven a pedir dos nuevos caracteres.
		cin >> c1 >> c2;
	}
	return 0;
}