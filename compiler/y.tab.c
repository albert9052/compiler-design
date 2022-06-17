/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1





# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 185 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Second part of user prologue.  */
#line 37 "d.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Initialize the parser
void initParser();

// yyerror for a simple string
void yyerror(char *);

// yyerror function for the situation of identifier being duplicated
void yyerrorForIdentifierDuplicated(char *identifierName);

// yyerror function for the situation of identifier not found
void yyerrorForIdentifierNotFound(char *identifierName);

// yyerror function for the situation of identifier not being a function
void yyerrorForIdentifierNotFunction(char* identifierName);

// yyerror function for the situation of identifier not begin a array
void yyerrorForIdentifierNotArray(char* identifierName);

// yyerror exit
void yyerrorExit();

FILE* file;

int yylex(void);
int sym[26];
char* className;

// This is a structure for passing the arguments information, in order to declare them after creating a new symbol table
typedef struct parserArguments {
	char** argumentNames;
	int* argumentTypes;
	int argumentNum;
} Arguments;

// These are constants used when passing type
#define NODE_INT 0
#define NODE_FLOAT 1
#define NODE_BOOL 2
#define NODE_STRING 3
#define NODE_ARRAY 4
#define NODE_FUNCTION_WITH_NO_RETURN_VALUE 5
#define NODE_FUNCTION_WITH_RETURN_VALUE 6
#define NODE_CLASS 7

// These are constants used when passing operator's type
#define OPERATOR_ADD 0
#define OPERATOR_SUB 1
#define OPERATOR_MUL 2
#define OPERATOR_DIV 3
#define OPERATOR_REM 4
#define OPERATOR_AND 5
#define OPERATOR_OR 6
#define OPERATOR_XOR 7
#define OPERATOR_LT 8
#define OPERATOR_GE 9
#define OPERATOR_LE 10
#define OPERATOR_EQ 11
#define OPERATOR_NE 12
#define OPERATOR_GT 13

// This is the structure of basic unit in symbol table
typedef struct TN {
	char* string;
	int type;
	int subType;
	int* argumentTypes;
	int argumentNum;
	int constant;
	int constantValue;
	int global;
	int index;
	struct TN* next;
} TableNode;

typedef struct PN {
	int value;
	char* stringValue;
	int type;
} ParameterNode;

typedef struct UnfinishedCC {
	int index;
	struct UnfinishedCC* next;
	struct UnfinishedCC* previous;
} UnfinishedConditionCounter;

UnfinishedConditionCounter* unfinishedConditionCounter;

// For counting the number of lines so far
int lineCount;

// Insert a new identifier and its information into the current symbol table
TableNode* insert(const char* key, int type, int subType, int* argumentTypes, int argumentNum, int constant, int constantValue);

// Look up a key in the current symbol table, and return its TableNode
TableNode* lookUpInThisScope(const char* key);

// Look up a key in every symbol table, and return its TableNode
TableNode* lookUpInEveryScope(const char* key);

// Create a new symbol table, and connect it to the previous symbol table
void createNewTable(int globalTable);

// Pop the current symbol table, and disconnect it from the previous symbol table
void popTable();

// Print out the current symbol table (For testing)
void printOneTable();

// Print out every symbol table (For testing)
void printAllTables();

// Initialize the scanner
void initScanner();

// Print out the start of a class
void printTheStartOfClassDeclaration(char* name);

// Print out the end of a class
void printTheEndOfClassDeclaration();

// Print out the start of a function
void printTheStartOfFunctionDeclaration(char* name, int type, struct parserArguments* arguments);

// Print out the end of a function
void printTheEndOfFunctionDeclaration();

// Print a "iload 0" or "iconst_0" to initialize a variable
void printZeroToInitializeIt(int type);

// Print out local variable declaration
void printLocalVariableDeclaration(int index);

// Print out global vairable declaration with a value
void printGlobalVariableDeclarationWithoutValue(char* name, int type);

// Print out global variable declaration
void printGlobalVariableDeclaration(char* name, int type, int value);

// Print out load variable
void printAssignVariable(TableNode* node);

// Print out ireturn to return
void printReturnVariable();

// Print out return to return
void printReturn();

// Print out ineg
void printUminus();

// Print out the value, to push the value into the stack
void printValue(int type, int value);

// Print out iload to load local variable
void printLoadingLocalVariable(int index);

// Print out iload to load global variable
void printLoadingGlobalVariable(char* name, int type);

// Print out those operators
void printOperator(int operator);

// Print out those condition operators
void printConditionWithOperator(int operator);

// Print out condition codes
void printCondition();

// Print out L<number>-FALSE flag
void printConditionElseFlag();

// Print out L<number>-REST flag
void printConditionRestFlag();

// Print out ldc to load the string
void printLoadingString(char* stringToPrint);

// Print the preparation of printing
void printPreparationForPrint();

// Invoke the function to print
void printPrinting(int type, int nextLine);

// Print the begin flag of a while loop
void printWhileLoopBeginFlag();

// Print the goto begin flag code at the end of the true flag section
void printGotoWhileLoopBeginFlag();

// Print the codes required between starting expression and ending expression
void printBetweenForLoopStartingNumAndEndingNum(int index);

// Print the codes required after starting expression and ending expression
void printAfterForLoopStartingNumAndEndingNum(int index);

// Print the end of the true flag section of a for loop
void printTheEndOfTrueFlagSectionOfForLoop();

// Print the invocation of a function
void printInvocationOfFunction(char* name, int type, int* argumentTypes, int argumentNum);

// Do some preparation before entering if
void printPreparationForIf();

// print nop
void printNOP();

int nextConditionCounter;

void initParser();

#line 418 "y.tab.c"


#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   409

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  104
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  199

#define YYUNDEFTOK  2
#define YYMAXUTOK   282


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,     2,     2,    46,    28,     2,
      22,    23,    38,    36,    45,    37,     2,    39,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    24,     2,
      30,    42,    35,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    43,     2,    44,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    25,    27,    26,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    31,    32,    33,
      34,    40,    41
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   255,   255,   255,   274,   281,   282,   283,   284,   287,
     305,   324,   343,   360,   371,   390,   390,   415,   415,   431,
     431,   456,   456,   474,   477,   502,   513,   514,   517,   518,
     519,   520,   521,   522,   523,   526,   540,   556,   556,   561,
     561,   566,   573,   576,   581,   585,   600,   603,   608,   612,
     615,   620,   624,   702,   705,   710,   714,   717,   722,   723,
     724,   725,   726,   727,   728,   729,   730,   731,   732,   733,
     734,   735,   738,   746,   765,   774,   779,   782,   799,   843,
     868,   886,   896,   916,   916,   921,   929,   929,   940,   940,
     953,   965,   967,   953,   977,   977,   984,   984,   993,   995,
    1000,  1003,  1008,  1013,  1018
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "FLOAT", "BOOLEAN", "STRING",
  "IDENTIFIER", "CLASS", "FUN", "VAR", "VAL", "TYPE", "PRINT", "PRINTLN",
  "READ", "RETURN", "IF", "ELSE", "FOR", "WHILE", "IN", "'('", "')'",
  "':'", "'{'", "'}'", "'|'", "'&'", "'!'", "'<'", "GE", "LE", "EQ", "NE",
  "'>'", "'+'", "'-'", "'*'", "'/'", "DD", "UMINUS", "'='", "'['", "']'",
  "','", "'%'", "$accept", "program", "$@1", "classIdentifier",
  "classBlock", "globalVariableDeclaration", "variableDeclaration",
  "constantDeclaration", "functionDeclaration", "$@2", "$@3", "$@4", "$@5",
  "functionIdentifier", "formalArguments", "block", "statement", "simple",
  "$@6", "$@7", "expression", "rightExpression", "constantExpression",
  "rightConstantExpression", "operator", "expressionTerminal",
  "constantExpressionTerminal", "functionInvocation",
  "functionInvocationArguments", "arrayReference", "conditional", "$@8",
  "ifRest", "$@9", "loop", "$@10", "@11", "$@12", "$@13", "simpleOrBlock",
  "$@14", "$@15", "procedureInvocation", "condition", "type", "value", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,    40,    41,    58,   123,   125,   124,    38,    33,
      60,   277,   278,   279,   280,    62,    43,    45,    42,    47,
     281,   282,    61,    91,    93,    44,    37
};
# endif

#define YYPACT_NINF (-152)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-97)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       2,    13,    12,  -152,  -152,  -152,    -3,    55,    31,    36,
      48,    57,    55,    55,    55,  -152,    51,    64,    64,  -152,
    -152,  -152,  -152,     4,    63,    52,    54,    74,    75,   -10,
    -152,    47,    47,    91,   100,    86,    89,   121,  -152,  -152,
    -152,  -152,    47,    47,   248,  -152,  -152,   248,  -152,  -152,
     384,   118,   104,   107,   128,    87,  -152,  -152,  -152,  -152,
    -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,
      99,   110,    65,   125,  -152,  -152,   133,   112,  -152,   120,
    -152,   384,  -152,  -152,   282,  -152,  -152,  -152,  -152,  -152,
    -152,  -152,   384,   135,  -152,    47,    47,  -152,  -152,   384,
      56,   112,   112,   124,   112,   112,  -152,   -13,   112,   112,
     248,  -152,  -152,  -152,  -152,   131,   143,   146,   299,  -152,
    -152,   127,   316,  -152,   148,    87,   333,  -152,   248,    -4,
     248,   208,   157,   147,   248,   248,   112,   168,    87,   117,
     112,  -152,  -152,   112,  -152,   384,  -152,  -152,  -152,  -152,
     112,   150,   129,   112,   228,  -152,   112,   112,  -152,  -152,
     248,   165,   149,   167,   350,   248,   112,   170,   248,  -152,
     188,    87,   183,   112,   183,  -152,   248,   166,  -152,   175,
     130,   184,   248,  -152,  -152,   194,    49,  -152,   384,   173,
     183,   367,   112,  -152,  -152,   248,   205,   183,  -152
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     4,     2,     1,     0,     8,     0,     0,
       0,     0,     8,     8,     8,    23,     0,   101,   101,     3,
       5,     6,     7,     0,     0,     9,     0,     0,    21,     0,
     100,     0,     0,     0,     0,     0,    19,     0,   102,   103,
     104,    77,     0,     0,    10,    54,    76,    14,    25,    17,
       0,     0,     0,     0,     0,    51,    64,    63,    65,    66,
      67,    68,    69,    70,    71,    58,    59,    60,    61,    62,
       0,     0,     0,     0,    37,    39,     0,    43,    83,     0,
      88,     0,    28,    29,     0,    27,    30,    98,    31,    32,
      33,    15,     0,     0,    53,     0,     0,    52,    57,     0,
       0,     0,     0,   101,     0,     0,    41,    73,     0,     0,
      42,    47,    74,    75,    72,     0,     0,     0,     0,    22,
      26,     0,     0,    24,     0,    55,     0,    79,    81,     0,
      35,     0,     0,    11,    38,    40,     0,     0,    44,     0,
       0,    84,    90,     0,    34,     0,    20,    56,    18,    78,
       0,     0,   100,     0,     0,    46,     0,     0,    45,    50,
      99,     0,     0,     0,     0,    80,     0,     0,    12,    82,
       0,    48,    94,     0,    94,    16,    36,     0,    49,    85,
       0,     0,    91,    89,    13,     0,     0,    95,     0,     0,
      94,     0,     0,    87,    97,    92,     0,    94,    93
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -152,  -152,  -152,  -152,   113,  -152,  -152,    44,  -152,  -152,
    -152,  -152,  -152,  -152,  -152,   -78,   -82,    50,  -152,  -152,
     -76,  -152,     5,  -152,   -39,    90,   161,   -50,  -152,  -152,
    -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -151,
    -152,  -152,  -152,   105,   -14,   -25
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,     4,    11,    12,    82,    83,    14,   121,
      71,    52,    35,    16,    29,    84,    85,    86,   104,   105,
     160,   158,    44,    97,   139,   111,    45,   112,   129,   113,
      88,   115,   141,   185,    89,   117,   162,   189,   196,   179,
     180,   181,    90,   161,    25,   114
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      87,   110,   120,   118,    26,    70,    46,    46,    70,   100,
       1,    27,     5,    36,   122,    70,    70,    46,    46,   149,
       3,   126,     7,   183,   128,   130,   131,    28,   134,   135,
     136,    87,   137,   138,    87,    37,   120,    47,    15,   193,
     120,   150,    87,    17,   120,    46,   198,    54,    55,    87,
      38,    13,    39,    40,    41,    18,    13,    13,    13,    38,
     154,    39,    40,   107,     8,     9,    10,   164,    87,    42,
      46,    46,    87,    23,   165,    30,    87,   168,   108,   127,
     170,   171,   120,    19,    43,    70,    70,   100,    24,   133,
     176,   101,   102,   109,    31,    87,    32,   182,    33,    34,
     124,   125,    38,    48,    39,    40,    41,   101,   102,   120,
     191,    50,    49,    51,    87,    38,   195,    39,    40,   107,
      38,    95,    39,    40,   107,    20,    21,    22,    53,    92,
      91,    93,   103,    69,   108,    99,    96,   186,    87,   156,
     106,    87,   116,    74,    75,    76,    77,   123,   132,   109,
     142,    94,   145,   140,   157,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,   143,   152,
     173,   147,   167,   177,    69,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,   172,   153,
     174,   155,   166,   -86,    69,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,   -96,   188,
     184,   178,   190,   192,    69,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,   197,   159,
     187,    98,     0,     0,    69,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,   163,     0,
       0,     0,   151,     0,    69,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,     0,     0,
       0,     0,   169,     0,    69,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,     0,    72,
       0,     0,    73,    10,    69,    74,    75,    76,    77,    78,
       0,    79,    80,     0,     0,     0,    72,    81,   119,    73,
      10,     0,    74,    75,    76,    77,    78,     0,    79,    80,
       0,     0,     0,    72,    81,   144,    73,    10,     0,    74,
      75,    76,    77,    78,     0,    79,    80,     0,     0,     0,
      72,    81,   146,    73,    10,     0,    74,    75,    76,    77,
      78,     0,    79,    80,     0,     0,     0,    72,    81,   148,
      73,    10,     0,    74,    75,    76,    77,    78,     0,    79,
      80,     0,     0,     0,    72,    81,   175,    73,    10,     0,
      74,    75,    76,    77,    78,     0,    79,    80,     0,     0,
       0,    72,    81,   194,    73,    10,     0,    74,    75,    76,
      77,    78,     0,    79,    80,     0,     0,     0,     0,    81
};

static const yytype_int16 yycheck[] =
{
      50,    77,    84,    81,    18,    44,    31,    32,    47,    22,
       8,     7,     0,    23,    92,    54,    55,    42,    43,    23,
       7,    99,    25,   174,   100,   101,   102,    23,   104,   105,
      43,    81,   108,   109,    84,    45,   118,    32,     7,   190,
     122,    45,    92,     7,   126,    70,   197,    42,    43,    99,
       3,     7,     5,     6,     7,     7,    12,    13,    14,     3,
     136,     5,     6,     7,     9,    10,    11,   145,   118,    22,
      95,    96,   122,    22,   150,    12,   126,   153,    22,    23,
     156,   157,   164,    26,    37,   124,   125,    22,    24,   103,
     166,    42,    43,    37,    42,   145,    42,   173,    24,    24,
      95,    96,     3,    12,     5,     6,     7,    42,    43,   191,
     188,    25,    12,    24,   164,     3,   192,     5,     6,     7,
       3,    22,     5,     6,     7,    12,    13,    14,     7,    25,
      12,    24,     7,    46,    22,    25,    37,     7,   188,    22,
       7,   191,    22,    13,    14,    15,    16,    12,    24,    37,
       7,    23,    25,    22,    37,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    22,    12,
      21,    23,    43,     3,    46,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    23,    42,
      23,    23,    42,    18,    46,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    25,    25,
      44,    23,    18,    40,    46,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    23,   139,
     180,    70,    -1,    -1,    46,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,   143,    -1,
      -1,    -1,    44,    -1,    46,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    -1,    -1,
      -1,    -1,    44,    -1,    46,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    -1,     7,
      -1,    -1,    10,    11,    46,    13,    14,    15,    16,    17,
      -1,    19,    20,    -1,    -1,    -1,     7,    25,    26,    10,
      11,    -1,    13,    14,    15,    16,    17,    -1,    19,    20,
      -1,    -1,    -1,     7,    25,    26,    10,    11,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    -1,    -1,    -1,
       7,    25,    26,    10,    11,    -1,    13,    14,    15,    16,
      17,    -1,    19,    20,    -1,    -1,    -1,     7,    25,    26,
      10,    11,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    -1,    -1,    -1,     7,    25,    26,    10,    11,    -1,
      13,    14,    15,    16,    17,    -1,    19,    20,    -1,    -1,
      -1,     7,    25,    26,    10,    11,    -1,    13,    14,    15,
      16,    17,    -1,    19,    20,    -1,    -1,    -1,    -1,    25
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,    48,     7,    50,     0,    49,    25,     9,    10,
      11,    51,    52,    54,    55,     7,    60,     7,     7,    26,
      51,    51,    51,    22,    24,    91,    91,     7,    23,    61,
      12,    42,    42,    24,    24,    59,    23,    45,     3,     5,
       6,     7,    22,    37,    69,    73,    92,    69,    12,    12,
      25,    24,    58,     7,    69,    69,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    46,
      71,    57,     7,    10,    13,    14,    15,    16,    17,    19,
      20,    25,    53,    54,    62,    63,    64,    74,    77,    81,
      89,    12,    25,    24,    23,    22,    37,    70,    73,    25,
      22,    42,    43,     7,    65,    66,     7,     7,    22,    37,
      67,    72,    74,    76,    92,    78,    22,    82,    62,    26,
      63,    56,    62,    12,    69,    69,    62,    23,    67,    75,
      67,    67,    24,    91,    67,    67,    43,    67,    67,    71,
      22,    79,     7,    22,    26,    25,    26,    23,    26,    23,
      45,    44,    12,    42,    67,    23,    22,    37,    68,    72,
      67,    90,    83,    90,    62,    67,    42,    43,    67,    44,
      67,    67,    23,    21,    23,    26,    67,     3,    23,    86,
      87,    88,    67,    86,    44,    80,     7,    64,    25,    84,
      18,    62,    40,    86,    26,    67,    85,    23,    86
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    49,    48,    50,    51,    51,    51,    51,    52,
      52,    53,    53,    53,    54,    56,    55,    57,    55,    58,
      55,    59,    55,    60,    61,    61,    62,    62,    63,    63,
      63,    63,    63,    63,    63,    64,    64,    65,    64,    66,
      64,    64,    64,    64,    67,    67,    67,    67,    68,    68,
      68,    69,    69,    69,    69,    70,    70,    70,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    72,    72,    72,    72,    73,    73,    74,    74,
      75,    75,    76,    78,    77,    79,    80,    79,    82,    81,
      83,    84,    85,    81,    87,    86,    88,    86,    89,    90,
      91,    91,    92,    92,    92
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     6,     1,     2,     2,     2,     0,     3,
       5,     3,     5,     7,     5,     0,    11,     0,    10,     0,
       9,     0,     8,     1,     5,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     6,     0,     3,     0,
       3,     2,     2,     1,     2,     3,     3,     1,     2,     3,
       1,     2,     3,     3,     1,     2,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     4,     3,
       3,     1,     4,     0,     3,     4,     0,     7,     0,     6,
       0,     0,     0,    12,     0,     2,     0,     4,     1,     1,
       2,     0,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 255 "d.y"
                                               {
			 	// Create a new symbol table before entering the classBlock
			 	createNewTable(1);
				printTheStartOfClassDeclaration((yyvsp[0].identifierName));
				className = (yyvsp[0].identifierName);
			 }
#line 1766 "y.tab.c"
    break;

  case 3:
#line 260 "d.y"
                                              {
				// Pop a symbol table before leaving the classBlock
				TableNode* tableNode = lookUpInThisScope("main");
				if (tableNode == NULL) {
					yyerror("Missing \"main\" function");
				}
				else if (tableNode -> type != NODE_FUNCTION_WITH_NO_RETURN_VALUE && tableNode -> type != NODE_FUNCTION_WITH_RETURN_VALUE) {
					yyerror("\"main\" is not a function");
				}
				popTable();
				printTheEndOfClassDeclaration();
			 }
#line 1783 "y.tab.c"
    break;

  case 4:
#line 274 "d.y"
                                                                    { 
							 	// Insert the class identifier into the current symbol table
								insert((yyvsp[0].identifierName), NODE_CLASS, -1, NULL, 0, 0, 0); 
								(yyval.identifierName) = (yyvsp[0].identifierName);
							 }
#line 1793 "y.tab.c"
    break;

  case 9:
#line 287 "d.y"
                                                                                                                     {
													// Check if there's already an identical identifier name in the current symbol table
													if (lookUpInThisScope((yyvsp[-1].identifierName)) != NULL) {
														yyerrorForIdentifierDuplicated((yyvsp[-1].identifierName));
													}
													else {
														// Check if there's a type definition. If not, the default type is integer. 
														TableNode* node;
														if ((yyvsp[0].intValue) != -1) {
															node = insert((yyvsp[-1].identifierName), (yyvsp[0].intValue), -1, NULL, 0, 0, 0);
															printGlobalVariableDeclarationWithoutValue(node -> string, (yyvsp[0].intValue));
														}
														else {
															node = insert((yyvsp[-1].identifierName), NODE_INT, -1, NULL, 0, 0, 0);
															printGlobalVariableDeclarationWithoutValue(node -> string, NODE_INT);
														}
													}
												 }
#line 1816 "y.tab.c"
    break;

  case 10:
#line 305 "d.y"
                                                                                                                                              {
													// Check if there's a type definition. If not, its type is recognized from constantExpression
													if ((yyvsp[-2].intValue) == -1) {
														(yyvsp[-2].intValue) = (yyvsp[0].node) -> type;
													}
													// Check if the type is matched, then check if there's already an identical identifier name in the current symbol table
													if ((yyvsp[-2].intValue) != (yyvsp[0].node) -> type) {
														yyerror("Type not matched.");
													}
													else if (lookUpInThisScope((yyvsp[-3].identifierName)) != NULL) {
														yyerrorForIdentifierDuplicated((yyvsp[-3].identifierName));
													}
													else {
														TableNode* node = insert((yyvsp[-3].identifierName), (yyvsp[-2].intValue), -1, NULL, 0, 0, 0);
														printGlobalVariableDeclaration(node -> string, (yyvsp[-2].intValue), (yyvsp[0].node) -> value);
													}
													free((yyvsp[0].node));
												 }
#line 1839 "y.tab.c"
    break;

  case 11:
#line 324 "d.y"
                                                                                             {
									 	// Check if there's already an identical identifier name in the current symbol table
									 	if (lookUpInThisScope((yyvsp[-1].identifierName)) != NULL) {
											yyerrorForIdentifierDuplicated((yyvsp[-1].identifierName));
										}
										else {
											// Check if there's a type definition. If not, the default type is integer. 
											TableNode* node;
											if ((yyvsp[0].intValue) != -1) {
												node = insert((yyvsp[-1].identifierName), (yyvsp[0].intValue), -1, NULL, 0, 0, 0);
												printZeroToInitializeIt((yyvsp[0].intValue));
											}
											else {
												node = insert((yyvsp[-1].identifierName), NODE_INT, -1, NULL, 0, 0, 0);
												printZeroToInitializeIt(NODE_INT);
											}
											printLocalVariableDeclaration(node -> index);
										}
									 }
#line 1863 "y.tab.c"
    break;

  case 12:
#line 343 "d.y"
                                                                                                              {
									 	// Check if there's a type definition. If not, its type is recognized from constantExpression
									 	if ((yyvsp[-2].intValue) == -1) {
											(yyvsp[-2].intValue) = (yyvsp[0].intValue);
										}
										// Check if the type is matched, then check if there's already an identical identifier name in the current symbol table
										if ((yyvsp[-2].intValue) != (yyvsp[0].intValue)) {
											yyerror("Type not matched.");
										}
										else if (lookUpInThisScope((yyvsp[-3].identifierName)) != NULL) {
											yyerrorForIdentifierDuplicated((yyvsp[-3].identifierName));
										}
										else {
											TableNode* node = insert((yyvsp[-3].identifierName), (yyvsp[-2].intValue), -1, NULL, 0, 0, 0);
											printLocalVariableDeclaration(node -> index);
										}
									 }
#line 1885 "y.tab.c"
    break;

  case 13:
#line 360 "d.y"
                                                                                                                   {
									 	// Check if there's already an identical identifier name in the current symbol table
										if (lookUpInThisScope((yyvsp[-5].identifierName)) != NULL) {
											yyerrorForIdentifierDuplicated((yyvsp[-5].identifierName));
										}
										else {
											insert((yyvsp[-5].identifierName), NODE_ARRAY, (yyvsp[-3].intValue), NULL, 0, 0, 0);
										}
									 }
#line 1899 "y.tab.c"
    break;

  case 14:
#line 371 "d.y"
                                                                                                                    {
									 	// Check if there's a type definition. If not, its type is recognized from constantExpression
									 	if ((yyvsp[-2].intValue) == -1) {
											(yyvsp[-2].intValue) = (yyvsp[0].node) -> type;
										}
										// Check if the type is matched, then check if there's already an identical identifier name in the current symbol table
										if ((yyvsp[-2].intValue) != (yyvsp[0].node) -> type) {
											yyerror("Type not matched.");
										}
										else if (lookUpInThisScope((yyvsp[-3].identifierName)) != NULL) {
											yyerrorForIdentifierDuplicated((yyvsp[-3].identifierName));
										}
										else {
											insert((yyvsp[-3].identifierName), (yyvsp[-2].intValue), -1, NULL, 0, 1, (yyvsp[0].node) -> value);
										}
										free((yyvsp[0].node));
									 }
#line 1921 "y.tab.c"
    break;

  case 15:
#line 390 "d.y"
                                                                                                                                 {
									 	// Check if there's already an identical identifier name in the current symbol table
									 	if (lookUpInThisScope((yyvsp[-5].identifierName)) != NULL) {
											yyerrorForIdentifierDuplicated((yyvsp[-5].identifierName));
										}
										else {
											insert((yyvsp[-5].identifierName), NODE_FUNCTION_WITH_RETURN_VALUE, (yyvsp[0].intValue), (yyvsp[-3].arguments) -> argumentTypes, (yyvsp[-3].arguments) -> argumentNum, 0, 0);
										}
										// Create a new symbol table for formalArguments and the following returnBlock
										createNewTable(0);
										// Get the arguments' definition from formalArguments and insert them into the current symbol table
										for (int i = 0; i < (yyvsp[-3].arguments) -> argumentNum; i++) {
											if (lookUpInThisScope((yyvsp[-3].arguments) -> argumentNames[i]) != NULL) {
												yyerrorForIdentifierDuplicated((yyvsp[-3].arguments) -> argumentNames[i]);
											}
											else {
												insert((yyvsp[-3].arguments) -> argumentNames[i], (yyvsp[-3].arguments) -> argumentTypes[i], -1, NULL, 0, 0, 0);
											}
										}
										printTheStartOfFunctionDeclaration((yyvsp[-5].identifierName), (yyvsp[0].intValue), (yyvsp[-3].arguments));
									 }
#line 1947 "y.tab.c"
    break;

  case 16:
#line 410 "d.y"
                                                                                         {
										// Pop the current symbol table before leaving this scope
										popTable();
										printTheEndOfFunctionDeclaration(0);
									 }
#line 1957 "y.tab.c"
    break;

  case 17:
#line 415 "d.y"
                                                                                                                   {
									 	// Check if there's already an identical identifier name in the current symbol table
									 	if (lookUpInThisScope((yyvsp[-4].identifierName)) != NULL) {
											yyerrorForIdentifierDuplicated((yyvsp[-4].identifierName));
										}
										else {
											insert((yyvsp[-4].identifierName), NODE_FUNCTION_WITH_RETURN_VALUE, (yyvsp[0].intValue), NULL, 0, 0, 0);
										}
										// Create a new symbol table for the following returnBlock
										createNewTable(0);
										printTheStartOfFunctionDeclaration((yyvsp[-4].identifierName), (yyvsp[0].intValue), NULL);
									 }
#line 1974 "y.tab.c"
    break;

  case 18:
#line 426 "d.y"
                                                                                         {
										// Pop the current symbol table before leaving this scope
									 	popTable();
										printTheEndOfFunctionDeclaration(0);
									 }
#line 1984 "y.tab.c"
    break;

  case 19:
#line 431 "d.y"
                                                                                                                          {
									 	// Check if there's already an identical identifier name in the current symbol table
									 	if (lookUpInThisScope((yyvsp[-3].identifierName)) != NULL) {
											yyerrorForIdentifierDuplicated((yyvsp[-3].identifierName));
										}
										else {
											insert((yyvsp[-3].identifierName), NODE_FUNCTION_WITH_NO_RETURN_VALUE, -1, (yyvsp[-1].arguments) -> argumentTypes, (yyvsp[-1].arguments) -> argumentNum, 0, 0);
										}
										// Create a new symbol table for the following returnBlock
										createNewTable(0);
										// Get the arguments' definition from formalArguments and insert them into the current symbol table
										for (int i = 0; i < (yyvsp[-1].arguments) -> argumentNum; i++) {
											if (lookUpInThisScope((yyvsp[-1].arguments) -> argumentNames[i]) != NULL) {
												yyerrorForIdentifierDuplicated((yyvsp[-1].arguments) -> argumentNames[i]);
											}
											else {
												insert((yyvsp[-1].arguments) -> argumentNames[i], (yyvsp[-1].arguments) -> argumentTypes[i], -1, NULL, 0, 0, 0);
											}
										}
										printTheStartOfFunctionDeclaration((yyvsp[-3].identifierName), -1, (yyvsp[-1].arguments));
									 }
#line 2010 "y.tab.c"
    break;

  case 20:
#line 451 "d.y"
                                                                                         {
									 	// Pop the current symbol table before leaving this scope
										popTable();
										printTheEndOfFunctionDeclaration(1);
									 }
#line 2020 "y.tab.c"
    break;

  case 21:
#line 456 "d.y"
                                                                                                          {
									 	// Check if there's already an identical identifier name in the current symbol table
									 	if (lookUpInThisScope((yyvsp[-2].identifierName)) != NULL) {
											yyerrorForIdentifierDuplicated((yyvsp[-2].identifierName));
										}
										else {
											insert((yyvsp[-2].identifierName), NODE_FUNCTION_WITH_NO_RETURN_VALUE, -1, NULL, 0, 0, 0);
										}
										// Create a new symbol table for the following returnBlock
										createNewTable(0);
										printTheStartOfFunctionDeclaration((yyvsp[-2].identifierName), -1, NULL);
									 }
#line 2037 "y.tab.c"
    break;

  case 22:
#line 467 "d.y"
                                                                                         {
									 	// Pop the current symbol table before leaving this scope
									 	popTable();
										printTheEndOfFunctionDeclaration(1);
									 }
#line 2047 "y.tab.c"
    break;

  case 23:
#line 474 "d.y"
                                                                                   { (yyval.identifierName) = (yyvsp[0].identifierName); }
#line 2053 "y.tab.c"
    break;

  case 24:
#line 477 "d.y"
                                                                                                 {
							 	// Store all the arguments information and return it
							 	char** previousArgumentNames = (yyvsp[-4].arguments) -> argumentNames;
							 	int* previousArgumentTypes = (yyvsp[-4].arguments) -> argumentTypes;
							 	int previousArgumentNum = (yyvsp[-4].arguments) -> argumentNum;
								(yyval.arguments) = (Arguments*)malloc(sizeof(Arguments));
							 	(yyval.arguments) -> argumentNames = (char**)malloc(sizeof(char*) * (previousArgumentNum + 1));
							 	(yyval.arguments) -> argumentTypes = (int*)malloc(sizeof(int) * (previousArgumentNum + 1));
								for (int i = 0; i < previousArgumentNum; i++) {
									(yyval.arguments) -> argumentNames[i] = previousArgumentNames[i];
									(yyval.arguments) -> argumentTypes[i] = previousArgumentTypes[i];
								}
								(yyval.arguments) -> argumentNames[previousArgumentNum] = (yyvsp[-2].identifierName);
								(yyval.arguments) -> argumentTypes[previousArgumentNum] = (yyvsp[0].intValue);
								(yyval.arguments) -> argumentNum = previousArgumentNum + 1;
								if (previousArgumentNames != NULL) {
									free(previousArgumentNames);
								}
								if (previousArgumentTypes != NULL) {
									free(previousArgumentTypes);
								}
								if ((yyvsp[-4].arguments) != NULL) {
									free((yyvsp[-4].arguments));
								}
							 }
#line 2083 "y.tab.c"
    break;

  case 25:
#line 502 "d.y"
                                                                               {
							 	// Store the argument information and return it
							 	(yyval.arguments) = (Arguments*)malloc(sizeof(Arguments));
								(yyval.arguments) -> argumentNames = (char**)malloc(sizeof(char*));
								(yyval.arguments) -> argumentTypes = (int*)malloc(sizeof(int));
								(yyval.arguments) -> argumentNames[0] = (yyvsp[-2].identifierName);
								(yyval.arguments) -> argumentTypes[0] = (yyvsp[0].intValue);
								(yyval.arguments) -> argumentNum = 1;
							 }
#line 2097 "y.tab.c"
    break;

  case 35:
#line 526 "d.y"
                                                  {
				// Check if the identifier exists, and check if the type is not matched. 
				TableNode* tableNode = lookUpInEveryScope((yyvsp[-2].identifierName));
				if (tableNode == NULL) {
					yyerrorForIdentifierNotFound((yyvsp[-2].identifierName));
				}
				if (tableNode -> constant == 1) {
					yyerror("Constant can't be assigned.");
				}
				else if (tableNode -> type != (yyvsp[0].intValue)) {
					yyerror("Type not matched.");
				}
				printAssignVariable(tableNode);
			}
#line 2116 "y.tab.c"
    break;

  case 36:
#line 540 "d.y"
                                                                       {
				// Check if the identifier exists, and check if the type is not matched, and check if the identifier between '[' and ']' is an integer
				TableNode* tableNode = lookUpInEveryScope((yyvsp[-5].identifierName));
				if (tableNode == NULL) {
					yyerrorForIdentifierNotFound((yyvsp[-5].identifierName));
				}
				else if (tableNode -> type != NODE_ARRAY) {
					yyerror("Type not matched.");
				}
				else if ((yyvsp[-3].intValue) != NODE_INT) {
					yyerror("Type not matched.");
				}
				else if (tableNode -> subType != (yyvsp[0].intValue)) {
					yyerror("Type not matched.");
				}
			}
#line 2137 "y.tab.c"
    break;

  case 37:
#line 556 "d.y"
                                {
				printPreparationForPrint();
			}
#line 2145 "y.tab.c"
    break;

  case 38:
#line 558 "d.y"
                                     {
				printPrinting((yyvsp[0].intValue), 0);
			}
#line 2153 "y.tab.c"
    break;

  case 39:
#line 561 "d.y"
                                  {
				printPreparationForPrint();
			}
#line 2161 "y.tab.c"
    break;

  case 40:
#line 563 "d.y"
                                     {
				printPrinting((yyvsp[0].intValue), 1);
			}
#line 2169 "y.tab.c"
    break;

  case 41:
#line 566 "d.y"
                                          {
				// Check if the identifier exists
				TableNode* tableNode = lookUpInEveryScope((yyvsp[0].identifierName));
				if (tableNode == NULL) {
					yyerrorForIdentifierNotFound((yyvsp[0].identifierName));
				}
			}
#line 2181 "y.tab.c"
    break;

  case 42:
#line 573 "d.y"
                                            {
				printReturnVariable();
			}
#line 2189 "y.tab.c"
    break;

  case 43:
#line 576 "d.y"
                                 {
				printReturn();
			}
#line 2197 "y.tab.c"
    break;

  case 44:
#line 581 "d.y"
                                                                    {
					 (yyval.intValue) = (yyvsp[0].intValue);
					 printUminus();
				  }
#line 2206 "y.tab.c"
    break;

  case 45:
#line 585 "d.y"
                                                                              {
						// Check if the types of the two sides match
						if ((yyvsp[-2].intValue) != (yyvsp[0].intValue)) {
							yyerror("Type not matched.");
						}
						else {
							if ((yyvsp[-1].intValue) <= OPERATOR_REM) {
								(yyval.intValue) = (yyvsp[-2].intValue);
							}
							else {
								(yyval.intValue) = NODE_BOOL;
							}
						}
						printOperator((yyvsp[-1].intValue));
					}
#line 2226 "y.tab.c"
    break;

  case 46:
#line 600 "d.y"
                                                             {
						(yyval.intValue) = (yyvsp[-1].intValue);
					}
#line 2234 "y.tab.c"
    break;

  case 47:
#line 603 "d.y"
                                                             {
						(yyval.intValue) = (yyvsp[0].intValue);
					}
#line 2242 "y.tab.c"
    break;

  case 48:
#line 608 "d.y"
                                                                                     {
							 	(yyval.intValue) = (yyvsp[0].intValue);
								printUminus();
							 }
#line 2251 "y.tab.c"
    break;

  case 49:
#line 612 "d.y"
                                                                              {
							 	(yyval.intValue) = (yyvsp[-1].intValue);
							 }
#line 2259 "y.tab.c"
    break;

  case 50:
#line 615 "d.y"
                                                                              {
							 	(yyval.intValue) = (yyvsp[0].intValue);
							 }
#line 2267 "y.tab.c"
    break;

  case 51:
#line 620 "d.y"
                                                                                                            {
									 (yyval.node) = (yyvsp[0].node);
									 (yyval.node) -> value *= -1;
									}
#line 2276 "y.tab.c"
    break;

  case 52:
#line 624 "d.y"
                                                                                                                              {
										// Check if the types of the two sides match
										if ((yyvsp[-2].node) -> type != (yyvsp[0].node) -> type) {
											yyerror("Type not matched.");
										}
										else {
											int operator = (yyvsp[-1].intValue);
											(yyval.node) = (yyvsp[-2].node);

											switch (operator) {
											case OPERATOR_ADD:
												(yyval.node) -> value += (yyvsp[0].node) -> value;
												break;

											case OPERATOR_SUB:
												(yyval.node) -> value -= (yyvsp[0].node) -> value;
												break;

											case OPERATOR_MUL:
												(yyval.node) -> value *= (yyvsp[0].node) -> value;
												break;

											case OPERATOR_DIV:
												(yyval.node) -> value /= (yyvsp[0].node) -> value;
												break;

											case OPERATOR_REM:
												(yyval.node) -> value %= (yyvsp[0].node) -> value;
												break;

											case OPERATOR_AND:
												(yyval.node) -> value = (yyval.node) -> value && (yyvsp[0].node) -> value;
												(yyval.node) -> type = NODE_BOOL;
												break;

											case OPERATOR_OR:
												(yyval.node) -> value = (yyval.node) -> value || (yyvsp[0].node) -> value;
												(yyval.node) -> type = NODE_BOOL;
												break;

											case OPERATOR_XOR:
												(yyval.node) -> value = (yyval.node) -> value != (yyvsp[0].node) -> value;
												(yyval.node) -> type = NODE_BOOL;
												break;

											case OPERATOR_LT:
												(yyval.node) -> value = (yyval.node) -> value < (yyvsp[0].node) -> value;
												(yyval.node) -> type = NODE_BOOL;
												break;

											case OPERATOR_GE:
												(yyval.node) -> value = (yyval.node) -> value >= (yyvsp[0].node) -> value;
												(yyval.node) -> type = NODE_BOOL;
												break;

											case OPERATOR_LE:
												(yyval.node) -> value = (yyval.node) -> value <= (yyvsp[0].node) -> value;
												(yyval.node) -> type = NODE_BOOL;
												break;

											case OPERATOR_EQ:
												(yyval.node) -> value = (yyval.node) -> value == (yyvsp[0].node) -> value;
												(yyval.node) -> type = NODE_BOOL;
												break;

											case OPERATOR_NE:
												(yyval.node) -> value = (yyval.node) -> value != (yyvsp[0].node) -> value;
												(yyval.node) -> type = NODE_BOOL;
												break;

											case OPERATOR_GT:
												(yyval.node) -> value = (yyval.node) -> value > (yyvsp[0].node) -> value;
												(yyval.node) -> type = NODE_BOOL;
												break;
											}
											free((yyvsp[0].node));
										}
									}
#line 2359 "y.tab.c"
    break;

  case 53:
#line 702 "d.y"
                                                                                                     {
										(yyval.node) = (yyvsp[-1].node);
									}
#line 2367 "y.tab.c"
    break;

  case 54:
#line 705 "d.y"
                                                                                                     {
										(yyval.node) = (yyvsp[0].node);
									}
#line 2375 "y.tab.c"
    break;

  case 55:
#line 710 "d.y"
                                                                                                                             {
											 	(yyval.node) = (yyvsp[0].node);
												(yyval.node) -> value *= -1;
											 }
#line 2384 "y.tab.c"
    break;

  case 56:
#line 714 "d.y"
                                                                                                                      {
											 	(yyval.node) = (yyvsp[-1].node);
											 }
#line 2392 "y.tab.c"
    break;

  case 57:
#line 717 "d.y"
                                                                                                                      {
											 	(yyval.node) = (yyvsp[0].node);
											 }
#line 2400 "y.tab.c"
    break;

  case 58:
#line 722 "d.y"
                                     { (yyval.intValue) = OPERATOR_ADD; }
#line 2406 "y.tab.c"
    break;

  case 59:
#line 723 "d.y"
                                       { (yyval.intValue) = OPERATOR_SUB; }
#line 2412 "y.tab.c"
    break;

  case 60:
#line 724 "d.y"
                                       { (yyval.intValue) = OPERATOR_MUL; }
#line 2418 "y.tab.c"
    break;

  case 61:
#line 725 "d.y"
                                       { (yyval.intValue) = OPERATOR_DIV; }
#line 2424 "y.tab.c"
    break;

  case 62:
#line 726 "d.y"
                                       { (yyval.intValue) = OPERATOR_REM; }
#line 2430 "y.tab.c"
    break;

  case 63:
#line 727 "d.y"
                                       { (yyval.intValue) = OPERATOR_AND; }
#line 2436 "y.tab.c"
    break;

  case 64:
#line 728 "d.y"
                                       { (yyval.intValue) = OPERATOR_OR; }
#line 2442 "y.tab.c"
    break;

  case 65:
#line 729 "d.y"
                                       { (yyval.intValue) = OPERATOR_XOR; }
#line 2448 "y.tab.c"
    break;

  case 66:
#line 730 "d.y"
                                       { (yyval.intValue) = OPERATOR_LT; }
#line 2454 "y.tab.c"
    break;

  case 67:
#line 731 "d.y"
                                      { (yyval.intValue) = OPERATOR_GE; }
#line 2460 "y.tab.c"
    break;

  case 68:
#line 732 "d.y"
                                      { (yyval.intValue) = OPERATOR_LE; }
#line 2466 "y.tab.c"
    break;

  case 69:
#line 733 "d.y"
                                      { (yyval.intValue) = OPERATOR_EQ; }
#line 2472 "y.tab.c"
    break;

  case 70:
#line 734 "d.y"
                                      { (yyval.intValue) = OPERATOR_NE; }
#line 2478 "y.tab.c"
    break;

  case 71:
#line 735 "d.y"
                                       { (yyval.intValue) = OPERATOR_GT; }
#line 2484 "y.tab.c"
    break;

  case 72:
#line 738 "d.y"
                                                                              {
										(yyval.intValue) = (yyvsp[0].node) -> type;
										if ((yyvsp[0].node) -> type == NODE_STRING) {
											printLoadingString((yyvsp[0].node) -> stringValue);
										} else {
											printValue((yyvsp[0].node) -> type, (yyvsp[0].node) -> value);
										}
									}
#line 2497 "y.tab.c"
    break;

  case 73:
#line 746 "d.y"
                                                                                     {
										// Check if the identifier exists
										TableNode* tableNode = lookUpInEveryScope((yyvsp[0].identifierName));
										if (tableNode == NULL) {
											yyerrorForIdentifierNotFound((yyvsp[0].identifierName));
										}
										else {
											(yyval.intValue) = tableNode -> type;
										}
										if (tableNode -> constant == 1) {
											printValue(tableNode -> type, tableNode -> constantValue);
										} else if (tableNode -> constant == 0) {
											if (tableNode -> global == 1) {
												printLoadingGlobalVariable(tableNode -> string, tableNode -> type);
											} else if (tableNode -> global == 0) {
												printLoadingLocalVariable(tableNode -> index);
											}
										}
									}
#line 2521 "y.tab.c"
    break;

  case 74:
#line 765 "d.y"
                                                                                             {
										// Check if the function has a return type
										if ((yyvsp[0].intValue) == -1) {
											yyerror("This function doesn't return a value.");
										}
										else {
											(yyval.intValue) = (yyvsp[0].intValue);
										}
									}
#line 2535 "y.tab.c"
    break;

  case 75:
#line 774 "d.y"
                                                                                         {
										(yyval.intValue) = (yyvsp[0].intValue);
									}
#line 2543 "y.tab.c"
    break;

  case 76:
#line 779 "d.y"
                                                                                                              {
														(yyval.node) = (yyvsp[0].node);
													}
#line 2551 "y.tab.c"
    break;

  case 77:
#line 782 "d.y"
                                                                                                                     {
														// Check if the identifier exists, and it is a constant
														TableNode* tableNode = lookUpInEveryScope((yyvsp[0].identifierName));
														if (tableNode == NULL) {
															yyerrorForIdentifierNotFound((yyvsp[0].identifierName));
														}
														else {
															if (tableNode -> constant != 1) {
																yyerror("You can only use constant expression to declare a \"var\" or \"val\".");
															}
															(yyval.node) = (ParameterNode*)malloc(sizeof(ParameterNode));
															(yyval.node) -> type = tableNode -> type;
															(yyval.node) -> value = tableNode -> constantValue;
														}
													}
#line 2571 "y.tab.c"
    break;

  case 78:
#line 799 "d.y"
                                                                                                                       {
										// Check if the identifier exists, and it's a function
										TableNode* tableNode = lookUpInEveryScope((yyvsp[-3].identifierName));
										if (tableNode == NULL) {
											yyerrorForIdentifierNotFound((yyvsp[-3].identifierName));
										}
										else if (tableNode -> type != NODE_FUNCTION_WITH_NO_RETURN_VALUE && tableNode -> type != NODE_FUNCTION_WITH_RETURN_VALUE) {
											yyerrorForIdentifierNotFunction((yyvsp[-3].identifierName));
										}
										else {
											// If it's a function with a return type, return its return type. If not, return -1. 
											if (tableNode -> type == NODE_FUNCTION_WITH_RETURN_VALUE) {
												(yyval.intValue) = tableNode -> subType;
											}
											else {
												(yyval.intValue) = -1;
											}
											// Check if the number of arguments is correct
											if ((yyvsp[-1].arguments) -> argumentNum != tableNode -> argumentNum) {
												yyerror("Number of arguments doesn't match.");
											}
											else {
												// Check if the types of arguments are correct
												int matched = 1;
												for (int i = 0; i < (yyvsp[-1].arguments) -> argumentNum; i++) {
													if ((yyvsp[-1].arguments) -> argumentTypes[i] != tableNode -> argumentTypes[i]) {
														matched = 0;
														break;
													}
												}
												if (matched == 0) {
													yyerror("Argument types don't match.");
												}
											}
										}
										// Release the memory
										if ((yyvsp[-1].arguments) -> argumentTypes != NULL) {
											free((yyvsp[-1].arguments) -> argumentTypes);
										}
										if ((yyvsp[-1].arguments) != NULL) {
											free((yyvsp[-1].arguments));
										}
										printInvocationOfFunction(tableNode -> string, tableNode -> subType, tableNode -> argumentTypes, tableNode -> argumentNum);
									}
#line 2620 "y.tab.c"
    break;

  case 79:
#line 843 "d.y"
                                                                                             {
										// Check if the identifier exists, and it's a function
										TableNode* tableNode = lookUpInEveryScope((yyvsp[-2].identifierName));
										if (tableNode == NULL) {
											yyerrorForIdentifierNotFound((yyvsp[-2].identifierName));
										}
										else if (tableNode -> type != NODE_FUNCTION_WITH_NO_RETURN_VALUE && tableNode -> type != NODE_FUNCTION_WITH_RETURN_VALUE) {
											yyerrorForIdentifierNotFunction((yyvsp[-2].identifierName));
										}
										else {
											// If it's a function with return type, return its return type. If not, return -1. 
											if (tableNode -> type == NODE_FUNCTION_WITH_RETURN_VALUE) {
												(yyval.intValue) = tableNode -> subType;
											}
											else {
												(yyval.intValue) = -1;
											}
											// If the number of arguments is not 0, error
											if (tableNode -> argumentNum != 0) {
												yyerror("Number of arguments doesn't match.");
											}
										}
									}
#line 2648 "y.tab.c"
    break;

  case 80:
#line 868 "d.y"
                                                                                                                                                    {
														// Store the arguments information and return it
														int* previousArgumentTypes = (yyvsp[-2].arguments) -> argumentTypes;
														int previousArgumentNum = (yyvsp[-2].arguments) -> argumentNum;
														(yyval.arguments) = (Arguments*)malloc(sizeof(Arguments));
														(yyval.arguments) -> argumentTypes = (int*)malloc(sizeof(int) * (previousArgumentNum + 1));
														for (int i = 0; i < previousArgumentNum; i++) {
															(yyval.arguments) -> argumentTypes[i] = previousArgumentTypes[i];
														}
														(yyval.arguments) -> argumentTypes[previousArgumentNum] = (yyvsp[0].intValue);
														(yyval.arguments) -> argumentNum = previousArgumentNum + 1;
														if (previousArgumentTypes != NULL) {
															free(previousArgumentTypes);
														}
														if ((yyvsp[-2].arguments) != NULL) {
															free((yyvsp[-2].arguments));
														}
													 }
#line 2671 "y.tab.c"
    break;

  case 81:
#line 886 "d.y"
                                                                                                                      {
														// Store the arguments information and return it
														(yyval.arguments) = (Arguments*)malloc(sizeof(Arguments));
														(yyval.arguments) -> argumentTypes = (int*)malloc(sizeof(int));
														(yyval.arguments) -> argumentTypes[0] = (yyvsp[0].intValue);
														(yyval.arguments) -> argumentNum = 1;
													 }
#line 2683 "y.tab.c"
    break;

  case 82:
#line 896 "d.y"
                                                                                      {
								// Check if the identifier exists, and it's an array
								TableNode* tableNode = lookUpInEveryScope((yyvsp[-3].identifierName));
								if (tableNode == NULL) {
									yyerrorForIdentifierNotFound((yyvsp[-3].identifierName));
								}
								else if (tableNode -> type != NODE_ARRAY) {
									yyerrorForIdentifierNotArray((yyvsp[-3].identifierName));
								}
								else {
									// Return its sub type
									(yyval.intValue) = tableNode -> subType;
									// Check if the type of expression is integer
									if ((yyvsp[-1].intValue) != NODE_INT) {
										yyerror("Array needs a integer between its brackets.");
									}
								}
							}
#line 2706 "y.tab.c"
    break;

  case 83:
#line 916 "d.y"
                                            {
					 	printPreparationForIf();
					 }
#line 2714 "y.tab.c"
    break;

  case 85:
#line 921 "d.y"
                                                        {
				// Check if the type of expression is bool
				if ((yyvsp[-2].intValue) != NODE_BOOL) {
					yyerror("\"if\" needs a Boolean in its brackets.");
				}
				printConditionElseFlag();
				printConditionRestFlag();
			}
#line 2727 "y.tab.c"
    break;

  case 86:
#line 929 "d.y"
                                                          {
				printConditionElseFlag();
			}
#line 2735 "y.tab.c"
    break;

  case 87:
#line 931 "d.y"
                                             {
				// Check if the type of expression is bool
				if ((yyvsp[-5].intValue) != NODE_BOOL) {
					yyerror("\"if\" needs a Boolean in its brackets.");
				}
				printConditionRestFlag();
				printNOP();
			}
#line 2748 "y.tab.c"
    break;

  case 88:
#line 940 "d.y"
                      {
			printNOP();
			printWhileLoopBeginFlag();
		}
#line 2757 "y.tab.c"
    break;

  case 89:
#line 943 "d.y"
                                                  {
			// Check if the type of expression is bool
			if ((yyvsp[-2].intValue) != NODE_BOOL) {
				yyerror("\"while\" needs a Boolean in its brackets.");
		 	}
			printGotoWhileLoopBeginFlag();
			printConditionElseFlag();
			printConditionRestFlag();
			printNOP();
		}
#line 2772 "y.tab.c"
    break;

  case 90:
#line 953 "d.y"
                                     {
			// Create a new symbol table for the identifier in the loop for
			createNewTable(0);
			// Check if the identifer exists (It shouldn't exist actually, because this is a new symbol table)
			TableNode* tableNode = lookUpInThisScope((yyvsp[0].identifierName));
			if (tableNode != NULL) {
				yyerrorForIdentifierDuplicated((yyvsp[0].identifierName));
			}
			else {
				tableNode = insert((yyvsp[0].identifierName), NODE_INT, -1, NULL, 0, 0, 0);
			}
			(yyval.intValue) = tableNode -> index;
		}
#line 2790 "y.tab.c"
    break;

  case 91:
#line 965 "d.y"
                                {
			printBetweenForLoopStartingNumAndEndingNum((yyvsp[-2].intValue));
		}
#line 2798 "y.tab.c"
    break;

  case 92:
#line 967 "d.y"
                                {
			printAfterForLoopStartingNumAndEndingNum((yyvsp[-5].intValue));
		}
#line 2806 "y.tab.c"
    break;

  case 93:
#line 969 "d.y"
                                    {
			// Pop the current symbol table
			popTable();
			printTheEndOfTrueFlagSectionOfForLoop((yyvsp[-8].intValue));
			printConditionElseFlag();
			printConditionRestFlag();
			printNOP();
		}
#line 2819 "y.tab.c"
    break;

  case 94:
#line 977 "d.y"
               {
							// Create a new symbol table because it has entering new scope
						 	createNewTable(0);
						 }
#line 2828 "y.tab.c"
    break;

  case 95:
#line 980 "d.y"
                                                          {
						 	// Pop the current symbol table because it is leaving this scope
						 	popTable();
						 }
#line 2837 "y.tab.c"
    break;

  case 96:
#line 984 "d.y"
                                                   {
							// Create a new symbol table because it has entering new scope
						 	createNewTable(0);
						 }
#line 2846 "y.tab.c"
    break;

  case 97:
#line 987 "d.y"
                                                                 {
						 	// Pop the current symbol table because it is leaving this scope
						 	popTable();
						 }
#line 2855 "y.tab.c"
    break;

  case 99:
#line 995 "d.y"
                      {
				 	(yyval.intValue) = (yyvsp[0].intValue);
					printCondition();
				 }
#line 2864 "y.tab.c"
    break;

  case 100:
#line 1000 "d.y"
                         {
			(yyval.intValue) = (yyvsp[0].intValue);
		}
#line 2872 "y.tab.c"
    break;

  case 101:
#line 1003 "d.y"
                  {
			(yyval.intValue) = -1;
		}
#line 2880 "y.tab.c"
    break;

  case 102:
#line 1008 "d.y"
                         {
		 	(yyval.node) = (ParameterNode*)malloc(sizeof(ParameterNode));
			(yyval.node) -> type = NODE_INT;
			(yyval.node) -> value = (yyvsp[0].intValue);
		 }
#line 2890 "y.tab.c"
    break;

  case 103:
#line 1013 "d.y"
                           {
		 	(yyval.node) = (ParameterNode*)malloc(sizeof(ParameterNode));
			(yyval.node) -> type = NODE_BOOL;
			(yyval.node) -> value = (yyvsp[0].boolValue);
		 }
#line 2900 "y.tab.c"
    break;

  case 104:
#line 1018 "d.y"
                          {
		 	(yyval.node) = (ParameterNode*)malloc(sizeof(ParameterNode));
			(yyval.node) -> type = NODE_STRING;
			(yyval.node) -> stringValue = (yyvsp[0].stringValue);
		 }
#line 2910 "y.tab.c"
    break;


#line 2914 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1023 "d.y"

void yyerror(char *s) {
	fprintf(stderr, "%s (Line: %d)\n", s, lineCount);
	yyerrorExit();
}
void yyerrorForIdentifierDuplicated(char* identifierName) {
	fprintf(stderr, "Identifier \"%s\" already exists. (Line: %d)\n", identifierName, lineCount);
	yyerrorExit();
}
void yyerrorForIdentifierNotFound(char* identifierName) {
	fprintf(stderr, "Identifier \"%s\" not found. (Line: %d)\n", identifierName, lineCount);
	yyerrorExit();
}
void yyerrorForIdentifierNotFunction(char* identifierName) {
	fprintf(stderr, "Identifier \"%s\" is not a function. (Line: %d)\n", identifierName, lineCount);
	yyerrorExit();
}
void yyerrorForIdentifierNotArray(char* identifierName) {
	fprintf(stderr, "Identifier \"%s\" is not a array. (Line: %d)\n", identifierName, lineCount);
	yyerrorExit();
}
void yyerrorExit() {
	exit(-1);
}
void printTheStartOfClassDeclaration(char* name) {
	fprintf(file, "class %s\n", name);
	fprintf(file, "{\n");
}
void printTheEndOfClassDeclaration() {
	fprintf(file, "}\n");
}
void printTheStartOfFunctionDeclaration(char* name, int type, Arguments* arguments) {
	if (strcmp(name, "main") == 0) {
		fprintf(file, "method public static void main(java.lang.String[])\n");
		fprintf(file, "max_stack 15\n");
		fprintf(file, "max_locals 15\n");
		fprintf(file, "{\n");
	} else {
		fprintf(file, "method public static ");
		if (type == NODE_INT) {
			fprintf(file, "int ");
		} else if (type == NODE_BOOL) {
			fprintf(file, "boolean ");
		} else if (type == -1) {
			fprintf(file, "void ");
		}
		fprintf(file, "%s(", name);
		if (arguments != NULL && arguments -> argumentNum > 0) {
			// arguments -> argumentNum[0]
			if (arguments -> argumentTypes[0] == NODE_INT) {
				fprintf(file, "int");
			} else if (arguments -> argumentTypes[0] == NODE_BOOL) {
				fprintf(file, "boolean");
			}
			// arguments -> argumentNum[i] (i > 0)
			for (int i = 1; i < arguments -> argumentNum; i++) {
				if (arguments -> argumentTypes[i] == NODE_INT) {
					fprintf(file, ", int");
				} else if (arguments -> argumentTypes[i] == NODE_BOOL) {
					fprintf(file, ", boolean");
				}
			}
		}
		fprintf(file, ")\n");
		fprintf(file, "max_stack 15\n");
		fprintf(file, "max_locals 15\n");
		fprintf(file, "{\n");
	}
}
void printTheEndOfFunctionDeclaration(int needReturn) {
	if (needReturn > 0) {
		fprintf(file, "return\n");
	} else {
		fprintf(file, "iload 0\n");
		fprintf(file, "ireturn\n");
	}
	fprintf(file, "}\n");
}
void printZeroToInitializeIt(int type) {
	if (type == NODE_INT) {
		fprintf(file, "iload 0\n");
	} else if (type == NODE_BOOL) {
		fprintf(file, "iconst_0\n");
	}
}
void printLocalVariableDeclaration(int index) {
	fprintf(file, "istore %d\n", index);
}
void printGlobalVariableDeclarationWithoutValue(char* name, int type) {
	fprintf(file, "field static ");
	if (type == NODE_INT) {
		fprintf(file, "int ");
	} else if (type == NODE_BOOL) {
		fprintf(file, "boolean ");
	}
	fprintf(file, "%s\n", name);
}
void printGlobalVariableDeclaration(char* name, int type, int value) {
	fprintf(file, "field static ");
	if (type == NODE_INT) {
		fprintf(file, "int ");
		fprintf(file, "%s = %d\n", name, value);
	} else if (type == NODE_BOOL) {
		fprintf(file, "boolean ");
		if (value == 0) {
			fprintf(file, "%s = 0\n", name);
		} else {
			fprintf(file, "%s = 1\n", name);
		}
	}
}
void printAssignVariable(TableNode* node) {
	if (node -> global == 1) {
		fprintf(file, "putstatic ");
		if (node -> type == NODE_INT) {
			fprintf(file, "int ");
		} else if (node -> type == NODE_BOOL) {
			fprintf(file, "boolean ");
		}
		fprintf(file, "%s.%s\n", className, node -> string);
	} else if (node -> global == 0) {
		fprintf(file, "istore %d\n", node -> index);
	}
}
void printReturnVariable() {
	fprintf(file, "ireturn\n");
}
void printReturn() {
	fprintf(file, "return\n");
}
void printUminus() {
	fprintf(file, "ineg\n");
}
void printValue(int type, int value) {
	if (type == NODE_INT) {
		fprintf(file, "sipush %d\n", value);
	} else if (type == NODE_BOOL) {
		if (value == 0) {
			fprintf(file, "iconst_0\n");
		} else {
			fprintf(file, "iconst_1\n");
		}
	}
}
void printLoadingLocalVariable(int index) {
	fprintf(file, "iload %d\n", index);
}
void printLoadingGlobalVariable(char* name, int type) {
	fprintf(file, "getstatic ");
	if (type == NODE_INT) {
		fprintf(file, "int ");
	} else if (type == NODE_BOOL) {
		fprintf(file, "boolean ");
	}
	fprintf(file, "%s.%s\n", className, name);
}
void printOperator(int operator) {
	if (operator >= OPERATOR_LT) {
		fprintf(file, "isub\n");
	}
	switch (operator) {
	case OPERATOR_ADD:
		fprintf(file, "iadd\n");
		break;

	case OPERATOR_SUB:
		fprintf(file, "isub\n");
		break;

	case OPERATOR_MUL:
		fprintf(file, "imul\n");
		break;

	case OPERATOR_DIV:
		fprintf(file, "idiv\n");
		break;

	case OPERATOR_REM:
		fprintf(file, "irem\n");
		break;

	case OPERATOR_AND:
		fprintf(file, "iand\n");
		break;

	case OPERATOR_OR:
		fprintf(file, "ior\n");
		break;

	case OPERATOR_XOR:
		fprintf(file, "ixor\n");
		break;

	case OPERATOR_LT:
		fprintf(file, "iflt L%d_TRUE\n", nextConditionCounter);
		break;

	case OPERATOR_GE:
		fprintf(file, "ifgt L%d_TRUE\n", nextConditionCounter);
		break;

	case OPERATOR_LE:
		fprintf(file, "ifle L%d_TRUE\n", nextConditionCounter);
		break;

	case OPERATOR_EQ:
		fprintf(file, "ifeq L%d_TRUE\n", nextConditionCounter);
		break;

	case OPERATOR_NE:
		fprintf(file, "ifne L%d_TRUE\n", nextConditionCounter);
		break;

	case OPERATOR_GT:
		fprintf(file, "ifgt L%d_TRUE\n", nextConditionCounter);
		break;
	}
	if (operator >= OPERATOR_LT) {
		fprintf(file, "iconst_0\n");
		fprintf(file, "goto L%d_REST\n", nextConditionCounter);
		fprintf(file, "L%d_TRUE:\n", nextConditionCounter);
		fprintf(file, "iconst_1\n");
		fprintf(file, "L%d_REST:\n", nextConditionCounter);
		nextConditionCounter++;
	}
}
void printConditionWithOperator(int operator) {
	fprintf(file, "isub\n");
	switch (operator) {
	case OPERATOR_LT:
		fprintf(file, "iflt L%d_TRUE\n", unfinishedConditionCounter -> index);
		break;

	case OPERATOR_GE:
		fprintf(file, "ifge L%d_TRUE\n", unfinishedConditionCounter -> index);
		break;

	case OPERATOR_LE:
		fprintf(file, "ifle L%d_TRUE\n", unfinishedConditionCounter -> index);
		break;

	case OPERATOR_EQ:
		fprintf(file, "ifeq L%d_TRUE\n", unfinishedConditionCounter -> index);
		break;

	case OPERATOR_NE:
		fprintf(file, "ifne L%d_TRUE\n", unfinishedConditionCounter -> index);
		break;

	case OPERATOR_GT:
		fprintf(file, "ifgt L%d_TRUE\n", unfinishedConditionCounter -> index);
		break;
	}
	fprintf(file, "goto L%d_FALSE\n", unfinishedConditionCounter -> index);
	fprintf(file, "L%d_TRUE:\n", unfinishedConditionCounter -> index);
}
void printCondition() {
	fprintf(file, "ifeq L%d_FALSE\n", unfinishedConditionCounter -> index);
	fprintf(file, "goto L%d_TRUE\n", unfinishedConditionCounter -> index);
	fprintf(file, "L%d_TRUE:\n", unfinishedConditionCounter -> index);
}
void printConditionElseFlag() {
	fprintf(file, "goto L%d_REST\n", unfinishedConditionCounter -> index);
	fprintf(file, "L%d_FALSE:\n", unfinishedConditionCounter -> index);
}
void printConditionRestFlag() {
	fprintf(file, "goto L%d_REST\n", unfinishedConditionCounter -> index);
	fprintf(file, "L%d_REST:\n", unfinishedConditionCounter -> index);
	UnfinishedConditionCounter* finished = unfinishedConditionCounter;
	unfinishedConditionCounter = unfinishedConditionCounter -> previous;
	unfinishedConditionCounter -> next = NULL;
	free(finished);
}
void printLoadingString(char* stringToPrint) {
	fprintf(file, "ldc \"%s\"\n", stringToPrint);
}
void printPreparationForPrint() {
	fprintf(file, "getstatic java.io.PrintStream java.lang.System.out\n");
}
void printPrinting(int type, int nextLine) {
	if (nextLine == 0) {
		fprintf(file, "invokevirtual void java.io.PrintStream.print(");
	} else if (nextLine == 1) {
		fprintf(file, "invokevirtual void java.io.PrintStream.println(");
	}
	if (type == NODE_INT) {
		fprintf(file, "int");
	} else if (type == NODE_BOOL) {
		fprintf(file, "boolean");
	} else if (type == NODE_STRING) {
		fprintf(file, "java.lang.String");
	}
	fprintf(file, ")\n");
}
void printWhileLoopBeginFlag() {
	fprintf(file, "L%d_BEGIN:\n", nextConditionCounter);
	unfinishedConditionCounter -> next = (UnfinishedConditionCounter*)malloc(sizeof(UnfinishedConditionCounter));
	unfinishedConditionCounter -> next -> index = nextConditionCounter;
	unfinishedConditionCounter -> next -> next = NULL;
	unfinishedConditionCounter -> next -> previous = unfinishedConditionCounter;
	unfinishedConditionCounter = unfinishedConditionCounter -> next;
	nextConditionCounter++;
}
void printGotoWhileLoopBeginFlag() {
	fprintf(file, "goto L%d_BEGIN\n", unfinishedConditionCounter -> index);
}
void printBetweenForLoopStartingNumAndEndingNum(int index) {
	fprintf(file, "istore %d\n", index);
	fprintf(file, "L%d_BEGIN:\n", nextConditionCounter);
	fprintf(file, "iload %d\n", index);
	unfinishedConditionCounter -> next = (UnfinishedConditionCounter*)malloc(sizeof(UnfinishedConditionCounter));
	unfinishedConditionCounter -> next -> index = nextConditionCounter;
	unfinishedConditionCounter -> next -> next = NULL;
	unfinishedConditionCounter -> next -> previous = unfinishedConditionCounter;
	unfinishedConditionCounter = unfinishedConditionCounter -> next;
	nextConditionCounter++;
}
void printAfterForLoopStartingNumAndEndingNum(int index) {
	printConditionWithOperator(OPERATOR_LE);
}
void printTheEndOfTrueFlagSectionOfForLoop(int index) {
	fprintf(file, "sipush 1\n");
	fprintf(file, "iload %d\n", index);
	fprintf(file, "iadd\n");
	fprintf(file, "istore %d\n", index);
	fprintf(file, "goto L%d_BEGIN\n", unfinishedConditionCounter -> index);
}
void printInvocationOfFunction(char* name, int type, int* argumentTypes, int argumentNum) {
	fprintf(file, "invokestatic ");
	if (type == NODE_INT) {
		fprintf(file, "int ");
	} else if (type == NODE_BOOL) {
		fprintf(file, "boolean ");
	} else if (type == -1) {
		fprintf(file, "void ");
	}
	fprintf(file, "%s.%s(", className, name);
	if (argumentNum > 0) {
		if (argumentTypes[0] == NODE_INT) {
			fprintf(file, "int");
		} else if (argumentTypes[0] == NODE_BOOL) {
			fprintf(file, "boolean");
		}
		for (int i = 1; i < argumentNum; i++) {
			if (argumentTypes[i] == NODE_INT) {
				fprintf(file, ", int");
			} else if (argumentTypes[i] == NODE_BOOL) {
				fprintf(file, ", boolean");
			}
		}
	}
	fprintf(file, ")\n");
}
void printPreparationForIf() {
	unfinishedConditionCounter -> next = (UnfinishedConditionCounter*)malloc(sizeof(UnfinishedConditionCounter));
	unfinishedConditionCounter -> next -> index = nextConditionCounter;
	unfinishedConditionCounter -> next -> next = NULL;
	unfinishedConditionCounter -> next -> previous = unfinishedConditionCounter;
	unfinishedConditionCounter = unfinishedConditionCounter -> next;
	nextConditionCounter++;
}
void printNOP() {
	fprintf(file, "nop\n");
}
void initParser() {
	nextConditionCounter = 0;
	unfinishedConditionCounter = (UnfinishedConditionCounter*)malloc(sizeof(UnfinishedConditionCounter));
	unfinishedConditionCounter -> index = -1;
	unfinishedConditionCounter -> next = NULL;
	unfinishedConditionCounter -> previous = NULL;
	file = fopen("temp.txt", "w");
	if (file == NULL) {
		fprintf(stderr, "Can't create a file to write.\n");
		exit(-1);
	}
	//printf("File created.\n");
}
int main(void) {
	initScanner();
	initParser();
	yyparse();
	char* fileExtention = ".jasm";
	char* filename = (char*)malloc(sizeof(char) * (strlen(className) + strlen(fileExtention) + 1));
	filename[0] = '\0';
	strcat(filename, className);
	strcat(filename, fileExtention);
	rename("temp.txt", filename);
	return 0;
}
