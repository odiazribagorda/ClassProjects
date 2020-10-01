#include <iostream>
#include <string>

using namespace std;

bool soniguales(string nombre1, string nombre2) {
	bool soniguales = true;
	for (int i = 0; i < nombre1.size(); ++i) {
		if (nombre1[i] != 'a' && nombre1[i] != 'e' && nombre1[i] != 'i' && nombre1[i] != 'o' && nombre1[i] != 'u' && nombre1[i] != nombre2[i])
			soniguales = false;
	}
	return soniguales;
}

int main() {
	int numVeces = 0;
	string nombre1 = "", nombre2 = "";

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) {
		cin >> nombre1 >> nombre2;
		if (nombre1.size() == nombre2.size() && soniguales(nombre1, nombre2)) cout << "Yes\n";
		else cout << "No\n";
	}


	return 0;
}