/*
Author: Oscar Diaz Ribagorda (ID: 1966444)

File: ComplexNum_P2.h

Description: Solution to Problem 2 of Assigment 3. This includes the complex number class with all the
correspondent procedures plus the 4 functions that executer complex number operations (power, exp, cos, sin).
*/

#pragma once

#include <iostream>
#include <cmath>

using namespace std;

class ComplexNum {
public:
	ComplexNum(double r = 0, double i = 0) {
		re = r; im = i;
	}

	ComplexNum(const ComplexNum & source) {
		re = source.re;
		im = source.im;
	}

	ComplexNum operator+(const ComplexNum & z) const {
		ComplexNum sum;
		sum.re = z.re + re;
		sum.im = z.im + im;
		return sum;
	}

	ComplexNum operator-(const ComplexNum & z) const {
		ComplexNum dif;
		dif.re = re - z.re;
		dif.im = im - z.im;
		return dif;
	}

	ComplexNum operator*(const ComplexNum & z) const {
		ComplexNum mul;
		mul.re = re * z.re - im * z.im;
		mul.im = re * z.im + im * z.re;
		return mul;
	}

	ComplexNum operator/(const ComplexNum & z) const {
		ComplexNum div;
		div.re = (re * z.re - im * (-z.im)) / (z.re * z.re + z.im * z.im);
		div.im = (re * (-z.im) + im * z.re) / (z.re * z.re + z.im * z.im);
		return div;
	}

	ComplexNum operator+(const double & z) const {
		ComplexNum sum;
		sum.re = z + re;
		return sum;
	}

	ComplexNum operator-(const double & z) const {
		ComplexNum dif;
		dif.re = re - z;
		return dif;
	}

	ComplexNum operator*(const double & z) const {
		ComplexNum mul;
		mul.re = re * z;
		mul.im = im * z;
		return mul;
	}

	ComplexNum operator/(const double & z) const {
		ComplexNum div;
		div.re = re / z;
		div.im = im / z;
		return div;
	}

	void PrintComplexNumber() {
		if (re != 0) {
			cout << re;
			if (im > 0)
				if (im != 1) cout << " + " << im << "i";
				else cout << " + i";
			else if (im < 0)
				if (im != -1) cout << " - " << -im << "i";
				else cout << " - i";
		}
		else if (im != 0) {
			if(im != 1 && im != -1) cout << im << "i";
			else if (im == 1) cout << "i";
			else cout << "-i";
		}
		else cout << 0;
	}

	double getNorm() {
		return sqrt(re * re + im * im);
	}

	ComplexNum getConjugate() {
		ComplexNum conjugate(re, -im);
		return conjugate;
	}

	ComplexNum getInverse() {
		ComplexNum inv(re / (re * re + im * im), -im / (re * re + im * im));
		return inv;
	}

	void getPolarCoordinates(double & r, double & arg) {
		r = getNorm();
		arg = atan(im / re);
	}

private:
	double re; // Real part of the complex number.
	double im; // Imaginary part of the complex number.
};

ComplexNum Power(ComplexNum const& z, int n) {
	ComplexNum power(z);
	for (int i = 0; i < n - 1; ++i) {
		power = power * z;
	}
	return power;
}

ComplexNum expComplex(ComplexNum const& z, int n) {
	ComplexNum aproximation(1);
	ComplexNum power(1);
	int factorial = 1;

	for (int i = 1; i <= n; ++i) {
		power = power * z;
		factorial = factorial * i;
		aproximation = aproximation + power / factorial;
	}

	return aproximation;
}

ComplexNum cosComplex(ComplexNum const& z, int n) {
	ComplexNum aproximation(1);
	ComplexNum power(1);
	int factorial = 1;

	for (int i = 1; i <= n; ++i) {
		power = power * z;
		factorial = factorial * i;
		if (i % 4 == 0) aproximation = aproximation + power / factorial;
		else if (i % 2 == 0) aproximation = aproximation - power / factorial;
	}

	return aproximation;
}

ComplexNum sinComplex(ComplexNum const& z, int n) {
	ComplexNum aproximation(0);
	ComplexNum power(1);
	int factorial = 1;

	for (int i = 1; i <= n; ++i) {
		power = power * z;
		factorial = factorial * i;
		if (i % 4 == 1) aproximation = aproximation + power / factorial;
		else if (i % 4 == 3) aproximation = aproximation - power / factorial;
	}

	return aproximation;
}
