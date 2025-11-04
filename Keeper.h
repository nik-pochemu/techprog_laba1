#pragma once
#include "Base.h"
#include "Student.h"
#include "Teacher.h"
#include "Administration.h"
#include <locale> 
using namespace std;


class Keeper {
private:
	Base** arr;
	int size;
public:
	Keeper();
	Keeper(int initialSize);
	Keeper(const Keeper& other);
	~Keeper();
	Keeper& operator=(const Keeper& other);
	void Add(Base* obj);
	void Remove(int typeCode, const char* name);
	void Edit(int typeCode, const char* name);
	void ShowAll() const;
	void SaveToFile(const char* filename) const;
	void LoadFromFile(const char* filename);

};