#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <windows.h>
#include <map>


using namespace std;

const string Menu[] = { "1. Input", "2. Read from file", "3. Show statistic", "4. Timing", "5. Quit" };

int Input(), Read(), Show(), Timing();
int(*Funcs[])() = {nullptr, Input,Read, Show,Timing };
bool checkString(const string& source, string& result);

int getInt(int &);

const int Num = sizeof(Menu) / sizeof(Menu[0]);
int main()
{
	int c;
	const char *msg = "";
	do
	{
		system("cls");
			for (int i = 0; i < Num; i++)
		{
			cout << Menu[i].c_str() << endl;
		}
		cout << "Your choice:------>";
		do
		{
			cout << msg;
			getInt(c);
			msg = "Error! Repeat, please!";

		} while (c > 5);
		if (c != 5) Funcs[c]();
		msg = "";
	} while (c != 5);

	cout << "\n\n" << endl;
	cout << "--------------That's all! Bye!--------------------------";
	return 0;
}

//ввод строк
int Input()
{
	cout << "Enter string:" << endl;
	string str;
	cin.ignore();
	getline(cin, str);
	string result;
	if (checkString(str, result)) //если ок
	{
		cout << "Right!" << result << endl; //выводим "верно" и имя user 
		ofstream f = ofstream("statistics.txt", ofstream::app);
		f << result << endl; //дописываем имя в файл со статистикой
		f.close();
	}
	else
	{
		cout << "Wrong!" << endl;
	}
	system("pause");
	return 1;
}


//чтение из файла test.txt
int Read()
{
	fstream fi;
	fi.open("test.txt", ios::in);////открыли
	if (fi.good()) //если файл вообще нашли
	{
		while (!fi.eof()) //пока в файле есть строки
		{
			string str;
			string result;
			getline(fi, str); //читаем
			cout << "string: " << str << " -> "; //выводим строку
			if (checkString(str, result))
			{
				cout << "Right! " << result << endl; //выводим результат
				ofstream 
					f = ofstream("statistics.txt", ofstream::app);
				f << result << endl; //дописываем имя user в файл со статистикой
				f.close();
			}
			else
			{
				cout << "Wrong!" << endl;
			}
		}
		cout << "file ended" << endl;
	}
	else
	{
		cout << "file test.txt not found" << endl;
	}
	fi.close();
	system("pause");
	return 1;
}

//вывод статистики из файла statistics.txt
int Show()
{
	map<string, int> stat; //map < имя user-число раз>
	fstream i;
	i.open("statistics.txt", ios::in);
	if (i.good())
	{
		while (!i.eof())
		{
			string str;
			getline(i, str);
			if (str.empty()) //пропускаем пустые строки
				continue;
			if (stat.find(str) != stat.end())
				stat[str]++; //инкремент числа упоминаний имя
			else
				stat.insert(pair<string, int>(str, 1)); //вставка нового имени функции
		}
		for (const auto& it : stat)
			cout << it.first << " : " << it.second << endl; //вывод статистики
	}
	else
	{
		cout << "file statistics.txt not found" << endl;
	}
	system("pause");
	return 1;
}

//функция проверки строки source на соответствие варианту
//в result возвращается значение для статистики
bool checkString(const string& source, string& result)
{
	regex re("(ftp:\\/\\/([a-zA-Z]{1,20})@([a-zA-Z]{1,20}\\.)+[a-zA-Z]{1,5})");


	smatch match; //match_results for string objects
	if (!regex_match(source, match, re)) //проверили строку на соответствие регулярному выражению
		return false;
	result = match[2]; //записали в результат стркоу для статистики
	return true;
}
int Timing()
{
	cout << "Preparing for timing" << endl;
	vector<string> vector; //вектор строк для таймирования
	ifstream fi = ifstream("test.txt");
	if (fi.good())
	{
		while (!fi.eof())
		{
			string str;
			getline(fi, str);
			vector.push_back(str); //переписываем строки из файла в вектор
		}
		fi.close();
		cout << "Timing started" << endl;

		//начинаем таймирование
		auto t = time(0);
		string result;
		for (int j = 0; j < 100000; ++j) //ищем время обработки 100 000 строк
		{
			checkString(vector[j % vector.size()], result);
			if ((j + 1) % 10000 == 0)
				cout << (j + 1) << " : " << time(0) - t << " s" << endl;
		}
		cout << "Timing ended" << endl;
	}
	else
	{
		cout << "file test.txt for timing not found" << endl;
	}
	return 1;
}

int getInt(int &a)
{
	cin >> a;
	if (!cin.good())
		return -1;
	return 1;
}