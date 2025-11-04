#include "Teacher.h"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

Teacher::Teacher() : Base() {
	group = nullptr;
	specialty = nullptr;
	size_group = 0;
	size_spec = 0;
	cout << "Teacher const without param" << endl;

}

Teacher::Teacher(const char* name, const char* group[], const char* specialty[], const int size_group, const int size_spec) : Base(name) {

	this->group = new char* [sizeof(size_group)];
	for (int i = 0; i < size_group; i++) {
		this->group[i] = new char[strlen(group[i]) + 1];
		strcpy_s(this->group[i], strlen(group[i]) + 1, group[i]);
	}
	this->specialty = new char* [sizeof(size_spec)];

	for (int i = 0; i < size_spec; i++) {
		this->specialty[i] = new char[strlen(specialty[i]) + 1];
		strcpy_s(this->specialty[i], strlen(specialty[i]) + 1, specialty[i]);
	}
	this->size_group = size_group;
	this->size_spec = size_spec;

	cout << "Teacher const with param" << endl;

}

Teacher::Teacher(const Teacher& other) : Base(other) {

	group = new char* [size_group];
	for (int i = 0; i < size_group; i++) {
		group[i] = new char[strlen(other.group[i]) + 1];
		strcpy_s(group[i], strlen(other.group[i]) + 1, other.group[i]);
	}
	specialty = new char* [size_spec];
	for (int i = 0; i < size_spec; i++) {
		specialty[i] = new char[strlen(other.specialty[i]) + 1];
		strcpy_s(specialty[i], strlen(other.specialty[i]) + 1, other.specialty[i]);
	}
	size_group = other.size_group;
	size_spec = other.size_spec;
	cout << "Teacher const copy" << endl;
}

Teacher& Teacher::operator= (const Teacher& other) {
	cout << "Teacher op copy" << endl;
	if (this != &other) {
		Base::operator=(other);

		for (int i = 0; i < size_group; i++) {
			delete group[i];
		}
		delete[] group;
		for (int i = 0; i < size_spec; i++) {
			delete specialty[i];
		}
		delete[] specialty;
		group = new char* [size_group];
		for (int i = 0; i < size_group; i++) {
			group[i] = new char[strlen(other.group[i]) + 1];
			strcpy_s(group[i], strlen(other.group[i]) + 1, other.group[i]);
		}
		specialty = new char* [size_spec];
		for (int i = 0; i < size_spec; i++) {
			specialty[i] = new char[strlen(other.specialty[i]) + 1];
			strcpy_s(specialty[i], strlen(other.specialty[i]) + 1, other.specialty[i]);
		}
		size_group = other.size_group;
		size_spec = other.size_spec;
	}
	return *this;
}

Teacher::~Teacher() {
	cout << "destruct Teacher" << endl;
	for (int i = 0; i < size_group; i++) {
		delete group[i];
	}
	delete[] group;
	for (int i = 0; i < size_spec; i++) {
		delete specialty[i];
	}
	delete[] specialty;

}

void Teacher::printInfo() const {
	cout << "Преподаватель: " << endl;
	cout << "Имя: " << GetName() << endl;
	cout << "Количество групп: " << size_group << endl;
	for (int i = 0; i < size_group; i++) {
		cout << "Группа " << i + 1 << ":" << group[i] << endl;
	}
	cout << "Количество специальностей: " << size_spec << endl;
	for (int i = 0; i < size_spec; i++) {
		cout << "Специальность " << i + 1 << ":" << specialty[i] << endl;
	}
}
void Teacher::SaveToFile(ofstream& out) const {

	out << "TEACHER\n";
	out << fullName << "\n";
	out << size_group << "\n";
	for (int i = 0; i < size_group; i++) {
		out << group[i] << "\n";
	}
	out << size_spec << "\n";
	for (int i = 0; i < size_spec; i++) {
		out << specialty[i] << "\n";
	}
}

void Teacher::LoadFromFile(ifstream& in) {
	char buffer[256];
	in.getline(buffer, 256);
	SetName(buffer);
	in >> size_group;
	in.getline(buffer, 256);
	delete[] group;
	group = new char* [size_group];
	for (int i = 0; i < size_group; i++) {
		in.getline(buffer, 256);
		group[i] = new char[strlen(buffer) + 1];
		strcpy_s(group[i], strlen(buffer) + 1, buffer);
	}
	in >> size_spec;
	delete[] specialty;
	in.getline(buffer, 256);
	specialty = new char* [size_spec];
	for (int i = 0; i < size_spec; i++) {
		in.getline(buffer, 256);
		specialty[i] = new char[strlen(buffer) + 1];
		strcpy_s(specialty[i], strlen(buffer) + 1, buffer);
	}
}
const char* Teacher::GetType() const { return "TEACHER"; };