#pragma once
/*
Author: Oscar Diaz Ribagorda (ID: 1966444)

File: BarrierOption.h

Description: Contains the different classes and functions neccesary to price
and calculate delta risks in the different types of Barrier Options.

Comment: The formulas used for the analytical solutions are following diferent
sources found in the internet. The formulas are quite confusing but suppose to
work, as the proof for them has been checked.
*/

#include "Option.h"
#include "EuropeanOption.h"

enum tBarrier { upNin, downNin, upNout, downNout };
enum tOption { Call, Put };

class BarrierOption : public Option {
public:

	double PriceOption() {
		return PriceOptionAnalytical();
	}

	// Uses different paths of price maturity. For each path, if the barrier has been breached,
	// the price will be either 0 or the Usual option price depending on the type of barrier.
	double PriceOptionMC() {

		double avgPrice = 0;
		for (int i = 0; i < N; ++i) {
			vector<double> pathPrices;
			samplePathPrice(pathPrices);
			double pathPrice;
			if (type == upNout || type == downNout) pathPrice = pathPrices[pathPrices.size() - 1];
			else pathPrice = 0;
			bool done = false;
			for (int j = 0; j < pathPrices.size() && !done; ++j) {
				switch (type) {
				case upNin: if (pathPrices[j] > H) { pathPrice = pathPrices[pathPrices.size() - 1]; done = true; } break;
				case downNin: if (pathPrices[j] < H) { pathPrice = pathPrices[pathPrices.size() - 1]; done = true; } break;
				case upNout: if (pathPrices[j] > H) { pathPrice = 0; done = true; } break;
				case downNout: if (pathPrices[j] < H) { pathPrice = 0; done = true; } break;
				}
			}
			avgPrice += pathPrice;
		}

		return avgPrice / N;
	}

protected:

	double H; // Barrier value.
	tBarrier type; // Type of Barrier option.
	tOption typeOp; // Type of Option Call or Put.

	void calculateDeltaParameters(double & A, double & B, double & C, double & D) {
		int ind1, ind2;
		if (type == downNin || type == downNout) ind1 = 1;
		else ind1 = -1;
		if (typeOp == Call) ind2 = 1;
		else ind2 = -1;

		double v = (r - q - sig * sig / 2) / (sig * sig);

		A = ind2 * exp(-q * t) * normalCDF(ind2 * d1(s0, X)) + exp(-q * t - d1(s0, X) * d1(s0, X) / 2) / (sig * sqrt(2 * M_PI * t))
			- X * exp(-r * t - (d1(s0, X) - sig * sqrt(t)) * (d1(s0, X) - sig * sqrt(t)) / 2) / (s0 * sig * sqrt(2 * M_PI * t));

		B = ind2 * exp(-q * t) * normalCDF(ind2 * d1(s0, H)) + exp(-q * t - d1(s0, H) * d1(s0, H) / 2) / (sig * sqrt(2 * M_PI * t))
			- X * exp(-r * t - (d1(s0, H) - sig * sqrt(t)) * (d1(s0, H) - sig * sqrt(t)) / 2) / (s0 * sig * sqrt(2 * M_PI * t));

		C = -(2 * ind1 + 1) * ind2 * exp(-q * t) * pow(H / s0, 2 * v + 2) * normalCDF(ind1 * d1(H*H / s0, X))
			- ind2 * ind1 * exp(-q * t) * pow(H / s0, 2 * v + 2) * exp(-d1(H*H / s0, X) * d1(H*H / s0, X) / 2) / (sig * sqrt(2 * M_PI * t))
			+ 2 * ind1 * ind2 * (X / s0) * exp(-r * t) * pow(H / s0, 2 * v) * normalCDF(ind1 * d1(H*H / s0, X) - ind1 * sig * sqrt(t))
			+ ind2 * ind1 * X * exp(-r * t) * pow(H / s0, 2 * v) * exp(-(d1(H*H / s0, X) - sig * sqrt(t)) * (d1(H*H / s0, X) - sig * sqrt(t)) / 2) / (s0 * sig * sqrt(2 * M_PI * t));

		D = -(2 * ind1 + 1) * ind2 * exp(-q * t) * pow(H / s0, 2 * v + 2) * normalCDF(ind1 * d1(H, s0))
			- ind2 * ind1 * exp(-q * t) * pow(H / s0, 2 * v + 2) * exp(-d1(H, s0) * d1(H, s0) / 2) / (sig * sqrt(2 * M_PI * t))
			+ 2 * ind1 * ind2 * (X / s0) * exp(-r * t) * pow(H / s0, 2 * v) * normalCDF(ind1 * d1(H, s0) - ind1 * sig * sqrt(t))
			+ ind2 * ind1 * X * exp(-r * t) * pow(H / s0, 2 * v) * exp(-(d1(H, s0) - sig * sqrt(t)) * (d1(H, s0) - sig * sqrt(t)) / 2) / (s0 * sig * sqrt(2 * M_PI * t));
	}
};

class BarrierCall : public BarrierOption {
public:

	// Constructor of EuropeanCall objects, redefined to establish an ID number on each call.
	BarrierCall(tBarrier t, double barrier)
	{
		ID = _id;
		++_id;

		type = t;
		H = barrier;
		typeOp = Call;
	}

	double PriceOptionAnalytical(double S = 0, double K = 0) {

		EuropeanCall auxCall;
		Option & auxC = auxCall;
		auxC.initialiseOption(s0, X, ct, et, sig, q, r);

		EuropeanPut auxPut;
		Option & auxP = auxPut;
		auxP.initialiseOption(s0, X, ct, et, sig, q, r);

		double v = r - sig * sig / 2;
		int indexHX = 0, indexXH = 0;
		if (H > X) indexHX = 1;
		if (X > H) indexXH = 1;

		switch (type) {
		case upNin: return pow((H / s0), 2 * v / (sig * sig)) * (auxP.PriceOptionAnalytical(H*H / s0, X)
			- auxP.PriceOptionAnalytical(H*H / s0, H) + (H - X) * exp(-r * t) * normalCDF(-d1(H, s0))) * indexHX
			+ auxC.PriceOptionAnalytical(s0, max(H, X)) + (max(H, X) - X) * exp(-r * t) * normalCDF(d1(s0, max(H, X)));
		case downNin: return pow((H / s0), 2 * v / (sig * sig)) * (auxC.PriceOptionAnalytical(H*H / s0, max(H, X))
			+ (max(H, X) - X) * exp(-r * t) * normalCDF(d1(H*H / s0, max(H, X)))) + (auxP.PriceOptionAnalytical(s0, X)
			- auxP.PriceOptionAnalytical(s0, H) + (H - X) * exp(-r * t) * normalCDF(-d1(s0, H))) * indexHX;
		case upNout: return (auxC.PriceOptionAnalytical(s0, X) - auxC.PriceOptionAnalytical(s0, H)
			- (H - X) * exp(-r * t) * normalCDF(d1(s0, H)) - pow((H / s0), 2 * v / (sig * sig))
			* (auxC.PriceOptionAnalytical(H*H / s0, X) - auxC.PriceOptionAnalytical(H*H / s0, H)
			- (H - X) * exp(-r * t) * normalCDF(d1(H, s0)))) * indexHX;
		case downNout: return auxC.PriceOptionAnalytical(s0, max(H, X)) - pow((H / s0), 2 * v / (sig * sig))
			* auxC.PriceOptionAnalytical(H*H / s0, max(H, X)) + (max(H, X) - X) * exp(-r * t)
			* (normalCDF(d1(s0, max(H, X)) - pow((H / s0), 2 * v / (sig * sig)) * normalCDF(d1(H*H / s0, max(H, X)))));
		}
	}

	double DeltaRisk() {
		double A, B, C, D;
		calculateDeltaParameters(A, B, C, D);
		switch (type) {
		case downNout: if (X < H) return B - D;
					   else return A - C;
		case upNout: if (X < H) return A - B + C - D;
					 else return 0;
		case downNin: if (X < H) return A - B + D;
					  else return C;
		case upNin: if (X < H) return B - C + D;
					else return A;
		}
	}

	double PayOffOptionMC() {
		return max(PriceOptionMC() - X, 0.0);
	}

private:

};

class BarrierPut : public BarrierOption {
public:

	// Constructor of EuropeanCall objects, redefined to establish an ID number on each call.
	BarrierPut(tBarrier t, double barrier)
	{
		ID = _id;
		++_id;

		type = t;
		H = barrier;
		typeOp = Put;
	}

	double PriceOptionAnalytical(double S = 0, double K = 0) {
		EuropeanCall auxCall;
		Option & auxC = auxCall;
		auxC.initialiseOption(s0, X, ct, et, sig, q, r);

		EuropeanPut auxPut;
		Option & auxP = auxPut;
		auxP.initialiseOption(s0, X, ct, et, sig, q, r);

		double v = r - sig * sig / 2;
		int indexHX = 0, indexXH = 0;
		if (H > X) indexHX = 1;
		if (X > H) indexXH = 1;

		switch (type) {
		case upNin: return pow((H / s0), 2 * v / (sig * sig)) * (auxP.PriceOptionAnalytical(H*H / s0, min(H, X))
			- (min(H, X) - X) * exp(-r * t) * normalCDF(-d1(H*H / s0, min(H, X)))) + (auxC.PriceOptionAnalytical(s0, X)
			- auxC.PriceOptionAnalytical(s0, H) - (H - X) * exp(-r * t) * normalCDF(d1(s0, H))) * indexXH;
		case downNin: return pow((H / s0), 2 * v / (sig * sig)) * (auxC.PriceOptionAnalytical(H*H / s0, X)
			- auxC.PriceOptionAnalytical(H*H / s0, H) - (H - X) * exp(-r * t) * normalCDF(d1(H, s0))) * indexXH
			+ auxP.PriceOptionAnalytical(s0, min(H, X)) - (min(H, X) - X) * exp(-r * t) * normalCDF(-d1(s0, min(H, X)));
		case upNout: return auxP.PriceOptionAnalytical(s0, min(H, X)) - pow((H / s0), 2 * v / (sig * sig))
			* auxP.PriceOptionAnalytical(H*H / s0, min(H, X)) - (min(H, X) - X) * exp(-r * t)
			* (normalCDF(-d1(s0, min(H, X)) - pow((H / s0), 2 * v / (sig * sig)) * normalCDF(-d1(H*H / s0, min(H, X)))));
		case downNout: return (auxP.PriceOptionAnalytical(s0, X) - auxP.PriceOptionAnalytical(s0, H)
			+ (H - X) * exp(-r * t) * normalCDF(-d1(H, s0)) - pow((H / s0), 2 * v / (sig * sig))
			* (auxP.PriceOptionAnalytical(H*H / s0, X) - auxP.PriceOptionAnalytical(H*H / s0, H)
				+ (H - X) * exp(-r * t) * normalCDF(d1(H, s0)))) * indexXH;
		}
	}

	double DeltaRisk() {
		double A, B, C, D;
		calculateDeltaParameters(A, B, C, D);
		switch (type) {
		case downNout: if (X < H) return 0;
					   else return A - B + C - D;
		case upNout: if (X < H) return A - C;
					 else return B - D;
		case downNin: if (X < H) return A;
					  else return B - C + D;
		case upNin: if (X < H) return C;
					else return A - B + D;
		}
	}

	double PayOffOptionMC() {
		return max(X - PriceOptionMC(), 0.0);
	}

private:

};