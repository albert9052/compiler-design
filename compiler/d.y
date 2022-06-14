%union {
int intValue;
float floatValue;
int boolValue;
char* stringValue;
int type;
char* identifierName;
struct PN* node;
struct parserArguments* arguments;
};
%token <node> INTEGER
%token <node> FLOAT
%token <node> BOOLEAN
%token <node> STRING
%token <node> IDENTIFIER CLASS FUN VAR VAL TYPE
%token <node> PRINT PRINTLN
%token <node> READ
%token <node> RETURN
%token <node> IF ELSE
%token <node> FOR WHILE IN
%type <node> value expression expressionTerminal functionInvocation arrayReference functionInvocationArguments procedureInvocation
%type <node> block statement variableDeclaration constantDeclaration simple conditional loop
%type <node> constantExpression constantExpressionTerminal rightConstantExpression
%type <intValue> type
%type <identifierName> classIdentifier
%token <node> '(' ')' ':' '{' '}'
%nonassoc ELSE
%left <node> '|'
%left <node> '&'
%left <node> '!'
%left <node> '<' GE LE EQ NE '>'
%left <node> '+' '-'
%left <node> '*' '/'
%left <node> DD
%nonassoc UMINUS
%start program
%{
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
%}
%%
program:
			 CLASS classIdentifier {
			 	// Create a new symbol table before entering the classBlock
			 	createNewTable(1);
				printTheStartOfClassDeclaration($<identifierName>2);
				className = $<identifierName>2;
			 } '{' classBlock '}' {
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
			 ;
classIdentifier:
							 IDENTIFIER { 
							 	// Insert the class identifier into the current symbol table
								insert($<identifierName>1, NODE_CLASS, -1, NULL, 0, 0, 0); 
								$$ = $<identifierName>1;
							 }
							 ;
classBlock:
					globalVariableDeclaration classBlock
					| constantDeclaration classBlock
					| functionDeclaration classBlock
					|
					;
globalVariableDeclaration:
												 VAR IDENTIFIER type {
													// Check if there's already an identical identifier name in the current symbol table
													if (lookUpInThisScope($<identifierName>2) != NULL) {
														yyerrorForIdentifierDuplicated($<identifierName>2);
													}
													else {
														// Check if there's a type definition. If not, the default type is integer. 
														TableNode* node;
														if ($<intValue>3 != -1) {
															node = insert($<identifierName>2, $<intValue>3, -1, NULL, 0, 0, 0);
															printGlobalVariableDeclarationWithoutValue(node -> string, $<intValue>3);
														}
														else {
															node = insert($<identifierName>2, NODE_INT, -1, NULL, 0, 0, 0);
															printGlobalVariableDeclarationWithoutValue(node -> string, NODE_INT);
														}
													}
												 }
												 | VAR IDENTIFIER type '=' constantExpression {
													// Check if there's a type definition. If not, its type is recognized from constantExpression
													if ($<intValue>3 == -1) {
														$<intValue>3 = $<node>5 -> type;
													}
													// Check if the type is matched, then check if there's already an identical identifier name in the current symbol table
													if ($<intValue>3 != $<node>5 -> type) {
														yyerror("Type not matched.");
													}
													else if (lookUpInThisScope($<identifierName>2) != NULL) {
														yyerrorForIdentifierDuplicated($<identifierName>2);
													}
													else {
														TableNode* node = insert($<identifierName>2, $<intValue>3, -1, NULL, 0, 0, 0);
														printGlobalVariableDeclaration(node -> string, $<intValue>3, $<node>5 -> value);
													}
													free($<node>5);
												 }
variableDeclaration:
									 VAR IDENTIFIER type {
									 	// Check if there's already an identical identifier name in the current symbol table
									 	if (lookUpInThisScope($<identifierName>2) != NULL) {
											yyerrorForIdentifierDuplicated($<identifierName>2);
										}
										else {
											// Check if there's a type definition. If not, the default type is integer. 
											TableNode* node;
											if ($<intValue>3 != -1) {
												node = insert($<identifierName>2, $<intValue>3, -1, NULL, 0, 0, 0);
												printZeroToInitializeIt($<intValue>3);
											}
											else {
												node = insert($<identifierName>2, NODE_INT, -1, NULL, 0, 0, 0);
												printZeroToInitializeIt(NODE_INT);
											}
											printLocalVariableDeclaration(node -> index);
										}
									 }
									 | VAR IDENTIFIER type '=' expression {
									 	// Check if there's a type definition. If not, its type is recognized from constantExpression
									 	if ($<intValue>3 == -1) {
											$<intValue>3 = $<intValue>5;
										}
										// Check if the type is matched, then check if there's already an identical identifier name in the current symbol table
										if ($<intValue>3 != $<intValue>5) {
											yyerror("Type not matched.");
										}
										else if (lookUpInThisScope($<identifierName>2) != NULL) {
											yyerrorForIdentifierDuplicated($<identifierName>2);
										}
										else {
											TableNode* node = insert($<identifierName>2, $<intValue>3, -1, NULL, 0, 0, 0);
											printLocalVariableDeclaration(node -> index);
										}
									 }
									 | VAR IDENTIFIER ':' TYPE '[' INTEGER ']' {
									 	// Check if there's already an identical identifier name in the current symbol table
										if (lookUpInThisScope($<identifierName>2) != NULL) {
											yyerrorForIdentifierDuplicated($<identifierName>2);
										}
										else {
											insert($<identifierName>2, NODE_ARRAY, $<intValue>4, NULL, 0, 0, 0);
										}
									 }
									 ;
constantDeclaration:
									 VAL IDENTIFIER type '=' constantExpression {
									 	// Check if there's a type definition. If not, its type is recognized from constantExpression
									 	if ($<intValue>3 == -1) {
											$<intValue>3 = $<node>5 -> type;
										}
										// Check if the type is matched, then check if there's already an identical identifier name in the current symbol table
										if ($<intValue>3 != $<node>5 -> type) {
											yyerror("Type not matched.");
										}
										else if (lookUpInThisScope($<identifierName>2) != NULL) {
											yyerrorForIdentifierDuplicated($<identifierName>2);
										}
										else {
											insert($<identifierName>2, $<intValue>3, -1, NULL, 0, 1, $<node>5 -> value);
										}
										free($<node>5);
									 }
									 ;
functionDeclaration:
									 FUN functionIdentifier '(' formalArguments ')' ':' TYPE {
									 	// Check if there's already an identical identifier name in the current symbol table
									 	if (lookUpInThisScope($<identifierName>2) != NULL) {
											yyerrorForIdentifierDuplicated($<identifierName>2);
										}
										else {
											insert($<identifierName>2, NODE_FUNCTION_WITH_RETURN_VALUE, $<intValue>7, $<arguments>4 -> argumentTypes, $<arguments>4 -> argumentNum, 0, 0);
										}
										// Create a new symbol table for formalArguments and the following returnBlock
										createNewTable(0);
										// Get the arguments' definition from formalArguments and insert them into the current symbol table
										for (int i = 0; i < $<arguments>4 -> argumentNum; i++) {
											if (lookUpInThisScope($<arguments>4 -> argumentNames[i]) != NULL) {
												yyerrorForIdentifierDuplicated($<arguments>4 -> argumentNames[i]);
											}
											else {
												insert($<arguments>4 -> argumentNames[i], $<arguments>4 -> argumentTypes[i], -1, NULL, 0, 0, 0);
											}
										}
										printTheStartOfFunctionDeclaration($<identifierName>2, $<intValue>7, $<arguments>4);
									 } '{' block '}' {
										// Pop the current symbol table before leaving this scope
										popTable();
										printTheEndOfFunctionDeclaration(0);
									 }
									 | FUN functionIdentifier '(' ')' ':' TYPE {
									 	// Check if there's already an identical identifier name in the current symbol table
									 	if (lookUpInThisScope($<identifierName>2) != NULL) {
											yyerrorForIdentifierDuplicated($<identifierName>2);
										}
										else {
											insert($<identifierName>2, NODE_FUNCTION_WITH_RETURN_VALUE, $<intValue>6, NULL, 0, 0, 0);
										}
										// Create a new symbol table for the following returnBlock
										createNewTable(0);
										printTheStartOfFunctionDeclaration($<identifierName>2, $<intValue>6, NULL);
									 } '{' block '}' {
										// Pop the current symbol table before leaving this scope
									 	popTable();
										printTheEndOfFunctionDeclaration(0);
									 }
									 | FUN functionIdentifier '(' formalArguments ')' {
									 	// Check if there's already an identical identifier name in the current symbol table
									 	if (lookUpInThisScope($<identifierName>2) != NULL) {
											yyerrorForIdentifierDuplicated($<identifierName>2);
										}
										else {
											insert($<identifierName>2, NODE_FUNCTION_WITH_NO_RETURN_VALUE, -1, $<arguments>4 -> argumentTypes, $<arguments>4 -> argumentNum, 0, 0);
										}
										// Create a new symbol table for the following returnBlock
										createNewTable(0);
										// Get the arguments' definition from formalArguments and insert them into the current symbol table
										for (int i = 0; i < $<arguments>4 -> argumentNum; i++) {
											if (lookUpInThisScope($<arguments>4 -> argumentNames[i]) != NULL) {
												yyerrorForIdentifierDuplicated($<arguments>4 -> argumentNames[i]);
											}
											else {
												insert($<arguments>4 -> argumentNames[i], $<arguments>4 -> argumentTypes[i], -1, NULL, 0, 0, 0);
											}
										}
										printTheStartOfFunctionDeclaration($<identifierName>2, -1, $<arguments>4);
									 } '{' block '}' {
									 	// Pop the current symbol table before leaving this scope
										popTable();
										printTheEndOfFunctionDeclaration(1);
									 }
									 | FUN functionIdentifier '(' ')' {
									 	// Check if there's already an identical identifier name in the current symbol table
									 	if (lookUpInThisScope($<identifierName>2) != NULL) {
											yyerrorForIdentifierDuplicated($<identifierName>2);
										}
										else {
											insert($<identifierName>2, NODE_FUNCTION_WITH_NO_RETURN_VALUE, -1, NULL, 0, 0, 0);
										}
										// Create a new symbol table for the following returnBlock
										createNewTable(0);
										printTheStartOfFunctionDeclaration($<identifierName>2, -1, NULL);
									 } '{' block '}' {
									 	// Pop the current symbol table before leaving this scope
									 	popTable();
										printTheEndOfFunctionDeclaration(1);
									 }
									 ;
functionIdentifier:
									IDENTIFIER { $<identifierName>$ = $<identifierName>1; }
									;
formalArguments:
							 formalArguments ',' IDENTIFIER ':' TYPE {
							 	// Store all the arguments information and return it
							 	char** previousArgumentNames = $<arguments>1 -> argumentNames;
							 	int* previousArgumentTypes = $<arguments>1 -> argumentTypes;
							 	int previousArgumentNum = $<arguments>1 -> argumentNum;
								$<arguments>$ = (Arguments*)malloc(sizeof(Arguments));
							 	$<arguments>$ -> argumentNames = (char**)malloc(sizeof(char*) * (previousArgumentNum + 1));
							 	$<arguments>$ -> argumentTypes = (int*)malloc(sizeof(int) * (previousArgumentNum + 1));
								for (int i = 0; i < previousArgumentNum; i++) {
									$<arguments>$ -> argumentNames[i] = previousArgumentNames[i];
									$<arguments>$ -> argumentTypes[i] = previousArgumentTypes[i];
								}
								$<arguments>$ -> argumentNames[previousArgumentNum] = $<identifierName>3;
								$<arguments>$ -> argumentTypes[previousArgumentNum] = $<intValue>5;
								$<arguments>$ -> argumentNum = previousArgumentNum + 1;
								if (previousArgumentNames != NULL) {
									free(previousArgumentNames);
								}
								if (previousArgumentTypes != NULL) {
									free(previousArgumentTypes);
								}
								if ($<arguments>1 != NULL) {
									free($<arguments>1);
								}
							 }
							 | IDENTIFIER ':' TYPE {
							 	// Store the argument information and return it
							 	$<arguments>$ = (Arguments*)malloc(sizeof(Arguments));
								$<arguments>$ -> argumentNames = (char**)malloc(sizeof(char*));
								$<arguments>$ -> argumentTypes = (int*)malloc(sizeof(int));
								$<arguments>$ -> argumentNames[0] = $<identifierName>1;
								$<arguments>$ -> argumentTypes[0] = $<intValue>3;
								$<arguments>$ -> argumentNum = 1;
							 }
							 ;
block:
		 block statement
		 | statement
		 ;
statement:
				 variableDeclaration
				 | constantDeclaration
				 | simple
				 | conditional
				 | loop
				 | procedureInvocation
				 ;
simple:
			IDENTIFIER '=' expression {
				// Check if the identifier exists, and check if the type is not matched. 
				TableNode* tableNode = lookUpInEveryScope($<identifierName>1);
				if (tableNode == NULL) {
					yyerrorForIdentifierNotFound($<identifierName>1);
				}
				if (tableNode -> constant == 1) {
					yyerror("Constant can't be assigned.");
				}
				else if (tableNode -> type != $<intValue>3) {
					yyerror("Type not matched.");
				}
				printAssignVariable(tableNode);
			}
			| IDENTIFIER '[' expression ']' '=' expression {
				// Check if the identifier exists, and check if the type is not matched, and check if the identifier between '[' and ']' is an integer
				TableNode* tableNode = lookUpInEveryScope($<identifierName>1);
				if (tableNode == NULL) {
					yyerrorForIdentifierNotFound($<identifierName>1);
				}
				else if (tableNode -> type != NODE_ARRAY) {
					yyerror("Type not matched.");
				}
				else if ($<intValue>3 != NODE_INT) {
					yyerror("Type not matched.");
				}
				else if (tableNode -> subType != $<intValue>6) {
					yyerror("Type not matched.");
				}
			}
			| PRINT {
				printPreparationForPrint();
			} expression {
				printPrinting($<intValue>3, 0);
			}
			| PRINTLN {
				printPreparationForPrint();
			} expression {
				printPrinting($<intValue>3, 1);
			}
			| READ IDENTIFIER {
				// Check if the identifier exists
				TableNode* tableNode = lookUpInEveryScope($<identifierName>2);
				if (tableNode == NULL) {
					yyerrorForIdentifierNotFound($<identifierName>2);
				}
			}
			| RETURN expression {
				printReturnVariable();
			}
			| RETURN {
				printReturn();
			}
			;
expression:
					'-' expression %prec UMINUS {
					 $<intValue>$ = $<intValue>2;
					 printUminus();
				  }
					| expression operator rightExpression {
						// Check if the types of the two sides match
						if ($<intValue>1 != $<intValue>3) {
							yyerror("Type not matched.");
						}
						else {
							if ($<intValue>2 <= OPERATOR_REM) {
								$<intValue>$ = $<intValue>1;
							}
							else {
								$<intValue>$ = NODE_BOOL;
							}
						}
						printOperator($<intValue>2);
					}
					| '(' expression ')' {
						$<intValue>$ = $<intValue>2;
					}
					| expressionTerminal {
						$<intValue>$ = $<intValue>1;
					}
					;
rightExpression:
							 '-' expression %prec UMINUS {
							 	$<intValue>$ = $<intValue>2;
								printUminus();
							 }
							 | '(' expression ')' {
							 	$<intValue>$ = $<intValue>2;
							 }
							 | expressionTerminal {
							 	$<intValue>$ = $<intValue>1;
							 }
							 ;
constantExpression:
									'-' constantExpression %prec UMINUS {
									 $<node>$ = $<node>2;
									 $<node>$ -> value *= -1;
									}
									| constantExpression operator rightConstantExpression {
										// Check if the types of the two sides match
										if ($<node>1 -> type != $<node>3 -> type) {
											yyerror("Type not matched.");
										}
										else {
											int operator = $<intValue>2;
											$<node>$ = $<node>1;

											switch (operator) {
											case OPERATOR_ADD:
												$<node>$ -> value += $<node>3 -> value;
												break;

											case OPERATOR_SUB:
												$<node>$ -> value -= $<node>3 -> value;
												break;

											case OPERATOR_MUL:
												$<node>$ -> value *= $<node>3 -> value;
												break;

											case OPERATOR_DIV:
												$<node>$ -> value /= $<node>3 -> value;
												break;

											case OPERATOR_REM:
												$<node>$ -> value %= $<node>3 -> value;
												break;

											case OPERATOR_AND:
												$<node>$ -> value = $<node>$ -> value && $<node>3 -> value;
												$<node>$ -> type = NODE_BOOL;
												break;

											case OPERATOR_OR:
												$<node>$ -> value = $<node>$ -> value || $<node>3 -> value;
												$<node>$ -> type = NODE_BOOL;
												break;

											case OPERATOR_XOR:
												$<node>$ -> value = $<node>$ -> value != $<node>3 -> value;
												$<node>$ -> type = NODE_BOOL;
												break;

											case OPERATOR_LT:
												$<node>$ -> value = $<node>$ -> value < $<node>3 -> value;
												$<node>$ -> type = NODE_BOOL;
												break;

											case OPERATOR_GE:
												$<node>$ -> value = $<node>$ -> value >= $<node>3 -> value;
												$<node>$ -> type = NODE_BOOL;
												break;

											case OPERATOR_LE:
												$<node>$ -> value = $<node>$ -> value <= $<node>3 -> value;
												$<node>$ -> type = NODE_BOOL;
												break;

											case OPERATOR_EQ:
												$<node>$ -> value = $<node>$ -> value == $<node>3 -> value;
												$<node>$ -> type = NODE_BOOL;
												break;

											case OPERATOR_NE:
												$<node>$ -> value = $<node>$ -> value != $<node>3 -> value;
												$<node>$ -> type = NODE_BOOL;
												break;

											case OPERATOR_GT:
												$<node>$ -> value = $<node>$ -> value > $<node>3 -> value;
												$<node>$ -> type = NODE_BOOL;
												break;
											}
											free($<node>3);
										}
									}
									| '(' constantExpression ')' {
										$<node>$ = $<node>2;
									}
									| constantExpressionTerminal {
										$<node>$ = $<node>1;
									}
									;
rightConstantExpression:
											 '-' constantExpression %prec UMINUS {
											 	$<node>$ = $<node>2;
												$<node>$ -> value *= -1;
											 }
											 | '(' constantExpression ')' {
											 	$<node>$ = $<node>2;
											 }
											 | constantExpressionTerminal {
											 	$<node>$ = $<node>1;
											 }
											 ;
operator:
				 '+' { $<intValue>$ = OPERATOR_ADD; }
				 | '-' { $<intValue>$ = OPERATOR_SUB; }
				 | '*' { $<intValue>$ = OPERATOR_MUL; }
				 | '/' { $<intValue>$ = OPERATOR_DIV; }
				 | '%' { $<intValue>$ = OPERATOR_REM; }
				 | '&' { $<intValue>$ = OPERATOR_AND; }
				 | '|' { $<intValue>$ = OPERATOR_OR; }
				 | '!' { $<intValue>$ = OPERATOR_XOR; }
				 | '<' { $<intValue>$ = OPERATOR_LT; }
				 | GE { $<intValue>$ = OPERATOR_GE; }
				 | LE { $<intValue>$ = OPERATOR_LE; }
				 | EQ { $<intValue>$ = OPERATOR_EQ; }
				 | NE { $<intValue>$ = OPERATOR_NE; }
				 | '>' { $<intValue>$ = OPERATOR_GT; }
				 ;
expressionTerminal:
									value {
										$<intValue>$ = $<node>1 -> type;
										if ($<node>1 -> type == NODE_STRING) {
											printLoadingString($<node>1 -> stringValue);
										} else {
											printValue($<node>1 -> type, $<node>1 -> value);
										}
									}
									| IDENTIFIER {
										// Check if the identifier exists
										TableNode* tableNode = lookUpInEveryScope($<identifierName>1);
										if (tableNode == NULL) {
											yyerrorForIdentifierNotFound($<identifierName>1);
										}
										else {
											$<intValue>$ = tableNode -> type;
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
									| functionInvocation {
										// Check if the function has a return type
										if ($<intValue>1 == -1) {
											yyerror("This function doesn't return a value.");
										}
										else {
											$<intValue>$ = $<intValue>1;
										}
									} // IT NEEDS TO BE A FUNCTION THAT HAS A RETURN VALUE
									| arrayReference {
										$<intValue>$ = $<intValue>1;
									}
									;
constantExpressionTerminal:
													value {
														$<node>$ = $<node>1;
													}
													| IDENTIFIER {
														// Check if the identifier exists, and it is a constant
														TableNode* tableNode = lookUpInEveryScope($<identifierName>1);
														if (tableNode == NULL) {
															yyerrorForIdentifierNotFound($<identifierName>1);
														}
														else {
															if (tableNode -> constant != 1) {
																yyerror("You can only use constant expression to declare a \"var\" or \"val\".");
															}
															$<node>$ = (ParameterNode*)malloc(sizeof(ParameterNode));
															$<node>$ -> type = tableNode -> type;
															$<node>$ -> value = tableNode -> constantValue;
														}
													}
													;
functionInvocation:
									IDENTIFIER '(' functionInvocationArguments ')' {
										// Check if the identifier exists, and it's a function
										TableNode* tableNode = lookUpInEveryScope($<identifierName>1);
										if (tableNode == NULL) {
											yyerrorForIdentifierNotFound($<identifierName>1);
										}
										else if (tableNode -> type != NODE_FUNCTION_WITH_NO_RETURN_VALUE && tableNode -> type != NODE_FUNCTION_WITH_RETURN_VALUE) {
											yyerrorForIdentifierNotFunction($<identifierName>1);
										}
										else {
											// If it's a function with a return type, return its return type. If not, return -1. 
											if (tableNode -> type == NODE_FUNCTION_WITH_RETURN_VALUE) {
												$<intValue>$ = tableNode -> subType;
											}
											else {
												$<intValue>$ = -1;
											}
											// Check if the number of arguments is correct
											if ($<arguments>3 -> argumentNum != tableNode -> argumentNum) {
												yyerror("Number of arguments doesn't match.");
											}
											else {
												// Check if the types of arguments are correct
												int matched = 1;
												for (int i = 0; i < $<arguments>3 -> argumentNum; i++) {
													if ($<arguments>3 -> argumentTypes[i] != tableNode -> argumentTypes[i]) {
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
										if ($<arguments>3 -> argumentTypes != NULL) {
											free($<arguments>3 -> argumentTypes);
										}
										if ($<arguments>3 != NULL) {
											free($<arguments>3);
										}
										printInvocationOfFunction(tableNode -> string, tableNode -> subType, tableNode -> argumentTypes, tableNode -> argumentNum);
									}
									| IDENTIFIER '(' ')' {
										// Check if the identifier exists, and it's a function
										TableNode* tableNode = lookUpInEveryScope($<identifierName>1);
										if (tableNode == NULL) {
											yyerrorForIdentifierNotFound($<identifierName>1);
										}
										else if (tableNode -> type != NODE_FUNCTION_WITH_NO_RETURN_VALUE && tableNode -> type != NODE_FUNCTION_WITH_RETURN_VALUE) {
											yyerrorForIdentifierNotFunction($<identifierName>1);
										}
										else {
											// If it's a function with return type, return its return type. If not, return -1. 
											if (tableNode -> type == NODE_FUNCTION_WITH_RETURN_VALUE) {
												$<intValue>$ = tableNode -> subType;
											}
											else {
												$<intValue>$ = -1;
											}
											// If the number of arguments is not 0, error
											if (tableNode -> argumentNum != 0) {
												yyerror("Number of arguments doesn't match.");
											}
										}
									}
									;
functionInvocationArguments:
													 functionInvocationArguments ',' expression {
														// Store the arguments information and return it
														int* previousArgumentTypes = $<arguments>1 -> argumentTypes;
														int previousArgumentNum = $<arguments>1 -> argumentNum;
														$<arguments>$ = (Arguments*)malloc(sizeof(Arguments));
														$<arguments>$ -> argumentTypes = (int*)malloc(sizeof(int) * (previousArgumentNum + 1));
														for (int i = 0; i < previousArgumentNum; i++) {
															$<arguments>$ -> argumentTypes[i] = previousArgumentTypes[i];
														}
														$<arguments>$ -> argumentTypes[previousArgumentNum] = $<intValue>3;
														$<arguments>$ -> argumentNum = previousArgumentNum + 1;
														if (previousArgumentTypes != NULL) {
															free(previousArgumentTypes);
														}
														if ($<arguments>1 != NULL) {
															free($<arguments>1);
														}
													 }
													 | expression {
														// Store the arguments information and return it
														$<arguments>$ = (Arguments*)malloc(sizeof(Arguments));
														$<arguments>$ -> argumentTypes = (int*)malloc(sizeof(int));
														$<arguments>$ -> argumentTypes[0] = $<intValue>1;
														$<arguments>$ -> argumentNum = 1;
													 }
													 ;
													 ;
arrayReference:
							IDENTIFIER '[' expression ']' {
								// Check if the identifier exists, and it's an array
								TableNode* tableNode = lookUpInEveryScope($<identifierName>1);
								if (tableNode == NULL) {
									yyerrorForIdentifierNotFound($<identifierName>1);
								}
								else if (tableNode -> type != NODE_ARRAY) {
									yyerrorForIdentifierNotArray($<identifierName>1);
								}
								else {
									// Return its sub type
									$<intValue>$ = tableNode -> subType;
									// Check if the type of expression is integer
									if ($<intValue>3 != NODE_INT) {
										yyerror("Array needs a integer between its brackets.");
									}
								}
							} // NEED TO CHECK IF THIS EXPRESSION IS INTEGER
							;
conditional:
					 IF {
					 	printPreparationForIf();
					 } ifRest
					 ;
ifRest:
			'(' condition ')' simpleOrBlock {
				// Check if the type of expression is bool
				if ($<intValue>2 != NODE_BOOL) {
					yyerror("\"if\" needs a Boolean in its brackets.");
				}
				printConditionElseFlag();
				printConditionRestFlag();
			} // NEED TO CHECK IF THIS EXPRESSION IS BOOLEAN
			| '(' condition ')' simpleOrBlock {
				printConditionElseFlag();
			} ELSE simpleOrBlock {
				// Check if the type of expression is bool
				if ($<intValue>2 != NODE_BOOL) {
					yyerror("\"if\" needs a Boolean in its brackets.");
				}
				printConditionRestFlag();
				printNOP();
			}
loop:
		WHILE {
			printNOP();
			printWhileLoopBeginFlag();
		} '(' condition ')' simpleOrBlock {
			// Check if the type of expression is bool
			if ($<intValue>4 != NODE_BOOL) {
				yyerror("\"while\" needs a Boolean in its brackets.");
		 	}
			printGotoWhileLoopBeginFlag();
			printConditionElseFlag();
			printConditionRestFlag();
			printNOP();
		}
		| FOR '(' IDENTIFIER {
			// Create a new symbol table for the identifier in the loop for
			createNewTable(0);
			// Check if the identifer exists (It shouldn't exist actually, because this is a new symbol table)
			TableNode* tableNode = lookUpInThisScope($<identifierName>3);
			if (tableNode != NULL) {
				yyerrorForIdentifierDuplicated($<identifierName>3);
			}
			else {
				tableNode = insert($<identifierName>3, NODE_INT, -1, NULL, 0, 0, 0);
			}
			$<intValue>$ = tableNode -> index;
		} IN expression {
			printBetweenForLoopStartingNumAndEndingNum($<intValue>4);
		} DD expression {
			printAfterForLoopStartingNumAndEndingNum($<intValue>4);
		} ')' simpleOrBlock {
			// Pop the current symbol table
			popTable();
			printTheEndOfTrueFlagSectionOfForLoop($<intValue>4);
			printConditionElseFlag();
			printConditionRestFlag();
			printNOP();
		};
simpleOrBlock: {
							// Create a new symbol table because it has entering new scope
						 	createNewTable(0);
						 } simple {
						 	// Pop the current symbol table because it is leaving this scope
						 	popTable();
						 }
						 | {
							// Create a new symbol table because it has entering new scope
						 	createNewTable(0);
						 } '{' block '}' {
						 	// Pop the current symbol table because it is leaving this scope
						 	popTable();
						 }
						 ;
procedureInvocation:
									 functionInvocation // NO LIMIT
									 ;
condition: expression {
				 	$<intValue>$ = $<intValue>1;
					printCondition();
				 };
type:
		':' TYPE {
			$$ = $<intValue>2;
		}
		| {
			$$ = -1;
		}
		;
value:
		 INTEGER {
		 	$<node>$ = (ParameterNode*)malloc(sizeof(ParameterNode));
			$<node>$ -> type = NODE_INT;
			$<node>$ -> value = $<intValue>1;
		 }
		 | BOOLEAN {
		 	$<node>$ = (ParameterNode*)malloc(sizeof(ParameterNode));
			$<node>$ -> type = NODE_BOOL;
			$<node>$ -> value = $<boolValue>1;
		 }
		 | STRING {
		 	$<node>$ = (ParameterNode*)malloc(sizeof(ParameterNode));
			$<node>$ -> type = NODE_STRING;
			$<node>$ -> stringValue = $<stringValue>1;
		 }
%%
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
