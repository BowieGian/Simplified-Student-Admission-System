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
	string line;

	//Read the domestic-stu.txt file and exit if failed
	ifstream domesticFile("domestic-stu.txt");
	if (!domesticFile.is_open()) {
		cout << "Unable to open file domestic-stu.txt" << endl;
		return -1;
	}

	//Read the first line of domestic-stu.txt, which specifies the file format. And then print it out to the screen
	getline(domesticFile, line);
	cout << "File format: " << line << endl;

	while (getline(domesticFile, line)) {
		/*Process each line, get each field separated by a comma.
		 *We use istringstream to handle it.
		 *Note in this example code here, we assume the file format
		 *is perfect and do NOT handle error cases. We will leave the
		 *error and exception handling of file format to Lab Assignment 4
		 */
		istringstream ss(line);

		string firstName = "", lastName = "", province = "", s_cgpa = "", s_researchScore = "";
		float cgpa = 0.0;
		int researchScore, applicationNumber = 0;

		//get data separated by commas
		getline(ss, firstName, ',');
		getline(ss, lastName, ',');
		getline(ss, province, ',');
		getline(ss, s_cgpa, ',');
		getline(ss, s_researchScore, ',');

		if (firstName == "" || lastName == "" || province == "" || s_cgpa == "" || s_researchScore == "")
			cout << "You are missing a field." << endl;

		if (!(province == "NL" || province == "PE" || province == "NS" || province == "NB" || province == "QC" || province == "ON" || province == "MB" ||
			province == "SK" || province == "AB" || province == "BC" || province == "YT" || province == "NT" || province == "NU"))
			cout << "Please enter a valid province" << endl;

		//fix capitalization
		formatString(firstName);
		formatString(lastName);
		//convert string to float
		cgpa = atof(s_cgpa.c_str());
		//convert string to int
		researchScore = atoi(s_researchScore.c_str());
		//get application number
		applicationNumber = Student::getApplicationNumber();

		domesticList.createSorted(firstName, lastName, cgpa, researchScore, province);
	}
	domesticFile.close();	//close the file
	cout << endl;

	int searchedApplicationID = 0; //specific value the user enters to see if there are any matches
	double searchedCGPA = 0.0;
	double searchedResearchScore = 0.0;
	string firstName = "";
	string lastName = "";
	char searchType = '\0';

	domesticList.display();
	while (searchType != 'Q') {
		cout << endl << "To search, enter A for application ID, C for CGPA, R for research score, N for name or Q to stop testing" << endl;
		cin >> searchType;
		cin.ignore(10000, '\n');

		if (searchType == 'A') {	//searches by application ID
			cout << endl << "Please enter the application ID you would like to search for. " << endl;
			while (true) {
				if (cin >> searchedApplicationID) {
					cin.ignore(10000, '\n');
					if ((searchedApplicationID >= 20200000) && (searchedApplicationID <= 20210000)) {
						domesticList.search(searchedApplicationID, searchType);
						break;
					}
					else
						cout << endl << "Please enter an integer between 20200000 and 20210000" << endl;
				}
				else {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "Please enter an integer between 20200000 and 20210000" << endl;
				}
			}
		}
		else if (searchType == 'C') {	//searches by CGPA
			cout << endl << "Please enter the CGPA you would like to search for. " << endl;
			while (true) {
				if (cin >> searchedCGPA) {
					cin.ignore(10000, '\n');
					if ((searchedCGPA >= 0) && (searchedCGPA < 4.34)) {
						domesticList.search(searchedCGPA, searchType);
						break;
					}
					else
						cout << endl << "Please enter a number between 0 and 4.33" << endl;
				}
				else {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "Please enter a number between 0 and 4.33" << endl;
				}
			}
		}
		else if (searchType == 'R') {	//searches by research score
			cout << endl << "Please enter the research score you would like to search for." << endl;
			while (true) {
				if (cin >> searchedResearchScore) {
					cin.ignore(10000, '\n');
					if ((searchedResearchScore >= 0) && (searchedResearchScore <= 100)) {
						domesticList.search(searchedResearchScore, searchType);
						break;
					}
					else
						cout << endl << "Please enter a valid research score" << endl;
				}
				else {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "Please enter an integer between 0 and 100" << endl;
				}
			}
		}
		else if (searchType == 'N') {	//searches by name
			cout << endl << "Please enter a first name" << endl;
			cin >> firstName;
			cin.ignore(10000, '\n');

			cout << endl << "Please enter a last name" << endl;
			cin >> lastName;
			cin.ignore(10000, '\n');

			domesticList.search(firstName, lastName);
		}
		else if (searchType == 'Q')
			break;
		else
			cout << "Please only enter a capital A, C, R, N or Q" << endl;
	}
	return 0;
}