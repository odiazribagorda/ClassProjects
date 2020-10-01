//DG05 Oscar Diaz Ribagorda

#include <iostream>
#include <string>

using namespace std;

int main() {
	string str = "";
	int i = 0;
	
	cin >> str;

	while (str != "XXX") {
		for (i = 0; i < str.size() - 1 && str.at(i) != str.at(i + 1); ++i);
		if (i == str.size() - 1)
			cout << "NO\n";
		else cout << i << '\n';
		
		cin >> str;
	}
	return 0;
}