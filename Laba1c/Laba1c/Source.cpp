#include <iostream>
#include "FlexLexer.h"
#include <fstream>
#include <array>
#include <string>
#include <functional>
#include <sstream>
#include <vector>
#include <map>
#include <set>


using namespace std;

int Input();  //ввод и проверка
int Read();   //чтение из файла
int Show();   //вывод статистики

#define SIZE 4
static const std::array<string, SIZE> msgs = { "1. Input", "2. Read from file", "3. Show statistic", "4. Exit" };
static const std::array<function<bool()>, SIZE> func = { Input, Read, Show };

int getInt(int &);

int main()
{
	int c;
	const char *msg = "";
	do
	{
		system("cls");
		for (int i = 0; i < SIZE; i++)
		{
			cout << msgs[i].c_str() << endl;
		}
		cout << "Your choice:------>";
		do
		{
			cout << msg;
			getInt(c);
			msg = "Error! Repeat, please!";

		} while (c > 4);
		if (c != 4) func[c - 1]();
		msg = "";
	} while (c != 4);

	cout << "\n\n" << endl;
	cout << "--------------That's all! Bye!--------------------------";
	return 0;
}

int Input()
{
	yyFlexLexer lexer;
	cout << "Enter string:" << endl;
	string str;
	getline(cin, str);
	getline(cin, str);
	istringstream i(str + "\n");
	ostringstream o;
	istream& input(i);
	ostream& ouput(o);
	lexer.switch_streams(&input, &ouput);
	if (lexer.yylex())
	{
		cout << "Ok: " << o.str() << endl;
		ofstream of = ofstream("statistics.txt", ofstream::app);
		of << o.str() << endl;
		of.close();
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
	cout << "open test.txt" << endl;
	ifstream fi = ifstream(string("test.txt")); //открыли
	if (fi.good()) //если файл вообще нашли
	{
		while (!fi.eof())
		{
			yyFlexLexer lexer;
			string str;
			getline(fi, str);
			istringstream i(str + "\n");
			ostringstream o;
			istream& input(i);
			ostream& ouput(o);
			lexer.switch_streams(&input, &ouput);
			cout << "string: " << str << " -> ";
			if (lexer.yylex())
			{
				cout << "Ok: " << o.str() << endl;
				ofstream of = ofstream("statistics.txt", ofstream::app);
				of << o.str() << endl;
				of.close();
			}
			else
			{
				cout << "Wrong!" << endl;
			}
		}
	}
	else
	{
		cout << "file test.txt not found" << endl;
	}
	system("pause");
	fi.close();
	return 1;
}

int Show()
{
	map<string, int> stat; //map - имя  - число раз
	ifstream i = ifstream(string("statistics.txt"));
	if (i.good())
	{
		while (!i.eof())
		{
			string str;
			getline(i, str);
			if (str.empty()) //пропускаем пустые строки
				continue;
			if (stat.find(str) != stat.end())
				stat[str]++; //инкремент числа упоминаний имя сервера
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


int getInt(int &a)
{
	cin >> a;
	if (!cin.good())
		return -1;
	return 1;
}