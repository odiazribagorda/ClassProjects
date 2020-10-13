#pragma once

/*
Author: Oscar Diaz Ribagorda (ID: 1966444)

File: EuropeanCall_P2.h

Description: Solution to Problem 2 of Assigment 2. It contains the class EuropeanCall that allows you to
calculate the prize of a call option by the Black-Scholes method and also calculates the Greeks (Delta, Gamma, Theta and Rho)
which are risk metrics for the call.
*/

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_set>

using namespace std;

/* Comments: For this program I used <cmath> tools to calculate values for the exp (exponential function), sqrt (square root),
M_PI (approximated value of PI), erfc (complementary error function) and log (naiperian logarithm) for its convenience and
efficiency.
There is also different definitions for some of the Greek metrics calculated. For example, in the function for Theta, I decided
to use the one that divides by the days in a year to optain an "average" value. And in the function for Rho, I decided to
divide by 100 to optain the value in [0, 1].
*/

class EuropeanCall
{
public:
	// Constructor of EuropeanCall objects, redefined to establish an ID number on each call.
	EuropeanCall()
	{
		static int _id = 0;
		ID = _id;
		++_id;
	}

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
	void initialiseCall(double SP, double SkP, double CT, double ET, double V, double D, double IR)
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

	// Returns the Price for the Call obtained by the Black-Scholes method.
	double priceCallAnalytic()
	{
		return s0 * exp(-q * t) * normalCDF(d1()) - X * exp(-r * t) * normalCDF(d2());
	}

	// Returns the Delta for the Call.
	double callDeltaAnalytic()
	{
		return exp(-q * t) * normalCDF(d1());
	}

	// Returns the Gamma for the Call.
	double callGammaAnalytic()
	{
		return exp(-q / t) * exp(-d1() * d1() / 2) / (s0 * sig * sqrt(t) * sqrt(2 * M_PI));
	}

	// Returns the Theta for the Call. I divide by T (days in a year) to obtain this value.
	double callThetaAnalytic()
	{
		return (-(s0 * sig * exp(-q * t) * exp(-d1() * d1() / 2) / (2 * sqrt(t) * sqrt(2 * M_PI)))
			- r * X * exp(-r * t) * normalCDF(d2()) + q * s0 * exp(-q * t) * normalCDF(d1())) / T; //------------
	}

	// Returns the Rho for the Call. I divide by 100 to obtain this value.
	double callRhoAnalytic()
	{
		return X * t * exp(-r * t) * normalCDF(d2()) / 100;
	}

	// Calculates the weighted prize of a portfolio of Calls given a list of Calls. The price is weighted based
	// on the number of appearences of each Call. This implementation tries to go through the list as little
	// as posible while at the same time not having to calculate the price of the Call if it큦 already been calculated.
	static double pricePortfolioOfCalls(vector<EuropeanCall> & portfolio)
	{
		vector<pair<int, double>> availableCalls; // Vector containing the different Calls in the portfolio with each prices.
		unordered_set<int> set; // I choose to build a set for better eficiency when searching for a Call (i.e. to see if it큦
								// being added already to the availableCalls list and to count how many times is being added).

		// FOR loop for analizing every Call in the portfolio. If it큦 a new Call it calculates the prize and adds it to the
		// available Calls list. Then it adds the ID to the set to keep count of the times that Call has appeared.
		for (int i = 0; i < portfolio.size(); ++i)
		{
			if (set.count(portfolio[i].getID()) == 0)
				availableCalls.push_back({ portfolio[i].getID(), portfolio[i].priceCallAnalytic() });
			set.insert(portfolio[i].getID());
		}

		// Another FOR loop now for going through the available calls list and adding each of the Call큦 price weighted
		// by the number of times that it큦 appeared (compared to the number of Calls in total).
		double price = 0;
		for (int i = 0; i < availableCalls.size(); ++i)
		{
			price += availableCalls[i].second * set.count(availableCalls[i].first) / set.size();
		}

		return price;
	}

private:

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
