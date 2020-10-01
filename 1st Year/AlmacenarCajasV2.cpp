//DG05 Oscar Diaz Ribagorda

#include <iostream>
using namespace std;

/* Programa que apila cajas en un contenedor según sea
más conveniente que coincida el largo de la caja con el largo del contenedor
o si es mejor que coincida con el ancho.*/

int main() {

	// Declaración de variables.
	int numVeces = 0, contx = 0, conty = 0, contz = 0, cajax = 0, cajay = 0, cajaz = 0, numCajasX = 0, numCajasY = 0, numCajasZ = 0;
	int numCajasTotalParalelo = 0, numCajasTotalPerpendicular = 0;

	// Pedimos el numero de veces a realizar la operación.
	//cout << "Establezca el numero de operaciones a realizar: " << endl;
	cin >> numVeces;

	// Bucle que recibe los datos de entrada y devuelve los correspondientes de salida el numVeces establecido.

	for (int i = 0; i < numVeces; ++i) {

		//cout << "Diga dimensiones del contenedor, X, Y, Z (en metros), y las dimensiones de la caja x, y, z (en centímetros): " << endl;
		cin >> contx >> conty >> contz >> cajax >> cajay >> cajaz;

		numCajasX = 100 * contx / cajax;
		numCajasY = 100 * conty / cajay;
		numCajasZ = 100 * contz / cajaz;

		numCajasTotalParalelo = numCajasX * numCajasY * numCajasZ;

		numCajasX = 100 * contx / cajay;
		numCajasY = 100 * conty / cajax;
		
		numCajasTotalPerpendicular = numCajasX * numCajasY * numCajasZ;

		if (numCajasTotalParalelo > numCajasTotalPerpendicular) {
			cout << numCajasTotalParalelo << " EN PARALELO" << endl;
		} if (numCajasTotalParalelo < numCajasTotalPerpendicular) {
			cout << numCajasTotalPerpendicular << " EN PERPENDICULAR" << endl;
		} if (numCajasTotalParalelo == numCajasTotalPerpendicular) {
			cout << numCajasTotalParalelo << " DA IGUAL" << endl;
		}
	}

	return 0;
}