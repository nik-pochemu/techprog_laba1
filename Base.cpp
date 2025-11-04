#include "Base.h"
#include <iostream>
#include <cstring>
using namespace std;

Base::Base() {
    fullName = new char[1];
    fullName[0] = '\0';
    cout << "Base const without param" << endl;
}

Base::Base(const char* name) {
    fullName = new char[strlen(name) + 1];
    strcpy_s(fullName, strlen(name) + 1, name);
    cout << "Base const with param" << endl;
}

Base::Base(const Base& other) {
    fullName = new char[strlen(other.fullName) + 1];
    strcpy_s(fullName, strlen(other.fullName) + 1, other.fullName);
    cout << "Base const copy" << endl;
}

Base& Base::operator=(const Base& other) {
    cout << "Base op copy" << endl;
    if (this != &other) {
        delete[] fullName;
        fullName = new char[strlen(other.fullName) + 1];
        strcpy_s(fullName, strlen(other.fullName) + 1, other.fullName);
    }
    return *this;
}

Base::~Base() {
    cout << "destruct Base" << endl;
    delete[] fullName;
}

const char* Base::GetName() const {
    return fullName;
}

void Base::SetName(const char* name) {
    delete[] fullName;
    fullName = new char[strlen(name) + 1];
    strcpy_s(fullName, strlen(name) + 1, name);
}
