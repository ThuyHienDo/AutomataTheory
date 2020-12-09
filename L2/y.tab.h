
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEGER = 258,
     ID = 259,
     T = 260,
     F = 261,
     INT = 262,
     NOT = 263,
     ASSIGN = 264,
     IF = 265,
     PRINT = 266,
     BOOLEAN = 267,
     CHECKTYPE = 268,
     FOR = 269,
     BEG = 270,
     END = 271,
     ARRAY = 272,
     CUBE = 273,
     FUNCTION = 274,
     RETURN = 275,
     GET = 276,
     SIZE = 277,
     LOCATION = 278,
     STOP = 279,
     LOOKBACK = 280,
     LOOKFORWARD = 281,
     LOOKRIGHT = 282,
     LOOKLEFT = 283,
     GOBACK = 284,
     GOFORWARD = 285,
     GOTO = 286,
     GORIGHT = 287,
     GOLEFT = 288,
     AND = 289,
     OR = 290
   };
#endif
/* Tokens.  */
#define INTEGER 258
#define ID 259
#define T 260
#define F 261
#define INT 262
#define NOT 263
#define ASSIGN 264
#define IF 265
#define PRINT 266
#define BOOLEAN 267
#define CHECKTYPE 268
#define FOR 269
#define BEG 270
#define END 271
#define ARRAY 272
#define CUBE 273
#define FUNCTION 274
#define RETURN 275
#define GET 276
#define SIZE 277
#define LOCATION 278
#define STOP 279
#define LOOKBACK 280
#define LOOKFORWARD 281
#define LOOKRIGHT 282
#define LOOKLEFT 283
#define GOBACK 284
#define GOFORWARD 285
#define GOTO 286
#define GORIGHT 287
#define GOLEFT 288
#define AND 289
#define OR 290




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 24 "lab2.y"

	int iValue; /* integer value */ 
	bool bValue;
	char* sIndex; /* symbol table index */
	nodeType *nPtr; /* node pointer */



/* Line 1676 of yacc.c  */
#line 131 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


