/*
Author: Oscar Diaz Ribagorda (ID: 1966444)

File: Date.h

Description: Contains class Date which stores a date given in either usual Date format or integer format
and converts in between them.

*/

#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

typedef int tDate[3]; // This type is defined for better comprehension when dealing with dates in {Day, Month, Year} format.

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
	// Returns date in {Day, Month, Year} format. The date is return with a referenced parameter because
	// its not allowed for a function to return arrays.
	void getDate(tDate & date)
	{
		date[1] = 1; date[2] = 1900;
		date[2] += intDate / 365; // Get how many years with a division.
		int rest = intDate % 365; // Get rest of the days with modulo.
		int i = 0;
		while (rest > Months[i].days) { // Adds days of complete months with the help of array Months.
			++date[1];
			rest -= Months[i].days;
			++i;
		}
		date[0] = rest; // The rest will be the days of the incomplete month.
	}

	// Changes the date given in {Day, Month, Year} format. Its argument is an array of size 3.
	void setDate(tDate date)
	{
		intDate = (date[2] - 1900) * 365 + date[0]; // Years times 365 plus days in the incomplete month.
		for (int i = date[1] - 1; i >= 1; --i)		// Adds the days in the complete months with the help
			intDate += Months[i].days;				// the Months array.
	}

	// Writes date on the console in an intelligible format ('Day' of 'Month' 'Year').
	void printDate()
	{
		tDate date; getDate(date);
		cout << date[0] << " of " << Months[date[1]].name << ' ' << date[2];
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
