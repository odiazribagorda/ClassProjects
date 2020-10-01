#include <iostream>

using namespace std;

int main() {
	int numVeces = 0, numFlips = 0;
	bool anterioresFelices = false;
	char mander = ' ';

	cin >> numVeces;
	cin.get(mander);

	for (int i = 1; i <= numVeces; ++i) {
		numFlips = 0;

		cin.get(mander);
		if (mander == '+') anterioresFelices = true;
		else anterioresFelices = false;

		while (mander != '\n') {
			if (mander == '-' && anterioresFelices) {
				anterioresFelices = false;
				++numFlips;
			}
			else if (mander == '+' && !anterioresFelices) {
				anterioresFelices = true;
				++numFlips;
			}
			cin.get(mander);
		}

		if (!anterioresFelices) ++numFlips;

		cout << "Case #" << i << ": " << numFlips << '\n';
	}
	return 0;
}