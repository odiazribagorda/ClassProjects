#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<int> matriz;
	bool simetrico = true;
	char aux = ' ';
	int numVeces = 0, N = 0, num = 0, D = 0, simk = 0;

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) {
		cin >> aux >> aux;
		cin >> N;

		if (N % 2 == 0) D = N;
		else D = N + 1;

		for (int j = 0; j < N * N; ++j) {
			cin >> num;
			matriz.push_back(num);
		}
		for (int k = 0; k < N * N; ++k) {
			simk = (N * N - 1) - k;
			if (matriz[k] != matriz[simk]) simetrico = false;
		}

		cout << "Test #" << i + 1 << ": ";
		if (simetrico) cout << "Symmetric.\n";
		else cout << "Non-symmetric.\n";

		simetrico = true;
	}

}