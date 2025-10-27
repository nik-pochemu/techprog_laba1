#include <iostream>
#include <cstring>
#include <fstream>
#include <locale> 
#include <string>
using namespace std;

class Base {
protected: 
	char* fullName;
public:
	Base() {
		fullName = new char(1);
		fullName[0] = '\0';
		cout << "Base const without param" << endl;
	}

	Base(const char* name) {
		fullName = new char[strlen(name) + 1];
		strcpy_s(fullName, strlen(name) + 1, name);
		cout << "Base const with param" << endl;
	}

	Base(const Base& other) {
		fullName = new char[strlen(other.fullName) + 1];
		strcpy_s(fullName, strlen(other.fullName) + 1, other.fullName);
		cout << "Base const copy" << endl;
	}

	Base& operator=(const Base& other) {
		cout << "Base op copy" << endl;
		if (this != &other) {
			delete[] fullName;
			fullName = new char[strlen(other.fullName) + 1];
		}
		return *this;
	}

	virtual ~Base() {
		cout << "destruct Base" << endl;
		delete[] fullName;
	}

	virtual void printInfo() const = 0;
	virtual void SaveToFile(ofstream& out) const = 0;
	virtual void LoadFromFile(ifstream& in) = 0;
	virtual const char* GetType() const = 0;
	const char* GetName() const {
		return fullName;
	}
	void SetName(const char* name) {
		delete[] fullName;
		fullName = new char[strlen(name) + 1];
		strcpy_s(fullName, strlen(name) + 1, name);
	}
};


class Student : public Base {
private:
	char* group;
	char* specialty;
	int course;
	double gpa;

public:
	Student() : Base() {
		group = new char[1];
		group[0] = '\0';
		specialty = new char[1];
		specialty[0] = '\0';
		course = 0;
		gpa = 0.0;
		cout << "Student const without param" << endl;
	}

	Student(const char* name, const char* group, const char* specialty, int course, double gpa) : Base(name) {
		this->group = new char[strlen(group) + 1];
		strcpy_s(this->group, strlen(group) + 1, group);
		this->specialty = new char[strlen(specialty) + 1];
		strcpy_s(this->specialty, strlen(specialty) + 1, specialty);
		this->course = course;
		this->gpa = gpa;
		cout << "Student const with param" << endl;

	}

	Student(const Student& other) : Base(other) {
		group = new char[strlen(other.group) + 1];
		strcpy_s(group, strlen(other.group) + 1, other.group);
		specialty = new char[strlen(other.specialty) + 1];
		strcpy_s(specialty, strlen(other.specialty) + 1, other.specialty);
		course = other.course;
		gpa = other.gpa;
		cout << "Student const copy" << endl;
	}

	Student& operator= (const Student& other) {
		cout << "Student op copy" << endl;
		if (this != &other) {
			Base::operator=(other);
			delete[] group;
			delete[] specialty;
			group = new char[strlen(other.group) + 1];
			strcpy_s(group, strlen(other.group) + 1, other.group);
			specialty = new char[strlen(other.specialty) + 1];
			strcpy_s(specialty,strlen(other.specialty) + 1, other.specialty);
			course = other.course;
			gpa = other.gpa;
		}
		return *this;
	}

	~Student() override {
		cout << "destruct Student" << endl;
		delete[] group;
		delete[] specialty;

	}

	void printInfo() const override {
		cout << "example" << endl;
		cout << "example" << GetName() << endl;
		cout << "example" << group << endl;
		cout << "example" << specialty << endl;
		cout << "example" << course << endl;
		cout << "example" << gpa << endl;
	}
	void SaveToFile(ofstream& out) const override {

		out << "STUDENT\n";
		out << fullName << "\n";
		out << group << "\n";
		out << specialty << "\n";
		out << course << "\n" << gpa << "\n";
	}
	void LoadFromFile(ifstream& in) override {

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
	const char* GetType() const override { return "STUDENT"; };
};

class Teacher : public Base {
private:


	char** group;
	char** specialty;
	int size_group;
	int size_spec;

public:
	Teacher() : Base() {
		group = nullptr;
		specialty = nullptr;
		size_group = 0;
		size_spec = 0;
		cout << "Teacher const without param" << endl;

	}

	/*Teacher(group(nullptr), size(0)) : Base() {}
	void input() {
		cout << "—колько групп вы хотите добавить?" << endl;
		cin >> size;
		cin.ignore();
		group = new char* [size];
		for (int i = 0; i < size; i++) {
			char buffer[256];
			cout << "¬ведите название/номер группы:";
			cin.getline(buffer, 256);
			group[i] = new char[strlen(buffer) + 1];
			strcpy_s(group[i], strlen(buffer) + 1, buffer);
		}
	}*/

	Teacher(const char* name, const char* group[], const char* specialty[], const int size_group, const int size_spec) : Base(name) {
		
		this->group  = new char* [sizeof(size_group)];
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

	Teacher(const Teacher& other) : Base(other) {

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

	Teacher& operator= (const Teacher& other) {
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

	~Teacher() override {
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

	void printInfo() const override {
		cout << "example" << endl;
		cout << "example" << GetName() << endl;
		cout << size_group << endl;
		for (int i = 0; i < size_group; i++) {
			cout << group[i] << endl;
		}
		cout << size_spec << endl;
		for (int i = 0; i < size_spec; i++) {
			cout << specialty[i] << endl;
		}
	}
	void SaveToFile(ofstream& out) const override {

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

	void LoadFromFile(ifstream& in) override {
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
	const char* GetType() const override { return "TEACHER"; };
};

class Administration : public Base {
private:
	char* number;
	char* specialty;
	char* zone;

public:
	Administration() : Base() {
		number = new char[1];
		number[0] = '\0';
		specialty = new char[1];
		specialty[0] = '\0';
		zone = new char[1];
		zone[0] = '\0';
		cout << "Admin const without param" << endl;
	}

	Administration(const char* name, const char* number, const char* specialty, const char* zone) : Base(name) {
		this->number = new char[strlen(number) + 1];
		strcpy_s(this->number, strlen(number) + 1, number);
		this->specialty = new char[strlen(specialty) + 1];
		strcpy_s(this->specialty, strlen(specialty) + 1, specialty);
		this->zone = new char[strlen(zone) + 1];
		strcpy_s(this->zone, strlen(zone) + 1, zone);
		cout << "Admin const with param" << endl;

	}

	Administration(const Administration& other) : Base(other) {
		number = new char[strlen(other.number) + 1];
		strcpy_s(number, strlen(other.number) + 1, other.number);
		specialty = new char[strlen(other.specialty) + 1];
		strcpy_s(specialty, strlen(other.specialty) + 1, other.specialty);
		zone = new char[strlen(other.zone) + 1];
		strcpy_s(zone, strlen(other.zone) + 1, other.zone);
		cout << "Admin const copy" << endl;
	}

	Administration& operator= (const Administration& other) {
		cout << "Student op copy" << endl;
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

	~Administration() override {
		cout << "destruct Student" << endl;
		delete[] number;
		delete[] specialty;
		delete[] zone;

	}

	void printInfo() const override {
		cout << "example" << endl;
		cout << "example" << GetName() << endl;
		cout << "example" << number << endl;
		cout << "example" << specialty << endl;
		cout << "example" << zone << endl;
	}
	void SaveToFile(ofstream& out) const override {

		out << "STUDENT\n";
		out << fullName << "\n";
		out << number << "\n";
		out << specialty << "\n";
		out << zone << "\n";
	}
	void LoadFromFile(ifstream& in) override {

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
	const char* GetType() const override { return "ADMINISTRATION"; };
};

class Keeper {
private:
	Base** arr;
	int size;
public:
	Keeper() : arr(nullptr), size(0) {
		cout << "Keeper const wuthout param" << endl;
	}

	Keeper(int initialSize) : size(initialSize) {
		cout << "Keeper const with param" << endl;
		arr = new Base * [size];
		for (int i = 0; i < size; i++) arr[i] = nullptr;
	}

	Keeper(const Keeper& other) : size(other.size) {
		cout << "Keeper const copy" << endl;
		arr = new Base * [size];
		for (int i = 0; i < size; i++) {
			if (other.arr[i] != nullptr) arr[i] = other.arr[i];
			else arr[i] = nullptr;
		}
	}

	~Keeper() {
		cout << "destruct Keeper" << endl;
		for (int i = 0; i < size; i++) delete arr[i];
		delete[] arr;
	}


	Keeper& operator=(const Keeper& other) {
		cout << "Keeper op copy" << endl;
		if (this != &other) {
			for (int i = 0; i < size; i++) delete arr[i];
			delete[] arr;
			size = other.size;
			arr = new Base * [size];
			for (int i = 0; i < size; i++) {
				if (strcmp(other.arr[i]->GetType(), "STUDENT") == 0) arr[i] = new Student(*(Student*)other.arr[i]);
				else if (strcmp(other.arr[i]->GetType(), "TEACHER") == 0) arr[i] = new Student(*(Student*)other.arr[i]);
				else if (strcmp(other.arr[i]->GetType(), "ADMINISTRATION") == 0) arr[i] = new Student(*(Student*)other.arr[i]);
				else arr[i] = nullptr;
			}
		}
		return *this;
	}

	void Add(Base* obj) {
		Base** newArr = new Base* [size + 1];
		for (int i = 0; i < size; i++) newArr[i] = arr[i];
		newArr[size] = obj;
		delete[] arr;
		arr = newArr;
		size++;
		cout << "new obj" << size << endl;
	}

	void Remove(int index) {
		if (index < 0 || index >= size) {
			cout << "error" << endl;
			return;
		}

		delete arr[index];
		Base** newArr = new Base*[size - 1];
		for (int i = 0, j = 0; i < size; i++) {
			if (i == index) continue;
			newArr[j++] = arr[i];
		}
		delete[] arr;
		arr = newArr;
		size--;
		cout << "obj deleted" << endl;
	}

	void ShowAll() const {
		cout << "all obj" << endl;
		for (int i = 0; i < size; i++) {
			arr[i]->printInfo();
			cout << "\n";
		}
	}


	void SaveToFile(const char* filename) const {
		ofstream  out;
		out.open(filename);
		if (!out) {
			cout << "file error\n";
			return;
		}
		out << size << "\n";
		for (int i = 0; i < size; i++) arr[i]->SaveToFile(out);
		out.close();
		cout << "keeper save to file\n";
	}

	void LoadFromFile(const char* filename) {
		ifstream in(filename);
		if (!in) {
			cout << "error file\n";
			return;
		}

		for (int i = 0; i < size; i++)
			delete arr[i];
		delete[] arr;
		arr = nullptr;
		size = 0;
		
		int newSize;
		in >> newSize;
		in.ignore();
		arr = new Base * [newSize];
		for (int i = 0; i < newSize; i++) {
			char type[64];
			in.getline(type, 64);
			cout << type << endl;
			if (strcmp(type, "STUDENT") == 0) {
				arr[i] = new Student();
				arr[i]->LoadFromFile(in);
			}
			else if (strcmp(type, "TEACHER") == 0) {
				arr[i] = new Teacher();
				arr[i]->LoadFromFile(in);
			}
			else if (strcmp(type, "ADMINISTRATION") == 0) {
				arr[i] = new Administration();
				arr[i]->LoadFromFile(in);
			}
			else {
				cout << "haha lol" << endl;
				arr[i] = nullptr;
			}
		}
		size = newSize;
		in.close();
		cout << "keeper load from file\n";
	}



};



int main() {
	setlocale(LC_ALL, "Russian");

	//Keeper keeper;
	//const char* data[] = { "afaa", "afafaf", "ahah"};
	//const char* data1[] = { "a", "b", "c" };
	//keeper.Add(new Teacher("vasya", data, data1, 3, 3));
	//keeper.Add(new Student("test1", "well2", "let2", 1, 4.2));
	//keeper.ShowAll();
	//keeper.SaveToFile("data.txt");
	//cout << "ens first test" << endl;
	//cout << "\n";

	Keeper keeper2;
	keeper2.LoadFromFile("data.txt");
	keeper2.ShowAll();

	return 0;
}