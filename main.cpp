#include <iostream>
#include <cstring>
#include <fstream>
#include <locale> 
#include <windows.h>

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
			strcpy_s(fullName, strlen(other.fullName) + 1, other.fullName);
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
			strcpy_s(specialty, strlen(other.specialty) + 1, other.specialty);
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
		cout << "Студент: " << endl;
		cout << "Имя: " << GetName() << endl;
		cout << "Группа: " << group << endl;
		cout << "Направление: " << specialty << endl;
		cout << "Курс: " << course << endl;
		cout << "Средний балл: " << gpa << endl;
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

	Teacher(const char* name, const char* group[], const char* specialty[], const int size_group, const int size_spec) : Base(name) {

		this->group = new char* [sizeof(size_group)];
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
		cout << "Преподаватель: " << endl;
		cout << "Имя: " << GetName() << endl;
		cout << "Количество групп: " << size_group << endl;
		for (int i = 0; i < size_group; i++) {
			cout << "Группа " << i + 1 << ":" << group[i] << endl;
		}
		cout << "Количество специальностей: " << size_spec << endl;
		for (int i = 0; i < size_spec; i++) {
			cout << "Специальность " << i + 1 << ":" << specialty[i] << endl;
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

	~Administration() override {
		cout << "destruct Admin" << endl;
		delete[] number;
		delete[] specialty;
		delete[] zone;

	}

	void printInfo() const override {
		cout << "Сотрудник:" << endl;
		cout << "Имя: " << GetName() << endl;
		cout << "Номер телефона: " << number << endl;
		cout << "Должность: " << specialty << endl;
		cout << "Область ответственности: " << zone << endl;
	}
	void SaveToFile(ofstream& out) const override {

		out << "ADMINISTRATION\n";
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

class KeeperException : public exception {
public:
	KeeperException(const char* msg) : exception(msg) {}
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
				else if (strcmp(other.arr[i]->GetType(), "TEACHER") == 0) arr[i] = new Teacher(*(Teacher*)other.arr[i]);
				else if (strcmp(other.arr[i]->GetType(), "ADMINISTRATION") == 0) arr[i] = new Administration(*(Administration*)other.arr[i]);
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

	void Remove(int typeCode, const char* name) {
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


	void Edit(int typeCode, const char* name) {
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
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Keeper keeper;

	int choice;
	int choice1;
	int choice2;

	char* nam = new char[64];
	char* group = new char[64];
	char* spec = new char[64];
	char* number = new char[64];
	char* specialty = new char[64];
	char* zone = new char[64];

	int course = 0;
	double gpa = 0.0;

	do {
		cout << "\n===== МЕНЮ УПРАВЛЕНИЯ KEEPER =====\n";
		cout << "1. Добавить объект\n";
		cout << "2. Удалить объект\n";
		cout << "3. Показать все объекты\n";
		cout << "4. Сохранить данные в файл\n";
		cout << "5. Загрузить данные из файла\n";
		cout << "6. Изменить объект\n";
		cout << "0. Выход\n";
		cout << "Выберите действие: ";
		cin >> choice;
		cout << endl;

		switch (choice) {
		case 1:
			cout << "1. Добавить студента\n";
			cout << "2. Добавить преподавателя\n";
			cout << "3. Добавить сотрудника\n";
			cin >> choice1;
			switch (choice1) {
			case 1:
				cin.ignore();
				cout << "Введите имя: \n";
				cin.getline(nam, 64);
				cout << "Введите группу: \n";
				cin.getline(group, 64);
				cout << "Введите направление: \n";
				cin.getline(spec, 64);
				cout << "Введите номер курса: \n";
				cin >> course;
				cout << "Введите средний балл: \n";
				cin >> gpa;

				keeper.Add(new Student(nam, group, spec, course, gpa));
				break;

			case 2: {
				cin.ignore();
				cout << "Введите имя:\n";
				cin.getline(nam, 64);

				int size_group;
				cout << "Сколько групп вы хотите добавить?\n";
				cin >> size_group;
				cin.ignore();

				char** groups = new char* [size_group];
				for (int i = 0; i < size_group; i++) {
					char buffer[256];
					cout << "Введите название группы " << i + 1 << ": ";
					cin.getline(buffer, 256);
					groups[i] = new char[strlen(buffer) + 1];
					strcpy_s(groups[i], strlen(buffer) + 1, buffer);
				}

				int size_spec;
				cout << "Сколько специальностей вы хотите добавить?\n";
				cin >> size_spec;
				cin.ignore();

				char** specs = new char* [size_spec];
				for (int i = 0; i < size_spec; i++) {
					char buffer[256];
					cout << "Введите название специальности " << i + 1 << ": ";
					cin.getline(buffer, 256);
					specs[i] = new char[strlen(buffer) + 1];
					strcpy_s(specs[i], strlen(buffer) + 1, buffer);
				}

				keeper.Add(new Teacher(nam, (const char**)groups, (const char**)specs, size_group, size_spec));

				for (int i = 0; i < size_group; i++) delete[] groups[i];
				delete[] groups;
				for (int i = 0; i < size_spec; i++) delete[] specs[i];
				delete[] specs;
				break;
			}

			case 3:
				cin.ignore();
				cout << "Введите имя: \n";
				cin.getline(nam, 64);
				cout << "Введите номер телефона: \n";
				cin.getline(number, 64);
				cout << "Введите должность: \n";
				cin.getline(specialty, 64);
				cout << "Введите область ответственности: \n";
				cin.getline(zone, 64);

				keeper.Add(new Administration(nam, number, specialty, zone));
				break;
			default:
				cout << "Ошибка: неверный выбор!\n";
				break;
			}
			break;

		case 2:
			cout << "1. Удалить студента:\n";
			cout << "2. Удалить преподавателя:\n";
			cout << "3. Удалить сотрудника:\n";
			cin >> choice2;
			cin.ignore();
			cout << "Введите имя:\n";
			cin.getline(nam, 64);
			keeper.Remove(choice2, nam);
			break;

		case 3:
			keeper.ShowAll();
			break;

		case 4:
			keeper.SaveToFile("data.txt");
			cout << "Данные сохранены в файл data.txt\n";
			break;


		case 6:
			try {
				cout << "1. Изменить студента\n";
				cout << "2. Изменить преподавателя\n";
				cout << "3. Изменить сотрудника\n";
				cin >> choice2;
				cin.ignore();
				cout << "Введите имя для изменения:\n";
				cin.getline(nam, 64);
				keeper.Edit(choice2, nam);

			}
			catch (const KeeperException& e) {
				cout << e.what() << endl;
			}
			break;

		case 5:
			keeper.LoadFromFile("data.txt");
			cout << "Данные загружены из файла data.txt\n";
			break;

		case 0:
			cout << "Выход из программы...\n";
			break;

		default:
			cout << "Ошибка: неверный выбор!\n";
			break;
		}

	} while (choice != 0);

	delete[] nam;
	delete[] group;
	delete[] spec;
	delete[] number;
	delete[] specialty;
	delete[] zone;

	return 0;
}
