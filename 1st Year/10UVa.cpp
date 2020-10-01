#include <iostream>
#include <cmath>

using namespace std;

int main() {
	float x0 = 0, y0 = 0, x1 = 0, y1 = 0, cx = 0, cy = 0, r = 0;
	int numVeces = 0;
	float length = 0, width = 0, Cx = 0, Cy = 0;

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) {
		cin >> x0 >> y0 >> x1 >> y1 >> cx >> cy >> r;
		length = x1 - x0;
		width = y1 - y0;
		Cx = cx - x0;
		Cy = cy - y0;

		if (length / width - 10.0 / 6 < 0.0001 && length / width - 10.0 / 6 > -0.0001 && length / r == 5 && Cx / length - 9.0 / 20 < 0.0001 && Cx / length - 9.0 / 20 > -0.0001 && width / Cy == 2)
			cout << "YES\n";
		else cout << "NO\n";
	}


	return 0;
}