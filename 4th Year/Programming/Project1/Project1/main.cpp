/*
Author: Oscar Diaz Ribagorda (ID: 1966444)

File: main.cpp

Description: Initialises a portfolio of Options and calculates the price and
Delta Risk of it, then displays on the console.

*/

#include "AsianOption.h"
#include "BarrierOption.h"
#include "EuropeanOption.h"
#include "Option.h"

int main() {
	EuropeanCall call1;
	call1.initialiseOption(50, 50, 0, 1, 0.2, 0, 0.1);
	BarrierCall bar1(upNin, 70);
	bar1.initialiseOption(50, 50, 0, 1, 0.2, 0, 0.1);
	BarrierCall bar2(upNout, 70);
	bar2.initialiseOption(50, 50, 0, 1, 0.2, 0, 0.1);
	AsianCall asian1;
	asian1.initialiseAsianOption(50, 50, 0, 1, 0.2, 0, 0.1);
	
	EuropeanCall call2;
	call2.initialiseOption(40, 35, 0, 2, 0.3, 0, 0.1);
	EuropeanPut put1;
	put1.initialiseOption(40, 35, 0, 2, 0.3, 0, 0.1);
	EuropeanPut put2;
	put2.initialiseOption(40, 35, 0, 2, 0.3, 0, 0.1);
	BarrierPut bar3(upNin, 55);
	bar3.initialiseOption(40, 35, 0, 2, 0.3, 0, 0.1);
	BarrierPut bar4(upNout, 55);
	bar4.initialiseOption(40, 35, 0, 2, 0.3, 0, 0.1);
	BarrierPut bar5(downNin, 30);
	bar5.initialiseOption(40, 35, 0, 2, 0.3, 0, 0.1);
	BarrierPut bar6(downNout, 30);
	bar6.initialiseOption(40, 35, 0, 2, 0.3, 0, 0.1);
	AsianPut asian2;
	asian2.initialiseAsianOption(40, 35, 0, 2, 0.3, 0, 0.1);

	vector<Option*> portfolio;
	for (int i = 0; i < 3; ++i) portfolio.push_back(&call1);
	for (int i = 0; i < 2; ++i) portfolio.push_back(&bar1);
	for (int i = 0; i < 1; ++i) portfolio.push_back(&bar2);
	for (int i = 0; i < 12; ++i) portfolio.push_back(&asian1);
	for (int i = 0; i < 5; ++i) portfolio.push_back(&call2);
	for (int i = 0; i < 3; ++i) portfolio.push_back(&put1);
	for (int i = 0; i < 7; ++i) portfolio.push_back(&put2);
	for (int i = 0; i < 3; ++i) portfolio.push_back(&bar3);
	for (int i = 0; i < 1; ++i) portfolio.push_back(&bar4);
	for (int i = 0; i < 3; ++i) portfolio.push_back(&bar5);
	for (int i = 0; i < 1; ++i) portfolio.push_back(&bar6);
	for (int i = 0; i < 12; ++i) portfolio.push_back(&asian2);

	cout << "The price of the portfolio is: " << PricePortfolioOfOptions(portfolio) << '\n';
	cout << "The delta risk of the portfolio is: " << CalculateDeltaRisk(portfolio) << '\n';

	cout << "\nProgram ended. Press ENTER to exit...\n";
	char aux = ' '; cin.get(aux);

	return 0;
}