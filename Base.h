#pragma once

#include <iostream>
#include <cstring>
#include <fstream>
#include <locale> 
using namespace std;


class Base {
protected:
    char* fullName;
public:
    Base();
    Base(const char* name);
    Base(const Base& other);
    Base& operator=(const Base& other);
    virtual ~Base();

    virtual void printInfo() const = 0;
    virtual void SaveToFile(ofstream& out) const = 0;
    virtual void LoadFromFile(ifstream& in) = 0;
    virtual const char* GetType() const = 0;
    const char* GetName() const;
    void SetName(const char* name);
};