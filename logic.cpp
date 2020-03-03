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
	GenerateTxtFiles(3);
	vector<Student> arr, best,worst;
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
		while (true)
		{
			ReadFile(arr);
			cout << "Nuskaityti dar viena faila? (y/n)" << endl;
			cin >> ats;
			if (ats=='y')
			{
				continue;
			}
			else
			{
				break;
			}
		}
		
	}
	/*if (medianShow)
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
	}*/

	sort(arr.begin(), arr.end(), [](const auto& lhs, const auto& rhs)
		{
			return lhs.name < rhs.name;
		});
	
	SortElements(arr, best, worst);
	PrintElements(best, worst);
}
void GenerationAlgorithm(int amountToGenerate, int counter) ///prielaida, kad counter <10
{
	ofstream fr("kursiokai"+ ConvertIntToString(amountToGenerate)+".txt");
	int fieldAmount = counter;
	fr << "Vardas Pavarde" << " ";
	for (int i = 1; i <= fieldAmount; i++)
	{
		fr << "ND" + ConvertIntToString(i) << " ";
	}
	fr << "Egz" << endl;
	omp_set_num_threads(4);
#pragma omp parallel for
	{
		for (int i = 0; i < amountToGenerate; i++)
		{
			fr << "Vardas" + ConvertIntToString(i) << " " << "Pavarde" + ConvertIntToString(i) << " ";
			for (int j = 0; j < fieldAmount; j++)
			{
				fr << ConvertIntToString(rand() % 10 + 1) << " ";
			}
			fr << ConvertIntToString(rand() % 10 + 1) << endl;
		}
	}
	
	fr.close();
}
void GenerateTxtFiles(int amountOfFiles)
{
	for (int i = 0; i < amountOfFiles; i++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		GenerationAlgorithm(1000 * pow(10, i),i+3);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = end - start;
		cout << 1000 * pow(10, i) << " elementu failo generavimas uztruko " << diff.count() << " sekundziu\n";
	}
}
string ConvertIntToString(int toConvert)
{
	string result;         
	ostringstream convert;   
	convert << toConvert;  
	result = convert.str();
	return result;
}
void ReadFile(vector<Student> &arr)
{
	try
	{
		cout << "Koks failo pavadinimas?" << endl;
		string fileName;
		cin >> fileName;
		ifstream read(fileName + ".txt");
		if (read.is_open())
		{
			cout << "Failas sekmingai atidarytas" << endl;
		}
		else
		{
			cout << "Failas nerastas" << endl;
			ReadFile(arr);
			return;
		}
		auto start = std::chrono::high_resolution_clock::now();
		string parameter;
		read >> parameter >> ws >> parameter;
		int n = 0;
		while (parameter != "Egzaminas" && read.is_open())
		{
			read >> ws >> parameter;

			if (parameter[0] == 'E')
			{
				break;
			}
			n++;
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
		read.close();
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = end - start;
		cout << "Failo skaitymas uztruko " << diff.count() << " sekundziu\n";
	}
	catch (const std::exception & e)
	{
		cerr << e.what() << endl;
		return;
	}
}
void PrintElements(vector<Student> best, vector<Student> worst)
{
	auto start = std::chrono::high_resolution_clock::now();
	ofstream fr("galvociai.txt");
	int i;
#pragma omp parallel for
	for (i = 0; i < best.size(); i++)
	{
		fr << "|" << setw(20) << best[i].name << "|" << setw(20) << best[i].surname << "|" <<
			setw(20) << fixed << setprecision(2) << best[i].final << "|" << endl;
	}
	fr.close();
	ofstream fr2("nuskriaustieji.txt");
#pragma omp parallel for
	for (i = 0; i < worst.size(); i++)
	{
		fr2 << "|" << setw(20) << worst[i].name << "|" << setw(20) << worst[i].surname << "|" <<
			setw(20) << fixed << setprecision(2) << worst[i].final << "|" << endl;
	}
	fr2.close();
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << "Rasymas i faila uztruko " << diff.count() << " sekundziu\n";
}
void SortElements(vector<Student> arr, vector<Student>& best, vector<Student>& worst)
{
	auto start = std::chrono::high_resolution_clock::now();
	/*cout << "|" << setw(20) << "Vardas" << "|" << setw(20) << "Pavarde" << "|" << setw(20) << (medianShow? "Galutinis (Mediana)": "Galutinis(Vidurkis)") << "|" << endl;
	for (int i = 0; i < 64; i++)
	{
		cout << "-";
	}
	cout << endl;*/
	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i].final >= 5.0f)
		{
			best.push_back(arr[i]);
		}
		else
		{
			worst.push_back(arr[i]);
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << "Vektoriaus skaidymas i du uztruko " << diff.count() << " sekundziu\n";
}
