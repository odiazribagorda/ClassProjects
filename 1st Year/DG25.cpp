// DG05 Oscar Diaz Ribagorda

#include <iostream>
#include <vector>

using namespace std;

int main() {
	int max = 0, cont = 0, num = 0;
	vector<int> v;

	cin >> num;
	while (num != 0) {
		max = num;
		while (num != 0) {
			if (num > max) {
				max = num;
				cont = 1;
			}
			else if (num == max) ++cont;
			cin >> num;
		}
		cout << max << ' ' << cont << '\n';
		cont = 0;
		cin >> num;
	}

	return 0;
}