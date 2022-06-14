/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INTEGER = 258,
    FLOAT = 259,
    BOOLEAN = 260,
    STRING = 261,
    IDENTIFIER = 262,
    CLASS = 263,
    FUN = 264,
    VAR = 265,
    VAL = 266,
    TYPE = 267,
    PRINT = 268,
    PRINTLN = 269,
    READ = 270,
    RETURN = 271,
    IF = 272,
    ELSE = 273,
    FOR = 274,
    WHILE = 275,
    IN = 276,
    GE = 277,
    LE = 278,
    EQ = 279,
    NE = 280,
    DD = 281,
    UMINUS = 282
  };
#endif
/* Tokens.  */
#define INTEGER 258
#define FLOAT 259
#define BOOLEAN 260
#define STRING 261
#define IDENTIFIER 262
#define CLASS 263
#define FUN 264
#define VAR 265
#define VAL 266
#define TYPE 267
#define PRINT 268
#define PRINTLN 269
#define READ 270
#define RETURN 271
#define IF 272
#define ELSE 273
#define FOR 274
#define WHILE 275
#define IN 276
#define GE 277
#define LE 278
#define EQ 279
#define NE 280
#define DD 281
#define UMINUS 282

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 1 "d.y"

int intValue;
float floatValue;
int boolValue;
char* stringValue;
int type;
char* identifierName;
struct PN* node;
struct parserArguments* arguments;

#line 122 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
