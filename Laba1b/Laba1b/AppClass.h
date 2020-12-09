
#include "Automata_sm.h"
#include <string>

class AppClass
{
private:

	AutomataContext _fsm;
	bool isAcceptable;
	std::string buf;  //буфер для результата
	std::string type; //буфер для заголовка
	int count;
	char temp;
	int dot;

public:

	AppClass() : _fsm(*this), isAcceptable(true), buf(""), count(0), dot(0) { }

	~AppClass() {};

	bool CheckString(std::string);

	//методы для инкремента, сброса и сравнения счётчика
	void inc() { ++count; }
	void incDot() { ++dot; }
	void clear() { count = 0; }
	void clearDot() { dot = 0; }
	void less(int number);
	//метод для вывода строки
	void print(std::string message);
	//методы для сохранения, получения и очистки строки (нужно, чтобы собирать статистику)
	void add() { buf += temp; }
	std::string get() const { return buf; }
	//методы для сохранения заголовка
	void pushHeadline() { type += temp; }
	void check();
	void checkZone();
	void Refresh() { count = 0; isAcceptable = true;}
	void checkDot() { if (!dot) return; Unacceptable();}
	void checkServer() { if (count) return; Unacceptable();}
	//методы оценки строки
	inline void Acceptable() { isAcceptable = true; };
	inline void Unacceptable() { isAcceptable = false; };
};


