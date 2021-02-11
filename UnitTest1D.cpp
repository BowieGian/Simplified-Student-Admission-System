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
	int researchScore;
	string firstName, lastName, province;
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

		cout << endl << "Enter their province" << endl;
		while (true) {
			cin >> province;
			cin.ignore(10000, '\n');

			if (!(province == "NL" || province == "PE" || province == "NS" || province == "NB" || province == "QC" || province == "ON" || province == "MB" ||
				province == "SK" || province == "AB" || province == "BC" || province == "YT" || province == "NT" || province == "NU"))
				cout << "Please enter a valid province" << endl;
			else
				break;
		}

		formatString(firstName);
		formatString(lastName); // gives inputed names a capital first letter and lower cases for the rest
		domesticList.createSorted(firstName, lastName, CGPA, researchScore, province);
		cout << endl << "Domestic student created!" << endl;
		domesticList.display();

		cout << "Enter Y to quit and N to keep testing." << endl;
		cin >> quit;
		cin.ignore(10000, '\n');
	}
	return 0;
}