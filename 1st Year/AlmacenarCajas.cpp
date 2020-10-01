#include <iostream>
using namespace std;

/* Programa que calcula el numero de cajas de dimensiones cx x cy x cz
que se pueden apilar en un contenedor de dimensiones ax x ay x az.
*/

int main() {

	// Declaración de variables.
	int numVeces = 0, contx = 0, conty = 0, contz = 0, cajax = 0, cajay = 0, cajaz = 0, numCajasX = 0, numCajasY = 0, numCajasZ = 0, numCajasTotal = 0;

	// Pedimos el numero de veces a realizar la operación.
		//cout << "Establezca el numero de operaciones a realizar: " << endl;
	cin >> numVeces;

	// Bucle que recibe los datos de entrada y devuelve los correspondientes de salida el numVeces establecido.

	for (int i = 0; i < numVeces; ++i) {

			//cout << "Diga dimensiones del contenedor, X, Y, Z (en metros), y las dimensiones de la caja x, y, z (en centímetros): " << endl;
		cin >> contx >> conty >> contz >> cajax >> cajay >> cajaz;

		// Operaciones
		numCajasX = 100 * contx / cajax;
		numCajasY = 100 * conty / cajay;
		numCajasZ = 100 * contz / cajaz;

		numCajasTotal = numCajasX * numCajasY * numCajasZ;

		// Devuelve el valor obtenido.
		cout << numCajasTotal << endl;
	}

	return 0;
}