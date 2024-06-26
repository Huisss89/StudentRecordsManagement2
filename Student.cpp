#include <iostream>
#include <iomanip>

#include "Student.h"


using namespace std;


Student::Student()
{
	strcpy_s(name, " ");
	id = 0;
	strcpy_s(address, " ");
	strcpy_s(DOB, " ");
	strcpy_s(course, " ");
	strcpy_s(phone_no, " ");
	cgpa = 0.0;

}


void Student::print(ostream &out)
{
	out << "\nName: " << name;
	out << "\nID: " << id;
	out << "\nAddress: " << address;
	out << "\nDate of Birth: " << DOB;
	out << "\nPhone No: " << phone_no;
	out << "\nCourse: " << course;
	out << "\nCGPA: " << fixed<<setprecision(5)<<cgpa;
	out << "\n";

}


bool Student::compare1(Student p2)
{
	if (id > p2.id)
		return true;
	return false;

}


bool Student::compare2(Student p2)
{
	if (id == p2.id)
		return true;
	return false;
}



bool Student::compare3(int id2)
{
	if (id == id2)
		return true;
	return false;
}
