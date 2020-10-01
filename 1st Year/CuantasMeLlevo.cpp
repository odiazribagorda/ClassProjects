#include <iostream>
#include <string>

using namespace std;

int main() {
	int cont = 0;
	string num1 = "", num2 = "";
	cin >> num1 >> num2;
	while (num1 != "0" && num2 != "0") {
		for (; 0 < num1.size() && 0 < num2.size();) {
			if (num1.back() + num2.back() > '9') {
				++cont;
				num1.erase(num1.size() - 1, 1);
				num2.erase(num2.size() - 1, 1);
				if (num1 > "")
					++num1.back();
			}
			else {
				num1.erase(num1.size() - 1, 1);
				num2.erase(num2.size() - 1, 1);
			}
		}
		cout << cont << '\n';

		cont = 0;
	}

	return 0;
}