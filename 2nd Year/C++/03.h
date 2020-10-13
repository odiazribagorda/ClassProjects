// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include <cmath>

using namespace std;

class complejo {
private:
	float a;
	float b;
public:
	complejo(){};

	complejo(float real, float imag) {
		a = real;
		b = imag;
	}

	complejo operator+(complejo const& c) {
		complejo cAux(a + c.a, b + c.b);
		return cAux;
	}

	complejo operator*(complejo const& c) {
		complejo cAux(a*c.a - b * c.b, a*c.b + b*c.a);
		return cAux;
	}

	float mod() {
		return sqrt(a*a + b*b);
	}
};