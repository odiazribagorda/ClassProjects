// DG05 Oscar Diaz Ribagorda

#include <iostream>
#include <string>

using namespace std;

int main() {
	int numVeces = 0, size = 0, cont = 0;
	string str = "";
	char aux = ' ';

	cin >> numVeces;
	cin.get(aux);
	
	for (int i = 0; i < numVeces; ++i) {
		getline(cin, str);

		for (int j = 0; j < str.size(); ++j) {
			while (j < str.size() - 1 && str.at(j) == str.at(j + 1)) {
				++cont;
				++j;
			}
			j -= cont;
			str.erase(j, cont);
			
			cont = 0;

		}

		cout << str << '\n';
	}

	return 0;
}