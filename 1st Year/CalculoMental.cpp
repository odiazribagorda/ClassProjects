// DG05 Oscar Diaz Ribagorda

#include <iostream>

using namespace std;

int main() {
	int num = 0, total = 0, numVeces;
	char signo = ' ';

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) {
		cin >> total >> signo;

		while (signo != '.') {
			cin >> num;
			if (signo == '+')
				total += num;
			else if (signo == '-')
				total -= num;
			cin >> signo;
			if (signo == '.')
				cout << total << '\n';
			else cout << total << ", ";
		}
	}
	return 0;
}