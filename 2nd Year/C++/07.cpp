// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include "07.h"
#include "deque_eda.h"

using namespace std;

int main() {
	int n = 0;
	while (cin >> n) {
		Extension<int> lista;
		while (n != 0) {
			lista.push_back(n);
			cin >> n;
		}
		lista.invierte();
		lista.mostrar();
	}
	return 0;
}