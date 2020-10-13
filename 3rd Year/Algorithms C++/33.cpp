// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int L = 0, N = 0;
	cin >> L >> N;
	while (L != 0 && N != 0) {
		vector<int> tabla(N + 2);
		tabla[0] = 0;
		for (int i = 1; i <= N; i++) {
			cin >> tabla[i];
		}
		tabla[N + 1] = L;
		vector<vector<int>> matriz(N + 2, vector<int>(N + 2, 0));
		for (int i = 2; i < N + 2; i++) {
			for (int j = i; j < N + 2; j++) {
				int minimo = matriz[j - i][j - i + 1] + matriz[j - i + 1][j];
				for (int k = j - i + 2; k < j; k++) {
					minimo = min(minimo, matriz[j - i][k] + matriz[k][j]);
				}
				matriz[j - i][j] = 2 * (tabla[j] - tabla[j - i]) + minimo;
			}
		}
		cout << matriz[0][N + 1] << '\n';

		cin >> L >> N;
	}
	return 0;
}