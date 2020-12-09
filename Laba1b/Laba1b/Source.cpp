#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <functional>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <map>
#include "AppClass.h"

using namespace std;
using namespace statemap;

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
			cout <<msgs[i].c_str() << endl;
		}
		cout << "Your choice:------>";
		do
		{
			cout << msg;
			getInt(c);
			msg = "Error! Repeat, please!";

		} while (c > 4);
		if (c!=4) func[c-1]();
		msg = "";
	} while (c != 4);

	cout << "\n\n" << endl;
	cout << "--------------That's all! Bye!--------------------------";
	return 0;
}

//ввод строк
int Input()
{
	AppClass thisContext;
	cout << "Enter string:" << endl;
	string str;
	cin.ignore();
	getline(cin, str);
	if (thisContext.CheckString(str)) //если ок
	{
		cout << "Right!" << thisContext.get() << endl; //выводим "верно" и имя user 
		ofstream f = ofstream("statistics.txt", ofstream::app);
		f << thisContext.get() << endl; //дописываем имя в файл со статистикой
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
			AppClass thisContext;
			string str;
			string result;
			getline(fi, str); //читаем
			cout << "string: " << str << " -> "; //выводим строку
			if (thisContext.CheckString(str))
			{
				result=thisContext.get();
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

int getInt(int &a)
{
	cin >> a;
	if (!cin.good())
		return -1;
	return 1;
}