#include <iostream>

using namespace std;

int main() {
	char c = ' ';
	char t = ' ';
	int veces = 0;

	cin.get(c);

	while (c >= '1' && c <= '4') {
		for (int i = 0; i < 5; ++i) {
			cin >> t;
			if (t == c) ++veces;
		}
		cout << veces << '\n';
		veces = 0;

		cin.get(c);
		cin.get(c);
	}

	return 0;
}