/*
Author: Oscar Diaz Ribagorda (ID: 1966444)

File: main_P1.cpp

Description: Solution to Problem 1 of Assigment 3. This includes the main function to test the procedures in
the European Option class. This is don by calculating the average price and delta risk of a portfolio given in
the problem description.
*/

#include "EuropeanOption_P1.h"

int main() {
	EuropeanCall call1, call2;
	EuropeanPut put1, put2;

	call1.initialiseOption(50, 50, 0, 1, 0.5, 0.2, 0.1);
	call2.initialiseOption(50, 40, 0, 1.5, 0.6, 0.3, 0.1);
	put1.initialiseOption(50, 50, 0, 1, 0.5, 0.2, 0.1);
	put2.initialiseOption(50, 40, 0, 1.5, 0.6, 0.3, 0.1);

	vector<EuropeanOption*> portfolio;

	for (int i = 0; i < 3; ++i) portfolio.push_back(&call1);
	for (int i = 0; i < 5; ++i) portfolio.push_back(&call2);
	for (int i = 0; i < 5; ++i) portfolio.push_back(&put1);
	for (int i = 0; i < 7; ++i) portfolio.push_back(&put2);

	cout << "The Price of the portfolio is: " << PricePortfolioOfOptions(portfolio) << '\n';
	cout << "The Delta Risk of the portfolio is: " << CalculateDeltaRisk(portfolio) << "\n\n";

	cout << "Program ended. Press ENTER to exit...\n";
	char c = ' '; cin.get(c);

	return 0;
}