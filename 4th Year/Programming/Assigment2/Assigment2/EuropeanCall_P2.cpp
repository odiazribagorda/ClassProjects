/*
Author: Oscar Diaz Ribagorda (ID: 1966444)

File: EuropeanCall_P2.cpp

Description: Solution to Problem 2 of Assigment 2. It contains the the program explained in the problem description
to try out the EuropeanCall class.
*/

#include "EuropeanCall_P2.h"

int main()
{
	EuropeanCall call1, call2, call3; // Create three different Calls.

	// Intitialize the three calls with the parameters established in the problem description. I assume that the current
	// time parameter is 0 since there is only one value given for time and this is most probably the time until expiration
	// from now (ct = 0).
	call1.initialiseCall(50, 50, 0, 1, 0.5, 0.2, 0.1);
	call2.initialiseCall(50, 40, 0, 1.5, 0.6, 0.3, 0.1);
	call3.initialiseCall(50, 60, 0, 2, 0.2, 0.0, 0.1);

	// Output of the price and metrics of the 3 Calls.
	cout << "This are the price and risks for each call:\n";
	cout << "CALL 1:\n";
	cout << "Call Price: " << call1.priceCallAnalytic() << '\n';
	cout << "Delta Analytic: " << call1.callDeltaAnalytic() << '\n';
	cout << "Gamma Analytic: " << call1.callGammaAnalytic() << '\n';
	cout << "Theta Analytic: " << call1.callThetaAnalytic() << '\n';
	cout << "Rho Analytic: " << call1.callRhoAnalytic() << '\n';
	cout << "----------------------------------\n";

	cout << "CALL 2:\n";
	cout << "Call Price: " << call2.priceCallAnalytic() << '\n';
	cout << "Delta Analytic: " << call2.callDeltaAnalytic() << '\n';
	cout << "Gamma Analytic: " << call2.callGammaAnalytic() << '\n';
	cout << "Theta Analytic: " << call2.callThetaAnalytic() << '\n';
	cout << "Rho Analytic: " << call2.callRhoAnalytic() << '\n';
	cout << "----------------------------------\n";

	cout << "CALL 3:\n";
	cout << "Call Price: " << call3.priceCallAnalytic() << '\n';
	cout << "Delta Analytic: " << call3.callDeltaAnalytic() << '\n';
	cout << "Gamma Analytic: " << call3.callGammaAnalytic() << '\n';
	cout << "Theta Analytic: " << call3.callThetaAnalytic() << '\n';
	cout << "Rho Analytic: " << call3.callRhoAnalytic() << '\n';
	cout << "----------------------------------\n";

	// Output of the value of the portfolio suggested in the problem description. For this, all the calls are inserted
	// into a vector and run through the corresponding function.
	cout << "This is the value of a portfolio that contains 3 CALL1s, 5 CALL2s and 12 CALL3s:\n";
	vector<EuropeanCall> portfolio;
	for (int i = 0; i < 3; ++i) portfolio.push_back(call1);
	for (int i = 0; i < 5; ++i) portfolio.push_back(call2);
	for (int i = 0; i < 12; ++i) portfolio.push_back(call3);
	cout << EuropeanCall::pricePortfolioOfCalls(portfolio) << '\n';

	// Instruction to exit the program to make the program more user friendly.
	cout << "\nEnd of program. Press ENTER to exit...\n";
	char c = ' '; cin.get(c);

	return 0;
}