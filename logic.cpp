#include "logic.h"
bool MODE = false;
Student* AddInfo(deque<Student> arr)
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
	Method program = DEQUE;
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
	cout<<"Pasirinkite konteinerio tipa:\nv - vector\nl-list\nd-deque\n";
    while (true)
	{
		cin >> ans;
		if (ans == 'v')
		{
			program=VECTOR;
			break;
		}
		else if (ans == 'l')
		{
			program=LIST;
			break;
		}
		else if(ans=='d')
        {
            program=DEQUE;
            break;
        }
		else
		{
			cout << "Netinkama ivestis\n";
		}
	}
	cout<<"Pasirinkite rusiavimo buda:\n1 - du konteineriai\n2- trys konteineriai\n";
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
		if (answ==1)
		{
			MODE=true;
			break;
		}
		else if(answ==2)
		{
			MODE=false;
			break;
		}
	}
	vector<Student> arr, best, worst;
	deque<Student> arr2, best2, worst2;
	list<Student> arr3, best3,worst3;
	medianShow = false;
	int counter = 1000;
	if (program == VECTOR)
	{
		for (int i = 0; i < n; i++)
		{
			auto start = std::chrono::high_resolution_clock::now();
			if (generates)
			{
				GenerationAlgorithm(counter, 5);
			}
			//arr.reserve(counter);
			bufer_nusk1("kursiokai" + ConvertIntToString(counter), arr);
			//SortByResults(arr);
			SortElements1(arr, best, worst);
			if(MODE)
            {
                SortByName1(arr);
            }
			SortByName1(best);
			if(!MODE)
            {
                SortByName1(worst);
            }
			PrintElements1(arr, best);
			vector<Student>().swap(arr);
			vector<Student>().swap(best);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> diff = end - start;
			cout << endl << counter << " dydzio vektoriaus testavimas uztruko " << diff.count() << " sekundziu\n";
			cout << "-----------------------------\n";
			arr.clear();
			best.clear();
			counter *= 10;
		}
	}
	else if (program == DEQUE)
	{
		for (int i = 0; i < n; i++)
		{
			auto start = std::chrono::high_resolution_clock::now();
			if (generates)
			{
				GenerationAlgorithm(counter, 5);
			}
			//arr.reserve(counter);
			bufer_nusk("kursiokai" + ConvertIntToString(counter), arr2);
			//SortByResults(arr);
			SortElements(arr2, best2,worst2);
			if(MODE)
            {
                SortByName(arr2);
            }
			SortByName(best2);
			if(!MODE)
            {
                SortByName(worst2);
            }
			PrintElements(arr2, best2);
			deque<Student>().swap(arr2);
			deque<Student>().swap(arr2);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> diff = end - start;
			cout << endl << counter << " dydzio deque testavimas uztruko " << diff.count() << " sekundziu\n";
			cout << "-----------------------------\n";
			arr2.clear();
			best2.clear();
			counter *= 10;
		}
	}
	else if (program == LIST)
	{
		for (int i = 0; i < n; i++)
		{
			auto start = std::chrono::high_resolution_clock::now();
			if (generates)
			{
				GenerationAlgorithm(counter, 5);
			}
			//arr.reserve(counter);
			bufer_nusk2("kursiokai" + ConvertIntToString(counter), arr3);
			//SortByResults(arr);
			SortElements2(arr3, best3,worst3);
			if(MODE)
            {
                SortByName2(arr3);
            }

			SortByName2(best3);
			if(!MODE)
            {
                SortByName2(worst3);
            }
			PrintElements2(arr3, best3);
			list<Student>().swap(arr3);
			list<Student>().swap(arr3);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> diff = end - start;
			cout << endl << counter << " dydzio list testavimas uztruko " << diff.count() << " sekundziu\n";
			cout << "-----------------------------\n";
			arr3.clear();
			best3.clear();
			counter *= 10;
		}
	}

}
void SortByResults(deque<Student>& arr)
{
	auto start = std::chrono::high_resolution_clock::now();
	sort(arr.begin(), arr.end(), [](const auto& lhs, const auto& rhs)
		{
			return lhs.final < rhs.final;
		});
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << arr.size() << " dydzio deque rusiavimas pagal rezultatus uztruko " << diff.count() << " sekundziu\n";
}
void SortByName(deque<Student>& arr)
{
	auto start = std::chrono::high_resolution_clock::now();
	sort(arr.begin(), arr.end(), [](const auto& lhs, const auto& rhs)
		{
			return lhs.name < rhs.name;
		});
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << arr.size() << " dydzio deque rusiavimas pagal vardus uztruko " << diff.count() << " sekundziu\n";
}
void GenerationAlgorithm(int amountToGenerate, int counter) ///prielaida, kad counter <10
{
	auto start = std::chrono::high_resolution_clock::now();
	ofstream fr("kursiokai" + ConvertIntToString(amountToGenerate) + ".txt");
	int fieldAmount = counter;
	fr << "Vardas Pavarde" << " ";
	for (int i = 1; i <= fieldAmount; i++)
	{
		fr << "ND" + ConvertIntToString(i) << " ";
	}
	fr << "Egz" << endl;
		for (int i = 0; i < amountToGenerate-1; i++)
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
	std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start; // Skirtumas (s)
	std::cout << "Failo generavimas uztruko: " << diff.count() << " s\n";
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
void PrintElements(deque<Student> arr, deque<Student> best)
{
	auto start = std::chrono::high_resolution_clock::now();
	ofstream fr("galvociai" + ConvertIntToString(best.size()) + ".txt");
	int i;
	for (deque<Student>::iterator i = best.begin(); i != best.end(); i++)
	{
		fr << "|" << setw(20) << (*i).name << "|" << setw(20) << (*i).surname << "|" <<
			setw(20) << fixed << setprecision(2) << (*i).final << "|" << endl;
	}
	fr.close();
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << "Galvociu rasymas i faila uztruko " << diff.count() << " sekundziu\n";
	start = std::chrono::high_resolution_clock::now();
	ofstream fr2("nuskriaustieji" + ConvertIntToString(arr.size()) + ".txt");
	for (deque<Student>::iterator i = arr.begin(); i != arr.end(); i++)
	{
		fr2 << "|" << setw(20) << (*i).name << "|" << setw(20) << (*i).surname << "|" <<
			setw(20) << fixed << setprecision(2) << (*i).final << "|" << endl;
	}
	fr2.close();
	end = std::chrono::high_resolution_clock::now();
	diff = end - start;
	cout << "Nuskriaustuju rasymas i faila uztruko " << diff.count() << " sekundziu\n";
}
void SortElements(deque<Student>& arr, deque<Student>& best, deque<Student>& worst)
{
	auto start = std::chrono::high_resolution_clock::now();

	if (MODE)
	{
		cout<<"Naudojama dvieju deque strategija"<<endl;
		int index = 0;
		SortByResults(arr);
		for (deque<Student>::iterator i = arr.begin(); i != arr.end(); i++)
		{
			index++;
			if ((*i).final >= 5.0f)
			{
				break;
			}
		}
		deque<Student>::iterator i = arr.begin();
		advance(i, index);
		for (i; i != arr.end(); i++)
		{
			best.push_back(*i);
		}
		//index++;
		arr.resize(index);
	}
	else
	{
		cout<<"Naudojama triju deque strategija"<<endl;
		for (deque<Student>::iterator i = arr.begin(); i != arr.end(); i++)
		{
			if ((*i).final >= 5.0f)
			{
				best.push_back((*i));
			}
			else
			{
				worst.push_back((*i));
			}
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << "Deque skaidymas i du uztruko " << diff.count() << " sekundziu\n";
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
void bufer_nusk(std::string read_vardas, deque<Student>& arr)
{
	try
	{
		auto start = std::chrono::high_resolution_clock::now();
		int homeworkElement, examResult;
		Student* studentas = new Student();
		vector<int> homework;
		std::vector<std::string> splited;
		std::string eil;
		std::stringstream my_buffer;
		std::ifstream open_f(read_vardas + ".txt");
		my_buffer << open_f.rdbuf();
		open_f.close();

		start = std::chrono::high_resolution_clock::now();
		while (my_buffer) {
			if (!my_buffer.eof()) {
				std::getline(my_buffer, eil);
				splited.push_back(eil);
			}
			else break;
		}

		start = std::chrono::high_resolution_clock::now();
		std::string outputas = "";
		for (std::string& a : splited) (a.compare(*splited.rbegin()) != 0) ? outputas += a + "\n" : outputas += a;
		splited.clear();
		istringstream data;
		data.str(outputas);
		string parameter;
		data >> parameter >> ws >> parameter;
		int n = 0;
		while (parameter != "Egzaminas" && !data.eof())
		{
			data >> ws >> parameter;

			if (parameter[0] == 'E')
			{
				break;
			}
			n++;
		}
		while (!data.eof())
		{
			data >> studentas->name >> studentas->surname;
			for (int i = 0; i < n; i++)
			{
				data >> homeworkElement;
				homework.push_back(homeworkElement);
			}
			data >> examResult;
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
		cout << arr.size() << endl;
		data.clear();
		std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start; // Skirtumas (s)
		std::cout << "Failo nuskaitymas uztruko: " << diff.count() << " s\n";
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
		return;
	}

}
Student* AddInfo1(vector<Student> arr)
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
void PrintElements1(vector<Student> arr, vector<Student> best)
{
	auto start = std::chrono::high_resolution_clock::now();
	ofstream fr("galvociai" + ConvertIntToString(best.size()) + ".txt");
	int i;
	for (vector<Student>::iterator i = best.begin(); i != best.end(); i++)
	{
		fr << "|" << setw(20) << (*i).name << "|" << setw(20) << (*i).surname << "|" <<
			setw(20) << fixed << setprecision(2) << (*i).final << "|" << endl;
	}
	fr.close();
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << "Galvociu rasymas i faila uztruko " << diff.count() << " sekundziu\n";
	start = std::chrono::high_resolution_clock::now();
	ofstream fr2("nuskriaustieji" + ConvertIntToString(arr.size()) + ".txt");
	for (vector<Student>::iterator i = arr.begin(); i != arr.end(); i++)
	{
		fr2 << "|" << setw(20) << (*i).name << "|" << setw(20) << (*i).surname << "|" <<
			setw(20) << fixed << setprecision(2) << (*i).final << "|" << endl;
	}
	fr2.close();
	end = std::chrono::high_resolution_clock::now();
	diff = end - start;
	cout << "Nuskriaustuju rasymas i faila uztruko " << diff.count() << " sekundziu\n";
}
void SortElements1(vector<Student>& arr, vector<Student>& best, vector<Student>& worst)
{
	auto start = std::chrono::high_resolution_clock::now();
	bool sortingMethod = false;
	if (MODE)
	{
		cout<<"Naudojama dvieju vektoriu strategija"<<endl;
		int index = 0;
		SortByResults1(arr);
		for (vector<Student>::iterator i = arr.begin(); i != arr.end(); i++)
		{
			index++;
			if ((*i).final >= 5.0f)
			{
				break;
			}
		}
		vector<Student>::iterator i = arr.begin();
		advance(i, index);
		for (i; i != arr.end(); i++)
		{
			best.push_back(*i);
		}
		//index++;
		arr.resize(index);
	}
	else
	{
		cout<<"Naudojama triju vektoriu strategija"<<endl;
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
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << "Vektoriaus skaidymas i du uztruko " << diff.count() << " sekundziu\n";
}
void SortByName1(vector<Student>& arr)
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
void SortByResults1(vector<Student>& arr)
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
void bufer_nusk1(std::string read_vardas, vector<Student>& arr)
{
	try
	{
		auto start = std::chrono::high_resolution_clock::now();
		int homeworkElement, examResult;
		Student* studentas = new Student();
		vector<int> homework;
		std::vector<std::string> splited;
		std::string eil;
		std::stringstream my_buffer;
		std::ifstream open_f(read_vardas + ".txt");
		my_buffer << open_f.rdbuf();
		open_f.close();

		start = std::chrono::high_resolution_clock::now();
		while (my_buffer) {
			if (!my_buffer.eof()) {
				std::getline(my_buffer, eil);
				splited.push_back(eil);
			}
			else break;
		}

		start = std::chrono::high_resolution_clock::now();
		std::string outputas = "";
		for (std::string& a : splited) (a.compare(*splited.rbegin()) != 0) ? outputas += a + "\n" : outputas += a;
		splited.clear();
		istringstream data;
		data.str(outputas);
		string parameter;
		data >> parameter >> ws >> parameter;
		int n = 0;
		while (parameter != "Egzaminas" && !data.eof())
		{
			data >> ws >> parameter;

			if (parameter[0] == 'E')
			{
				break;
			}
			n++;
		}
		while (!data.eof())
		{
			data >> studentas->name >> studentas->surname;
			for (int i = 0; i < n; i++)
			{
				data >> homeworkElement;
				homework.push_back(homeworkElement);
			}
			data >> examResult;
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
		cout << arr.size() << endl;
		data.clear();
		std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start; // Skirtumas (s)
		std::cout << "Failo nuskaitymas uztruko: " << diff.count() << " s\n";
	}
	catch (const std::exception & e)
	{
		cerr << e.what() << endl;
		return;
	}
}
Student* AddInfo2(list<Student> arr)
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
void PrintElements2(list<Student> arr, list<Student> best)
{
	auto start = std::chrono::high_resolution_clock::now();
	ofstream fr("galvociai" + ConvertIntToString(best.size()) + ".txt");
	int i;
	for (list<Student>::iterator i = best.begin(); i != best.end(); i++)
	{
		fr << "|" << setw(20) << (*i).name << "|" << setw(20) << (*i).surname << "|" <<
			setw(20) << fixed << setprecision(2) << (*i).final << "|" << endl;
	}
	fr.close();
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << "Galvociu rasymas i faila uztruko " << diff.count() << " sekundziu\n";
	start = std::chrono::high_resolution_clock::now();
	ofstream fr2("nuskriaustieji" + ConvertIntToString(arr.size()) + ".txt");
	for (list<Student>::iterator i = arr.begin(); i != arr.end(); i++)
	{
		fr2 << "|" << setw(20) << (*i).name << "|" << setw(20) << (*i).surname << "|" <<
			setw(20) << fixed << setprecision(2) << (*i).final << "|" << endl;
	}
	fr2.close();
	end = std::chrono::high_resolution_clock::now();
	diff = end - start;
	cout << "Nuskriaustuju rasymas i faila uztruko " << diff.count() << " sekundziu\n";
}
void SortElements2(list<Student>& arr, list<Student>& best, list<Student>& worst)
{
	auto start = std::chrono::high_resolution_clock::now();
	if (MODE)
	{
        cout<<"Naudojama dvieju listu strategija"<<endl;
		int index = 0;
		SortByResults2(arr);
		for (list<Student>::iterator i = arr.begin(); i != arr.end(); i++)
		{
			index++;
			if ((*i).final >= 5.0f)
			{
				break;
			}
		}
		list<Student>::iterator i = arr.begin();
		advance(i, index);
		for (i; i != arr.end(); i++)
		{
			best.push_back(*i);
		}
		//index++;
		arr.resize(index);
	}
	else
	{
		cout<<"Naudojama triju listu strategija"<<endl;
		for (list<Student>::iterator i=arr.begin();i!=arr.end();i++)
		{
			if ((*i).final >= 5.0f)
			{
				best.push_back((*i));
			}
			else
			{
				worst.push_back((*i));
			}
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << "Listo skaidymas i du uztruko " << diff.count() << " sekundziu\n";
}
void SortByName2(list<Student>& arr)
{
	auto start = std::chrono::high_resolution_clock::now();
	arr.sort([](const Student& player1, const Student& player2)
		{
			if (player1.name == player2.name)
				return player1.surname < player2.surname;
			return player1.name < player2.name;
		});
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << arr.size() << " dydzio listo rusiavimas pagal vardus uztruko " << diff.count() << " sekundziu\n";
}
void SortByResults2(list<Student>& arr)
{
	auto start = std::chrono::high_resolution_clock::now();
	arr.sort([](const Student& player1, const Student& player2)
		{
			return player1.final < player2.final;
		});
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << arr.size() << " dydzio listo rusiavimas pagal rezultatus uztruko " << diff.count() << " sekundziu\n";
};
void bufer_nusk2(std::string read_vardas, list<Student>& arr)
{
	try
	{
		auto start = std::chrono::high_resolution_clock::now();
		int homeworkElement, examResult;
		Student* studentas = new Student();
		vector<int> homework;
		std::vector<std::string> splited;
		std::string eil;
		std::stringstream my_buffer;
		std::ifstream open_f(read_vardas + ".txt");
		my_buffer << open_f.rdbuf();
		open_f.close();

		start = std::chrono::high_resolution_clock::now();
		while (my_buffer) {
			if (!my_buffer.eof()) {
				std::getline(my_buffer, eil);
				splited.push_back(eil);
			}
			else break;
		}

		start = std::chrono::high_resolution_clock::now();
		std::string outputas = "";
		for (std::string& a : splited) (a.compare(*splited.rbegin()) != 0) ? outputas += a + "\n" : outputas += a;
		splited.clear();
		istringstream data;
		data.str(outputas);
		string parameter;
		data >> parameter >> ws >> parameter;
		int n = 0;
		while (parameter != "Egzaminas" && !data.eof())
		{
			data >> ws >> parameter;

			if (parameter[0] == 'E')
			{
				break;
			}
			n++;
		}
		while (!data.eof())
		{
			data >> studentas->name >> studentas->surname;
			for (int i = 0; i < n; i++)
			{
				data >> homeworkElement;
				homework.push_back(homeworkElement);
			}
			data >> examResult;
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
		cout << arr.size() << endl;
		data.clear();
		std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start; // Skirtumas (s)
		std::cout << "Failo nuskaitymas uztruko: " << diff.count() << " s\n";
	}
	catch (const std::exception & e)
	{
		cerr << e.what() << endl;
		return;
	}
}
