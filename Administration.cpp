#include "Administration.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

Administration::Administration() : Base() {
	number = new char[1];
	number[0] = '\0';
	specialty = new char[1];
	specialty[0] = '\0';
	zone = new char[1];
	zone[0] = '\0';
	cout << "Admin const without param" << endl;
}

Administration::Administration(const char* name, const char* number, const char* specialty, const char* zone) : Base(name) {
	this->number = new char[strlen(number) + 1];
	strcpy_s(this->number, strlen(number) + 1, number);
	this->specialty = new char[strlen(specialty) + 1];
	strcpy_s(this->specialty, strlen(specialty) + 1, specialty);
	this->zone = new char[strlen(zone) + 1];
	strcpy_s(this->zone, strlen(zone) + 1, zone);
	cout << "Admin const with param" << endl;

}

Administration::Administration(const Administration& other) : Base(other) {
	number = new char[strlen(other.number) + 1];
	strcpy_s(number, strlen(other.number) + 1, other.number);
	specialty = new char[strlen(other.specialty) + 1];
	strcpy_s(specialty, strlen(other.specialty) + 1, other.specialty);
	zone = new char[strlen(other.zone) + 1];
	strcpy_s(zone, strlen(other.zone) + 1, other.zone);
	cout << "Admin const copy" << endl;
}

Administration& Administration :: operator= (const Administration& other) {
	cout << "Admin op copy" << endl;
	if (this != &other) {
		Base::operator=(other);
		delete[] number;
		delete[] specialty;
		delete[] zone;
		number = new char[strlen(other.number) + 1];
		strcpy_s(number, strlen(other.number) + 1, other.number);
		specialty = new char[strlen(other.specialty) + 1];
		strcpy_s(specialty, strlen(other.specialty) + 1, other.specialty);
		zone = new char[strlen(other.zone) + 1];
		strcpy_s(zone, strlen(other.zone) + 1, other.zone);
	}
	return *this;
}

Administration :: ~Administration() {
	cout << "destruct Admin" << endl;
	delete[] number;
	delete[] specialty;
	delete[] zone;

}

void Administration::printInfo() const {
	cout << "Сотрудник:" << endl;
	cout << "Имя: " << GetName() << endl;
	cout << "Номер телефона: " << number << endl;
	cout << "Должность: " << specialty << endl;
	cout << "Область ответственности: " << zone << endl;
}
void Administration::SaveToFile(ofstream& out) const {

	out << "ADMINISTRATION\n";
	out << fullName << "\n";
	out << number << "\n";
	out << specialty << "\n";
	out << zone << "\n";
}
void Administration::LoadFromFile(ifstream& in) {

	char buffer[256];
	in.getline(buffer, 256);
	SetName(buffer);
	in.getline(buffer, 256);
	delete[] number;
	number = new char[strlen(buffer) + 1];
	strcpy_s(number, strlen(buffer) + 1, buffer);
	in.getline(buffer, 256);
	delete[] specialty;
	specialty = new char[strlen(buffer) + 1];
	strcpy_s(specialty, strlen(buffer) + 1, buffer);
	specialty = new char[strlen(buffer) + 1];
	strcpy_s(specialty, strlen(buffer) + 1, buffer);
	in.ignore();
}
const char* Administration::GetType() const { return "ADMINISTRATION"; };