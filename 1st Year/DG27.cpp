#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// DG05 y DG11 - Oscar Diaz Ribagorda y Rafael Herrera Troca - DG27: El valor de la moda I

const int size = 201;

void maximo(vector<int> v, bool & unica, bool & solo1num, int & posmax)
{
	int max = v[0];
	vector<int> cero(size, 0);
	posmax = 0;
	for (int i = 1; i < size; ++i)
	{
		if (v[i] > max)
		{
			max = v[i];
			posmax = i;
			unica = true;
		}
		else if (v[i] == max)
			unica = false;
	}
	v[posmax] = 0;
	if (v == cero) solo1num = true;
}

void resolucion()
{
	bool unica = true, solo1num = false;
	int num = 0, moda = 0;
	long long unsigned int tam = 0;
	vector<int> v(size, 0);
	cin >> tam;
	for (long long unsigned int i = 0; i < tam; ++i)
	{
		cin >> num;
		num += 100;
		++v[num];	 
	}
	maximo(v, unica, solo1num, moda);
	if (solo1num) cout << "NO HAY MODA\n";
	else if (unica) cout << "MODA " << moda - 100 << '\n';
	else cout << "NO HAY MODA\n";
}

int main()
{
	int numCasos = 0;
	cin >> numCasos;
	for (int i = 0; i < numCasos; ++i) resolucion();
	return 0;
}