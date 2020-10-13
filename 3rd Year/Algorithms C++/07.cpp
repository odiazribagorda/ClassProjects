// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include "PriorityQueue.h"

using namespace std;


int main() {
	int mediana = 0, numParejas;
	cin >> mediana >> numParejas;
	while (mediana != 0 && numParejas != 0) {
		PriorityQueue<int> mayores;
		PriorityQueue<int, std::greater<int>> menores;
		int pajaro1 = 0, pajaro2 = 0;
		for (int i = 0; i < numParejas; ++i) {
			cin >> pajaro1 >> pajaro2;
			if (pajaro1 <= mediana && pajaro2 > mediana) {
				menores.push(pajaro1); mayores.push(pajaro2);
			}
			else if (pajaro2 <= mediana && pajaro1 > mediana) {
				menores.push(pajaro2); mayores.push(pajaro1);
			}
			else if (pajaro1 <= mediana && pajaro2 <= mediana) {
				menores.push(pajaro1); menores.push(pajaro2);
				mayores.push(mediana);
				menores.pop(mediana);
			}
			else if (pajaro1 > mediana && pajaro2 > mediana) {
				mayores.push(pajaro1); mayores.push(pajaro2);
				menores.push(mediana);
				mayores.pop(mediana);
			}
			if(i < numParejas - 1) cout << mediana << ' ';
			else cout << mediana << '\n';
		}

		cin >> mediana >> numParejas;
	}

}