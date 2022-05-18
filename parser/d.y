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
%type <intValue> type returnBlock
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

int yylex(void);
int sym[26];

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

// This is the structure of basic unit in symbol table
typedef struct TN {
	char* string;
	int type;
	int subType;
	int* argumentTypes;
	int argumentNum;
	int constant;
	struct TN* next;
} TableNode;

// Insert a new identifier and its information into the current symbol table
void insert(const char* key, int type, int subType, int* argumentTypes, int argumentNum, int constant);

// Look up a key in the current symbol table, and return its TableNode
TableNode* lookUpInThisScope(const char* key);

// Look up a key in every symbol table, and return its TableNode
TableNode* lookUpInEveryScope(const char* key);

// Create a new symbol table, and connect it to the previous symbol table
void createNewTable();

// Pop the current symbol table, and disconnect it from the previous symbol table
void popTable();

// Print out the current symbol table (For testing)
void printOneTable();

// Print out every symbol table (For testing)
void printAllTables();

// Initialize the scanner
void initScanner();

// For counting the number of lines so far
int lineCount;
%}
%%
program:
			 CLASS classIdentifier {
			 	// Create a new symbol table befoer entering the classBlock
			 	createNewTable();
			 } '{' classBlock '}' {
				// Pop a symbol table before leaving the classBlock
				popTable();
			 }
			 ;
classIdentifier:
							 IDENTIFIER { 
							 	// Insert the class identifier into the current symbol table
								if (strcmp($<identifierName>1, "main") != 0) {
									yyerror("A program needs a class \"main\"");
								}
								insert($<identifierName>1, NODE_CLASS, -1, NULL, 0, 0); 
							 }
							 ;
classBlock:
					variableDeclaration classBlock
					| constantDeclaration classBlock
					| functionDeclaration classBlock
					|
					;
variableDeclaration:
									 VAR IDENTIFIER type {
									 	// Check if there's already an identical identifier name in the current symbol table
									 	if (lookUpInThisScope($<identifierName>2) != NULL) {
											yyerrorForIdentifierDuplicated($<identifierName>2);
										}
										else {
											// Check if there's a type definition. If not, the default type is integer. 
											if ($<intValue>3 != -1) {
												insert($<identifierName>2, $<intValue>3, -1, NULL, 0, 0);
											}
											else {
												insert($<identifierName>2, NODE_INT, -1, NULL, 0, 0);
											}
										}
									 }
									 | VAR IDENTIFIER type '=' constantExpression {
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
											insert($<identifierName>2, $<intValue>3, -1, NULL, 0, 0);
										}
									 }
									 | VAR IDENTIFIER ':' TYPE '[' INTEGER ']' {
									 	// Check if there's already an identical identifier name in the current symbol table
										if (lookUpInThisScope($<identifierName>2) != NULL) {
											yyerrorForIdentifierDuplicated($<identifierName>2);
										}
										else {
											insert($<identifierName>2, NODE_ARRAY, $<intValue>4, NULL, 0, 0);
										}
									 }
									 ;
constantDeclaration:
									 VAL IDENTIFIER type '=' constantExpression {
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
											insert($<identifierName>2, $<intValue>3, -1, NULL, 0, 1);
										}
									 }
									 ;
functionDeclaration:
									 FUN functionIdentifier '(' formalArguments ')' ':' TYPE {
									 	// Check if there's already an identical identifier name in the current symbol table
									 	if (lookUpInThisScope($<identifierName>2) != NULL) {
											yyerrorForIdentifierDuplicated($<identifierName>2);
										}
										else {
											insert($<identifierName>2, NODE_FUNCTION_WITH_RETURN_VALUE, $<intValue>7, $<arguments>4 -> argumentTypes, $<arguments>4 -> argumentNum, 0);
										}
										// Create a new symbol table for formalArguments and the following returnBlock
										createNewTable();
										// Get the arguments' definition from formalArguments and insert them into the current symbol table
										for (int i = 0; i < $<arguments>4 -> argumentNum; i++) {
											if (lookUpInThisScope($<arguments>4 -> argumentNames[i]) != NULL) {
												yyerrorForIdentifierDuplicated($<arguments>4 -> argumentNames[i]);
											}
											else {
												insert($<arguments>4 -> argumentNames[i], $<arguments>4 -> argumentTypes[i], -1, NULL, 0, 0);
											}
										}
									 } '{' returnBlock '}' {
									 	// Check if there's a type definition. If not, its type is recognized from returnBlock
									 	if ($<intValue>7 == -1) {
											$<intValue>7 = $<intValue>10;
										}
										// Check if the type definition is the same as returnBlock
										if ($<intValue>7 != $<intValue>10) {
											yyerror("Function return type not matched. ");
										}
										// Pop the current symbol table before leaving this scope
										popTable();
									 }
									 | FUN functionIdentifier '(' ')' ':' TYPE {
									 	// Check if there's already an identical identifier name in the current symbol table
									 	if (lookUpInThisScope($<identifierName>2) != NULL) {
											yyerrorForIdentifierDuplicated($<identifierName>2);
										}
										else {
											insert($<identifierName>2, NODE_FUNCTION_WITH_RETURN_VALUE, $<intValue>6, NULL, 0, 0);
										}
										// Create a new symbol table for the following returnBlock
										createNewTable();
									 } '{' returnBlock '}' {
									 	// Check if there's a type definition. If not, its type is recognized from returnBlock
									 	if ($<intValue>6 == -1) {
											$<intValue>6 = $<intValue>9;
										}
										// Check if the type definition is the same as returnBlock
										if ($<intValue>6 != $<intValue>9) {
											yyerror("Function return type not matched. ");
										}
										// Pop the current symbol table before leaving this scope
									 	popTable();
									 }
									 | FUN functionIdentifier '(' formalArguments ')' {
									 	// Check if there's already an identical identifier name in the current symbol table
									 	if (lookUpInThisScope($<identifierName>2) != NULL) {
											yyerrorForIdentifierDuplicated($<identifierName>2);
										}
										else {
											insert($<identifierName>2, NODE_FUNCTION_WITH_NO_RETURN_VALUE, -1, $<arguments>4 -> argumentTypes, $<arguments>4 -> argumentNum, 0);
										}
										// Create a new symbol table for the following returnBlock
										createNewTable();
										// Get the arguments' definition from formalArguments and insert them into the current symbol table
										for (int i = 0; i < $<arguments>4 -> argumentNum; i++) {
											if (lookUpInThisScope($<arguments>4 -> argumentNames[i]) != NULL) {
												yyerrorForIdentifierDuplicated($<arguments>4 -> argumentNames[i]);
											}
											else {
												insert($<arguments>4 -> argumentNames[i], $<arguments>4 -> argumentTypes[i], -1, NULL, 0, 0);
											}
										}
									 } '{' block '}' {
									 	// Pop the current symbol table before leaving this scope
										popTable();
									 }
									 | FUN functionIdentifier '(' ')' {
									 	// Check if there's already an identical identifier name in the current symbol table
									 	if (lookUpInThisScope($<identifierName>2) != NULL) {
											yyerrorForIdentifierDuplicated($<identifierName>2);
										}
										else {
											insert($<identifierName>2, NODE_FUNCTION_WITH_NO_RETURN_VALUE, -1, NULL, 0, 0);
										}
										// Create a new symbol table for the following returnBlock
										createNewTable();
									 } '{' block '}' {
									 	// Pop the current symbol table before leaving this scope
									 	popTable();
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
returnBlock:
					 block RETURN expression block {
					 	$$ = $<intValue>3;
					 }
					 | block RETURN expression  {
					 	$$ = $<intValue>3;
					 }
					 | RETURN expression {
					 	$$ = $<intValue>2;
					 }
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
				else if (tableNode -> type != $<intValue>3) {
					yyerror("Type not matched.");
				}
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
			| PRINT expression
			| PRINTLN expression
			| READ IDENTIFIER {
				// Check if the identifier exists
				TableNode* tableNode = lookUpInEveryScope($<identifierName>2);
				if (tableNode == NULL) {
					yyerrorForIdentifierNotFound($<identifierName>2);
				}
			}
			| RETURN expression
			| RETURN
			;
expression:
					'-' expression %prec UMINUS {
					 $<intValue>$ = $<intValue>2;
				  }
					| expression operator rightExpression {
						// Check if the types of the two sides match
						if ($<intValue>1 != $<intValue>3) {
							yyerror("Type not matched.");
						}
						else {
							// If the operator return -1, it means the return value of this expression is the same as the type of the two sides
							if ($<intValue>2 != -1) {
								$<intValue>$ = $<intValue>2;
							}
							else {
								$<intValue>$ = $<intValue>1;
							}
						}
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
									 $<intValue>$ = $<intValue>2;
									}
									| constantExpression operator rightConstantExpression {
										// Check if the types of the two sides match
										if ($<intValue>1 != $<intValue>3) {
											yyerror("Type not matched.");
										}
										else {
											// If the operator return -1, it means the type of this expression is the same as the types of the two sides
											if ($<intValue>2 != -1) {
												$<intValue>$ = $<intValue>2;
											}
											else {
												$<intValue>$ = $<intValue>1;
											}
										}
									}
									| '(' constantExpression ')' {
										$<intValue>$ = $<intValue>2;
									}
									| constantExpressionTerminal {
										$<intValue>$ = $<intValue>1;
									}
									;
rightConstantExpression:
											 '-' constantExpression %prec UMINUS {
											 	$<intValue>$ = $<intValue>2;
											 }
											 | '(' constantExpression ')' {
											 	$<intValue>$ = $<intValue>2;
											 }
											 | constantExpressionTerminal {
											 	$<intValue>$ = $<intValue>1;
											 }
											 ;
operator:
				 '+' { $<intValue>$ = -1; }
				 | '-' { $<intValue>$ = -1; }
				 | '*' { $<intValue>$ = -1; }
				 | '/' { $<intValue>$ = -1; }
				 | '!' { $<intValue>$ = NODE_BOOL; }
				 | '&' { $<intValue>$ = NODE_BOOL; }
				 | '|' { $<intValue>$ = NODE_BOOL; }
				 | '<' { $<intValue>$ = NODE_BOOL; }
				 | GE { $<intValue>$ = NODE_BOOL; }
				 | LE { $<intValue>$ = NODE_BOOL; }
				 | EQ { $<intValue>$ = NODE_BOOL; }
				 | NE { $<intValue>$ = NODE_BOOL; }
				 | '>' { $<intValue>$ = NODE_BOOL; }
				 ;
expressionTerminal:
									value {
										$<intValue>$ = $<intValue>1;
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
														$<intValue>$ = $<intValue>1;
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
															$<intValue>$ = tableNode -> type;
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
					 IF '(' expression ')' simpleOrBlock {
					 	// Check if the type of expression is bool
					 	if ($<intValue>3 != NODE_BOOL) {
							yyerror("\"if\" needs a Boolean in its brackets.");
						}
					 } // NEED TO CHECK IF THIS EXPRESSION IS BOOLEAN
					 | IF '(' expression ')' simpleOrBlock ELSE simpleOrBlock {
					 	// Check if the type of expression is bool
					 	if ($<intValue>3 != NODE_BOOL) {
							yyerror("\"if\" needs a Boolean in its brackets.");
						}
					 }
					 ;
loop:
		WHILE '(' expression ')' simpleOrBlock {
			// Check if the type of expression is bool
			if ($<intValue>3 != NODE_BOOL) {
				yyerror("\"while\" needs a Boolean in its brackets.");
		 	}
		} 
		| FOR '(' IDENTIFIER IN INTEGER DD INTEGER ')' {
			// Create a new symbol table for the identifier in the loop for
			createNewTable();
			// Check if the identifer exists (It shouldn't exist actually, because this is a new symbol table)
			TableNode* tableNode = lookUpInThisScope($<identifierName>3);
			if (tableNode != NULL) {
				yyerrorForIdentifierDuplicated($<identifierName>3);
			}
			else {
				insert($<identifierName>3, NODE_INT, -1, NULL, 0, 0);
			}
		} simpleOrBlock {
			// Pop the current symbol table
			popTable();
		}
		;
simpleOrBlock: {
							// Create a new symbol table because it has entering new scope
						 	createNewTable();
						 } simple {
						 	// Pop the current symbol table because it is leaving this scope
						 	popTable();
						 }
						 | {
							// Create a new symbol table because it has entering new scope
						 	createNewTable();
						 } '{' block '}' {
						 	// Pop the current symbol table because it is leaving this scope
						 	popTable();
						 }
						 ;
procedureInvocation:
									 functionInvocation // NO LIMIT
									 ;
type:
		':' TYPE {
			$$ = $<intValue>2;
		}
		| {
			$$ = -1;
		}
		;
value:
		 INTEGER { $<intValue>$ = NODE_INT; }
		 | FLOAT { $<intValue>$ = NODE_FLOAT; }
		 | BOOLEAN { $<intValue>$ = NODE_BOOL; }
		 | STRING { $<intValue>$ = NODE_STRING; }
%%
void yyerror(char *s) {
	fprintf(stderr, "%s (Line: %d)\n", s, lineCount);
}
void yyerrorForIdentifierDuplicated(char* identifierName) {
	fprintf(stderr, "Identifier \"%s\" already exists. (Line: %d)\n", identifierName, lineCount);
}
void yyerrorForIdentifierNotFound(char* identifierName) {
	fprintf(stderr, "Identifier \"%s\" not found. (Line: %d)\n", identifierName, lineCount);
}
void yyerrorForIdentifierNotFunction(char* identifierName) {
	fprintf(stderr, "Identifier \"%s\" is not a function. (Line: %d)\n", identifierName, lineCount);
}
void yyerrorForIdentifierNotArray(char* identifierName) {
	fprintf(stderr, "Identifier \"%s\" is not a array. (Line: %d)\n", identifierName, lineCount);
}
int main(void) {
	initScanner();
	yyparse();
	return 0;
}
