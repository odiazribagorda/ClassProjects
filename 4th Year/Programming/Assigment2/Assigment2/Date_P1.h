#pragma once

/*
Author: Oscar Diaz Ribagorda (ID: 1966444)

File: Date_P1.h

Description: Solution to Problem 1 of Assigment 2. This is the Date class which stores an integer
that represents the date (from 1/1/1900) and contains methods to get and change this dates in different
formats.
*/

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Date
{
public:
	// Returns date in its integer form.
	int getIntDate()
	{
		return intDate;
	}
	// Changes date in its integer form.
	void setIntDate(int data)
	{
		intDate = data;
	}
	// Returns date in {Day, Month, Year} format. The date is return through 3 referenced integers because
	// its not allowed for a function to return arrays.
	void getDate(int & day, int & month, int & year)
	{
		month = 1; year = 1900;
		year += intDate / 365; // Gets how many years with a division.
		int rest = intDate % 365; // Gets rest of the days with modulo.
		int i = 0;
		while (rest > Months[i].days) { // Adds days of complete months with the help of array Months.
			++month;
			rest -= Months[i].days;
			++i;
		}
		day = rest; // The rest will be the days of the incomplete month.
	}

	// Changes the date given in {Day, Month, Year} format. Its arguments are the integers corresponding to the parameters.
	void setDate(int day, int month, int year)
	{
		intDate = (year - 1900) * 365 + day;		// Years times 365 plus days in the incomplete month.
		for (int i = month - 1; i >= 1; --i)		// Adds the days in the complete months with the help the Months array.
			intDate += Months[i - 1].days;
	}

	// Writes date on the console in an intelligible format ('Day' of 'Month' 'Year').
	void printDate()
	{
		int date[3]; getDate(date[0], date[1], date[2]);
		cout << date[0] << " of " << Months[date[1] - 1].name << ' ' << date[2];
	}

private:
	int intDate; // Integer parameter to store dates (from 1/1/1900).

	struct Month { // Struct to store months with their name and number of days.
		string name;
		int days;
	};

	// This array is a tool to translate integer dates into the usual format and viceversa.
	// It contains the 12 months with its corresponding number of days.
	const Month Months[12] = { {"January", 31}, {"February", 28}, {"March", 31}, {"April", 30}, {"May", 31}, {"June", 30},
							   {"July", 31}, {"August", 31}, {"September", 30}, {"October", 31}, {"November", 30},
							   {"December", 31} };

};