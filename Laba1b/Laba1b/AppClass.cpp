#include "AppClass.h"
#include <cctype>
#include <iostream>
#include <regex>

using namespace std;
int isletter(char a)
{
	regex re("[a-zA-Z]"); 
	string c(1, a);
	if (!regex_match(c, re)) return 0;
	return 1;
}
bool AppClass::CheckString(string str)
{
	_fsm.enterStartState();
	isAcceptable = true;
	buf = "";
	for (const auto& c : str)
	{
		temp = c;
		if (!isAcceptable)
		{
			bool ret = isAcceptable;
			Refresh();
			return false;
		}
		if (isletter(c))
			_fsm.Letter();
		else if (c == ' ' || c == '\t')
			_fsm.Devider();
		else if (c == ':')
			_fsm.Colon();
		else if (c == '/')
			_fsm.Slash();
		else if (c == '@')
			_fsm.At();
		else if (c == '.')
			_fsm.Dot();

		else
			_fsm.Unknown();
	}
	_fsm.EOS();
	bool ret = isAcceptable;
	Refresh();
	return ret;
}

void AppClass::less(int number)
{
	if (count <= number)
		return;
	Unacceptable();
}

void AppClass::print(std::string message)
{
	cout << message << endl;
}

void AppClass::check()
{
	if (type != "ftp" ) Unacceptable();
}

void AppClass::checkZone()
{
	if (count>5) Unacceptable();
}