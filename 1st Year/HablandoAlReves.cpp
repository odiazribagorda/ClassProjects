//DG05 Oscar Diaz Ribagorda.

#include <iostream>
#include <string>

using namespace std;

int main() {
	string str = "", a = "";
	int numVeces = 0;
	char aux = ' ', c = ' ';

	cin >> numVeces;
	cin.get(aux);

	for (int i = 0; i < numVeces; ++i) {
		getline(cin, str);
		
		for (int j = 0; j < str.size(); ++j) {
			c = str.at(str.size() - 1 - j);
			if (islower(c))
				c = toupper(c);
			a = a + c;
		}

		cout << str.size() << ' ' << a << '\n';

		a = "";
	}
	
	return 0;
}