#ifndef LOGIC_H
#define LOGIC_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <omp.h>
#include <sstream>
#include <chrono>
#include <list>
#include <algorithm>
#include <deque>
#include <sstream>
#include <list>
#include <vector>
using namespace std;
using std::cout;
static bool medianShow = false;
static const int threadNum = 4;
enum Method
{
	VECTOR,
	LIST,
	DEQUE
};
class Student
{
public:
	string name = "", surname = "";

	string Name() { return name; }
	string Surname() { return surname; }
	double final;
	double CountAverage(vector<int> homework);

	double CountMedian(vector<int> homework);

	void CountFinal(double data, double examResult);

	void Print();

	Student()
	{
		name = "Vardenis";
		surname = "Pavardenis";
	}
	Student(string name, string surname)
	{
		this->name = name;
		this->surname = surname;
	}
	Student(string name, string surname, vector<int> homework)
	{
		this->name = name;
		this->surname = surname;
	}
	bool operator ()(Student const& a, Student const& b) const
	{
		return a.final < b.final;
	}
};
Student* AddInfo(deque<Student> arr);

Student* AddInfo1(vector<Student> arr);

Student* AddInfo2(list<Student> arr);

bool ReturnMedianQuestion();
bool ReturnFileReadQuestion();
void Program();
void GenerationAlgorithm(int amountToGenerate, int counter);
void GenerateTxtFiles(int amountOfFiles);
string ConvertIntToString(int toConvert);

void PrintElements(deque<Student> arr, deque<Student> best);
void SortElements(deque<Student>& arr, deque<Student>& best, deque<Student>& worst);
void SortByName(deque<Student>& arr);
void SortByResults(deque<Student>& arr);
void bufer_nusk(std::string read_vardas, deque<Student>& arr);

void PrintElements1(vector<Student> arr, vector<Student> best);
void SortElements1(vector<Student>& arr, vector<Student>& best, vector<Student>& worst);
void SortByName1(vector<Student>& arr);
void SortByResults1(vector<Student>& arr);
void bufer_nusk1(std::string read_vardas, vector<Student>& arr);

void PrintElements2(list<Student> arr, list<Student> best);
void SortElements2(list<Student>& arr, list<Student>& best, list<Student>& worst);
void SortByName2(list<Student>& arr);
void SortByResults2(list<Student>& arr);
void bufer_nusk2(std::string read_vardas, list<Student>& arr);
#endif // LOGIC_H
