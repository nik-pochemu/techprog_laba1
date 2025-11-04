#include "Student.h"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

Student::Student() : Base() {
    group = new char[1]; group[0] = '\0';
    specialty = new char[1]; specialty[0] = '\0';
    course = 0; gpa = 0.0;
    cout << "Student const without param" << endl;
}

Student::Student(const char* name, const char* group, const char* specialty, int course, double gpa) : Base(name) {
    this->group = new char[strlen(group) + 1];
    strcpy_s(this->group, strlen(group) + 1, group);
    this->specialty = new char[strlen(specialty) + 1];
    strcpy_s(this->specialty, strlen(specialty) + 1, specialty);
    this->course = course;
    this->gpa = gpa;
    cout << "Student const with param" << endl;
}

Student::Student(const Student& other) : Base(other) {
    group = new char[strlen(other.group) + 1];
    strcpy_s(group, strlen(other.group) + 1, other.group);
    specialty = new char[strlen(other.specialty) + 1];
    strcpy_s(specialty, strlen(other.specialty) + 1, other.specialty);
    course = other.course;
    gpa = other.gpa;
    cout << "Student const copy" << endl;
}

Student& Student::operator=(const Student& other) {
    cout << "Student op copy" << endl;
    if (this != &other) {
        Base::operator=(other);
        delete[] group;
        delete[] specialty;
        group = new char[strlen(other.group) + 1];
        strcpy_s(group, strlen(other.group) + 1, other.group);
        specialty = new char[strlen(other.specialty) + 1];
        strcpy_s(specialty, strlen(other.specialty) + 1, other.specialty);
        course = other.course;
        gpa = other.gpa;
    }
    return *this;
}

Student::~Student() {
    cout << "destruct Student" << endl;
    delete[] group;
    delete[] specialty;
}

void Student::printInfo() const {
    cout << "Студент: " << endl;
    cout << "Имя: " << GetName() << endl;
    cout << "Группа: " << group << endl;
    cout << "Направление: " << specialty << endl;
    cout << "Курс: " << course << endl;
    cout << "Средний балл: " << gpa << endl;
}

void Student::SaveToFile(ofstream& out) const {
    out << "STUDENT\n";
    out << fullName << "\n";
    out << group << "\n";
    out << specialty << "\n";
    out << course << "\n" << gpa << "\n";
}

void Student::LoadFromFile(ifstream& in) {
    char buffer[256];
    in.getline(buffer, 256);
    SetName(buffer);
    in.getline(buffer, 256);
    delete[] group;
    group = new char[strlen(buffer) + 1];
    strcpy_s(group, strlen(buffer) + 1, buffer);
    in.getline(buffer, 256);
    delete[] specialty;
    specialty = new char[strlen(buffer) + 1];
    strcpy_s(specialty, strlen(buffer) + 1, buffer);
    in >> course;
    in >> gpa;
    in.ignore();
}

const char* Student::GetType() const { return "STUDENT"; }
