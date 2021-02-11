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
	InternationalList internationalList;
	string line;

	//Read the international-stu.txt file and exit if failed
	ifstream internationalFile("international-stu.txt");
	if (!internationalFile.is_open()) {
		cout << "Unable to open file international-stu.txt" << endl;
		return -1;
	}

	//Read the first line of international-stu.txt, which specifies the file format. And then print it out to the screen
	getline(internationalFile, line);
	cout << "File format: " << line << endl;

	while (getline(internationalFile, line)) {
		istringstream ss(line);

		string firstName = "", lastName = "", country = "", s_cgpa = "", s_researchScore = "", s_reading = "", s_listening = "", s_speaking = "", s_writing = "";
		float cgpa = 0;
		int researchScore = 0, reading = 0, listening = 0, speaking = 0, writing = 0, applicationNumber = 0;

		//get data separated by commas
		getline(ss, firstName, ',');
		getline(ss, lastName, ',');
		getline(ss, country, ',');
		getline(ss, s_cgpa, ',');
		getline(ss, s_researchScore, ',');
		getline(ss, s_reading, ',');
		getline(ss, s_listening, ',');
		getline(ss, s_speaking, ',');
		getline(ss, s_writing, ',');

		if (firstName == "" || lastName == "" || country == "" || s_cgpa == "" || s_researchScore == "" || s_reading == "" || s_listening == "" || s_speaking == "" || s_writing == "")
			cout << "You are missing a field." << endl;

		if (country == "Idian")
			country = "Indian";
		else if (!(country == "Canada" || country == "China" || country == "India" || country == "Iran" || country == "Korea"))
			cout << "Please enter a valid country." << endl;

		//fix capitalization
		formatString(firstName);
		formatString(lastName);
		formatString(country);
		//convert string to float
		cgpa = atof(s_cgpa.c_str());
		//convert string to int
		researchScore = atoi(s_researchScore.c_str());
		reading = atoi(s_reading.c_str());
		listening = atoi(s_listening.c_str());
		speaking = atoi(s_speaking.c_str());
		writing = atoi(s_writing.c_str());
		//get application number
		applicationNumber = Student::getApplicationNumber();

		internationalList.createSorted(firstName, lastName, cgpa, researchScore, country, reading, listening, speaking, writing);
	}
	internationalFile.close();	//close the file

	int searchedApplicationID = 0; //specific value the user enters to see if there are any matches
	double searchedCGPA = 0.0;
	double searchedResearchScore = 0.0;
	string firstName = "";
	string lastName = "";
	char searchType = '\0';

	internationalList.display();
	while (searchType != 'Q') {
		cout << endl << "To search, enter A for application ID, C for CGPA, R for research score, N for name or Q to stop testing " << endl;
		cin >> searchType;
		cin.ignore(10000, '\n');

		if (searchType == 'A') {
			cout << endl << "Please enter the application ID you would like to search for. " << endl;
			while (true) {
				if (cin >> searchedApplicationID) {
					cin.ignore(10000, '\n');
					if ((searchedApplicationID >= 20200000) && (searchedApplicationID <= 20210000)) {
						internationalList.search(searchedApplicationID, searchType);
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
		else if (searchType == 'C') {
			cout << endl << "Please enter the CGPA you would like to search for. " << endl;
			while (true) {
				if (cin >> searchedCGPA) {
					cin.ignore(10000, '\n');
					if ((searchedCGPA >= 0) && (searchedCGPA < 4.34)) {
						internationalList.search(searchedCGPA, searchType);
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
		else if (searchType == 'R') {
			cout << endl << "Please enter the research score you would like to search for." << endl;
			while (true) {
				if (cin >> searchedResearchScore) {
					cin.ignore(10000, '\n');
					if ((searchedResearchScore >= 0) && (searchedResearchScore <= 100)) {
						internationalList.search(searchedResearchScore, searchType);
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
		else if (searchType == 'N') {
			cout << endl << "Please enter a first name" << endl;
			cin >> firstName;
			cin.ignore(10000, '\n');

			cout << endl << "Please enter a last name" << endl;
			cin >> lastName;
			cin.ignore(10000, '\n');

			internationalList.search(firstName, lastName);
		}
		else if (searchType == 'Q')
			break;
		else
			cout << "Please only enter a capital A, C, R, or N" << endl;
	}
	return 0;
}