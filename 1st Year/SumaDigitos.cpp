//DG05 Oscar Diaz Ribagorda

#include <iostream>
#include <string>

using namespace std;

int main() {
	int total = 0, numVeces = 0;
	string num = "";

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) {
		cin >> num;
		for (int j = 0; j < num.size(); ++j) {
			total += int(num.at(j) - '0');
		}
		cout << total << '\n';
		total = 0;
	}
	return 0;
}