#include <iostream>
#include <cstring>
#include <fstream>
#include <locale> 
#include <windows.h>
#include "Keeper.h"
#include "KeeperException.h"
#include "Student.h"
#include "Teacher.h"
#include "Administration.h"
#include "Base.h"
using namespace std;


int main() {
	setlocale(LC_ALL, "Russian");
	cout << "привет" << endl;


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
