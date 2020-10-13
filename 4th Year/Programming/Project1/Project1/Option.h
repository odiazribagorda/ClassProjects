#pragma once

/*
Author: Oscar Diaz Ribagorda (ID: 1966444)

File: Option.h

Description: Contains an abstract class that handles all the operations that
can be done to an Option and contains the value for the common parameters
between options. It also contains a method to calculate the price of a portfolio
of Options and the Delta Risk of the same.
*/

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_set>
#include <random>
#include <algorithm>



using namespace std;

enum type2calculate { Price, Delta };

int _id = 0;

class Option {
public:

	virtual double PriceOption() = 0;
	virtual double PriceOptionAnalytical(double S = 0, double K = 0) = 0;
	virtual double PriceOptionMC() = 0;
	virtual double DeltaRisk() = 0;
	virtual double PayOffOptionMC() = 0;

	// All the accesor functions to the different accesable parameters of the object.
	double getSharePrice()
	{
		return s0;
	}
	double getStrikePrice()
	{
		return X;
	}
	double getCurrentTime()
	{
		return ct;
	}
	double getExpiryTime()
	{
		return et;
	}
	double getTime() {
		return t;
	}
	double getVolatility()
	{
		return sig;
	}
	double getDividend()
	{
		return q;
	}
	double getInterestRate()
	{
		return r;
	}
	int getID()
	{
		return ID;
	}
	void setSharePrice(double data)
	{
		s0 = data;
	}
	void setStrikePrice(double data)
	{
		X = data;
	}
	void setCurrentTime(double data)
	{
		ct = data;
	}
	void setExpiryTime(double data)
	{
		et = data;
	}
	void setVolatility(double data)
	{
		sig = data;
	}
	void setDividend(double data)
	{
		q = data;
	}
	void setInterestRate(double data)
	{
		r = data;
	}
	void setTime() // This setter is added to calculate the time until expiring (since the initialiser asks
	{			   // for current time and expiry time).
		t = et - ct;
	}

	// Initialises the instance of an option, filling in the values for the different parameters.
	virtual void initialiseOption(double SP, double SkP, double CT, double ET, double V, double D, double IR)
	{
		setSharePrice(SP);
		setStrikePrice(SkP);
		setCurrentTime(CT);
		setExpiryTime(ET);
		setVolatility(V);
		setDividend(D);
		setInterestRate(IR);
		setTime();
	}

	// Function that returns the value of the cumulative standard normal distribution function in x.
	double normalCDF(double x)
	{
		return erfc(-x / sqrt(2)) / 2;
	}
	// Calculates d1 a parameter needed to calculate the price of the Call and the different metrics.
	double d1(double S = 0, double K = 0)
	{
		double s, x;
		if (S != 0) s = S;
		else s = s0;
		if (K != 0) x = K;
		else x = X;

		return (log(s / x) + t * (r - q + sig * sig / 2)) / (sig * sqrt(t));
	}
	// Calculates d1 a parameter needed to calculate the price of the Call and the different metrics.
	double d2()
	{
		return d1() - sig * sqrt(t);
	}

protected:
	int ID; // ID of the Call. This way we will be able to tell if a call is equal or different to another one.

	double s0; // Share Price
	double ct; // Current Time. In years.
	double et; // Expiry Time. In years.
	double X; // Strike Price
	double sig; // Volatility
	double q; // Dividend
	double r; // Interest Rate
	double t; // Time until expiring. (Expiry time - Current time) In Years.
	const int T = 365; // Number of days per year (depends on if we want to count calendar days or trading days).

	const int N = 10; // number of paths used to calculate the average price.
	const int M = 10; // precision of each sample price.

	// Simulates the way the a stock matures with a random parameter
	// and returns a vector with the prices at diferent discrete times.
	// Using this function more than one time will give us different paths that
	// the price of the stock could follow.
	void samplePathPrice(vector<double> & pathPrices) {
		random_device random_dev;
		mt19937 random_gen(random_dev());
		normal_distribution<double> dis(0, 1);
		double rand = dis(random_gen);

		double S = s0;
		for (int i = 0; i < M; ++i) {
			S = S * exp((r - (sig*sig) / 2)*(t / M) + sig * sqrt(t / M) * rand); // This is how the price of the asset matures. (geometric Brownian).
			pathPrices.push_back(S);
		}
	}
};

double CalculatePortfolio(vector<Option*> & portfolio, type2calculate type) {
	vector<pair<int, double>> availableOptions; // Vector containing the different Options in the portfolio with each prices.
	unordered_set<int> set; // I choose to build a set for better eficiency when searching for a Option (i.e. to see if it큦
							// being added already to the availableOptions list and to count how many times is being added).

	// FOR loop for analizing every Option in the portfolio. If it큦 a new Option it calculates the prize and adds it to the
	// available Options list. Then it adds the ID to the set to keep count of the times that Option has appeared.
	for (int i = 0; i < portfolio.size(); ++i)
	{
		if (set.count(portfolio[i]->getID()) == 0)
			switch (type) {
			case Price: availableOptions.push_back({ portfolio[i]->getID(), portfolio[i]->PriceOption() }); break;
			case Delta: availableOptions.push_back({ portfolio[i]->getID(), portfolio[i]->DeltaRisk() }); break;
			}
		set.insert(portfolio[i]->getID());
	}

	// Another FOR loop now for going through the available options list and adding each of the Option큦 price weighted
	// by the number of times that it큦 appeared (compared to the number of Options in total).
	double price = 0;
	for (int i = 0; i < availableOptions.size(); ++i)
	{
		price += availableOptions[i].second * set.count(availableOptions[i].first) / set.size();
	}

	return price;
}

double PricePortfolioOfOptions(vector<Option*> & portfolio) {
	return CalculatePortfolio(portfolio, type2calculate::Price);
}

double CalculateDeltaRisk(vector<Option*> & portfolio) {
	return CalculatePortfolio(portfolio, type2calculate::Delta);
}

