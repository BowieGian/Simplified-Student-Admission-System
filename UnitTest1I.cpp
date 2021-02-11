#include <iostream>	//cin and cout
#include <fstream>	//file processing
#include <sstream>	//formatted string processing
#include <cstdlib>	//atof and atoi
#include <string>	//strings
#include <cctype>	//toupper and tolower
#include <cmath>	//abs()
#include "student.hpp"

int main() {
	srand(time(0));						//seed rand() for random student numbers
	Student::setupAvailableIDs();		//initiate array of available IDs
	DomesticList domesticList;
	InternationalList internationalList;
	MergedList mergedList;

	float CGPA;
	int researchScore, reading, listening, speaking, writing;
	string firstName, lastName, country;
	char quit = '\0';

	while (quit != 'Y') {
		cout << endl << "Enter the first name of the student" << endl;
		cin >> firstName;
		cin.ignore(10000, '\n');

		cout << endl << "Enter the last name of the student" << endl;
		cin >> lastName;
		cin.ignore(10000, '\n');

		cout << endl << "Enter their CGPA" << endl;
		while (true) {
			if (cin >> CGPA) {
				cin.ignore(10000, '\n');
				if ((CGPA >= 0) && (CGPA < 4.34))
					break;
				else
					cout << endl << "Please enter a number between 0 and 4.33" << endl;
			}
			else {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Please enter a number between 0 and 4.33" << endl;
			}
		}

		cout << endl << "Enter their research score" << endl;
		while (true) {
			if (cin >> researchScore) {
				cin.ignore(10000, '\n');
				if ((researchScore >= 0) && (researchScore <= 100))
					break;
				else
					cout << endl << "Please enter an integer between 0 and 100" << endl;
			}
			else {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Please enter an integer between 0 and 100" << endl;
			}
		}

		cout << endl << "Enter their country" << endl;
		while (true) {
			cin >> country;
			cin.ignore(10000, '\n');
			formatString(country);

			if (!(country == "Canada" || country == "China" || country == "India" || country == "Iran" || country == "Korea"))
				cout << "Please enter a valid country." << endl;
			else
				break;
		}

		cout << endl << "Enter their TOEFL reading score" << endl;
		while (true) {
			if (cin >> reading) {
				cin.ignore(10000, '\n');
				if ((reading >= 0) && (reading <= 30))
					break;
				else
					cout << endl << "Please enter an integer between 0 and 30" << endl;
			}
			else {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Please enter an integer between 0 and 30" << endl;
			}
		}

		cout << endl << "Enter their TOEFL listening score" << endl;
		while (true) {
			if (cin >> listening) {
				cin.ignore(10000, '\n');
				if ((listening >= 0) && (listening <= 30))
					break;
				else
					cout << endl << "Please enter an integer between 0 and 30" << endl;
			}
			else {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Please enter an integer between 0 and 30" << endl;
			}
		}

		cout << endl << "Enter their TOEFL speaking score" << endl;
		while (true) {
			if (cin >> speaking) {
				cin.ignore(10000, '\n');
				if ((speaking >= 0) && (speaking <= 30))
					break;
				else
					cout << endl << "Please enter an integer between 0 and 30" << endl;
			}
			else {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Please enter an integer between 0 and 30" << endl;
			}
		}

		cout << endl << "Enter their TOEFL writing score" << endl;
		while (true) {
			if (cin >> writing) {
				cin.ignore(10000, '\n');
				if ((writing >= 0) && (writing <= 30))
					break;
				else
					cout << endl << "Please enter an integer between 0 and 30" << endl;
			}
			else {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Please enter an integer between 0 and 30" << endl;
			}
		}

		formatString(firstName);
		formatString(lastName);
		internationalList.createSorted(firstName, lastName, CGPA, researchScore, country, reading, listening, speaking, writing);
		cout << "International student created!" << endl;
		internationalList.display();

		cout << "Enter Y to quit and N to keep testing." << endl;
		cin >> quit;
		cin.ignore(10000, '\n');
	}
	return 0;
}