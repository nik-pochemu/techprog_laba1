#pragma once
#include "Base.h" 

class Student : public Base {
private:
    char* group;
    char* specialty;
    int course;
    double gpa;
public:
    Student();
    Student(const char* name, const char* group, const char* specialty, int course, double gpa);
    Student(const Student& other);
    Student& operator=(const Student& other);
    ~Student() override;

    void printInfo() const override;
    void SaveToFile(ofstream& out) const override;
    void LoadFromFile(ifstream& in) override;
    const char* GetType() const override;
};
