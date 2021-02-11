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

	mergedList.mergeLists(domesticList, internationalList);

	int researchScore_threshold;
	float CGPA_threshold;
	char quit = '\0';

	while (quit != 'Q') {
		cout << endl << endl << "Please enter your research score threshold" << endl;
		while (true) {
			if (cin >> researchScore_threshold) {
				cin.ignore(10000, '\n');
				if (researchScore_threshold >= 0 && researchScore_threshold <= 100)
					break;
				else
					cout << "Please enter an integer between 0 and 100" << endl;
			}
			else {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Please enter an integer between 0 and 100" << endl;
			}
		}

		cout << endl << endl << "Please enter your CGPA threshold" << endl;
		while (true) {
			if (cin >> CGPA_threshold) {
				cin.ignore(10000, '\n');
				if (CGPA_threshold >= 0 && CGPA_threshold < 4.34)
					break;
				else
					cout << "Please enter a number between 0 and 4.33" << endl;
			}
			else {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Please enter a number between 0 and 4.33" << endl;
			}
		}

		mergedList.searchBoth(CGPA_threshold, researchScore_threshold);

		cout << "Enter Y to quit and N to keep testing." << endl;
		cin >> quit;
		cin.ignore(10000, '\n');

		if (quit == 'Y')
			break;
	}
	return 0;
}