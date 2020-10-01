#include <iostream>

using namespace std;

int main() {
	int dia = 1;
	int d = 0, m = 0;
	int numVeces = 0;

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) {
		cin >> m >> d;

		switch (m) {
		case 1: dia = dia + (d - 10) % 7; break;
		case 2: dia = dia + (d - 21) % 7; break;
		case 3: dia = dia + (d + 28 - 21) % 7; break;
		case 4: dia = dia + (d - 4) % 7; break;
		case 5: dia = dia + (d - 9) % 7; break;
		case 6: dia = dia + (d - 6) % 7; break;
		case 7: dia = dia + (d - 11) % 7; break;
		case 8: dia = dia + (d - 8) % 7; break;
		case 9: dia = dia + (d - 5) % 7; break;
		case 10: dia = dia + (d - 10) % 7; break;
		case 11: dia = dia + (d - 7) % 7; break;
		case 12: dia = dia + (d - 12) % 7; break;
		}

		switch (dia) {
		case 1: cout << "Monday\n"; break;
		case 2:;
		case -5: cout << "Tuesday\n"; break;
		case 3:;
		case -4: cout << "Wednesday\n"; break;
		case 4:;
		case -3: cout << "Thursday\n"; break;
		case 5:;
		case -2: cout << "Friday\n"; break;
		case 6:;
		case -1: cout << "Saturday\n"; break;
		case 7:;
		case 0: cout << "Sunday\n"; break;
		}
	}

	return 0;
}