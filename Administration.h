#pragma once
#include "Base.h"
#include <iostream>


class Administration : public Base {
private:
	char* number;
	char* specialty;
	char* zone;

public:
	Administration();
	Administration(const char* name, const char* number, const char* specialty, const char* zone);
	Administration(const Administration& other);

	Administration& operator= (const Administration& other);

	~Administration() override;

	void printInfo() const override;
	void SaveToFile(ofstream& out) const override;
	void LoadFromFile(ifstream& in) override;

	const char* GetType() const override;
};