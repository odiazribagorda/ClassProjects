// DG05 Oscar Diaz Ribagorda

#include <iostream>
#include <cctype>

using namespace std;

// Programa que cuenta el numero de caracteres en una frase y cuenta la cantidad de un caracter dado en dicha frase.
int main() {

	// Declaración de variables.
	char letra = ' ', c = ' ';
	int numVeces = 0;

	cin >> numVeces;

	// Bucle for para el numero de casos de prueba.
	for (int i = 0; i < numVeces; ++i) {
		int vecesLetra = 0, contador = 0;
		
		cin.get(letra);
		// Como cin.get lee el anterior retorno, hay que pedir el valor dos veces para que nos de un caracter.
		if (letra == 10) cin.get(letra);
		
		if (isupper(letra))
			letra = tolower(letra);

		cin.get(c);
		cin.get(c);

		// Bucle while para leer todos los caracteres de la frase contando los mismos y las veces que aparece la 'letra'.
		while (c != '\n') {
			if (isupper(c))
				c = tolower(c);
			if (c == letra)
				++vecesLetra;
			++contador;
			cin.get(c);
		}
		cout << vecesLetra << ' ' << contador << '\n';
	}
	
	return 0;
}