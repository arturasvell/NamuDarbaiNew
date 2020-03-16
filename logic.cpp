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
	int n = 5;
	cout << "YES: Generuoti txt failus is naujo\nNO: Skaityti esamus txt failus\n(y/n)" << endl;
	char ans;
	bool generates = false;
	while (true)
	{
		cin >> ans;
		if (ans == 'y')
		{
			generates = true;
			break;
		}
		else if (ans == 'n')
		{
			break;
		}
		else
		{
			cout << "Netinkama ivestis\n";
		}
	}
	cout << "Pasirinkite skaitomu failu skaiciu: (1-" << n << ")" << endl;
	int answ;
	while (true)
	{
		cin >> answ;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Netinkama ivestis" << endl;
			continue;
		}
		if (answ<1 || answ>n)
		{
			cout << "Ivestis netelpa i intervala" << endl;
		}
		else
		{
			n = answ;
			break;
		}
	}
	vector<Student> arr, best;
	medianShow = false;
	int counter = 1000;
	for (int i = 0; i < n; i++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		if (generates)
		{
			GenerationAlgorithm(counter, 5);
		}
		arr.reserve(counter);
		ReadFile(arr, "kursiokai" + ConvertIntToString(counter));
		
		SortElements(arr, best);
		SortByName(arr);
		SortByName(best);
		PrintElements(arr, best);
		vector<Student>().swap(arr);
		vector<Student>().swap(best);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = end - start;
		cout << endl << counter << " dydzio vektoriaus testavimas uztruko " << diff.count() << " sekundziu\n";
		cout << "-----------------------------\n";
		arr.clear();
		arr.shrink_to_fit();
		best.clear();
		best.shrink_to_fit();
		counter *= 10;
	}
}
void SortByResults(vector<Student>& arr)
{
	auto start = std::chrono::high_resolution_clock::now();
	sort(arr.begin(), arr.end(), [](const auto& lhs, const auto& rhs)
		{
			return lhs.final < rhs.final;
		});
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << arr.size() << " dydzio vektoriaus rusiavimas pagal rezultatus uztruko " << diff.count() << " sekundziu\n";
}
void SortByName(vector<Student>& arr)
{
	auto start = std::chrono::high_resolution_clock::now();
	sort(arr.begin(), arr.end(), [](const auto& lhs, const auto& rhs)
		{
			return lhs.name < rhs.name;
		});
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << arr.size() << " dydzio vektoriaus rusiavimas pagal vardus uztruko " << diff.count() << " sekundziu\n";
}
void GenerationAlgorithm(int amountToGenerate, int counter) ///prielaida, kad counter <10
{
	ofstream fr("kursiokai" + ConvertIntToString(amountToGenerate) + ".txt");
	int fieldAmount = counter;
	fr << "Vardas Pavarde" << " ";
	for (int i = 1; i <= fieldAmount; i++)
	{
		fr << "ND" + ConvertIntToString(i) << " ";
	}
	fr << "Egz" << endl;
		for (int i = 0; i < amountToGenerate - 1; i++)
		{
			fr << "Vardas" + ConvertIntToString(i) << " " << "Pavarde" + ConvertIntToString(i) << " ";
			for (int j = 0; j < fieldAmount; j++)
			{
				fr << ConvertIntToString(rand() % 10 + 1) << " ";
			}
			fr << ConvertIntToString(rand() % 10 + 1) << endl;
		}
		fr.clear();
	fr.close();
}
void GenerateTxtFiles(int amountOfFiles)
{
	for (int i = 0; i < amountOfFiles; i++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		GenerationAlgorithm(1000 * pow(10, i), i + 3);
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
void ReadFile(vector<Student>& arr, string fileName)
{
	try
	{
		ifstream read(fileName + ".txt");
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
		Student* studentas = new Student();
		vector<int> homework;
		while (!read.eof())
		{
			
			read >> vardas >> pavarde;
			studentas->name = vardas;
			studentas->surname = pavarde;
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
			vector<int>().swap(homework);
			arr.push_back(*studentas);
		}
		homework.clear();
		homework.shrink_to_fit();
		delete studentas;
		read.clear();
		read.close();
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = end - start;
		cout << "Failo " << fileName + ".txt" << " skaitymas uztruko " << diff.count() << " sekundziu\n";
	}
	catch (const std::exception & e)
	{
		cerr << e.what() << endl;
		return;
	}
}
void PrintElements(vector<Student> arr, vector<Student> best)
{
	auto start = std::chrono::high_resolution_clock::now();
	ofstream fr("galvociai" + ConvertIntToString(best.size()) + ".txt");
	int i;
	for (i = 0; i < best.size(); i++)
	{
		fr << "|" << setw(20) << best[i].name << "|" << setw(20) << best[i].surname << "|" <<
			setw(20) << fixed << setprecision(2) << best[i].final << "|" << endl;
	}
	fr.close();
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << "Galvociu rasymas i faila uztruko " << diff.count() << " sekundziu\n";
	start = std::chrono::high_resolution_clock::now();
	ofstream fr2("nuskriaustieji" + ConvertIntToString(arr.size()) + ".txt");
	for (i = 0; i < arr.size(); i++)
	{
		fr2 << "|" << setw(20) << arr[i].name << "|" << setw(20) << arr[i].surname << "|" <<
			setw(20) << fixed << setprecision(2) << arr[i].final << "|" << endl;
	}
	fr2.close();
	end = std::chrono::high_resolution_clock::now();
	diff = end - start;
	cout << "Nuskriaustuju rasymas i faila uztruko " << diff.count() << " sekundziu\n";
}
void SortElements(vector<Student>& arr, vector<Student>& best)
{
	auto start = std::chrono::high_resolution_clock::now();
	int index=0;
	SortByResults(arr);
	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i].final >= 5.0f)
		{
			index = i;
			break;
		}
	}
	for (int i = index; i < arr.size(); i++)
	{
		best.push_back(arr[i]);
	}
	arr.resize(index + 1);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << "Vektoriaus skaidymas i du uztruko " << diff.count() << " sekundziu\n";
}
double Student::CountMedian(vector<int> homework)
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
void Student::CountFinal(double data, double examResult)
{
	final = data * 0.4 + 0.6 * examResult;
}
void Student::Print()
{
	cout << "|" << setw(20) << name << "|" << setw(20) << surname << "|" << setw(20) << fixed << setprecision(2) << final << "|" << endl;
}
double Student::CountAverage(vector<int> homework)
{
	double sum = 0, average;
	for (int i = 0; i < homework.size(); i++)
	{
		sum += (double)homework[i];
	}
	average = (double)sum / (double)homework.size();
	return average;
}
