#ifndef LOGIC_H
#define LOGIC_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <omp.h>
#include <algorithm>
#include <sstream>
#include <chrono>
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
Student* AddInfo(vector<Student> arr);
bool ReturnMedianQuestion();
bool ReturnFileReadQuestion();
void Program();
void GenerationAlgorithm(int amountToGenerate, int counter);
void GenerateTxtFiles(int amountOfFiles);
string ConvertIntToString(int toConvert);
void ReadFile(vector<Student> &arr, string fileName);
void PrintElements(vector<Student> best, vector<Student> worst);
void SortElements(vector<Student> arr, vector<Student> &best, vector<Student> &worst);
void SortByName(vector<Student> &arr);
#endif // LOGIC_H

