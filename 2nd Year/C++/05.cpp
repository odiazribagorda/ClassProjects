// Oscar Diaz Ribagorda(DG04)

#include <iostream>
#include <string>
#include "05.h"

using namespace std;

int main() {

	char op = ' ';
	
	while (cin >> op) {
		if (op == 'N') {
			set < int > container;
			int n = 0;
			cin >> n;
			int num = 0;
			cin >> num;
			while (num != -1) {
				container.insert(num, n);
				cin >> num;
			}
			
			while (container.size() > 1) {
				cout << container.getMinor() << ' ';
				container.eraseMinor();
			}
			cout << container.getMinor() << '\n';
			container.eraseMinor();
		}
		else if (op == 'P') {
			set < string > container;
			int n = 0;
			cin >> n;
			string s = "";
			cin >> s;
			while (s != "FIN") {
				container.insert(s, n);
				cin >> s;
			}

			while (container.size() > 1) {
				cout << container.getMinor() << ' ';
				container.eraseMinor();
			}
			cout << container.getMinor() << '\n';
			container.eraseMinor();
		}
		

	}

	return 0;
}