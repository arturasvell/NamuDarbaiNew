#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
bool medianShow = false;
class Student
{
private:
	string name="", surname="";
public:
    vector<int> homework;
	double average, median, final;
	int examResult;
	void AddHomeworkElement(int result)
	{
		homework.push_back(result);
	}
	void CountAverage()
	{
		double sum = 0;
		for (int i = 0; i < homework.size(); i++)
		{
			sum += (double)homework[i];
		}
		average = (double)sum / (double)homework.size();
	}
	void CountMedian()
	{
		for (int i = 0; i < homework.size(); i++)
		{
			for (int j = i+1; j < homework.size(); j++)
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
		average = 0;
		median = 0;
		examResult = 0;
	}
	Student(string name, string surname)
	{
		this->name = name;
		this->surname = surname;
		average = 0;
		median = 0;
		examResult = 0;
	}
	Student(string name, string surname, vector<int> homework)
	{
		this->name = name;
		this->surname = surname;
		average = 0;
		median = 0;
		examResult = 0;
		this->homework=homework;
	}
};
Student* AddInfo(vector<Student> arr)
{
	bool end = false;
    string vardas, pavarde;
    int rezultatas;
    cout << "Irasykite studento varda ir pavarde" << endl;
    cin >> vardas >> pavarde;
    Student* student = new Student(vardas, pavarde);
    cout<<"Ivesti paciam ar generuoti rezultatus? (p/g)"<<endl;
    char ats='o';
    while (ats != 'p' && ats != 'g')
    {
        cin >> ats;
    }
    if (ats == 'p')
    {
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
    }
    else if (ats == 'g')
    {
        int n;
        srand(time(NULL));
        n=rand()%10;
        for(int i=0;i<n;i++)
        {
            int rezultatas=rand()%11;
            student->AddHomeworkElement(rezultatas);
        }
        rezultatas=rand()%11;
        student->examResult=rezultatas;
    }

    return student;
}
int main()
{
	char ats='0';
	vector<Student> arr;
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

		arr.push_back(*studentToAdd);

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
	}
	else
	{
		cout <<"|"<<setw(20)<<"Vardas"<< "|" <<setw(20)<<"Pavarde" << "|"<<setw(20) << "Galutinis (Vidurkis)" << "|" << endl;
		for(int i=0;i<64;i++)
        {
            cout<<"-";
        }
        cout<<endl;
	}
	for (int i = 0; i < arr.size(); i++)
	{
		arr[i].Print();
	}
	return 0;
}

