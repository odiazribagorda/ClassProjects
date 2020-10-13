/*
Author: Oscar Diaz Ribagorda (ID: 1966444)

File: main_P2.cpp

Description: Solution to Problem 2 of Assigment 3. This includes the main function which tests
the different procedures for the complex number class and outputs the results.
*/

#include "ComplexNum_P2.h"

int main() {
	ComplexNum z1(2, 2), z2(3, -1);
	ComplexNum z3(z1);
	cout << "Value of Z2: "; z2.PrintComplexNumber(); cout << '\n';
	cout << "Norm of Z2: " << z2.getNorm() << '\n';
	cout << "Conjugate of Z2: "; z2.getConjugate().PrintComplexNumber(); cout << '\n';
	cout << '\n';
	cout << "Inverse of Z3: "; z3.getInverse().PrintComplexNumber(); cout << '\n';

	double r = 0, arg = 0;
	z3.getPolarCoordinates(r, arg);
	cout << "Polar coordinates of Z3: R = " << r << "; Arg = " << arg << '\n';
	cout << '\n';

	cout << "Z1 * Z2 = ";
	(z1 * z2).PrintComplexNumber();
	cout << '\n';

	cout << "4 * Z2 = ";
	(z2 * 4).PrintComplexNumber();
	cout << '\n';

	cout << "Z1^4 = ";
	Power(z1, 4).PrintComplexNumber();
	cout << '\n';

	cout << '\n';

	cout << "exp(Z1) = ";
	expComplex(z1, 10).PrintComplexNumber();
	cout << '\n';

	cout << "cos(Z1) = ";
	cosComplex(z1, 10).PrintComplexNumber();
	cout << '\n';

	cout << "sin(Z1) = ";
	sinComplex(z1, 10).PrintComplexNumber();
	cout << '\n';

	cout << '\n';

	cout << "Comparison of exp(z1*i) and cos(z1) + sin(z1) * i:\n";
	cout << "exp(z1*i) = ";
	ComplexNum i(0, 1);
	expComplex(z1 * i, 10).PrintComplexNumber();
	cout << '\n';

	cout << "cos(z1) + sin(z1)*i = ";
	(cosComplex(z1, 10) + sinComplex(z1, 10) * i).PrintComplexNumber();
	cout << '\n';

	cout << "\nAs we can see this expresions are equal. It's a mathematics equality\n" <<
		"which shouldn't fail. What could give us some trouble is, if the precision\n" <<
		"is different in the two terms then the values might not be exactly the same.\n" <<
		"Also comparing real numbers is not very precise, so the computer might say\n" <<
		"they are different.\n";

	cout << "\nProgram ended. Press ENTER to exit...\n";
	char c = ' '; cin.get(c);
}