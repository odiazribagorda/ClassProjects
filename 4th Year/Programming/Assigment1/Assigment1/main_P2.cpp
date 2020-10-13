/*
Author: Oscar Diaz Ribagorda (ID: 1966444)

File: main_P2.cpp

Description: Problem 2 of Problem Sheet 1.
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

// Solution through the sum. Instead of having to do all the additions that you would going step by step,
// this is a more eficient implementetion where an acumulating value is used so we dont have to repeat some
// operations over and over.
int mySolution(int m) {
	int sum = 0, total = 0;
	for (int i = 1; i <= m; ++i) {
		sum += i * i * i;
		total += sum;
	}
	return total;
}

// Analytical Solution for the sum. (Given in the Problem question)
int analyticalSolution(int m) {
	return m * (1 + 6 * m + 3 * m * m) * (2 + m) * (1 + m) / 60;
}

// Runs the program, gets the value of M and shows the solution given by both algorithms.
// It also compares to see if they are both the same.
int main() {
	int m = 0;
	cout << "Enter the value (integer) of M: ";
	cin >> m;

	int s1 = mySolution(m), s2 = analyticalSolution(m);
	cout << "My Solution: " << s1 << '\n';
	cout << "Analytical Solution: " << s2 << '\n';

	if (s1 == s2) cout << "Both Solutions are the same as expected.\n";
	else cout << "They are different! Something went wrong.\n";
	cout << "Press ENTER to exit.\n";
	char aux = ' '; cin.get(aux); cin.get(aux);

	return 0;
}