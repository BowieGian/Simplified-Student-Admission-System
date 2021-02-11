//header file student.hpp to declare your classes

#ifndef STUDENT_H
#define STUDENT_H

using namespace std;	//use namespace std
#include <string>		//strings
#include <iostream>		//cin and cout
#include <iomanip>		//fixed and setprecision
#include <cstdlib>		//rand() and srand()
#include <ctime>		//time()

class ToeflScore {		//declares Class ToeflScore
public: //allows members below to be accessed outside of the class
	ToeflScore(int newReading, int newListening, int newSpeaking, int newWriting);		//initializes objects of type ToeflScore
	ToeflScore();
	void setTOEFL(int newReading, int newListening, int newSpeaking, int newWriting);	//sets the score of their respective part of the TOEFL test
	void setReading(int newReading);
	void setListening(int newListening);
	void setSpeaking(int newSpeaking);
	void setWriting(int newWriting);

	int getReading();	//gets the score of their respective part of the TOEFL test
	int getListening();
	int getSpeaking();
	int getWriting();
	int getTotal();		//gets the sum of the scores of the different components of TOEFL
	friend ostream& operator <<(ostream& outs, ToeflScore& myToeflScore);

private: //members below can not be used outside of the class
	int reading, listening, speaking, writing, total;
};

typedef class Student* StudentPtr;
class Student {		//declares class Student
public: //allows members below to be accessed outside of the class	
	Student(string newFirstName, string newLastName, float newCGPA, int newResearchScore);	//initializes objects of type Student
	Student(string newFirstName, string newLastName);
	Student();
	static void setupAvailableIDs();

	void setName(string newFirstName, string newLastName);
	void setFirstName(string newFirstName);
	void setLastName(string newLastName);
	void setCGPA(float newCGPA);
	void setResearchScore(int newResearchScore);
	static void setApplicationNumber(int newApplicationNumber);
	void setStudentLink(StudentPtr newLink);

	string getFirstName();
	string getLastName();
	float getCGPA();
	int getResearchScore();
	int getID();
	static int getApplicationNumber();
	StudentPtr getStudentLink() const;

	virtual void display();

	friend int compareFirstName(Student student1, Student student2);		//outputs -1 if student1 < student2
	friend int compareLastName(Student student1, Student student2);			//outputs 0 if student1 == student2
	friend int compareCGPA(Student student1, Student student2);				//outputs 1 if student1 > student2
	friend int compareResearchScore(Student student1, Student student2);
private: //members below can not be used outside of the class
	void setID();	//creates unique ID for each student

	string firstName, lastName;
	float CGPA;
	int researchScore, ID;
	static int applicationNumber;	//variable to count the number of applications (static values stay constant for every object in the class)
	static int availableIDs[10000];
	StudentPtr studentLink;
};

typedef class DomesticStudent* DomesticStudentPtr;
class DomesticStudent : public Student {	//declares class DomesticStudent, which inherits class Student
public: //allows members below to be accessed outside of the class
	DomesticStudent(string newFirstName, string newLastName, float newCGPA, int newResearchScore, string newProvince);
	DomesticStudent(string newFirstName, string newLastName, float newCGPA, int newResearchScore);
	DomesticStudent(string newFirstName, string newLastName);
	DomesticStudent();

	void setProvince(string newProvince);	//indicates where in Canada the student is from in case there are region-specific scholarships, etc.
	void setLink(DomesticStudentPtr newLink);
	string getProvince();
	DomesticStudentPtr getLink() const;

	virtual void display();

	friend int compareProvince(DomesticStudent student1, DomesticStudent student2);
	friend ostream& operator <<(ostream& outs, DomesticStudent& myDomesticStudent);
private: //members below can not be used outside of the class
	string province;
	DomesticStudentPtr link;
};

typedef class InternationalStudent* InternationalStudentPtr;
class InternationalStudent : public Student {	//declares class InternationalStudent, which inherits class Student
public: //allows members below to be accessed outside of the class
	InternationalStudent(string newFirstName, string newLastName, float newCGPA, int newResearchScore, string newCountry, int newReading, int newListening, int newSpeaking, int newWriting);
	InternationalStudent(string newFirstName, string newLastName, float newCGPA, int newResearchScore, string newCountry);
	InternationalStudent(string newFirstName, string newLastName, float newCGPA, int newResearchScore);
	InternationalStudent(string newFirstName, string newLastName);
	InternationalStudent();

	void setCountry(string newCountry); //shows which country the international applicant is from
	void setLink(InternationalStudentPtr newLink);
	string getCountry();
	InternationalStudentPtr getLink() const;

	virtual void display();

	friend int compareCountry(InternationalStudent student1, InternationalStudent student2);
	friend ostream& operator <<(ostream& outs, InternationalStudent& myInternationalStudent);

	ToeflScore TOEFL;
private: //members below can not be used outside of the class
	string country;
	InternationalStudentPtr link;
};

class DomesticList {
public:
	//default constructor
	DomesticList();
	//copy constructor
	DomesticList(DomesticList& list);

	//creates a new Domestic Student at the end
	void createEnd(string newFirstName, string newLastName, float newCGPA, int newResearchScore, string newProvince);
	//creates a new Domestic Student and inserts it into the sorted list
	void createSorted(string newFirstName, string newLastName, float newCGPA, int newResearchScore, string newProvince);

	//removes head node
	void removeHead();
	//removes tail node
	void removeTail();
	//removes head and tail node(s)
	void removeHeadTail();
	//removes the node after 'before'
	void remove(DomesticStudentPtr& before);
	//removes nodes with matching first and last names
	void removeName(string firstName, string lastName);

	//displays students with matching information
	void search(double number, char searchType);
	void search(string firstName, string lastName);

	//returns head
	DomesticStudentPtr getHead();
	//displays the whole list
	void display();

	//destructor that deletes all the nodes
	~DomesticList();
private:
	//head and tail of the list
	DomesticStudentPtr head, tail;
};

class InternationalList {
public:
	//default constructor
	InternationalList();
	//copy constructor
	InternationalList(InternationalList& list);

	//creates a new International Student at the end
	void createEnd(string newFirstName, string newLastName, float newCGPA, int newResearchScore, string newCountry, int newReading, int newListening, int newSpeaking, int newWriting);
	//creates a new International Student and inserts it into the sorted list
	void createSorted(string newFirstName, string newLastName, float newCGPA, int newResearchScore, string newCountry, int newReading, int newListening, int newSpeaking, int newWriting);

	//removes head node
	void removeHead();
	//removes tail node
	void removeTail();
	//removes head and tail node(s)
	void removeHeadTail();
	//removes the node after 'before'
	void remove(InternationalStudentPtr& before);
	//removes nodes with matching first and last names
	void removeName(string firstName, string lastName);

	//displays students with matching information
	void search(double number, char searchType);
	void search(string firstName, string lastName);

	//returns head
	InternationalStudentPtr getHead();
	//displays the whole list
	void display();

	//destructor that deletes all the nodes
	~InternationalList();
private:
	//head and tail of the list
	InternationalStudentPtr head, tail;
};

class MergedList {
public:
	//default constructor
	MergedList();

	//add child objects to the end of the list
	void addEnd(DomesticStudentPtr newStudentPtr);
	void addEnd(InternationalStudentPtr newStudentPtr);

	//merge the two lists sorted
	void mergeLists(DomesticList domesticList, InternationalList internationalList);
	//remove head
	void removeHead();
	//display students over both the threshold
	void searchCGPA(float CGPA_threshold);
	void searchRS(int RS_threshold);
	void searchBoth(float CGPA_threshold, int RS_threshold);

	//use virtual functions to display students
	void display();

	//destructor that deletes all the nodes
	~MergedList();
private:
	StudentPtr head, tail;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//		Function Declarations
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//input a string with one word
//capitalizes the first letter and lowercases the rest
void formatString(string& myString);

//input two students to compare and the type of comparison 
//compares two students based on the method chosen by the user
int compareStudent(DomesticStudent student1, DomesticStudent student2, char sortType);
int compareStudent(InternationalStudent student1, InternationalStudent student2, char sortType);
int compareStudent(DomesticStudent student1, InternationalStudent student2);
#endif