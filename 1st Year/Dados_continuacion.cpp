// DG05 Oscar Diaz Ribagorda

#include <iostream>
using namespace std;

int main() {
	// Declaración de variables.
	int ana1 = 0, ana = 0, jorge1 = 0, jorge = 0, amigo1 = 0, amigo = 0, numVeces = 0;

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) {
		cin >> jorge >> jorge1 >> ana >> ana1 >> amigo >> amigo1;
		jorge += jorge1;
		ana += ana1;
		amigo += amigo1;

		if (jorge > ana && jorge > amigo)
			cout << "JORGE " << jorge << '\n';
		else if (ana > amigo && ana > jorge)
			cout << "ANA " << ana << '\n';
		else if (amigo > ana && amigo > jorge)
			cout << "AMIGO " << amigo << '\n';
		else if (jorge == ana && jorge == amigo)
			cout << "EMPATE AMIGO ANA JORGE " << jorge << '\n';
		else if (jorge == ana)
			cout << "EMPATE ANA JORGE " << jorge << '\n';
		else if (jorge == amigo)
			cout << "EMPATE AMIGO JORGE " << jorge << '\n';
		else
			cout << "EMPATE AMIGO ANA " << ana << '\n';
	}
	
	return 0;
}