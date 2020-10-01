// DG05 Oscar Diaz Ribagorda

#include <iostream>
#include <string>

using namespace std;

int main() {
	string str = "", sub = "", saux = "";
	int cont = 0, j = 0, aux = 0, letras = 0;

	cin >> str;

	while (str != "XXX") {
		letras = str.size();

		if (letras > 1) {
			for (int i = 0; i < letras - 1; ++i) {
				j = i;
				while (j <= letras - 2 && str.at(j) < str.at(j + 1)) {
					++cont;
					sub += str.at(j);
					++j;
				}
				sub += str.at(j);
				++cont;
				if (cont > aux) {
					aux = cont;
					saux = sub;
				}
				cont = 0;
				sub = "";
				i = j;
			}

			cout << letras << ' ' << aux << ' ' << saux << '\n';
		}
		else
			cout << "1 1 " << str << '\n';

		aux = 0;
		saux = "";

		cin >> str;
	}
	return 0;
}