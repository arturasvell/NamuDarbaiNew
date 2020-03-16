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
using namespace std;
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
};
Student* AddInfo(list<Student> arr);
bool ReturnMedianQuestion();
bool ReturnFileReadQuestion();
void Program();
void GenerationAlgorithm(int amountToGenerate, int counter);
void GenerateTxtFiles(int amountOfFiles);
string ConvertIntToString(int toConvert);
void ReadFile(list<Student>& arr, string fileName);
void PrintElements(list<Student> arr, list<Student> best);
void SortElements(list<Student>& arr, list<Student>& best);
void SortByName(list<Student>& arr);
void SortByResults(list<Student>& arr);
#endif // LOGIC_H
