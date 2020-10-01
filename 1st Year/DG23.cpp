#include <iostream>
#include <vector>

using namespace std;

// DG05 y DG11 - Oscar Diaz Ribagorda y Rafael Herrera Troca - DG23: Por encima de la media

void resolucion()
{
	int peso = 0, total = 0, pesomuestra = 0, numM = 0, numm = 0;
	float media = 0;
	vector<int> v;
	cin >> peso;
	cin >> pesomuestra;
	while (pesomuestra != 0)
	{
		total += pesomuestra;
		v.push_back(pesomuestra);
		cin >> pesomuestra;
	}
	media = float(total) / v.size();
	if (peso >= media) {
		cout << "MAYOR ";
		for (int num : v)
			if (num >= media) ++numM;
		cout << numM << '\n';
		numM = 0;
	}
	else {
		cout << "MENOR ";
		for (int num : v)
			if (num < media) ++numm;
		cout << numm << '\n';
		numm = 0;
	}
	total = 0;
}

int main()
{
	int numCasos = 0;
	cin >> numCasos;
	for (int i = 0; i < numCasos; ++i) resolucion();
	return 0;
}