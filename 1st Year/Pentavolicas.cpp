// DG05 Oscar Diaz Ribagorda

#include <iostream>
using namespace std;

// Programa que te dice si una palabra es pentavólica o no.
int main() {
	// Declaración de variables.
	char c = ' ';
	int numVeces = 0, a = 0, e = 0, i = 0, o = 0, u = 0;

	cin >> numVeces;

	for (int b = 0; b < numVeces; ++b) {
		cin.get(c);
		if (c == '\n')
			cin.get(c);
		while ('a' <= c && c <= 'z') {
			if (c == 'a')
				++a;
			else if (c == 'e')
				++e;
			else if (c == 'i')
				++i;
			else if (c == 'o')
				++o;
			else if (c == 'u')
				++u;
			cin.get(c);
		}
		if (a != 0 && e != 0 && i != 0 && o != 0 && u != 0)
			cout << "SI" << '\n';
		else
			cout << "NO" << '\n';
		a = 0, e = 0, i = 0, o = 0, u = 0;
	}
	return 0;
}