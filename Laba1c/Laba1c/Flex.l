%option noyywrap
%option c++
%option outfile="Flex.cpp"

%x ERROR USER SERVERandZONE
%{
	#include <string>
	std::string user;
%}

%%
<INITIAL>
{
	ftp\:\/\/  { BEGIN(USER); }
	.? { BEGIN(ERROR); }
}
<USER>
{
	[a-zA-Z]{1,20} {user = std::string(yytext); BEGIN(SERVERandZONE);}
	.? { BEGIN(ERROR); }
}
<SERVERandZONE>
{
	@([a-zA-Z]{1,20}\.)+[a-zA-Z]{1,5}\n  {yyout << user; return 1; }
	.? { BEGIN(ERROR); }
}
<ERROR>
{
	.? { BEGIN(INITIAL); return 0; }
}
%%
