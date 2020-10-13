/*
Author: Oscar Diaz Ribagorda (ID: 1966444)

File: main_P1.cpp

Description: Problem 1 of Problem Sheet 1. This program reads 2 vectors from console
and returns their means, standart deviations and their correlation. The sizes of the
vectors must be the same, if not, program gives an error.
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

// Comment: vectors are given to functions by constant reference to safe memory space, i.e
// we use the original reference of the vector without changing it and that way we don´t
// copy the values every time we use a function.

// Function for reading vector entries. An auxiliar character is used to end the insertion.
// There is many methods to read a vector, this method is chosen because I believe it´s more
// intuitive for the user.
void read(vector<double> & v, string name) {
	cout << "Insert values for vector " << name << " (separated by spaces, end the insertion by pressing ENTER):\n";
	char aux = ' ';
	double value = 0;
	while (aux != '\n') {
		cin >> value;
		v.push_back(value);
		cin.get(aux);
	}
}

// Calculates Mean of a vector of any size. Acumulates the sum and then divides by the size of the vector.
double calculateMean(vector<double> const& v) {
	double sum = 0;
	for (int i = 0; i < v.size(); ++i)
		sum += v[i];
	return sum / v.size();
}

// Calculates Variance of a vector. In order to do this the Mean is calculated first and then used to calculate
// the Variance the usual way.
double calculateVariance(vector<double> const& v) {
	double mean = calculateMean(v);
	double sum = 0;
	for (int i = 0; i < v.size(); ++i)
		sum += (v[i] - mean) * (v[i] - mean);
	return sum / v.size();
}

// Calculates Standart Deviation. Uses the method for square root (sqrt) of the libary <cmath>.
double calculateStandartDeviation(vector<double> const& v) {
	return sqrt(calculateVariance(v));
}

// Calculates Covariance between two vectors. It first has to calculate both Means and then execute the
// usual formula for calculating the Covariance.
double calculateCovariance(vector<double> const& v1, vector<double> const& v2) {
	double mean1 = calculateMean(v1);
	double mean2 = calculateMean(v2);
	double sum = 0;
	for (int i = 0; i < v1.size(); ++i)
		sum += (v1[i] - mean1) * (v2[i] - mean2);
	return sum / v1.size();
}

// Calculates Correlation between two vectors. It first calculates the Covariance between the two and divides
// by the product of the StandartDeviations (calculated here as well).
double calculateCorrelation(vector<double> const& v1, vector<double> const& v2) {
	double covariance = calculateCovariance(v1, v2);
	return covariance / (calculateStandartDeviation(v1) * calculateStandartDeviation(v2));
}


// Main function that runs the wanted program.
int main() {
	vector<double> x, y;
	
	read(x, "X");
	read(y, "Y");

	if (x.size() == y.size()) {
		cout << "Mean of X: " << calculateMean(x) << '\n';
		cout << "Mean of Y: " << calculateMean(y) << '\n';
		cout << "Standar Deviation of X: " << calculateStandartDeviation(x) << '\n';
		cout << "Standar Deviation of Y: " << calculateStandartDeviation(y) << '\n';
		cout << "Correlation between X and Y: " << calculateCorrelation(x, y) << '\n';
		cout << "END of program. Press ENTER to exit.\n";
		char aux = ' ';
		cin.get(aux);
	}
	// Asking to press ENTER to finish the program is done to make the program more user friendly.
	else {
		cout << "ERROR: Different vector sizes. Press ENTER to exit.\n";
		char aux = ' ';
		cin.get(aux);
	}

	return 0;
}