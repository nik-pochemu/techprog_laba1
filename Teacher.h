#pragma once
#include "Base.h"

class Teacher : public Base {
private:
	char** group;
	char** specialty;
	int size_group;
	int size_spec;

public:
	Teacher();
	Teacher(const char* name, const char* group[], const char* specialty[], const int size_group, const int size_spec);
	Teacher(const Teacher& other);
	Teacher& operator= (const Teacher& other);
	~Teacher() override;

	void printInfo() const override;
	void SaveToFile(ofstream& out) const override;
	void LoadFromFile(ifstream& in) override;
	const char* GetType() const override;
};