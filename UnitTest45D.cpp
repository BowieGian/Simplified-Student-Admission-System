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

	domesticList.createSorted("Abcde", "Edcba", 1, 1, "BC");
	domesticList.createSorted("Abcde", "Edcba", 1, 1, "BC");
	domesticList.createSorted("Abcde", "Edcba", 1, 1, "BC");

	char deleteAction = '\0';
	string firstName, lastName = "";

	domesticList.display();
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

			domesticList.removeName(firstName, lastName); //deletes student with the inputed name
			domesticList.display();
		}
		else if (deleteAction == 'F') {
			domesticList.removeHeadTail(); //deletes head and tail of the linked list
			cout << endl << "First and last domestic student deleted!" << endl;
			domesticList.display();
		}
		else if (deleteAction == 'Q')
			break;
		else
			cout << endl << "Please enter a valid action prompt." << endl;
	}
	return 0;
}