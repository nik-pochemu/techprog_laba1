#include <iostream>
#include <cstring>
#include <fstream>
#include "Keeper.h"
#include "KeeperException.h"
using namespace std;


Keeper::Keeper() : arr(nullptr), size(0) {
	cout << "Keeper const wuthout param" << endl;
}

Keeper::Keeper(int initialSize) : size(initialSize) {
	cout << "Keeper const with param" << endl;
	arr = new Base * [size];
	for (int i = 0; i < size; i++) arr[i] = nullptr;
}

Keeper::Keeper(const Keeper& other) : size(other.size) {
	cout << "Keeper const copy" << endl;
	arr = new Base * [size];
	for (int i = 0; i < size; i++) {
		if (other.arr[i] != nullptr) arr[i] = other.arr[i];
		else arr[i] = nullptr;
	}
}

Keeper :: ~Keeper() {
	cout << "destruct Keeper" << endl;
	for (int i = 0; i < size; i++) delete arr[i];
	delete[] arr;
}


Keeper& Keeper :: operator=(const Keeper& other) {
	cout << "Keeper op copy" << endl;
	if (this != &other) {
		for (int i = 0; i < size; i++) delete arr[i];
		delete[] arr;
		size = other.size;
		arr = new Base * [size];
		for (int i = 0; i < size; i++) {
			if (strcmp(other.arr[i]->GetType(), "STUDENT") == 0) arr[i] = new Student(*(Student*)other.arr[i]);
			else if (strcmp(other.arr[i]->GetType(), "TEACHER") == 0) arr[i] = new Teacher(*(Teacher*)other.arr[i]);
			else if (strcmp(other.arr[i]->GetType(), "ADMINISTRATION") == 0) arr[i] = new Administration(*(Administration*)other.arr[i]);
			else arr[i] = nullptr;
		}
	}
	return *this;
}

void Keeper::Add(Base* obj) {
	Base** newArr = new Base * [size + 1];
	for (int i = 0; i < size; i++) newArr[i] = arr[i];
	newArr[size] = obj;
	delete[] arr;
	arr = newArr;
	size++;
	cout << "new obj" << size << endl;
}

void Keeper::Remove(int typeCode, const char* name) {
	if (size <= 0) {
		std::cout << "Список пуст!" << std::endl;
		return;
	}

	const char* typeName = nullptr;
	switch (typeCode) {
	case 1: typeName = "STUDENT"; break;
	case 2: typeName = "TEACHER"; break;
	case 3: typeName = "ADMINISTRATION"; break;
	default:
		std::cout << "Неверный код типа: " << typeCode << std::endl;
		return;
	}

	int index = -1;
	for (int i = 0; i < size; ++i) {
		if (arr[i] != nullptr &&
			std::strcmp(arr[i]->GetType(), typeName) == 0 &&
			std::strcmp(arr[i]->GetName(), name) == 0) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		std::cout << "Объект не найден!" << std::endl;
		return;
	}

	delete arr[index];
	arr[index] = nullptr;

	Base** newArr = nullptr;
	if (size - 1 > 0) {
		newArr = new Base * [size - 1];
		int j = 0;
		for (int i = 0; i < size; ++i) {
			if (i == index) continue;
			newArr[j++] = arr[i];
		}
	}
	delete[] arr;
	arr = newArr;
	--size;

	std::cout << "Объект удалён!" << std::endl;
}


void Keeper::Edit(int typeCode, const char* name) {
	if (size <= 0)
		throw KeeperException("Ошибка: список объектов пуст!");

	const char* typeName = nullptr;
	switch (typeCode) {
	case 1: typeName = "STUDENT"; break;
	case 2: typeName = "TEACHER"; break;
	case 3: typeName = "ADMINISTRATION"; break;
	default:
		throw KeeperException("Ошибка: неверный код типа объекта!");
	}

	int index = -1;
	for (int i = 0; i < size; ++i) {
		if (arr[i] && strcmp(arr[i]->GetType(), typeName) == 0 &&
			strcmp(arr[i]->GetName(), name) == 0) {
			index = i;
			break;
		}
	}

	if (index == -1)
		throw KeeperException("Ошибка: объект не найден!");

	cout << "Редактирование " << typeName << " (" << arr[index]->GetName() << ")\n";
	if (strcmp(typeName, "STUDENT") == 0) {
		Student* st = dynamic_cast<Student*>(arr[index]);
		char newName[64], group[64], spec[64];
		int course; double gpa;
		cout << "Новое имя: "; cin.getline(newName, 64);
		cout << "Группа: "; cin.getline(group, 64);
		cout << "Направление: "; cin.getline(spec, 64);
		cout << "Курс: "; cin >> course;
		cout << "Средний балл: "; cin >> gpa;
		*st = Student(newName, group, spec, course, gpa);
	}
	else if (strcmp(typeName, "TEACHER") == 0) {
		Teacher* t = dynamic_cast<Teacher*>(arr[index]);
		char newName[64];
		int nGroups, nSpecs;
		cout << "Новое имя: "; cin.getline(newName, 64);

		cout << "Количество групп: "; cin >> nGroups; cin.ignore();
		char** groups = new char* [nGroups];
		for (int i = 0; i < nGroups; i++) {
			char buf[256];
			cout << "Группа " << i + 1 << ": ";
			cin.getline(buf, 256);
			groups[i] = new char[strlen(buf) + 1];
			strcpy_s(groups[i], strlen(buf) + 1, buf);
		}

		cout << "Количество специальностей: "; cin >> nSpecs; cin.ignore();
		char** specs = new char* [nSpecs];
		for (int i = 0; i < nSpecs; i++) {
			char buf[256];
			cout << "Специальность " << i + 1 << ": ";
			cin.getline(buf, 256);
			specs[i] = new char[strlen(buf) + 1];
			strcpy_s(specs[i], strlen(buf) + 1, buf);
		}

		*t = Teacher(newName, (const char**)groups, (const char**)specs, nGroups, nSpecs);

		for (int i = 0; i < nGroups; i++) delete[] groups[i];
		delete[] groups;
		for (int i = 0; i < nSpecs; i++) delete[] specs[i];
		delete[] specs;
	}
	else if (strcmp(typeName, "ADMINISTRATION") == 0) {
		Administration* a = dynamic_cast<Administration*>(arr[index]);
		char newName[64], number[64], spec[64], zone[64];
		cout << "Новое имя: "; cin.getline(newName, 64);
		cout << "Номер телефона: "; cin.getline(number, 64);
		cout << "Должность: "; cin.getline(spec, 64);
		cout << "Область ответственности: "; cin.getline(zone, 64);
		*a = Administration(newName, number, spec, zone);
	}

	cout << "Изменения успешно сохранены!\n";
}


void Keeper::ShowAll() const {
	cout << "all obj" << endl;
	for (int i = 0; i < size; i++) {
		arr[i]->printInfo();
		cout << "\n";
	}
}


void Keeper::SaveToFile(const char* filename) const {
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

void Keeper::LoadFromFile(const char* filename) {
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