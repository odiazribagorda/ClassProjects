// DG05 Oscar Diaz Ribagorda

#include <iostream>
#include <string>

using namespace std;


int main() {
	// Declaración de variables.
	string str = "";
	char c = ' ';
	int numVeces = 0, a = 0;

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) {
		cin >> str;
		
		for (int i = 0; i < str.size(); ++i) {
			c = str.at(i);
			if (isupper(c))
				c = tolower(c);
			cout << c;
		}
		cout << '\n';
	}
	return 0;
}