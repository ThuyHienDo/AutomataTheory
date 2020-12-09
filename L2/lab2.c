#include <stdio.h>
#include "lab2.h"
#include "y.tab.h"
#include <stdbool.h>

char lbl = 0;
int error_flag = 0;
int k = 0;

int ex(nodeType* p) {
	if (!p) return 0;
	if (lbl == p->label)
		lbl = 0;
	if (!lbl)
		switch (p->type) {
		case typeCon:

			return p->con.value;
		case typeId: k = change(p->id.c); 
			return sym[k];
		case typeOpr:
			switch (p->opr.oper) {
			case IF: {
				if (ex(p->opr.op[0]))
					ex(p->opr.op[1]);
				else if (p->opr.nops > 2)
					ex(p->opr.op[2]);
				return 0;
			}
			case PRINT: if (p->opr.op[0]->type == typeId)
				printf("%s = ", p->opr.op[0]->id.c);
				printf("%d\n", ex(p->opr.op[0]));
				return 0;
			case ';': ex(p->opr.op[0]); return ex(p->opr.op[1]);
			case '=':
				k = change(p->opr.op[0]->id.c);
				if (p->opr.op[0]->id.i < 3) {
					return sym[k] = ex(p->opr.op[1]);
				}
				else if (p->opr.op[0]->id.i < 5)
					return sym[k] = (bool)(ex(p->opr.op[1]));
				else if (p->opr.op[0]->id.i == 5)
					return sym[k] = (ex(p->opr.op[1]));
				else if (p->opr.op[0]->id.i == 7)
					return sym[k] = (ex(p->opr.op[1]));
			case '+': return ex(p->opr.op[0]) + ex(p->opr.op[1]);
			case '-': {
				if (p->opr.nops == 2) return ex(p->opr.op[0]) - ex(p->opr.op[1]);
				if (p->opr.nops == 1) return -ex(p->opr.op[0]); }
			case '>': return ex(p->opr.op[0]) > ex(p->opr.op[1]);
			case '<': return ex(p->opr.op[0]) < ex(p->opr.op[1]);
			case OR: {
				int firstOp = ex(p->opr.op[0]);
				int secondOp = ex(p->opr.op[1]);
				bool first;
				bool second;

				if (firstOp == 0) {
					first = false;
				}
				else first = true;

				if (secondOp == 0) {
					second = false;
				}
				else second = true;

				return first || second;
			}
			case AND:
			{
				int firstOp = ex(p->opr.op[0]);
				int secondOp = ex(p->opr.op[1]);
				bool first;
				bool second;

				if (firstOp == 0) {
					first = false;
				}
				else first = true;

				if (secondOp == 0) {
					second = false;
				}
				else second = true;

				return first && second;
			}
			case NOT: {
				int firstOp = ex(p->opr.op[0]);
				bool first;
				if (firstOp == 0) {
					first = false;
				}
				else first = true;
				return !first;
			}
			case FOR: {
				int beg = ex(p->opr.op[0]);
				int end = ex(p->opr.op[1]);
				for (int i = beg; i < end; i++) {
					ex(p->opr.op[2]);
				}
			}

					return 0;
			}
		}
	else
	{
		switch (p->type) {
		case typeCon: return 0;
		case typeId: return 0;
		case typeOpr:
			switch (p->opr.oper) {
			case IF: ex(p->opr.op[1]);
				if (lbl && p->opr.nops > 2)
					ex(p->opr.op[2]);
				return 0;
			case ';': ex(p->opr.op[0]); return ex(p->opr.op[1]);
			default: return 0;
			}
		}
	}
	return 0;
}

int exec(nodeType* p)
{
	do
	{
		ex(p);
	} while (lbl);
}

int change(char* s)
{
	int res = 0;
	for (int i = 0; i < strlen(s); i++)
	{
		if ((s[i] == '=') || (s[i] == ':') || ( s[i] == ' ' )) break;
		else {
			res = res + (s[i] - '0');
		}
	}
	return res % 100;
}




