%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "lab2.h"
#include <stdbool.h>
#include <string.h>

extern FILE * yyin;
extern int yylineno;
/* prototypes */

nodeType *opr(int oper, int nops, ...);
nodeType *id(int i, char c[30]);
nodeType *con(int value);
void freeNode(nodeType *p);
int exec(nodeType *p);
int yylex(void);
void init (void);
void yyerror(const char *s);
int *sym;
%}

%union {
	int iValue; /* integer value */ 
	bool bValue;
	char* sIndex; /* symbol table index */
	nodeType *nPtr; /* node pointer */
};

%token <iValue> INTEGER 
%token <sIndex> ID
%token <bValue> T F 
%token INT NOT ASSIGN IF PRINT BOOLEAN CHECKTYPE FOR BEG END ARRAY CUBE FUNCTION RETURN GET SIZE
%token LOCATION STOP LOOKBACK LOOKFORWARD LOOKRIGHT LOOKLEFT GOBACK GOFORWARD GOTO GORIGHT GOLEFT
%left OR AND
%left '<' '>'
%left '+' '-'
%type <nPtr> stmt expr stmt_list function
%%

program:
	function {exec($1); freeNode($1); exit(0);}
	;
function:
	function stmt { $$ = opr(';', 2, $1, $2);/*ex($2); freeNode($2);*/ }
	| /* NULL */ { init(); $$ = 0;}
	;
stmt:
	';' { $$ = opr(';', 2, NULL, NULL); }
	| expr ';' { $$ = $1; }
	| PRINT expr ';' { $$ = opr(PRINT, 1, $2); }
	| ID ASSIGN expr ';' { $$ = opr('=', 2, id(1,$1), $3 ); }
	| ID expr ';' { printf("Missing operand in line: %d\n", yylineno);$$ = opr(';', 2, NULL, NULL);yyerrok;}
	| ID ASSIGN error ';' { printf("Illegal right part of variable assignment in line: %d\n", yylineno);$$ = opr(';', 2, NULL, NULL);yyerrok; }
	| ID ASSIGN expr error { printf("Expected ';' in the end: %d\n", yylineno);$$ = opr(';', 2, NULL, NULL);yyerrok; }
	| INT ID '=' expr ';' { $$ = opr('=', 2, id(1,$2), $4); }
	| INT error ';' {printf("Variable identificator is missed in declaration in line: %d\n",yylineno); $$=opr(';',2,NULL,NULL);yyerrok;}
	| INT error ASSIGN expr ';'  {freeNode($4);printf("Variable identificator is missed in declaration in line: ",yylineno); $$=opr(';',2,NULL,NULL);yyerrok;}
	| INT ID '=' error ';' { printf("Illegal right part of variable assignment in line: %d\n", yylineno);$$ = opr(';', 2, NULL, NULL);yyerrok; }
	| INT ID expr ';'  { printf("Missing operand in line: %d\n", yylineno);$$ = opr(';', 2, NULL, NULL);yyerrok;}
	| INT ID '=' expr error { printf("Expected ';' in the end: %d\n", yylineno);$$ = opr(';', 2, NULL, NULL);yyerrok; }
	| BOOLEAN ID '=' expr ';' {$$ = opr('=', 2, id(3,$2), $4);} 
	| BOOLEAN ID expr ';' { printf("Missing operand in line: %d\n", yylineno);$$ = opr(';', 2, NULL, NULL);yyerrok;}
	| BOOLEAN error ';' {printf("Variable identificator is missed in declaration in line: %d\n",yylineno); $$=opr(';',2,NULL,NULL);yyerrok;}
	| BOOLEAN error ASSIGN expr ';'  {freeNode($4);printf("Variable identificator is missed in declaration in line: ",yylineno); $$=opr(';',2,NULL,NULL);yyerrok;}
	| BOOLEAN ID '=' error ';' {printf("Illegal right part of variable assignment in line: %d\n",yylineno); $$=opr(';',2,NULL,NULL);yyerrok;}
	| BOOLEAN ID '=' expr error { printf("Expected ';' in the end: %d\n", yylineno);$$ = opr(';', 2, NULL, NULL);yyerrok; }
	| '(' stmt_list ')' { $$ = $2; }
	| IF expr stmt { $$ = opr(IF, 2, $2, $3); }
	| BEG stmt_list END {$$ = $2;}
	| BEG stmt_list error {freeNode($2);$$=opr(';',2,NULL,NULL); printf("Close operator is missed in line: %d\n",yylineno); yyerrok;}
	| FOR expr ':' expr stmt {$$=opr(FOR,3,$2,$4,$5);}
	;

stmt_list:
	stmt { $$ = $1; }
	| stmt_list stmt { $$ = opr(';', 2, $1, $2); }
	;

expr:
	 INTEGER { $$ = con($1); }
	| ID { $$ = id(1,$1); }
	| expr '+' expr { $$ = opr('+', 2, $1, $3); }
	| expr '-' expr { $$ = opr('-', 2, $1, $3); } 
	| '-' expr {$$=opr('-',1,$2);}
	| expr '<' expr { $$ = opr('<', 2, $1, $3); }
	| expr '>' expr { $$ = opr('>', 2, $1, $3); }
	| expr OR expr {$$=opr(OR,2,$1,$3);}
	| NOT expr {$$=opr(NOT,1,$2);}
	| expr AND expr {$$=opr(AND,2,$1,$3);}
	| '(' expr ')' { $$ = $2; }
	|'(' expr error {$$=opr(';',2,NULL,NULL);freeNode($2); printf("Close bracket is missed in line: %d\n",yylineno); yyerrok;}
	| T {$$ = con(1);}
	| F {$$ = con(0);}
	;

%%
#define SIZEOF_NODETYPE ((char *)&p->con - (char *)p)
nodeType *con(int value) {
	nodeType *p;
	size_t nodeSize;
	/* allocate node */
	nodeSize = SIZEOF_NODETYPE + sizeof(conNodeType);
	if ((p = (nodeType*) malloc(nodeSize)) == NULL)
	yyerror("out of memory");
	/* copy information */
	p->type = typeCon;
	p->con.value = value;
	return p;
}
nodeType *id(int i, char c[30]) {
	nodeType *p;
	size_t nodeSize;
	/* allocate node */
	nodeSize = SIZEOF_NODETYPE + sizeof(idNodeType);
	if ((p = (nodeType*) malloc(nodeSize)) == NULL)
	yyerror("out of memory");
	/* copy information */
	p->type = typeId;
	p->id.i = i;
	strcpy(p->id.c,c);
	return p;
}
nodeType *opr(int oper, int nops, ...) {
	va_list ap;
	nodeType *p;
	size_t nodeSize;
	int i;
	/* allocate node */
	nodeSize = SIZEOF_NODETYPE + sizeof(oprNodeType) + (nops - 1) * sizeof(nodeType*);
	if ((p = (nodeType*) malloc(nodeSize)) == NULL)
	yyerror("out of memory");
	/* copy information */
	p->type = typeOpr;
	p->opr.oper = oper;
	p->opr.nops = nops;
	va_start(ap, nops);
	for (i = 0; i < nops; i++)
		p->opr.op[i] = va_arg(ap, nodeType*);
	va_end(ap);
	return p;
}
void freeNode(nodeType *p) {
	int i;
	if (!p) return;
	if (p->type == typeOpr) {
	for (i = 0; i < p->opr.nops; i++)
		freeNode(p->opr.op[i]);
	}
	free (p);
}

void init (void)
	{
	sym=(int*)calloc(100,sizeof(int));
	}
	
void yyerror(const char *s) {
	fprintf(stderr, "%s\n", s);
}

int main(void) {
	yyin = fopen ("./test.txt", "r");
	yyparse();
	fclose (yyin);
	return 0;
}