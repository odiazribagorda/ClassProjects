/*
Author: Oscar Diaz Ribagorda (ID: 1966444)

File: main.cpp

Description: Contains the main execution of the program. Uses the European Option class to execute the operations
descrived in the project description sheet. The project is not complete (didn´t implement the alternative model for
pricing).
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Date.h"
#include "EuropeanOption.h"

using namespace std;

// Type defined to be able to read Prices associated with the time the correspond to.
typedef pair<int, double> DatedPrice;

const int givenStrikes[] = { 9100, 9500, 9800, 10700, 10750, 10800, 10850, 10900, 11100, 11400, 12200, 12550, 13750, 16000 };

// Reads an option with given strike price into a DatedPrice vector from the original .csv file.
void readOption(vector<DatedPrice> & v, int strike) {
	ifstream file;
	file.open("18092020_DAX_" + to_string(strike) + ".csv");
	int time;
	double close, aux;
	char c = ' '; string s;
	file >> s;
	while (file.good() && file >> time >> c >> aux >> c >> aux >> c >> aux >> c >> close >> c >> s) {
		v.push_back({ time, close });
	}
	file.close();
}

// Reads the DAX.csv file into a DatedPrice vector.
void readDAX(vector<DatedPrice> & v) {
	ifstream file;
	file.open("DAX.csv");
	int time;
	double close, aux;
	char c = ' '; string s;
	file >> s;
	while (file.good() && file >> time >> c >> aux >> c >> aux >> c >> aux >> c >> close >> c >> aux) {
		v.push_back({ time, close });
	}
	file.close();
}

// Writes the implied volatility of European options in a .csv file with the name option + a given string data.
void writeOptions(vector<EuropeanOption*> & v, string data) {
	ofstream fileOut;
	fileOut.open("option" + data + ".csv");
	fileOut << "Time,Implied Volatility\n";
	for (int i = v.size() - 1; i >= 0; --i) {
		fileOut << v[i]->getCurrentTime() << "," << v[i]->getVolatility();
		fileOut << '\n';
	}
	fileOut.close();
}

void writeVolatilityStrikeComparison(vector<vector<DatedPrice>> const& volatilities) {
	for (int i = 0; i < volatilities[0].size(); ++i) {
		ofstream fileOut;
		fileOut.open("option" + to_string(volatilities[0][i].first) + ".csv");

		fileOut << "Strike,Implied Volatility\n";
		for (int j = 0; j < size(givenStrikes); ++j) {
			fileOut << givenStrikes[j] << "," << volatilities[j][i].second;
			fileOut << '\n';
		}
		fileOut.close();
	}
}

// Does the delta hedge experiment specified on the project. There´s an option to use a fixed amount of euros to start with.
void deltaHedgeExperiment(vector<DatedPrice> & stock, double strike, Date & expiry, double intRate, double portfPrice = 0) {
	cout << "DELTA HEDGING EXPERIMENT\nOption chosen (strike price): " << strike << "\n\n";

	vector<DatedPrice> optionPrice;
	readOption(optionPrice, strike);
	EuropeanCall call;
	EuropeanOption* op = &call;

	op->initialisePricedOption(stock[stock.size() - 1].second, strike, stock[stock.size() - 1].first, expiry.getIntDate(), intRate, optionPrice[optionPrice.size() - 1].second);
	double delta = op->DeltaBlackScholes();

	double portfolioPrice;
	if (portfPrice == 0) {
		portfolioPrice = optionPrice[optionPrice.size() - 1].second - delta * stock[stock.size() - 1].second;
	}
	else portfolioPrice = portfPrice;

	cout << "Portfolio(t1): " << portfolioPrice << '\n';

	for (int i = 1; i < stock.size(); ++i) {
		portfolioPrice += (optionPrice[optionPrice.size() - i - 1].second - optionPrice[optionPrice.size() - i].second) - delta * (stock[stock.size() - i - 1].second - stock[stock.size() - i].second);
		cout << "Portfolio(t" << i + 1 << "): " << portfolioPrice << '\n';

		op->initialisePricedOption(stock[i].second, strike, stock[i].first, expiry.getIntDate(), intRate, optionPrice[i].second);
		double delta = op->DeltaBlackScholes();
	}

	cout << "\nProgram ended. Press ENTER to exit...\n";
	char c = ' '; cin.get(c);
}

// NOT USED IN THE PROJECT
// This is a test for the delta hedging experiment of a put option with stock developing with the values specified in Stock[]. In 24 steps of time.
void testForDeltaHedging() {
	// Test for delta hedging
	double ir = 0.01;
	double Strike = 150;
	double vol = 0.4;
	int numSteps = 24;
	double Stock[] = { 162, 162.91, 182.66, 190.81, 209.12, 187.35, 182.89, 197.80,
		196.19, 216.03, 205.62, 220.34, 187.62, 182.25, 175.81, 169.68, 192.22, 210.51,
		214.92, 219.71, 232.45, 234.46, 231.06, 216.89, 218.39 };
	cout << size(Stock) << '\n';

	for (int i = 0; i < numSteps; ++i) {
		EuropeanPut put;
		EuropeanOption* op = &put;
		op->initialiseOption(Stock[i], Strike, i, numSteps + 1, vol, ir);
		op->setTime(1 - ((double)i) / numSteps);
		double delta = op->DeltaBlackScholes();
		cout << i << ' ' << 1 - ((double)i) / numSteps << ' ' << Stock[i] << ' ' << op->d1() << ' ' << delta << ' ' << Stock[i] * (-delta) << '\n';
	}
	cout << "\nProgram ended. Press ENTER to exit...\n";
	char c = ' '; cin.get(c);

}

int main() {
	Date expiry;
	expiry.setDate(tDate{ 18,9,2020 });
	double intRate = 0.004;
	
	vector<DatedPrice> DAX;
	readDAX(DAX);

	vector<vector<DatedPrice>> volatilities;

	// This loop, reads options and calculates implied volatilies for each time step and for every strike price.
	for (int i = 0; i < size(givenStrikes); ++i) {
		vector<DatedPrice> volatility;

		vector<EuropeanOption*> v;
		vector<DatedPrice> optionDev;
		readOption(optionDev, givenStrikes[i]);
		EuropeanCall* call;
		for (int j = optionDev.size() - 1; j >= 0; --j) {
			call = new EuropeanCall();
			call->initialisePricedOption(DAX[j].second, givenStrikes[i], DAX[j].first, expiry.getIntDate(), intRate, optionDev[j].second * 100);
			v.push_back(call);

			volatility.push_back({ call->getCurrentTime(), call->getVolatility() });
		}
		writeOptions(v, to_string(givenStrikes[i]));

		volatilities.push_back(volatility);
	}

	writeVolatilityStrikeComparison(volatilities);

	//deltaHedgeExperiment(DAX, givenStrikes[0], expiry, intRate);
	deltaHedgeExperiment(DAX, givenStrikes[0], expiry, intRate, 1000);

	
	return 0;
}