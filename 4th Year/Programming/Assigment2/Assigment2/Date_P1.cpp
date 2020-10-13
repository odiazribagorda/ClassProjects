/*
Author: Oscar Diaz Ribagorda (ID: 1966444)

File: Date_P1.cpp

Description: Solution to Problem 1 of Assigment 2. Program to run test for the Date class as asked in the
problem description.
*/

#include "Date_P1.h"

int main() {
	Date date; // Creates a new Date.

	date.setDate(2, 2, 1900); // Sets the date to 2/2/1900.
	cout << "First Result:\n";
	date.printDate();
	cout << '\n';

	date.setIntDate(1000); // Gives the date the value 1000.
	cout << "Second Result:\n";
	date.printDate();
	cout << '\n';

	// Instruction to exit the program to make the program more user friendly.
	cout << "\nProgram ended. Press ENTER to exit...\n";
	char c = ' '; cin.get(c);

	return 0;
}