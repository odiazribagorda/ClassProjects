#include <iostream>
#include <vector>

using namespace std;

// DG05 y DG11 - Oscar Diaz Ribagorda y Rafael Herrera Troca - DG24: Maximos y minimos

void resolucion()
{
	int tam = 0, posmax = 0, posmin = 0, max = 0, min = 0;
	cin >> tam;
	vector<int> v(tam);
	for (int & num : v) cin >> num;
	max = v[0];
	min = v[0];
	for (int i = 0; i < tam; ++i)
	{
		if (v[i] > max)
		{
			max = v[i];
			posmax = i;
		}
		else if (v[i] < min)
		{
			min = v[i];
			posmin = i;
		}
	}
	cout << max << ' ' << posmax << ' ' << min << ' ' << posmin << '\n';
}

int main()
{
	int numCasos = 0;
	cin >> numCasos;
	for (int i = 0; i < numCasos; ++i) resolucion();
	return 0;
}