%{
#include <stdlib.h>
#include "y.tab.h"
void yyerror(char *);
int maxTempStringLength = 10;
int currentTempStringLength = 0;
char* tempString;
void initScanner(void);
void initTempString(void);
void extendTempString(void);

#define TABLE_SIZE 256
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL
#define NODE_INT 0
#define NODE_FLOAT 1
#define NODE_BOOL 2
#define NODE_STRING 3
#define NODE_ARRAY 4
#define NODE_FUNCTION_WITH_NO_RETURN_VALUE 5
#define NODE_FUNCTION_WITH_RETURN_VALUE 6
#define NODE_CLASS 7

typedef struct TN {
	char* string;
	int type;
	int subType;
	int* argumentTypes;
	int argumentNum;
	int constant;
	struct TN* next;
} TableNode;

typedef struct ST {
	TableNode** table;
	struct ST* next;
	struct ST* previous;
} SymbolTable;

SymbolTable* symbolTable;

long long int hash(const char* key);
TableNode* lookUpInThisScope(const char* key);
TableNode* lookUpInEveryScope(const char* key);
void insert(const char* key, int type, int subType, int* argumentTypes, int argumentNum, int constant);
void createNewTable();
void popTable();
void printOneTable();
void printAllTables();

int lineCount;
%}
%Start STRING_MODE COMMAND_MODE_1 COMMAND_MODE_2
%%
<STRING_MODE>\"\"					{
														if (currentTempStringLength + 1 >= maxTempStringLength) {
															extendTempString();
														}
														tempString[currentTempStringLength + 1] = '\"';
														currentTempStringLength++;
													}
<STRING_MODE>\"						{
														BEGIN 0;
														tempString[currentTempStringLength + 1] = '\0';
														yylval.stringValue = tempString;
														return STRING; 
													}
<STRING_MODE>[^\"]*				{
														int yytextLength = strlen(yytext);
														while (currentTempStringLength + yytextLength >= maxTempStringLength) {
															extendTempString();
														}
														if (tempString[0] == '\0') {
															for (int i = 0; i < yytextLength; i++) {
																tempString[i] = yytext[i];
															}
														}
														else {
															for (int i = 0; i < yytextLength; i++) {
																tempString[currentTempStringLength + i + 1] = yytext[i];
															}
														}
														currentTempStringLength += yytextLength;

														// Check how many lines does it have
														for (int i = 0; i < strlen(yytext); i++) {
															if (yytext[i] == '\n') {
																lineCount++;
															}
														}
													}
<COMMAND_MODE_1>[^\n]*		;
<COMMAND_MODE_1>"\n"			{ BEGIN 0; lineCount++; }
<COMMAND_MODE_2>[^*]*			{
														// Check how many lines does it have
														for (int i = 0; i < strlen(yytext); i++) {
															if (yytext[i] == '\n') {
																lineCount++;
															}
														}
													}
<COMMAND_MODE_2>"*"				;
<COMMAND_MODE_2>"*/"			{ BEGIN 0; }
"class"										{ return CLASS; }
"fun"											{ return FUN; }
"var"											{ return VAR; }
"val"											{ return VAL; }
"print"										{ return PRINT; }
"println"									{ return PRINTLN; }
"read"										{ return READ; }
"return"									{ return RETURN; }
"if"											{ return IF; }
"else"										{ return ELSE; }
"for"											{ return FOR; }
"while"										{ return WHILE; }
"in"											{ return IN; }
"int"											|
"integer"									{ yylval.type = NODE_INT; return TYPE; }
"float"										{ yylval.type = NODE_FLOAT; return TYPE; }
"bool"										|
"boolean"									{ yylval.type = NODE_BOOL; return TYPE; }
"string"									{ yylval.type = NODE_STRING; return TYPE; }
"0"												{ yylval.intValue = atoi(yytext); return INTEGER; }
[1-9][0-9]*  							{ yylval.intValue = atoi(yytext); return INTEGER; }
[1-9][0-9]*\.[0-9]+				{ yylval.floatValue = atof(yytext); return FLOAT; }
"true"										{ yylval.boolValue = 1; return BOOLEAN; }
"false"										{ yylval.boolValue = 0; return BOOLEAN; }
\"												{ BEGIN STRING_MODE; initTempString(); }
"//"											{ BEGIN COMMAND_MODE_1; }
"/*"											{ BEGIN COMMAND_MODE_2; }
[a-zA-Z][a-zA-Z0-9]*			{ 
														yylval.identifierName = (char*)malloc(sizeof(char) * (strlen(yytext) + 1)); 
														for (int i = 0; i < strlen(yytext); i++) {
															yylval.identifierName[i] = yytext[i];
														}
														yylval.identifierName[strlen(yytext)] = '\0';
														return IDENTIFIER; 
													}
"{"												{ return *yytext; }
"}"												{ return *yytext; }
".."											{ return DD; }
[-+()=/*|&!:<>,\[\]]			{ return *yytext; }
"<="											{ return LE; }
">="											{ return GE; }
"=="											{ return EQ; }
"!="											{ return NE; }
[ \t]      								;
[\n]											{ lineCount++; }
"\r\n"										{ lineCount++; }
.               					{
														yyerror("invalid character");
													}
%%
void initTempString(void) {
	currentTempStringLength = 0;
	tempString[0] = '\0';
}
void extendTempString(void) {
	char* newString = (char*)malloc(sizeof(char) * maxTempStringLength * 2);
	for (int i = 0; i < maxTempStringLength; i++) {
		newString[i] = tempString[i];
	}
	free(tempString);
	tempString = newString;
	maxTempStringLength *= 2;
}
int yywrap(void) {
	return 1;
}
void initScanner(void) {
	tempString = (char*)malloc(sizeof(char) * maxTempStringLength);
	tempString[0] = '\0';
	symbolTable = (SymbolTable*)malloc(sizeof(SymbolTable));
	symbolTable -> table = (TableNode**)malloc(sizeof(TableNode*) * TABLE_SIZE);
	for (int i = 0; i < TABLE_SIZE; i++) {
		symbolTable -> table[i] = NULL;
	}
	symbolTable -> next = NULL;
	symbolTable -> previous = NULL;
	lineCount = 1;
}

// Return 64-bit FNV-1a hash for key (NUL-terminated). See description:
// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
long long int hash(const char* key)
{
	long long int hashValue = FNV_OFFSET;
	for (const char* p = key; *p; p++) {
		hashValue ^= (long long int)(unsigned char)(*p);
		hashValue *= FNV_PRIME;
	}
	return hashValue;
}

TableNode* lookUpInThisScope(const char* key) {
#ifdef DEBUG
	printf("Look Up this Scope for %s\n", key);
	printAllTables();
#endif
	long long int index = hash(key) % TABLE_SIZE;
	TableNode** table = symbolTable -> table;
	while(index < 0)
	{
		index += TABLE_SIZE;
	}
	if (table[index] != NULL)
	{
		TableNode* currentNode = table[index];
		if (strcmp(currentNode -> string, key) == 0)
		{
			return currentNode;
		}
		while(currentNode -> next != NULL)
		{
			currentNode = currentNode -> next;
			if (strcmp(currentNode -> string, key) == 0)
			{
				return currentNode;
			}
		}
	}
	return NULL;
}

TableNode* lookUpInEveryScope(const char* key) {
#ifdef DEBUG
	printf("Look Up Every Scope for %s\n", key);
	printAllTables();
	//printf("Start %s: \n", key);
#endif
	SymbolTable* currentSymbolTable = symbolTable;
	while (currentSymbolTable != NULL) {
		long long int index = hash(key) % TABLE_SIZE;
		TableNode** table = currentSymbolTable -> table;
		while(index < 0)
		{
			index += TABLE_SIZE;
		}
		if (table[index] != NULL)
		{
			TableNode* currentNode = table[index];
#ifdef DEBUG
			//printf("(%s, %s)\n", currentNode -> string, key);
#endif
			if (strcmp(currentNode -> string, key) == 0)
			{
				return currentNode;
			}
			while(currentNode -> next != NULL)
			{
				currentNode = currentNode -> next;
				if (strcmp(currentNode -> string, key) == 0)
				{
					return currentNode;
				}
			}
		}
		currentSymbolTable = currentSymbolTable -> previous;
	}
	return NULL;
}

void insert(const char* key, int type, int subType, int* argumentTypes, int argumentNum, int constant) {
#ifdef DEBUG
	printf("INSERT %s\n", key);
#endif
	long long int foundIndex = hash(key) % TABLE_SIZE;
	while(foundIndex < 0)
	{
		foundIndex += TABLE_SIZE;
	}
	TableNode* newNode = (TableNode*)malloc(sizeof(TableNode));
	newNode -> string = (char*)malloc(sizeof(char) * (strlen(key) + 1));
	newNode -> string[0] = '\0';
	newNode -> argumentTypes = argumentTypes;
	newNode -> argumentNum = argumentNum;
	newNode -> type = type;
	newNode -> subType = subType;
	newNode -> constant = constant;
	strcat(newNode -> string, key);
	newNode -> next = NULL;

	TableNode* currentNode = symbolTable -> table[foundIndex];
	if (currentNode != NULL)
	{
		while(currentNode -> next != NULL)
		{
			currentNode = currentNode -> next;
		}
		currentNode -> next = newNode;
	}
	else
	{
		symbolTable -> table[foundIndex] = newNode;
	}
}

void createNewTable() {
	SymbolTable* newTable = (SymbolTable*)malloc(sizeof(SymbolTable));
	newTable -> table = (TableNode**)malloc(sizeof(TableNode*) * TABLE_SIZE);
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		newTable -> table[i] = NULL;
	}
	newTable -> next = NULL;
	symbolTable -> next = newTable;
	newTable -> previous = symbolTable;
	symbolTable = symbolTable -> next;
}

void popTable() {
	SymbolTable* poppedTable = symbolTable;
	symbolTable = symbolTable -> previous;
	for (int i = 0; i < TABLE_SIZE; i++) {
		while (poppedTable -> table[i] != NULL) {
			free(poppedTable -> table[i] -> string);
			free(poppedTable -> table[i] -> argumentTypes);
			TableNode* nextTable = poppedTable -> table[i] -> next;
			free(poppedTable -> table[i]);
			poppedTable -> table[i] = nextTable;
		}
	}
	free(poppedTable -> table);
	free(poppedTable);
}

void printOneTable(SymbolTable* symbolTable) {
	TableNode** table = symbolTable -> table;
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (table[i] != NULL) {
			TableNode* currentNode = table[i];
			while(currentNode != NULL) {
				printf("%s\n", currentNode -> string);
				currentNode = currentNode -> next;
			}
		}
	}
}

void printAllTables() {
	SymbolTable* currentSymbolTable = symbolTable;
	printf("\nTABLES: \n");
	printf("------------------------------\n");
	while(currentSymbolTable != NULL) {
		printOneTable(currentSymbolTable);
		currentSymbolTable = currentSymbolTable -> previous;
		printf("------------------------------\n");
	}
}
