#include "logic.h"
Student* AddInfo(vector<Student> arr)
{
	vector<int> homework;
	int examResult;
	bool end = false;
	string vardas, pavarde;
	int rezultatas;
	cout << "Irasykite studento varda ir pavarde" << endl;
	cin >> vardas >> pavarde;
	Student* student = new Student(vardas, pavarde);
	cout << "Ivesti paciam ar generuoti rezultatus? (p/g)" << endl;
	char ats = 'o';
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
			if (rezultatas > 10 || rezultatas < -1)
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
			else if (rezultatas == -1 && homework.size() > 0)
			{
				cin.clear();
				break;
			}
			homework.push_back(rezultatas);
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
		examResult = rez;
	}
	else if (ats == 'g')
	{
		int n;
		srand(time(NULL));
		n = rand() % 10;
		for (int i = 0; i < n; i++)
		{
			int rezultatas = rand() % 11;
			homework.push_back(rezultatas);
		}
		rezultatas = rand() % 11;
		examResult = rezultatas;
	}
	if (medianShow)
	{
		double median = student->CountMedian(homework);
		student->CountFinal(median, examResult);
	}
	else
	{
		double average = student->CountAverage(homework);
		student->CountFinal(average, examResult);
	}
	return student;
}
bool ReturnMedianQuestion()
{
	char ats = '0';
	bool answer = false;
	cout << "Rodyti vidurki ar mediana? (v/m)" << endl;
	while (ats != 'v' && ats != 'm')
	{
		cin >> ats;
	}
	if (ats == 'v')
	{
		answer = false;
	}
	else if (ats == 'm')
	{
		answer = true;
	}
	return answer;
}
bool ReturnFileReadQuestion() ///true - input, false - read file
{
	char ats = 'o';
	while (ats != 'd' && ats != 'f')
	{
		cin >> ats;
	}
	if (ats == 'd')
	{
		return true;
	}
	else if (ats == 'f')
	{
		return false;
	}
}
void Program()
{
	vector<Student> arr;
	medianShow = ReturnMedianQuestion();
	cout << "Ivesti duomenis ar nuskaityti is failo? (d/f)" << endl;
	char ats = '0';
	bool inputByHand = ReturnFileReadQuestion();
	if (inputByHand)
	{
		while (true)
		{
			Student* studentToAdd = AddInfo(arr);
			arr.push_back(*studentToAdd);
			delete studentToAdd;
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
	}
	else
	{
		try
		{
			ifstream read("kursiokai.txt");
			string parameter;
			read >> parameter >> ws >> parameter;
			int n = 0;
			while (parameter != "Egzaminas"&&read.is_open())
			{
				read >> ws >> parameter;

				if (parameter[0] == 'E')
				{
					break;
				}
				n++;
				cout << n << endl;
			}

			string vardas, pavarde;
			int homeworkElement, examResult;
			while (!read.eof())
			{
				vector<int> homework;
				read >> vardas >> pavarde;
				Student* studentas = new Student(vardas, pavarde);
				for (int i = 0; i < n; i++)
				{
					read >> homeworkElement;
					homework.push_back(homeworkElement);
				}
				read >> homeworkElement;
				examResult = homeworkElement;
				if (medianShow)
				{
					double median = studentas->CountMedian(homework);
					studentas->CountFinal(median, examResult);
				}
				else
				{
					double average = studentas->CountAverage(homework);
					studentas->CountFinal(average, examResult);
				}

				arr.push_back(*studentas);
				//studentas->Print();
				delete studentas;
			}
		}
		catch (const std::exception& e)
		{
			cerr << e.what() << endl;
			return;
		}
		
		
	}
	if (medianShow)
	{
		cout << "|" << setw(20) << "Vardas" << "|" << setw(20) << "Pavarde" << "|" << setw(20) << "Galutinis (Mediana)" << "|" << endl;
		for (int i = 0; i < 64; i++)
		{
			cout << "-";
		}
		cout << endl;
	}
	else
	{
		cout << "|" << setw(20) << "Vardas" << "|" << setw(20) << "Pavarde" << "|" << setw(20) << "Galutinis (Vidurkis)" << "|" << endl;
		for (int i = 0; i < 64; i++)
		{
			cout << "-";
		}
		cout << endl;
	}
	sort(arr.begin(), arr.end(), [](const auto& lhs, const auto& rhs)
		{
			return lhs.name < rhs.name;
		});
#pragma omp parallel
	{
		int i;
#pragma omp parallel for default(none),shared(i,arr)
		for (i = 0; i < arr.size(); i++)
		{
			arr[i].Print();
		}
	}
	
}
