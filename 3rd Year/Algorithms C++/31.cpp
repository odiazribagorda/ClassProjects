// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	string s1 = "", s2 = "";
	while (cin >> s1 >> s2) {
		vector<vector<int>> matriz(2, vector<int>(s1.size() + 1, 0));
		int mem1 = 1, mem2 = 0;
		for (int i = 1; i <= s2.size(); ++i) {
			for (int j = 1; j <= s1.size(); ++j) {
				if (s2[i - 1] == s1[j - 1]) {
					matriz[mem1][j] = matriz[mem2][j - 1] + 1;
				}
				else {
					matriz[mem1][j] = max(matriz[mem1][j - 1],
						matriz[mem2][j]);
				}
			}
			int aux = mem1;
			mem1 = mem2;
			mem2 = aux;
		}
		cout << matriz[mem2][s1.size()] << '\n';
	}

	return 0;
}