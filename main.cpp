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
			country = "India";
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

	while (true)
	{
		char studentType = '\0'; //indicates if the user wants to do something to the domestic or international linked list
		char searchType = '\0'; //indicates what the user wants to search for
		char mainAction = '\0'; //indicates what the user wants the program to do
		char studentAction = '\0'; //indicates what the user wants to do with the domestic or international student
		char deleteAction = '\0'; //indicates what the user wants to delete

		int searchedApplicationID = 0; //specific value the user enters to see if there are any matches
		double searchedCGPA = 0.0;
		double searchedResearchScore = 0.0;
		string firstName = "";
		string lastName = "";

		double CGPA_threshold = 0.0;
		double researchScore_threshold = 0.0;

		cout << endl << endl << "To do something with students, enter D for domestic or I for international students. To merge lists, enter M, to quit this program, enter Q" << endl;
		cin >> mainAction;
		cin.ignore(10000, '\n');	//clear cin

		if (mainAction == 'D') {	//searches, creates a new node, or deletes something related to domestic students based on user input
			while (true) {
				cout << endl << endl << "Enter S to search through domestic students, C to create a new node, R to remove objects, D to display or Q to quit." << endl;
				cin >> studentAction;
				cin.ignore(10000, '\n');

				if (studentAction == 'S') {		//if user chooses to search, do the following
					cout << endl << "To search, enter A for application ID, C for CGPA, R for research score, or N for name " << endl;
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
					else
						cout << "Please only enter a capital A, C, R, or N" << endl;
				}
				else if (studentAction == 'C') {	//creates a new node
					float CGPA;
					int researchScore;
					string province;

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
				}
				else if (studentAction == 'R') {	//removes objects in the linked list
					cout << endl << "To delete by name, enter N. To delete the first and last student, enter F." << endl;
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
					}
					else if (deleteAction == 'F') {
						domesticList.removeHeadTail(); //deletes head and tail of the linked list
						cout << endl << "First and last domestic student deleted!" << endl;
					}
					else
						cout << endl << "Please enter a valid action prompt." << endl;
				}
				else if (studentAction == 'D')
					domesticList.display();
				else if (studentAction == 'Q') //stops the loop and goes back to the action selection menu
					break;
				else
					cout << endl << endl << "Please enter a valid action prompt." << endl;
			}
		} //end of D
		else if (mainAction == 'I') {	//same as above, but for international students instead of domestic students
			while (true) {
				cout << endl << endl << "Enter S to search through international students, C to create a new node, R to remove objects, D to display or Q to quit." << endl;
				cin >> studentAction;
				cin.ignore(10000, '\n');

				if (studentAction == 'S') {
					cout << endl << "To search, enter A for application ID, C for CGPA, R for research score, or N for name " << endl;
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
					else
						cout << "Please only enter a capital A, C, R, or N" << endl;
				}
				else if (studentAction == 'C') {
					float CGPA;
					int researchScore, reading, listening, speaking, writing;
					string country;

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
				}
				else if (studentAction == 'R') {
					cout << endl << "To delete by name, enter N. To delete the first and last student, enter F." << endl;
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
					}
					else if (deleteAction == 'F') {
						internationalList.removeHeadTail();
						cout << endl << "First and last international student deleted!" << endl;
					}
					else
						cout << endl << "Please enter a valid action prompt." << endl;
				}
				else if (studentAction == 'D')
					internationalList.display();
				else if (studentAction == 'Q')
					break;
				else
					cout << endl << endl << "Please enter a valid action prompt." << endl;
			}
		} // end of I
		else if (mainAction == 'M') { //merges the linked lists
			mergedList.mergeLists(domesticList, internationalList);
			mergedList.display();

			while (true) {
				cout << endl << endl << "Enter R to filter by research score threshold, C to filter by CGPA, B for both, D to display and Q to quit" << endl;
				cin >> studentAction;
				cin.ignore(10000, '\n');

				if (studentAction == 'R') {
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

					mergedList.searchRS(researchScore_threshold);
				}
				else if (studentAction == 'C') {
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

					mergedList.searchCGPA(CGPA_threshold);
				}
				else if (studentAction == 'B') {
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

					mergedList.searchBoth(CGPA_threshold, researchScore_threshold); //displays students above the threshold
				}
				else if (studentAction == 'D')
					mergedList.display();
				else if (studentAction == 'Q')
					break;
				else
					cout << endl << endl << "Please enter a valid action prompt." << endl;
			}
		}
		else if ((mainAction == 'Q')) //ends the program
			break;
		else
			cout << endl << endl << "Please enter a valid action prompt." << endl;
	}
	return 0;
}