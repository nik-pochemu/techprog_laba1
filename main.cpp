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
		/*fullName = new char[1];
		fullName[0] = '\0';*/
		group = new char[1];
		group[0] = '\0';
		specialty = new char[1];
		specialty[0] = '\0';
		course = 0;
		gpa = 0.0;
		cout << "Student const without param" << endl;
	}

	Student(const char* name, const char* group, const char* specialty, int course, double gpa) : Base(name) {
		/*this->fullName = new char[strlen(name) + 1];
		strcpy_s(this->fullName, strlen(name) + 1, name);*/
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

//class Teacher {};

//class Administration {};

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
				else arr[i] = nullptr;
			}
		}
		return *this;
	}

	void Add(Base* obj) {
		Base** newArr = new Base * [size + 1];
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
			if (strcmp(type, "STUDENT") == 0) {
				arr[i] = new Student();
				arr[i]->LoadFromFile(in);
			}
			else {
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

	Keeper keeper;

	keeper.Add(new Student("test", "well", "let", 2, 4.5));
	keeper.Add(new Student("test1", "well2", "let2", 1, 4.2));
	keeper.ShowAll();
	keeper.SaveToFile("data.txt");
	/*string line;
	ifstream in("data.txt");
	while (getline(in, line)) {
		cout << line << endl;
	}
	in.close();*/
	Keeper keeper2;
	keeper2.LoadFromFile("data.txt");
	keeper2.ShowAll();
	//keeper2.SaveToFile("data.txt");
	//ofstream out;          // поток для записи
	/*out.open("data.txt");
	out << "?????" << endl;
	out.close();
	/*cout << "test" << endl;
	Student s1("test", "test", "test", 3, 4.6);
	s1.printInfo();

	cout << "test copy" << endl;
	Student s2 = s1;
	s2.printInfo();

	cout << "test oper copy " << endl;
	Student s3;
	s3 = s1;
	s3.printInfo();

	cout << "end test" << endl;*/
	return 0;
}
/*int main() {
	Keeper keeper;

	keeper.Add(new Student("Иванов Иван", "ИВТ-21", "Информатика", 2, 4.5));
	keeper.Add(new Student("Петров Петр", "ПМИ-22", "Математика", 1, 4.2));

	keeper.ShowAll();
	keeper.SaveToFile("data.txt");

	std::cout << "\n=== Загружаем данные из файла ===\n";
	Keeper keeper2;
	keeper2.LoadFromFile("data.txt");
	keeper2.ShowAll();

	return 0;*/