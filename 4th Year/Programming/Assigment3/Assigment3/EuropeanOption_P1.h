/*
Author: Oscar Diaz Ribagorda (ID: 1966444)

File: EuropeanOption_P1.h

Description: Solution to Problem 1 of Assigment 3. This includes the 3 different classes needed to define the different
European options with the relevant procedures like Price of the option and Delta risk of the option (option can be call
or put option). And some functions to be able to calculate the average prize in a portfolio and the average delta risk.
*/

#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_set>

using namespace std;

enum type2calculate { Price, Delta };
enum tPricing {BlackScholes};

int _id = 0;

class EuropeanOption {
public:

	virtual double DeltaBlackScholes() = 0;
	virtual double PriceBlackScholes() = 0;

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

	// Initialises the instance of a call, filling in the values for the different parameters.
	void initialiseOption(double SP, double SkP, double CT, double ET, double V, double D, double IR)
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

	double PriceOption(tPricing type = BlackScholes) {
		switch (type) {
		case BlackScholes: return PriceBlackScholes();
		}
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

	// Function that returns the value of the cumulative standard normal distribution function in x.
	double normalCDF(double x)
	{
		return erfc(-x / sqrt(2)) / 2;
	}
	// Calculates d1 a parameter needed to calculate the price of the Call and the different metrics.
	double d1()
	{
		return (log(s0 / X) + t * (r - q + sig * sig / 2)) / (sig * sqrt(t));
	}
	// Calculates d1 a parameter needed to calculate the price of the Call and the different metrics.
	double d2()
	{
		return d1() - sig * sqrt(t);
	}
};

class EuropeanCall : public EuropeanOption {
public:

	// Constructor of EuropeanCall objects, redefined to establish an ID number on each call.
	EuropeanCall()
	{
		ID = _id;
		++_id;
	}

	double PriceBlackScholes() {
		return s0 * exp(-q * t) * normalCDF(d1()) - X * exp(-r * t) * normalCDF(d2());
	}

	double DeltaBlackScholes() {
		return exp(-q * t) * normalCDF(d1());
	}

private:

};

class EuropeanPut : public EuropeanOption {
public:

	// Constructor of EuropeanCall objects, redefined to establish an ID number on each call.
	EuropeanPut()
	{
		ID = _id;
		++_id;
	}

	double PriceBlackScholes() {
		return X * exp(-r * t) * normalCDF(-d2()) - s0 * exp(-q * t) * normalCDF(-d1());
	}

	double DeltaBlackScholes() {
		return exp(-q * t) * (normalCDF(d1()) - 1);

	}

private:

};

double CalculatePortfolio(vector<EuropeanOption*> & portfolio, type2calculate type) {
	vector<pair<int, double>> availableOptions; // Vector containing the different Options in the portfolio with each prices.
	unordered_set<int> set; // I choose to build a set for better eficiency when searching for a Option (i.e. to see if it큦
							// being added already to the availableOptions list and to count how many times is being added).

	// FOR loop for analizing every Option in the portfolio. If it큦 a new Option it calculates the prize and adds it to the
	// available Options list. Then it adds the ID to the set to keep count of the times that Option has appeared.
	for (int i = 0; i < portfolio.size(); ++i)
	{
		if (set.count(portfolio[i]->getID()) == 0)
			switch (type) {
				case Price: availableOptions.push_back({ portfolio[i]->getID(), portfolio[i]->PriceOptionAnalytical() });
				case Delta: availableOptions.push_back({ portfolio[i]->getID(), portfolio[i]->DeltaAnalytical() });
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

double PricePortfolioOfOptions(vector<EuropeanOption*> & portfolio) {
	return CalculatePortfolio(portfolio, type2calculate::Price);
}

double CalculateDeltaRisk(vector<EuropeanOption*> & portfolio) {
	return CalculatePortfolio(portfolio, type2calculate::Delta);
}

