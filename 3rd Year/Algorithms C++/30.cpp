// Oscar Diaz Ribagorda (DG04)

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	string s = "";
	while (cin >> s) {
		vector<vector<int>> matriz(2, vector<int>(s.size(), 0));
		for (int i = 1; i < s.size(); ++i) {
			for (int j = s.size() - i - 1; j >= 0; j--) {
				int aux = matriz[0][j + i];
				if (s[j] == s[j + i]) {
					matriz[0][j + i] = matriz[1][(j + i) - 1];
				}
				else {
					matriz[0][j + i] = min(matriz[0][j + i],
						matriz[0][j + i - 1]) + 1;
				}
				matriz[1][j + i] = aux;
			}
		}
		cout << matriz[0][s.size() - 1] << '\n';
	}

	return 0;
}