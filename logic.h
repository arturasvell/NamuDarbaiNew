#ifndef LOGIC_H
#define LOGIC_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <omp.h>
#include <algorithm>
using namespace std;
static bool medianShow=false;
static const int threadNum = 4;
class Student
{
public:
	string name = "", surname = "";

	string Name() { return name; }
	string Surname() { return surname; }
	double final;
	double CountAverage(vector<int> homework)
	{
		double sum = 0, average;
		for (int i = 0; i < homework.size(); i++)
		{
			sum += (double)homework[i];
		}
		average = (double)sum / (double)homework.size();
		return average;
	}
	double CountMedian(vector<int> homework)
	{
		double median;
		for (int i = 0; i < homework.size(); i++)
		{
			for (int j = i + 1; j < homework.size(); j++)
			{
				if (homework[i] > homework[j])
				{
					int temp = homework[i];
					homework[i] = homework[j];
					homework[j] = temp;
				}
			}
		}
		if (homework.size() % 2 != 0)
		{
			median = homework[homework.size() / 2];
		}
		else
		{
			median = (double)homework[homework.size() / 2] + homework[homework.size() / 2 - 1];
		}
		return median;
	}
	void CountFinal(double data, double examResult)
	{
		final = data * 0.4 + 0.6 * examResult;
	}
	void Print()
	{
		cout << "|" << setw(20) << name << "|" << setw(20) << surname << "|" << setw(20) << fixed << setprecision(2) << final << "|" << endl;
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
};
Student* AddInfo(vector<Student> arr);
bool ReturnMedianQuestion();
bool ReturnFileReadQuestion();
void SortArray(vector<Student>& arr);
void Program();
#endif // LOGIC_H

