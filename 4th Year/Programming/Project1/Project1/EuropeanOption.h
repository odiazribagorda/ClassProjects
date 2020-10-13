#pragma once

/*
Author: Oscar Diaz Ribagorda (ID: 1966444)

File: EuropeanOption.h

Description: Contains the different classes and functions neccesary to price
and calculate delta risk on European Options.

*/

#include "Option.h"

class EuropeanOption : public Option {
public:

	double PriceOption() {
		return PriceOptionAnalytical();
	}

	double PriceOptionMC() {

		double avgPrice = 0;
		for (int i = 0; i < N; ++i) {
			vector<double> pathPrices;
			samplePathPrice(pathPrices);
			avgPrice += pathPrices[pathPrices.size() - 1];
		}

		return avgPrice / N;
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

	double PriceOptionAnalytical(double S = 0, double K = 0) {
		double s, x;
		if (S != 0) s = S;
		else s = s0;
		if (K != 0) x = K;
		else x = X;

		return s * exp(-q * t) * normalCDF(d1(s, x)) - x * exp(-r * t) * normalCDF(d2());
	}

	double DeltaRisk() {
		return exp(-q * t) * normalCDF(d1());
	}

	static double PriceEuropeanCall(Option & op) {
		return op.getSharePrice() * exp(-op.getDividend() * op.getTime()) * op.normalCDF(op.d1()) - op.getStrikePrice() * exp(-op.getInterestRate() * op.getTime()) * op.normalCDF(op.d2());
	}

	double PayOffOptionMC() {
		return max(PriceOptionMC() - X, 0.0);
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

	double PriceOptionAnalytical(double S = 0, double K = 0) {
		double s, x;
		if (S != 0) s = S;
		else s = s0;
		if (K != 0) x = K;
		else x = X;

		return x * exp(-r * t) * normalCDF(-d2()) - s * exp(-q * t) * normalCDF(-d1(s, x));
	}

	double DeltaRisk() {
		return exp(-q * t) * (normalCDF(d1()) - 1);
	}

	static double PriceEuropeanPut(Option & op) {
		return op.getStrikePrice() * exp(-op.getInterestRate() * op.getTime()) * op.normalCDF(-op.d2()) - op.getSharePrice() * exp(-op.getDividend() * op.getTime()) * op.normalCDF(-op.d1());
	}

	double PayOffOptionMC() {
		return max(X - PriceOptionMC(), 0.0);
	}

private:

};

