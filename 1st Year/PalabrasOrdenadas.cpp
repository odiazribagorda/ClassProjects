// DG05 Oscar Diaz Ribagorda.

#include <iostream>
#include <string>

using namespace std;

int main() {
	//Declaración de variables.
	int cont = 0;
	string str = "";

	cin >> str;

	while (str != "XXX") {
		for (int i = 0; i < str.size() - 1; ++i) {
			if (str.at(i) < str.at(i + 1)) {
				++cont;
			}
		}
		if (cont == str.size() - 1)
			cout << "SI\n";
		else
			cout << "NO\n";
		cont = 0;
		cin >> str;
	}
}