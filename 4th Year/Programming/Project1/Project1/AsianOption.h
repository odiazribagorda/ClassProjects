#pragma once

/*
Author: Oscar Diaz Ribagorda (ID: 1966444)

File: AsianOption.h

Description: Contains the different classes and functions neccesary to price
and calculate delta risk in Asian Options.

Comment: Asian Options don´t have an analytic method to calculate prices or delta
so only the MC methods can be used.
*/

#include "Option.h"

class AsianOption : public Option {
public:

	virtual void pathsPayoff(vector<double> & pathsPayoff) = 0;

	// It initialises a vector with the prices for different paths. The different paths
	// are taken to use MC methods and the price is calculated by averaging the price
	// in the different discrete time points.
	void initialisePrices() {
		pathsPrices.clear();
		for (int i = 0; i < N; ++i) {
			vector<double> pathPrices;
			samplePathPrice(pathPrices);
			double sum = 0;
			for (int j = 0; j < pathPrices.size(); ++j) {
				sum += pathPrices[j];
			}
			pathsPrices.push_back(sum / pathPrices.size());
		}
	}

	void initialiseAsianOption(double SP, double SkP, double CT, double ET, double V, double D, double IR) {
		initialiseOption(SP, SkP, CT, ET, V, D, IR);
		initialisePrices();
	}

	double PriceOption() {
		return PriceOptionMC();
	}

	double PriceOptionMC() {
		double avgPrice = 0;
		for (int i = 0; i < pathsPrices.size(); ++i) {
			avgPrice += pathsPrices[i];
		}
		return avgPrice / N;
	}

	// No analytical way of calculating this.
	double PriceOptionAnalytical(double S = 0, double K = 0) {
		return 0;
	}

	// Delta Risk calculated doing an average of the deltas of the different paths.
	double DeltaRisk() {
		vector<double> payoffs;
		pathsPayoff(payoffs);

		double sum = 0;
		for (int i = 0; i < pathsPrices.size(); ++i) {
			if (payoffs[i] > 0) sum += (pathsPrices[i] / s0) * exp(-r * t);
		}

		return sum / pathsPrices.size();
	}

protected:

	vector<double> pathsPrices; // Prices of the diferent paths calculated as arithmetic asian options.
	
};

class AsianCall : public AsianOption {
public:

	// Constructor of EuropeanCall objects, redefined to establish an ID number on each call.
	AsianCall()
	{
		ID = _id;
		++_id;
	}

	void pathsPayoff(vector<double> & pathsPayoff) {
		pathsPayoff.clear();
		for (int i = 0; i < pathsPrices.size(); ++i) {
			pathsPayoff.push_back(max((pathsPrices[i] - X) * exp(-r * t), 0.0));
		}
	}

	double PayOffOptionMC() {
		return max(PriceOptionMC() - X, 0.0);
	}

private:

};

class AsianPut : public AsianOption {
public:

	// Constructor of EuropeanCall objects, redefined to establish an ID number on each call.
	AsianPut()
	{
		ID = _id;
		++_id;
	}

	void pathsPayoff(vector<double> & pathsPayoff) {
		pathsPayoff.clear();
		for (int i = 0; i < pathsPrices.size(); ++i) {
			pathsPayoff.push_back(max((X - pathsPrices[i]) * exp(-r * t), 0.0));
		}
	}

	double PayOffOptionMC() {
		return max(X - PriceOptionMC(), 0.0);
	}

private:

};
