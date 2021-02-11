//student.cpp to implement your classes
#include "student.hpp"
#include <cmath>
#include <cstdlib>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//			ToeflScore Class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ToeflScore::ToeflScore(int newReading, int newListening, int newSpeaking, int newWriting) : total(-1) {
	setTOEFL(newReading, newListening, newSpeaking, newWriting);
}

//default constructor function sets initial scores for the TOEFL components to be -1 to indicate a student forgot to enter scores
ToeflScore::ToeflScore()
	: reading(-1), listening(-1), speaking(-1), writing(-1), total(-1) {}

void ToeflScore::setTOEFL(int newReading, int newListening, int newSpeaking, int newWriting) {
	setReading(newReading);
	setListening(newListening);
	setSpeaking(newSpeaking);
	setWriting(newWriting);
}

void ToeflScore::setReading(int newReading) {								//assigns an integer value read from a file to the a variable corresponding to a TOEFL component
	if (newReading < 0)
		cout << "Error: Reading score cannot be negative" << endl;			//outputs an error message when the respective read TOEFL score is below the minimum allowed value
	else if (newReading > 30)
		cout << "Error: Reading score cannot be greater than 30" << endl;	//outputs an error message when the respective read TOEFL score is above the maximum allowed value
	else
		reading = newReading;
}

void ToeflScore::setListening(int newListening) {
	if (newListening < 0)
		cout << "Error: Listening score cannot be negative" << endl;
	else if (newListening > 30)
		cout << "Error: Listening score cannot be greater than 30" << endl;
	else
		listening = newListening;
}

void ToeflScore::setSpeaking(int newSpeaking) {
	if (newSpeaking < 0)
		cout << "Error: Speaking score cannot be negative" << endl;
	else if (newSpeaking > 30)
		cout << "Error: Speaking score cannot be greater than 30" << endl;
	else
		speaking = newSpeaking;
}

void ToeflScore::setWriting(int newWriting) {
	if (newWriting < 0)
		cout << "Error: Writing score cannot be negative" << endl;
	else if (newWriting > 30)
		cout << "Error: Writing score cannot be greater than 30" << endl;
	else
		writing = newWriting;
}

int ToeflScore::getReading() {
	return reading;
}

int ToeflScore::getListening() {
	return listening;
}

int ToeflScore::getSpeaking() {
	return speaking;
}

int ToeflScore::getWriting() {
	return writing;
}

int ToeflScore::getTotal() {	//sum of each individual component of TOEFL
	total = reading + listening + speaking + writing;
	return total;
}

ostream& operator <<(ostream& outs, ToeflScore& myToeflScore) {	//overloaded the << operator to cout TOEFL score information
	int reading, listening, speaking, writing, total;
	reading = myToeflScore.getReading();
	listening = myToeflScore.getListening();
	speaking = myToeflScore.getSpeaking();
	writing = myToeflScore.getWriting();
	total = myToeflScore.getTotal();

	outs << "TOEFL Scores: Reading - " << reading << ", Listening - " << listening
		<< ", Speaking - " << speaking << ", Writing - " << writing << ", Total - " << setw(3) << total;

	return outs;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//			Student Class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Student::Student(string newFirstName, string newLastName, float newCGPA, int newResearchScore)
	: firstName(newFirstName), lastName(newLastName), studentLink(NULL) {	//sets all values to what is read from the file
	setCGPA(newCGPA);
	setResearchScore(newResearchScore);
	setID(); //assigns an application number to the student
}

//sets CGPA and researchScore to -1 if the applicant did not enter one, -1 is used  to show that nothing was entered and that the student did not actually get a score of 0
Student::Student(string newFirstName, string newLastName)
	: CGPA(-1.0), researchScore(-1), studentLink(NULL) {
	setName(newFirstName, newLastName);	//sets the student's name to the first and second string values of a line
	setID();	//assigns an application number to the student
}

//sets CGPA and researchScore to -1 and firstName and lastName to nothing if none were read, prevents random values being assigned
Student::Student()
	: firstName(""), lastName(""), CGPA(-1.0), researchScore(-1), studentLink(NULL) {
	setID();	//assigns an application number to the student
}

void Student::setupAvailableIDs() {		//makes array of IDs to be selected by the setID function
	for (int i = 0; i < 10000; i++)
		availableIDs[i] = i;
}

void Student::setName(string newFirstName, string newLastName) {
	firstName = newFirstName;
	lastName = newLastName;
}

void Student::setFirstName(string newFirstName) {
	firstName = newFirstName;
}

void Student::setLastName(string newLastName) {
	lastName = newLastName;
}

void Student::setCGPA(float newCGPA) {
	if (newCGPA < 0)
		cout << "Error: CGPA cannot be negative" << endl; //outputs an error message when the read CGPA is below the minimum allowed value
	else if (newCGPA > 4.33)
		cout << "Error: CGPA cannot be greater than 4.33" << endl; //outputs an error message when the read CGPA is above the maximum allowed value
	else
		CGPA = newCGPA; //sets CGPA to the value read if it is within the allowed values
}

void Student::setResearchScore(int newResearchScore) {
	if (newResearchScore < 0)
		cout << "Error: Research score cannot be negative" << endl; //outputs an error message when the entered research score is below the minimum allowed value
	else if (newResearchScore > 100)
		cout << "Error: Research score cannot be greater than 100" << endl; //outputs an error message when the entered research score is above the maximum allowed value
	else
		researchScore = newResearchScore;
}

void Student::setApplicationNumber(int newApplicationNumber) {
	if (newApplicationNumber < 0)
		cout << "Error: Application number cannot be negative" << endl; //outputs an error message if the application number is not valid
	else
		applicationNumber = newApplicationNumber;
}

void Student::setStudentLink(StudentPtr newLink) {
	studentLink = newLink;
}

string Student::getFirstName() {
	return firstName;
}

string Student::getLastName() {
	return lastName;
}

float Student::getCGPA() {
	return CGPA;
}

int Student::getResearchScore() {
	return researchScore;
}

int Student::getID() {
	return ID;
}

int Student::getApplicationNumber() {
	return applicationNumber;
}

StudentPtr Student::getStudentLink() const {
	return studentLink;
}

void Student::display() {

}

//compares student information
int compareFirstName(Student student1, Student student2) {
	if (student1.firstName < student2.firstName)
		return -1;
	else if (student1.firstName == student2.firstName)
		return 0;
	else
		return 1;
}

int compareLastName(Student student1, Student student2) {
	if (student1.lastName < student2.lastName)
		return -1;
	else if (student1.lastName == student2.lastName)
		return 0;
	else
		return 1;
}

int compareCGPA(Student student1, Student student2) {
	if (student1.CGPA < student2.CGPA)
		return -1;
	else if (student1.CGPA == student2.CGPA)
		return 0;
	else
		return 1;
}

int compareResearchScore(Student student1, Student student2) {
	if (student1.researchScore < student2.researchScore)
		return -1;
	else if (student1.researchScore == student2.researchScore)
		return 0;
	else
		return 1;
}

int Student::applicationNumber = 0;
int Student::availableIDs[] = { 0 };
void Student::setID() {								//generates random ID for students
	int remainingSeats, selection, partialID;

	remainingSeats = 10000 - applicationNumber;
	if (remainingSeats < 1)							//if there are < 1 seats, no more seats left
		cout << "Sorry, there are no more seats available." << endl;

	selection = rand() % (remainingSeats + 1);
	partialID = availableIDs[selection];
	ID = 20200000 + partialID;						//generates a unique student ID starting at 20200000

	availableIDs[selection] = availableIDs[remainingSeats];
	applicationNumber++;							//increases the value of the student ID by 1 every time it runs again
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//		DomesticStudent Class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DomesticStudent::DomesticStudent(string newFirstName, string newLastName, float newCGPA, int newResearchScore, string newProvince)
	: Student(newFirstName, newLastName, newCGPA, newResearchScore), province(newProvince), link(NULL) {}

DomesticStudent::DomesticStudent(string newFirstName, string newLastName, float newCGPA, int newResearchScore)
	: Student(newFirstName, newLastName, newCGPA, newResearchScore), province(""), link(NULL) {}

DomesticStudent::DomesticStudent(string newFirstName, string newLastName)
	: Student(newFirstName, newLastName), province(""), link(NULL) {}

DomesticStudent::DomesticStudent()
	: Student(), province(""), link(NULL) {}

void DomesticStudent::setProvince(string newProvince) {
	province = newProvince;
}

void DomesticStudent::setLink(DomesticStudentPtr newLink) {
	link = newLink;
}

string DomesticStudent::getProvince() {
	return province;
}

DomesticStudentPtr DomesticStudent::getLink() const {
	return link;
}

void DomesticStudent::display() {
	string firstName, lastName;
	float CGPA;
	int researchScore, ID;

	firstName = getFirstName();
	lastName = getLastName();
	CGPA = getCGPA();
	researchScore = getResearchScore();
	ID = getID();

	cout << "Domestic Student: " << firstName << " " << lastName << ", ID: " << ID << ", Province: " << province << endl
		<< "CGPA: " << fixed << setprecision(2) << CGPA << ", Research Score: " << setw(3) << researchScore;
}

int compareProvince(DomesticStudent student1, DomesticStudent student2) {	//compare the province string
	if (student1.province < student2.province)
		return -1;
	else if (student1.province == student2.province)
		return 0;
	else
		return 1;
}

ostream& operator <<(ostream& outs, DomesticStudent& myDomesticStudent) {	//overloaded the << operator to cout domestic student information
	string firstName, lastName, province;
	float CGPA;
	int researchScore, ID;

	firstName = myDomesticStudent.getFirstName();
	lastName = myDomesticStudent.getLastName();
	province = myDomesticStudent.getProvince();
	CGPA = myDomesticStudent.getCGPA();
	researchScore = myDomesticStudent.getResearchScore();
	ID = myDomesticStudent.getID();

	outs << "Domestic Student: " << firstName << " " << lastName << ", ID: " << ID << ", Province: " << province << endl
		<< "CGPA: " << fixed << setprecision(2) << CGPA << ", Research Score: " << setw(3) << researchScore;

	return outs;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//		InternationalStudent Class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
InternationalStudent::InternationalStudent(string newFirstName, string newLastName, float newCGPA, int newResearchScore, string newCountry, int newReading, int newListening, int newSpeaking, int newWriting)
	: Student(newFirstName, newLastName, newCGPA, newResearchScore), country(newCountry), link(NULL) {
	TOEFL.setTOEFL(newReading, newListening, newSpeaking, newWriting);
}

InternationalStudent::InternationalStudent(string newFirstName, string newLastName, float newCGPA, int newResearchScore, string newCountry)
	: Student(newFirstName, newLastName, newCGPA, newResearchScore), country(newCountry), link(NULL) {}

InternationalStudent::InternationalStudent(string newFirstName, string newLastName, float newCGPA, int newResearchScore)
	: Student(newFirstName, newLastName, newCGPA, newResearchScore), country(""), link(NULL) {}

InternationalStudent::InternationalStudent(string newFirstName, string newLastName)
	: Student(newFirstName, newLastName), country(""), link(NULL) {}

InternationalStudent::InternationalStudent()
	: Student(), country(""), link(NULL) {}

void InternationalStudent::setCountry(string newCountry) {
	country = newCountry;
}

void InternationalStudent::setLink(InternationalStudentPtr newLink) {
	link = newLink;
}

string InternationalStudent::getCountry() {
	return country;
}

InternationalStudentPtr InternationalStudent::getLink() const {
	return link;
}

void InternationalStudent::display() {
	string firstName, lastName;
	float CGPA;
	int researchScore, ID;

	firstName = getFirstName();
	lastName = getLastName();
	CGPA = getCGPA();
	researchScore = getResearchScore();
	ID = getID();

	cout << "International Student: " << firstName << " " << lastName << ", ID: " << ID << ", Country: " << country << endl
		<< "CGPA: " << fixed << setprecision(2) << CGPA << ", Research Score: " << setw(3) << researchScore
		<< ", " << TOEFL;
}

int compareCountry(InternationalStudent student1, InternationalStudent student2) {	//compare the country string
	if (student1.country < student2.country)
		return -1;
	else if (student1.country == student2.country)
		return 0;
	else
		return 1;
}

ostream& operator <<(ostream& outs, InternationalStudent& myInternationalStudent) {	//overloaded the << operator to cout international student information
	string firstName, lastName, country;
	float CGPA;
	int researchScore, ID;

	firstName = myInternationalStudent.getFirstName();
	lastName = myInternationalStudent.getLastName();
	country = myInternationalStudent.getCountry();
	CGPA = myInternationalStudent.getCGPA();
	researchScore = myInternationalStudent.getResearchScore();
	ID = myInternationalStudent.getID();

	outs << "International Student: " << firstName << " " << lastName << ", ID: " << ID << ", Country: " << country << endl
		<< "CGPA: " << fixed << setprecision(2) << CGPA << ", Research Score: " << setw(3) << researchScore
		<< ", " << myInternationalStudent.TOEFL;

	return outs;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//		Domestic Student Linked List
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DomesticList::DomesticList()
	: head(NULL), tail(NULL) {}

DomesticList::DomesticList(DomesticList& list) : head(NULL), tail(NULL) {
	DomesticStudentPtr current = list.head;
	while (current != NULL) {
		createEnd(current->getFirstName(), current->getLastName(), current->getCGPA(), current->getResearchScore(), current->getProvince());
		current = current->getLink();
	}
}

void DomesticList::createEnd(string newFirstName, string newLastName, float newCGPA, int newResearchScore, string newProvince) {
	DomesticStudentPtr tempPtr = new DomesticStudent(newFirstName, newLastName, newCGPA, newResearchScore, newProvince);

	if (head == NULL) {
		head = tempPtr;
		tail = tempPtr;
	}
	else {
		tail->setLink(tempPtr);
		tail = tempPtr;
	}
}

void DomesticList::createSorted(string newFirstName, string newLastName, float newCGPA, int newResearchScore, string newProvince) {
	DomesticStudentPtr tempPtr = new DomesticStudent(newFirstName, newLastName, newCGPA, newResearchScore, newProvince);

	if (head == NULL) {
		head = tempPtr;
		tail = tempPtr;
		return;
	}

	DomesticStudentPtr after = head;
	int comparison = compareStudent(*tempPtr, *after, 'O');

	if ((comparison == -1) || (comparison == 0)) {
		tempPtr->setLink(after);
		head = tempPtr;
		return;
	}

	while (after->getLink() != NULL) {
		DomesticStudentPtr before = after;
		after = after->getLink();
		comparison = compareStudent(*tempPtr, *after, 'O');

		if ((comparison == -1) || (comparison == 0)) {
			tempPtr->setLink(after);
			before->setLink(tempPtr);
			return;
		}
	}

	DomesticStudentPtr before = after;		//insert after tail
	after = after->getLink();
	tempPtr->setLink(after);
	before->setLink(tempPtr);
	tail = tempPtr;
}

void DomesticList::removeHead() {
	if (head == NULL)
		return;
	else if (head == tail) {
		delete head;
		head = NULL;
		tail = NULL;
		return;
	}
	DomesticStudentPtr target = head;
	head = target->getLink();
	delete target;
}

void DomesticList::removeTail() {
	if (tail == NULL)
		return;
	else if (tail == head) {
		delete tail;
		tail = NULL;
		head = NULL;
		return;
	}

	DomesticStudentPtr targetTail = tail;
	DomesticStudentPtr beforeTail = head;
	while (beforeTail->getLink() != tail)
		beforeTail = beforeTail->getLink();

	tail = beforeTail;
	beforeTail->setLink(NULL);
	delete targetTail;
}

void DomesticList::removeHeadTail() {
	removeHead();
	removeTail();
}

void DomesticList::remove(DomesticStudentPtr& before) {
	DomesticStudentPtr target = before->getLink();
	if (target == tail)
		tail = before;

	before->setLink(target->getLink());
	delete target;
}

void DomesticList::removeName(string firstName, string lastName) {
	bool found = false;
	formatString(firstName);
	formatString(lastName);
	while ((head->getFirstName() == firstName) && (head->getLastName() == lastName)) {
		removeHead();
		cout << "Domestic student removed!" << endl;
		found = true;
	}

	DomesticStudentPtr before = head;
	DomesticStudentPtr target = head->getLink();
	while (target != NULL) {
		if ((target->getFirstName() == firstName) && (target->getLastName() == lastName)) {
			remove(before);
			target = before->getLink();
			cout << "Domestic student removed!" << endl;
			found = true;
		}
		else {
			before = target;
			target = target->getLink();
		}
	}

	if (found == false)
		cout << "No match found" << endl;
}

void DomesticList::search(double number, char searchType) { //search function for numerical values for domestic students
	bool found = false;
	DomesticStudentPtr target = head;

	cout << endl;
	while (target != NULL) {
		if (searchType == 'A') { //searches by application ID
			if (target->getID() == int(number)) {
				cout << *target << endl;
				found = true; //returns true if the specified ID is found
			}
		}
		else if (searchType == 'C') { //searches by CGPA
			if (abs(target->getCGPA() - number) < 0.005) {
				cout << *target << endl;
				found = true; //returns true if the specified CGPA is found
			}
		}
		else if (searchType == 'R') { //searches by research score
			if (target->getResearchScore() == int(number)) {
				cout << *target << endl;
				found = true; //returns true if the specified research score is found
			}
		}

		target = target->getLink();
	}

	if (found == false)
		cout << "No match found." << endl; // returns false if nothing in the list matches the user input
}

void DomesticList::search(string firstName, string lastName) { //search function for string values for domestic students
	bool found = false;
	DomesticStudentPtr target = head;
	formatString(firstName);
	formatString(lastName);

	cout << endl;
	while (target != NULL) { //searches for a student with the specified first and last name
		if ((target->getFirstName() == firstName) && (target->getLastName() == lastName)) {
			cout << *target << endl;
			found = true; // returns true if the student exists within the list
		}

		target = target->getLink();
	}

	if (found == false)
		cout << "No match found." << endl; // returns false if the student is not found
}

DomesticStudentPtr DomesticList::getHead() {
	return head;
}

void DomesticList::display() {
	if (head == NULL) {
		cout << "The domestic list is empty!" << endl;
		return;
	}
	DomesticStudentPtr tempPtr = new DomesticStudent;
	tempPtr = head;

	while (tempPtr != NULL) {
		cout << *tempPtr << endl;
		tempPtr = tempPtr->getLink();
	}
}

DomesticList::~DomesticList() {
	while (head != NULL)
		removeHead();
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	International Student Linked List
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
InternationalList::InternationalList()
	: head(NULL), tail(NULL) {}

InternationalList::InternationalList(InternationalList& list) : head(NULL), tail(NULL) {
	InternationalStudentPtr current = list.head;
	while (current != NULL) {
		createEnd(current->getFirstName(), current->getLastName(), current->getCGPA(), current->getResearchScore(), current->getCountry(),
			current->TOEFL.getReading(), current->TOEFL.getListening(), current->TOEFL.getSpeaking(), current->TOEFL.getWriting());
		current = current->getLink();
	}
}

void InternationalList::createEnd(string newFirstName, string newLastName, float newCGPA, int newResearchScore, string newCountry, int newReading, int newListening, int newSpeaking, int newWriting) {
	InternationalStudentPtr tempPtr = new InternationalStudent(newFirstName, newLastName, newCGPA, newResearchScore, newCountry, newReading, newListening, newSpeaking, newWriting);

	if (head == NULL) {
		head = tempPtr;
		tail = tempPtr;
	}
	else {
		tail->setLink(tempPtr);
		tail = tempPtr;
	}
}

void InternationalList::createSorted(string newFirstName, string newLastName, float newCGPA, int newResearchScore, string newCountry, int newReading, int newListening, int newSpeaking, int newWriting) {
	InternationalStudentPtr tempPtr = new InternationalStudent(newFirstName, newLastName, newCGPA, newResearchScore, newCountry, newReading, newListening, newSpeaking, newWriting);

	if (tempPtr->TOEFL.getTotal() < 93)			//TOEFL requirements
		return;
	else if (tempPtr->TOEFL.getReading() < 20)
		return;
	else if (tempPtr->TOEFL.getListening() < 20)
		return;
	else if (tempPtr->TOEFL.getSpeaking() < 20)
		return;
	else if (tempPtr->TOEFL.getWriting() < 20)
		return;

	if (head == NULL) {
		head = tempPtr;
		tail = tempPtr;
		return;
	}

	InternationalStudentPtr after = head;
	int comparison = compareStudent(*tempPtr, *after, 'O');

	if ((comparison == -1) || (comparison == 0)) {
		tempPtr->setLink(after);
		head = tempPtr;
		return;
	}

	while (after->getLink() != NULL) {
		InternationalStudentPtr before = after;
		after = after->getLink();
		comparison = compareStudent(*tempPtr, *after, 'O');

		if ((comparison == -1) || (comparison == 0)) {
			tempPtr->setLink(after);
			before->setLink(tempPtr);
			return;
		}
	}

	InternationalStudentPtr before = after;		//insert after tail
	after = after->getLink();
	tempPtr->setLink(after);
	before->setLink(tempPtr);
	tail = tempPtr;
}

void InternationalList::removeHead() {
	if (head == NULL)
		return;
	else if (head == tail) {
		delete head;
		head = NULL;
		tail = NULL;
		return;
	}
	InternationalStudentPtr target = head;
	head = target->getLink();
	delete target;
}

void InternationalList::removeTail() {
	if (tail == NULL)
		return;
	else if (tail == head) {
		delete tail;
		tail = NULL;
		head = NULL;
		return;
	}

	InternationalStudentPtr targetTail = tail;
	InternationalStudentPtr beforeTail = head;
	while (beforeTail->getLink() != tail)
		beforeTail = beforeTail->getLink();

	tail = beforeTail;
	beforeTail->setLink(NULL);
	delete targetTail;
}

void InternationalList::removeHeadTail() {
	removeHead();
	removeTail();
}

void InternationalList::remove(InternationalStudentPtr& before) {
	InternationalStudentPtr target = before->getLink();
	if (target == tail)
		tail = before;

	before->setLink(target->getLink());
	delete target;
}

void InternationalList::removeName(string firstName, string lastName) {
	bool found = false;
	formatString(firstName);
	formatString(lastName);
	while ((head->getFirstName() == firstName) && (head->getLastName() == lastName)) {
		removeHead();
		cout << "International student deleted!" << endl;
		found = true;
	}

	InternationalStudentPtr before = head;
	InternationalStudentPtr target = head->getLink();
	while (target != NULL) {
		if ((target->getFirstName() == firstName) && (target->getLastName() == lastName)) {
			remove(before);
			target = before->getLink();
			cout << "International student deleted!" << endl;
			found = true;
		}
		else {
			before = target;
			target = target->getLink();
		}
	}

	if (found == false)
		cout << "No match found" << endl;
}

void InternationalList::search(double number, char searchType) { //search function for numerical values in the international linked list
	bool found = false;
	InternationalStudentPtr target = head;

	cout << endl;
	while (target != NULL) {
		if (searchType == 'A') {
			if (target->getID() == int(number)) {
				cout << *target << endl;
				found = true;
			}
		}
		else if (searchType == 'C') {
			if (abs(target->getCGPA() - number) < 0.005) {
				cout << *target << endl;
				found = true;
			}
		}
		else if (searchType == 'R') {
			if (target->getResearchScore() == int(number)) {
				cout << *target << endl;
				found = true;
			}
		}

		target = target->getLink();
	}

	if (found == false)
		cout << "No match found." << endl;
}

void InternationalList::search(string firstName, string lastName) { //search function for sting values in the international linked list
	bool found = false;
	InternationalStudentPtr target = head;
	formatString(firstName);
	formatString(lastName);

	cout << endl;
	while (target != NULL) {
		if ((target->getFirstName() == firstName) && (target->getLastName() == lastName)) {
			cout << *target << endl;
			found = true;
		}

		target = target->getLink();
	}

	if (found == false)
		cout << "No match found." << endl;
}

InternationalStudentPtr InternationalList::getHead() {
	return head;
}

void InternationalList::display() {
	if (head == NULL) {
		cout << "The international list is empty!" << endl;
		return;
	}
	InternationalStudentPtr tempPtr = new InternationalStudent;
	tempPtr = head;

	while (tempPtr != NULL) {
		cout << *tempPtr << endl;
		tempPtr = tempPtr->getLink();
	}
}

InternationalList::~InternationalList() {
	while (head != NULL)
		removeHead();
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//		Merged Linked List
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MergedList::MergedList()
	: head(NULL), tail(NULL) {}

void MergedList::addEnd(DomesticStudentPtr newStudentPtr) {
	DomesticStudentPtr tmp = new DomesticStudent(newStudentPtr->getFirstName(), newStudentPtr->getLastName(), newStudentPtr->getCGPA(), newStudentPtr->getResearchScore(),
		newStudentPtr->getProvince());

	StudentPtr studentPtr = tmp;
	if (head == NULL) {
		head = studentPtr;
		tail = studentPtr;
	}
	else {
		tail->setStudentLink(studentPtr);
		tail = studentPtr;
	}
}

void MergedList::addEnd(InternationalStudentPtr newStudentPtr) {
	InternationalStudentPtr tmp = new InternationalStudent(newStudentPtr->getFirstName(), newStudentPtr->getLastName(), newStudentPtr->getCGPA(), newStudentPtr->getResearchScore(),
		newStudentPtr->getCountry(), newStudentPtr->TOEFL.getReading(), newStudentPtr->TOEFL.getListening(), newStudentPtr->TOEFL.getSpeaking(), newStudentPtr->TOEFL.getWriting());

	StudentPtr studentPtr = tmp;
	if (head == NULL) {
		head = studentPtr;
		tail = studentPtr;
	}
	else {
		tail->setStudentLink(studentPtr);
		tail = studentPtr;
	}
}

void MergedList::mergeLists(DomesticList domesticList, InternationalList internationalList) {
	DomesticStudentPtr domesticPtr = domesticList.getHead();
	InternationalStudentPtr internationalPtr = internationalList.getHead();

	int compared;

	while ((domesticPtr != NULL) && (internationalPtr != NULL)) {
		compared = compareStudent(*domesticPtr, *internationalPtr);

		if (compared == -1) {
			addEnd(domesticPtr);
			if (domesticPtr->getLink() == NULL)
				break;
			domesticPtr = domesticPtr->getLink();
		}
		else if (compared == 1) {
			addEnd(internationalPtr);
			if (internationalPtr->getLink() == NULL)
				break;
			internationalPtr = internationalPtr->getLink();
		}
		else {
			addEnd(domesticPtr);
			if (domesticPtr->getLink() == NULL)
				break;
			domesticPtr = domesticPtr->getLink();
		}
	}

	while (domesticPtr == NULL) {
		if (internationalPtr == NULL)
			return;
		addEnd(internationalPtr);
		internationalPtr = internationalPtr->getLink();
	}

	while (internationalPtr == NULL) {
		if (domesticPtr == NULL)
			return;
		addEnd(domesticPtr);
		domesticPtr = domesticPtr->getLink();
	}
}

void MergedList::removeHead() {
	if (head == NULL)
		return;
	else if (head == tail) {
		delete head;
		head = NULL;
		tail = NULL;
		return;
	}
	StudentPtr target = head;
	head = target->getStudentLink();
	delete target;
}

void MergedList::searchCGPA(float CGPA_threshold) {
	bool found = false;
	StudentPtr target = head;

	cout << endl;
	while (target != NULL) {
		if (target->getCGPA() >= CGPA_threshold) {
			target->display();
			cout << endl;
			found = true;
		}

		target = target->getStudentLink();
	}

	if (found == false)
		cout << "No match found." << endl;
}

void MergedList::searchRS(int RS_threshold) {
	bool found = false;
	StudentPtr target = head;

	cout << endl;
	while (target != NULL) {
		if (target->getResearchScore() >= RS_threshold) {
			target->display();
			cout << endl;
			found = true;
		}

		target = target->getStudentLink();
	}

	if (found == false)
		cout << "No match found." << endl;
}

void MergedList::searchBoth(float CGPA_threshold, int RS_threshold) {
	bool found = false;
	StudentPtr target = head;

	cout << endl;
	while (target != NULL) {
		if ((target->getCGPA() >= CGPA_threshold) && (target->getResearchScore() >= RS_threshold)) {
			target->display();
			cout << endl;
			found = true;
		}

		target = target->getStudentLink();
	}

	if (found == false)
		cout << "No match found." << endl;
}

void MergedList::display() {
	if (head == NULL) {
		cout << "The merged list is empty!" << endl;
		return;
	}
	StudentPtr tempPtr = new Student;
	tempPtr = head;

	while (tempPtr != NULL) {
		tempPtr->display();
		cout << endl;
		tempPtr = tempPtr->getStudentLink();
	}
}

MergedList::~MergedList() {
	while (head != NULL)
		removeHead();
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//		Function Definitions
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void formatString(string& myString) {	//formats the string for sorting
	myString[0] = toupper(myString[0]);	//capitalizes the first char

	int i = 1;
	while (myString[i]) {				//lowercases the rest of the string
		myString[i] = tolower(myString[i]);
		i++;
	}
}

int compareStudent(DomesticStudent student1, DomesticStudent student2, char sortType) {		//function to compare domestic students
	int tmp = -2;
	if (sortType == 'C')											//compares students based on the user's preferences
		tmp = compareCGPA(student1, student2);
	else if (sortType == 'R')
		tmp = compareResearchScore(student1, student2);
	else if (sortType == 'F')
		return compareFirstName(student1, student2);
	else if (sortType == 'L')
		return compareLastName(student1, student2);
	else if (sortType == 'O') {
		int comparedRS = compareResearchScore(student1, student2);	//overall student comparing
		if (comparedRS == 0) {
			int comparedCGPA = compareCGPA(student1, student2);		//compares CGPA of students if their research scores are equivalent
			if (comparedCGPA == 0)
				return compareProvince(student1, student2);			//then compares province last
			else
				tmp = comparedCGPA;
		}
		else
			tmp = comparedRS;
	}

	if (tmp == -1)		//research score and CGPA are sorted high to low
		return 1;
	else if (tmp == 1)
		return -1;
	else
		return tmp;
}

int compareStudent(InternationalStudent student1, InternationalStudent student2, char sortType) {	//function to compare international students
	int tmp = -2;
	if (sortType == 'C')											//compares students based on the user's preferences
		tmp = compareCGPA(student1, student2);
	else if (sortType == 'R')
		tmp = compareResearchScore(student1, student2);
	else if (sortType == 'F')
		return compareFirstName(student1, student2);
	else if (sortType == 'L')
		return compareLastName(student1, student2);
	else if (sortType == 'O') {
		int comparedRS = compareResearchScore(student1, student2);	//overall student comparing
		if (comparedRS == 0) {
			int comparedCGPA = compareCGPA(student1, student2);		//compares CGPA of students if their research scores are equivalent
			if (comparedCGPA == 0)
				return compareCountry(student1, student2);			//then compares province last
			else
				tmp = comparedCGPA;
		}
		else
			tmp = comparedRS;
	}

	if (tmp == -1)		//research score and CGPA are sorted high to low
		return 1;
	else if (tmp == 1)
		return -1;
	else
		return tmp;
}

int compareStudent(DomesticStudent student1, InternationalStudent student2) {
	int tmp = -2;
	int comparedRS = compareResearchScore(student1, student2);
	if (comparedRS == 0)
		tmp = compareCGPA(student1, student2);
	else
		tmp = comparedRS;

	if (tmp == -1)		//research score and CGPA are sorted high to low
		return 1;
	else if (tmp == 1)
		return -1;
	else
		return tmp;
}