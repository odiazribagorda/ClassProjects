#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
	int x = 0, y = 0, r = 0, numVeces = 0;
	float dist = 0;

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) {
		cin >> x >> y >> r;
		dist = sqrt(x * x + y * y);
		dist = (roundf(dist * 10)) / 10;
		cout << fixed << setprecision(2) << r - dist << ' ' << r + dist << '\n';
	}


	return 0;
}