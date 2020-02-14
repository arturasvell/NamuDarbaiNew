#include <iostream>
#include <iomanip>
#include <stdlib.h>
using namespace std;
bool medianShow = false;
class Student
{
private:
	string name="", surname="";


	int* homework=new int[1];
public:

	double average, median, final;
	int examResult;
	int counter = 0;
	void AddHomeworkElement(int result)
	{
		if (counter==0)
		{
			*(homework) = result;
			counter++;
		}
		else
		{
			int* resize = new int[counter + 1];
			for (int i = 0; i < counter; i++)
				*(resize+i) = *(homework+i);

			*(resize + counter) = result;
			counter++;
			delete[] homework;
			homework = new int[counter];
			for (int i = 0; i < counter; i++)
			{
				*(homework + i) = *(resize + i);
			}
			delete[] resize;
		}
	}
	void CountAverage()
	{
		double sum = 0;
		for (int i = 0; i < counter; i++)
		{
			sum += (double)homework[i];
		}
		average = (double)sum / (double)counter;
	}
	void CountMedian()
	{
		for (int i = 0; i < counter; i++)
		{
			for (int j = i+1; j < counter; j++)
			{
				if (homework[i] > homework[j])
				{
					int temp = homework[i];
					homework[i] = homework[j];
					homework[j] = temp;
				}
			}
		}
		if (counter % 2 != 0)
		{
			median = homework[counter / 2];
		}
		else
		{
			median = (double)homework[counter / 2] + homework[counter / 2 - 1];
		}
	}
	void CountFinal()
	{
		if(medianShow)
        {
            final = median * 0.4 + 0.6 * examResult;
        }
        else
        {
            final = average * 0.4 + 0.6 * examResult;
        }

	}
	void Print()
	{
        cout <<"|"<<setw(20)<<name<< "|" <<setw(20)<<surname << "|"<<setw(20) <<fixed<<setprecision(2)<< final << "|" << endl;
	}
	Student()
	{
		name = "Vardenis";
		surname = "Pavardenis";
		counter = 0;
		average = 0;
		median = 0;
		examResult = 0;
		homework = new int[1];
	}
	Student(string name, string surname)
	{
		this->name = name;
		this->surname = surname;
		counter = 0;
		average = 0;
		median = 0;
		examResult = 0;
		homework = new int[1];
	}
	Student(string name, string surname, int counter, int* homework)
	{
		this->name = name;
		this->surname = surname;
		this->counter = counter;
		average = 0;
		median = 0;
		examResult = 0;
		this->homework = new int[counter];
		for (int i = 0; i < counter; i++)
		{
			*(this->homework+i) = *(homework + i);
		}
		delete[] homework;
	}
};
Student* AddInfo(Student* arr)
{
	bool end = false;
	string vardas, pavarde;
	int rezultatas;
	cout << "Irasykite studento varda ir pavarde" << endl;
	cin >> vardas >> pavarde;
	Student* student = new Student(vardas, pavarde);
	cout << "Irasykite namu darbus: -1 baigia irasymo procesa" << endl;
	while (true)
	{
		cin >> rezultatas;
		if (rezultatas > 10||rezultatas<-1)
		{
			cout << "Netinka. Rezultatas netelpa i pazymio intervala" << endl;
			continue;
		}
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Netinkama ivestis" << endl;
			continue;
		}
		else if (rezultatas == -1 && student->counter > 0)
		{
			cin.clear();
			break;
		}
		student->AddHomeworkElement(rezultatas);
	}
	cout << "Irasykite egzaminu rezultatus" << endl;
	int rez;
	while (true)
	{
		cin >> rez;
		if (rez > 10 || rez < 0)
		{
			cout << "Netinka. Rezultatas netelpa i pazymio intervala" << endl;
			continue;
		}
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Netinkama ivestis" << endl;
			continue;
		}
		else
		{
			break;
		}
	}
	student->examResult = rez;
	return student;
}
int main()
{
	int counter = 0;
	char ats='0';
	Student* arr = new Student[1];
	cout << "Rodyti vidurki ar mediana? (v/m)" << endl;
	while (ats != 'v' && ats != 'm')
	{
		cin >> ats;
	}
	if (ats == 'v')
	{
		medianShow = false;
	}
	else if (ats == 'm')
	{
		medianShow = true;
	}
	while (true)
	{
		Student *studentToAdd=AddInfo(arr);
		studentToAdd->CountAverage();
		studentToAdd->CountFinal();
		studentToAdd->CountMedian();

		if (counter == 0)
		{
			arr[0] = *studentToAdd;
			counter++;
		}
		else
		{
			Student* arrCopy = new Student[counter + 1];
			for (int i = 0; i < counter; i++)
			{
				arrCopy[i] = arr[i];
			}
			arrCopy[counter] = *studentToAdd;
			counter++;
			delete[] arr;
			arr = new Student[counter];
			for (int i = 0; i < counter; i++)
			{
				arr[i] = arrCopy[i];
			}
		}

		cout << "Testi ivedima? (y/n)" << endl;
		cin >> ats;
		if (ats == 'y')
		{
			system("cls");
			continue;
		}
		else
		{
			system("cls");
			break;
		}
	}
	if (medianShow)
	{
		cout <<"|"<<setw(20)<<"Vardas"<< "|" <<setw(20)<<"Pavarde" << "|"<<setw(20) << "Galutinis (Mediana)" << "|" << endl;
		for(int i=0;i<64;i++)
        {
            cout<<"-";
        }
        cout<<endl;
		//printf("%75s \n","_");
		//cout << "Vardas" << "\t" << "Pavarde" << "\t"<<"Galutinis/ Mediana" << endl;
		//cout << "______________________________________________________________" << endl;
	}
	else
	{
		cout <<"|"<<setw(20)<<"Vardas"<< "|" <<setw(20)<<"Pavarde" << "|"<<setw(20) << "Galutinis (Vidurkis)" << "|" << endl;
		for(int i=0;i<64;i++)
        {
            cout<<"-";
        }
        cout<<endl;
		//printf("%75s \n","_");
		//cout << "Vardas" << "\t" << "Pavarde" << "\t" << "Galutinis/ Vidurkis" << endl;
		//cout << "______________________________________________________________" << endl;
	}
	for (int i = 0; i < counter; i++)
	{
		arr[i].Print();
	}
	return 0;
}

