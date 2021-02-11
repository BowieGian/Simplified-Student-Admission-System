/* ENSC 251 Lab 3
 * Bowie Gian 301361834
 * Marcus Yan 301357801
 * Created on: Sept. 18, 2019
 * Modified on: Nov. 22, 2019
 */

 //main.cpp
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
	DomesticList emptyDomesticList, fullDomesticList;
	InternationalList emptyInternationalList, fullInternationalList;
	MergedList emptyMergedList, domesticMergedList, internationalMergedList, fullMergedList;
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

		fullDomesticList.createSorted(firstName, lastName, cgpa, researchScore, province);
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

		fullInternationalList.createSorted(firstName, lastName, cgpa, researchScore, country, reading, listening, speaking, writing);
	}
	internationalFile.close();	//close the file

	emptyMergedList.mergeLists(emptyDomesticList, emptyInternationalList);
	emptyMergedList.display();

	cout << endl << endl;

	domesticMergedList.mergeLists(fullDomesticList, emptyInternationalList);
	domesticMergedList.display();

	cout << endl << endl;

	internationalMergedList.mergeLists(emptyDomesticList, fullInternationalList);
	internationalMergedList.display();

	cout << endl << endl;

	fullMergedList.mergeLists(fullDomesticList, fullInternationalList);
	fullMergedList.display();

	return 0;
}