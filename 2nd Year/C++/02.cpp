// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <algorithm>
#include "02.h";

using namespace std;

istream & operator>>(istream & archEnt, vector<pelicula> & v) {
	for (int i = 0; i < v.size(); ++i) archEnt >> v[i];
	return archEnt;
}

ostream & operator<<(ostream & archSal, vector<pelicula> const& v) {
	for (int i = 0; i < v.size(); ++i) archSal << v[i] << '\n';
	return archSal;
}

int main() {
	int n = 0;
	cin >> n;
	while (n != 0) {
		vector<pelicula> cartelera(n);

		cin >> cartelera;
		sort(cartelera.begin(), cartelera.end());
		cout << cartelera << "---\n";

		cin >> n;
	}

	return 0;
}