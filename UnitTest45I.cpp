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

	internationalList.createSorted("Abcde", "Edcba", 1, 1, "China", 30, 30, 30, 30);
	internationalList.createSorted("Abcde", "Edcba", 1, 1, "China", 30, 30, 30, 30);
	internationalList.createSorted("Abcde", "Edcba", 1, 1, "China", 30, 30, 30, 30);

	char deleteAction = '\0';
	string firstName, lastName = "";

	internationalList.display();
	while (deleteAction != 'Q') {
		cout << endl << "To delete by name, enter N. To delete the first and last student, enter F. To stop testing, enter Q." << endl;
		cin >> deleteAction;
		cin.ignore(10000, '\n');

		if (deleteAction == 'N') {
			cout << endl << endl << "Enter the first name of the student" << endl;
			cin >> firstName;
			cin.ignore(10000, '\n');

			cout << endl << endl << "Enter the last name of the student" << endl;
			cin >> lastName;
			cin.ignore(10000, '\n');

			internationalList.removeName(firstName, lastName);
			internationalList.display();
		}
		else if (deleteAction == 'F') {
			internationalList.removeHeadTail();
			cout << endl << "First and last international student deleted!" << endl;
			internationalList.display();
		}
		else if (deleteAction == 'Q')
			break;
		else
			cout << endl << "Please enter a valid action prompt." << endl;
	}
	return 0;
}