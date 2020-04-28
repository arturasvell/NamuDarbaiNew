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
#include <cmath>
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
class Person
{
protected:
    string name="", surname="";
public:
    virtual void DisplayNameSurname()=0;
};
class Student:Person
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
    void DisplayNameSurname()
    {
        cout<<name<<" "<<surname<<endl;
    }
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
	Student* operator + (Student &a)
	{
        if(a.name==this->name&&a.surname==this->surname)
        {
            this->final=(a.final+this->final)/2.0;
            delete &a;
            return this;
        }
	}
	Student* operator - (Student &a)
	{
        if(a.name==this->name&&a.surname==this->surname)
        {
            this->final=(abs)(a.final-this->final)/2.0;
            delete &a;
            return this;
        }
	}
	float operator / (Student const& a)
	{
        return this->final/a.final;
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
