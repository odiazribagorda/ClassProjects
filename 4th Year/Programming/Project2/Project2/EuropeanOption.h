/*
Author: Oscar Diaz Ribagorda (ID: 1966444)

File: EuropeanOption.h

Description: This document contains all classes and functions that operate with European Options (both Call and Put).
Also contains a function to delta hedge a portfolio of options and functions to calculate the average delta of a portfolio
and the weighted price of a portfolio.
*/

#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <unordered_set>

using namespace std;

enum type2calculate { Price, Delta };
enum tPricing {BlackScholes};

int _id = 0;

class EuropeanOption {
public:

	virtual double DeltaBlackScholes() = 0;

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
	double getPrice() {
		return P;
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
	void setTime(double time = -1) // This setter is added to calculate the time in percentage per year.
	{
		if (time < 0)
			t = (et - ct) / T;
		else t = time;
	}
	void setPrice(double Price) {
		P = Price;
	}

	// Initialises the instance of a call, filling in the values for the different parameters.
	void initialiseOption(double SP, double SkP, double CT, double ET, double V, double IR, double D = 0)
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
	void initialisePricedOption(double SP, double SkP, double CT, double ET, double IR, double Price, double V = -1, double D = 0)
	{
		setSharePrice(SP);
		setStrikePrice(SkP);
		setCurrentTime(CT);
		setExpiryTime(ET);
		setDividend(D);
		setInterestRate(IR);
		setTime();
		setPrice(Price);
		if (V < 0) setVolatility(impliedVol());
		else setVolatility(V);
	}

	// Updated the time and the implied volatility for the new current time.
	void updateTime(double ct) {
		setCurrentTime(ct);
		setTime();
		setVolatility(impliedVol());

	}

	double PriceOption(tPricing type = BlackScholes) {
		switch (type) {
		case BlackScholes: return PriceBlackScholes();
		}
	}

	double impliedVol() {
		double v_aux = getVolatility();

		double v = 1; // Initial value for the implied volatility.

		double dif;
		do {
			setVolatility(v);
			dif = PriceBlackScholes() - P;
			v = v - dif / vega();
		} while (dif > ADMISSIBILITY); // Loops until the estimated price is close enough to the real price.

		setVolatility(v_aux);
		return v;
	}

	// Calculates d1 a parameter needed to calculate the price of the Call and the different metrics.
	double d1()
	{
		return (log(s0 / X) + t * (r - q + sig * sig / 2)) / (sig * sqrt(t));
	}

protected:
	int ID; // ID of the Call. This way we will be able to tell if a call is equal or different to another one.

	double P; // Price of the option.
	double s0; // Share Price
	double ct; // Current Time. In years.
	double et; // Expiry Time. In years.
	double X; // Strike Price
	double sig; // Volatility
	double q; // Dividend
	double r; // Interest Rate
	double t; // Time until expiring. (Expiry time - Current time) In Years.
	const int T = 365; // Number of days per year (depends on if we want to count calendar days or trading days).
	const double ADMISSIBILITY = 0.5; // Admissibility for the Newton-Raphson method (implied volatility).

	virtual double PriceBlackScholes() = 0;

	// Function that returns the value of the cumulative standard normal distribution function in x.
	double normalCDF(double x)
	{
		return erfc(-x / sqrt(2)) / 2;
	}
	// Calculates d1 a parameter needed to calculate the price of the Call and the different metrics.
	/*
	double d1()
	{
		return (log(s0 / X) + t * (r - q + sig * sig / 2)) / (sig * sqrt(t));
	}
	*/
	// Calculates d1 a parameter needed to calculate the price of the Call and the different metrics.
	double d2()
	{
		return d1() - sig * sqrt(t);
	}

	double vega() {
		return s0 * sqrt(t) * exp(-d1() * d1() / 2) / sqrt(2 * M_PI);
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

private:

	double PriceBlackScholes() {
		return s0 * exp(-q * t) * normalCDF(d1()) - X * exp(-r * t) * normalCDF(d2());
	}

	double DeltaBlackScholes() {
		return exp(-q * t) * normalCDF(d1());
	}

};

class EuropeanPut : public EuropeanOption {
public:

	// Constructor of EuropeanCall objects, redefined to establish an ID number on each call.
	EuropeanPut()
	{
		ID = _id;
		++_id;
	}

private:

	double PriceBlackScholes() {
		return X * exp(-r * t) * normalCDF(-d2()) - s0 * exp(-q * t) * normalCDF(-d1());
	}

	double DeltaBlackScholes() {
		return exp(-q * t) * (normalCDF(d1()) - 1);

	}

};

// For a given portfolio, calculates the total delta of the position based on the delta for each option and the quantity of each option.
// The hedge returned represents the number of shares of the underlying stock that you need to buy (if the returned number is positive)
// or sell (if the returned number is negative).
double deltaHedge(vector<EuropeanOption*> const& portfolio) {
	vector<pair<int, double>> availableOptions; // Vector containing the different Options in the portfolio with each delta.
	unordered_set<int> set;

	for (int i = 0; i < portfolio.size(); ++i)
	{
		if (set.count(portfolio[i]->getID()) == 0)
			availableOptions.push_back({ portfolio[i]->getID(), portfolio[i]->DeltaBlackScholes() });
		set.insert(portfolio[i]->getID());
	}

	double hedge = 0;
	for (int i = 0; i < availableOptions.size(); ++i)
	{
		hedge += availableOptions[i].second * set.count(availableOptions[i].first);
	}

	return - hedge * 100;
}

double CalculatePortfolio(vector<EuropeanOption*> & portfolio, type2calculate type) {
	vector<pair<int, double>> availableOptions; // Vector containing the different Options in the portfolio.
	unordered_set<int> set; // I choose to build a set for better eficiency when searching for a Option (i.e. to see if it큦
							// being added already to the availableOptions list and to count how many times is being added).

	// FOR loop for analizing every Option in the portfolio. If it큦 a new Option it calculates the prize (or delta) and adds it to the
	// available Options list. Then it adds the ID to the set to keep count of the times that Option has appeared.
	for (int i = 0; i < portfolio.size(); ++i)
	{
		if (set.count(portfolio[i]->getID()) == 0)
			switch (type) {
			case Price: availableOptions.push_back({ portfolio[i]->getID(), portfolio[i]->PriceOption() });
			case Delta: availableOptions.push_back({ portfolio[i]->getID(), portfolio[i]->DeltaBlackScholes() });
			}
		set.insert(portfolio[i]->getID());
	}

	// Another FOR loop now for going through the available options list and adding each of the Option큦 price (or delta) weighted
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