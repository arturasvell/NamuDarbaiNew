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
using namespace std;
using std::cout;
static bool medianShow = false;
static const int threadNum = 4;
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
bool ReturnMedianQuestion();
bool ReturnFileReadQuestion();
void Program();
void GenerationAlgorithm(int amountToGenerate, int counter);
void GenerateTxtFiles(int amountOfFiles);
string ConvertIntToString(int toConvert);
void ReadFile(deque<Student>& arr, string fileName);
void PrintElements(deque<Student> arr, deque<Student> best);
void SortElements(deque<Student>& arr, deque<Student>& best);
void SortByName(deque<Student>& arr);
void SortByResults(deque<Student>& arr);
#endif // LOGIC_H
