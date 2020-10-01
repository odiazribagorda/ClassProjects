// Oscar Diaz Ribagorda (DG05)

#include <iostream>
#include <vector>

using namespace std;

void resolucion() {
	int numVectores = 0, j = 0, k = 0;
	long unsigned int num = 0;
	vector<unsigned long int> v, sol, sol2, vacia;

	cin >> numVectores;

	cin >> num;
	while (num != 0) {
		v.push_back(num);
		cin >> num;
	}
	
	sol = v;
	v.clear();

	for (int i = 1; i < numVectores; ++i) {
		cin >> num;
		while (num != 0) {
			v.push_back(num);
			cin >> num;
		}
		while (j < sol.size() && k < v.size()) {
			if (sol[j] > v[k]) ++k;
			else if (sol[j] == v[k]) {
				sol2.push_back(sol[j]);
				++j;
				++k;
			}
			else ++j;
		}
		sol.clear();
		for (int h = 0; h < sol2.size(); ++h) {
			sol.push_back(sol2[h]);
		}
		sol2.clear();
		v.clear();
		j = 0;
		k = 0;
	}
	if (sol.size() > 0) {
		cout << sol[0];
		for (int i = 1; i < sol.size(); ++i)
			cout << ' ' << sol[i];
	}
	cout << '\n';
}

int main() {
	int numVeces = 0;

	cin >> numVeces;
	for (int i = 0; i < numVeces; ++i) resolucion();

	return 0;
}