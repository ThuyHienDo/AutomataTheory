
%{
#include <stdlib.h>
#include <string.h>
#include "lab2.h"
#include "y.tab.h"


void yyerror(const char*);
%}
%option yylineno

GOFORWARD \^_\^
GOBACK v_v
GOLEFT <_<
GORIGHT >_>
LOOKFORWARD \^_0
LOOKBACK v_0
LOOKLEFT <_0
LOOKRIGHT >_0
STOP >_<
LOCATION \*_\*

%%
[0-9]+ {
yylval.iValue = atoi(yytext);
return INTEGER;
}
[();=+-><]  return *yytext;

"TRUE" return T;
"FALSE" return F;
"INT" return INT;
"BOOLEAN" return BOOLEAN;
"cub" return CUBE;
"arr" return ARRAY;
"size" return SIZE;
"checktyp" return CHECKTYPE;
"for" return FOR;
"begin" return BEG;
"end" return END;
"func" return FUNCTION;
"return" return RETURN;
"=>" return GET;
"~" return NOT;
"&&" return AND;
"||" return OR;
"IF" return IF;
"print" return PRINT;
"goto" return GOTO;
":=" return ASSIGN;

{GOFORWARD} {return (GOFORWARD);}
{GOBACK} {return (GOBACK);}
{GOLEFT} {return (GOLEFT);}
{GORIGHT} {return (GORIGHT);}
{LOOKFORWARD} {return (LOOKFORWARD);}
{LOOKBACK} {return (LOOKBACK);}
{LOOKLEFT} {return (LOOKLEFT);}
{LOOKRIGHT} {return (LOOKRIGHT);}
{STOP} {return (STOP);}
{LOCATION} {return (LOCATION);}

[a-zA-Z][a-zA-Z0-9]* {
	yylval.sIndex = yytext;
	return ID;
}
[ \t\n]+ ; /* ignore whitespace */
. {yyerror("Unknown character");}
%%
int yywrap(void) {
return 1;
}