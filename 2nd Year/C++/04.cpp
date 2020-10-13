// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include <vector>

using namespace std;

struct tipoP {
	int p = -1;
	int max = 0;
};

ostream & operator<<(ostream & archSal, vector<tipoP> const& v) {
	if (v.size() > 0) {
		archSal << v[0].p;
		for (int i = 1; i < v.size(); ++i)
			archSal << ' ' << v[i].p;
	}

	return archSal;
}

istream & operator>>(istream & archEnt, vector<int> & v) {
	char aux = ' ';

	archEnt >> v[0];
	for (int i = 1; i < v.size(); ++i) {
		archEnt >> v[i];
	}

	return archEnt;
}

/* El algoritmo de calcular todos los p's recorre una unica vez el vector a[] de numeros, pero por cada uno tiene un bucle que
	puede recorrer el vector[p] de p's guardados. La cuestion esque ese vector como mucho va a tener n elementos diferentes durante
	la ejecución del algoritmo, entonces si por ejemplo en un momento dado el vector p[] tiene n/2 elementos y los tiene que
	eliminar todos, recorre todas esas posiciones pero despues como mucho va a tener otros n/2 elementos que vaya a poder recorrer.
	La conclusion esque la complejidad del algoritmo es n (del vector a[]) + n (el peor caso del vector p) = 2n ~ n.
	Tiene complejidad LINEAL. */
void calcular(vector<tipoP> & p, vector<int> const& a) {
	tipoP pIni;
	pIni.max = a[0];
	p.push_back(pIni);

	for (int i = 1; i < a.size(); ++i) {
		/* Si el elemento es mayor que el maximo hasta ese momento, se almacena su posicion con el max correspondiente.
			El vector p siempre tiene un elemento mas apuntando al -1 para ir guardando el que podria ser el maximo 
			para un siguiente p. */
		if (a[i] > p[p.size() - 1].max) {
			p[p.size() - 1].p = i - 1;
			p.push_back(pIni);
			p[p.size() - 1].max = a[i];
		}
		/* Si el elemento es menor que el ultimo maximo guardado, se tienen que ir eliminando hasta que el maximo sea menor que
		el elemento o bien no queden p's guardadas en el vector. */
		while ((p.size() >= 2) && (a[i] <= p[p.size() - 2].max)) {
			p[p.size() - 2] = p[p.size() - 1];
			p.pop_back();
		}
	}

	if (p[p.size() - 1].p == -1)
		p.pop_back();
}

int main() {
	int numVeces = 0, n = 0, aux = 0;

	cin >> numVeces;
	for (int i = 0; i < numVeces; i++) {
		cin >> n;
		vector<int> numeros(n);

		cin >> numeros;
		
		vector<tipoP> p;

		calcular(p, numeros);

		cout << p << '\n';
	}


	return 0;
}