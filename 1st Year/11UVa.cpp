#include <iostream>
#include <string>
#include <cmath>

using namespace std;

bool isArmstrong(string num) {
	long int mult = 1;
	long int calculo = 0;
	long int numero = 0;
	
	for (int i = num.size() - 1; i >= 0; --i) {
		numero += int(num[i] - '0') * mult;
		mult *= 10;
		calculo += pow(int(num[i] - '0'), num.size());
	}
	if (calculo == numero) return true;
	else return false;
}

int main() {
	int numVeces = 0;
	string num = "";

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) {
		cin >> num;
		if (isArmstrong(num)) cout << "Armstrong\n";
		else cout << "Not Armstrong\n";
	}

	return 0;
}