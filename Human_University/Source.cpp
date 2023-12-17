#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

/*Общий класс Human (name, age), конструкторы, ввод, вывод
  Классы наследники: Student (массив оценок, год обучения, факультет)
  University (U_name, year, ректор), конструкторы, ввод, вывод*/

class Human
{
protected:
	char* name;
	int age;

public:
	//con
	Human(const char* name, int age) : age(age) {
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}
	//des
	virtual ~Human() {
		delete[] name;
	}

	//get
	const char* getName() const { return name; }
	int getAge() const { return age; }

	//set
	void setName(const char* newName) {
		delete[] name;
		name = new char[strlen(newName) + 1];
		strcpy(name, newName); 
	}
	void setAge(int newAge) { age = newAge; }

	//input
	virtual void input() {
		//буфер для ввода
		char inputName[100];
		//ввод имени
		cout << "Enter your name: ";
		cin.getline(inputName, sizeof(inputName));
		delete[] name;
		//запись имени
		name = new char[strlen(inputName) + 1];
		strcpy(name, inputName);

		//ввод и запись возраста
		cout << "Enter your age: ";
		cin >> age;
		cin.ignore();
	}

	virtual void display() const {
		cout << "Name: " << name << ", Age: " << age << endl;
	}
};


class Student : Human {
private:
	char* faculty;
	int size = 20;
	int* marks; //указатель для массива
	int* year; //количество лет обучения

public:
	//con
	Student(const char* name, int age, const char* faculty, int year, int marks[], int size)
		: Human(name, age), faculty(nullptr), size(size), marks(nullptr), year(nullptr) {
		this->faculty = new char[strlen(faculty) + 1];
		strcpy(this->faculty, faculty);

		this->marks = new int[size];
		memcpy(this->marks, marks, size * sizeof(int));

		this->year = new int;
		*(this->year) = year;
	}

	//des
	virtual ~Student() {
		delete[] faculty;
		delete[] marks;
		delete year;
	}

	//get
	const char* getFaculty() const { return faculty; }
	int* getMarks() const { return marks; }
	int getYear() const { return *year; }

	//set
	void setFaculty(const char* newFaculty) {
		delete[] faculty;
		faculty = new char[strlen(newFaculty) + 1];
		strcpy(faculty, newFaculty);
	}
	void setMarks(int newMarks[]) {
		delete[] marks;
		marks = new int[size];
		memcpy(marks, newMarks, size * sizeof(int));
	}
	void setYear(int newYear) {
		*(year) = newYear;
	}

	//input
	void input() override {
		Human::input();

		char inputFaculty[100];
		cout << "Enter faculty: ";
		cin.getline(inputFaculty, sizeof(inputFaculty));
		delete[] faculty;
		faculty = new char[strlen(inputFaculty) + 1];
		strcpy(faculty, inputFaculty);

		cout << "Enter number of years: ";
		cin >> *year;
		cin.ignore();

		cout << "Enter number of maeks: ";
		cin >> size;

		cout << "Enter marks (size " << size << "): ";
		for (int i = 0; i < size; ++i) {
			cin >> marks[i];
		}
		cin.ignore();
	}

	double Average() const {
		int sum = 0;
		for (int i = 0; i < size; ++i) {
			sum += marks[i];
		}
		return sum / size;
	}

	void display() const override {
		Human::display();
		cout << "Faculty: " << faculty << ", Year: " << *year << ", Marks: [";
		for (int i = 0; i < size; ++i) {
			cout << marks[i] << " ";
		}
		cout << "]" << endl;
		cout << "Average mark: " << Average() << endl;
	}
};

class University : public Human {
private:
	char* U_name;
	int U_year;
	char* rector;

public:
	//con
	University(const char* name, int age, const char* U_name, int U_year, const char* rector)
		: Human(name, age), U_name(nullptr), rector(nullptr) {
		this->U_name = new char[strlen(U_name) + 1];
		strcpy(this->U_name, U_name);

		this->U_year = U_year;

		this->rector = new char[strlen(rector) + 1];
		strcpy(this->rector, rector);
	}

	//des
	virtual ~University() {
		delete[] U_name;
		delete[] rector;
	}

	//get
	const char* getUName() const { return U_name; }
	int getUYear() const { return U_year; }
	const char* getRector() const { return rector; }

	//set
	void setUName(const char* newUName) {
		delete[] U_name;
		U_name = new char[strlen(newUName) + 1];
		strcpy(U_name, newUName);
	}
	void setUYear(int newUYear) {
		U_year = newUYear;
	}
	void setRector(const char* newRector) {
		delete[] rector;
		rector = new char[strlen(newRector) + 1];
		strcpy(rector, newRector);
	}

	//input
	void input() override {
		Human::input();

		char inputUName[100];
		cout << "Enter university name: ";
		cin.getline(inputUName, sizeof(inputUName));
		delete[] U_name;
		U_name = new char[strlen(inputUName) + 1];
		strcpy(U_name, inputUName);

		cout << "Enter university year: ";
		cin >> U_year;
		cin.ignore();

		char inputRector[100];
		cout << "Enter rector name: ";
		cin.getline(inputRector, sizeof(inputRector));
		delete[] rector;
		rector = new char[strlen(inputRector) + 1];
		strcpy(rector, inputRector);
	}

	void display() const override {
		Human::display();
		cout << "University Name: " << U_name << ", University Year: " << U_year << ", Rector: " << rector << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "");

	Student student("Boris", 20, "Programmer", 3, new int[20] {}, 20);
	student.input();
	student.display();

	cout << "===================" << endl;

	University university("Academy IT", 140, "IT", 8, "Alexander Riskovic");
	university.input();
	university.display();

	return 0;
}