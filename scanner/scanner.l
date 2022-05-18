%option noyywrap
%{
#define LIST     strcat(buf,yytext)
#define token(t) {LIST; printf("<%s>\n","t");}
#define tokenInteger(t,i) {LIST; printf("<%s:%d>\n","t",i);}
#define tokenString(t,s) {LIST; printf("<%s:%s>\n","t",s);}

#define MAX_LINE_LENG 256
#define TABLE_SIZE 256

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

int linenum = 1;
char buf[MAX_LINE_LENG];
char tempString[MAX_LINE_LENG];
static skipcmnts1();
static skipcmnts2();
static printBuf();

typedef struct N {
	char* string;
	struct N* next;
} node;

node** symbolTable;

long long int hash(const char* key);

static void create();
static long long int lookup(char* s);
static long long int insert(char* s);
static void dump();


%}

%Start NORMAL_MODE COMMAND_1_MODE COMMAND_2_MODE STRING_MODE REAL_MODE

%%
<NORMAL_MODE>"/*"																						{
																														LIST;
																														BEGIN COMMAND_1_MODE;
																														}
<COMMAND_1_MODE>"*/" 																				{
																														LIST;
																														BEGIN NORMAL_MODE;
																														}
<COMMAND_2_MODE>\n 																					{
																														BEGIN NORMAL_MODE;
																														unput(yytext[0]);
																														}
<COMMAND_2_MODE>.																						|
<COMMAND_1_MODE>. 																					{
																														LIST;
																														}
<NORMAL_MODE>"//"																						{
																														LIST;
																														BEGIN COMMAND_2_MODE;
																														}

<STRING_MODE>\"\"																						{
																														LIST;
																														int tempStringLength = strlen(tempString);
																														tempString[tempStringLength] = '\"';
																														tempString[tempStringLength + 1] = '\0';
																														}

<STRING_MODE>\"																							{
																														LIST;
																														printf("<string: %s>\n", tempString);
																														BEGIN NORMAL_MODE;
																														}

<STRING_MODE>.																							{
																														LIST;
																														int tempStringLength = strlen(tempString);
																														tempString[tempStringLength] = yytext[0];
																														tempString[tempStringLength + 1] = '\0';
																														}

<NORMAL_MODE>"->"																						|
<NORMAL_MODE>[,:;()\[\]{}] 																	|
<NORMAL_MODE>[\+\-*/%<>&|!=]																|
<NORMAL_MODE>"<="																						|
<NORMAL_MODE>">="																						|
<NORMAL_MODE>"=="																						|
<NORMAL_MODE>"!="																						|
<NORMAL_MODE>"+="																						|
<NORMAL_MODE>"-="																						|
<NORMAL_MODE>"*="																						|
<NORMAL_MODE>"/="																						{
																														LIST;
																														printf("<'%s'>\n", yytext);
																														}

<NORMAL_MODE>"bool"																					|
<NORMAL_MODE>"break"																				|
<NORMAL_MODE>"char"																					|
<NORMAL_MODE>"case"																					|
<NORMAL_MODE>"class"																				|
<NORMAL_MODE>"continue"																			|
<NORMAL_MODE>"declare"																			|
<NORMAL_MODE>"do"																						|
<NORMAL_MODE>"else"																					|
<NORMAL_MODE>"exit"																					|
<NORMAL_MODE>"false"																				|
<NORMAL_MODE>"float"																				|
<NORMAL_MODE>"for"																					|
<NORMAL_MODE>"fun"																					|
<NORMAL_MODE>"if"																						|
<NORMAL_MODE>"int"																					|
<NORMAL_MODE>"loop"																					|
<NORMAL_MODE>"print"																				|
<NORMAL_MODE>"println"																			|
<NORMAL_MODE>"return"																				|
<NORMAL_MODE>"string"																				|
<NORMAL_MODE>"true"																					|
<NORMAL_MODE>"val"																					|
<NORMAL_MODE>"var"																					|
<NORMAL_MODE>"while"																				{
																														LIST;
																														printf("<");
																														for (int i = 0; i < strlen(yytext); i++)
																														{
																															printf("%c", yytext[i] - 32);
																														}
																														printf(">\n");
																														}

<NORMAL_MODE>[A-Za-z][A-Za-z0-9]*														{
																														LIST;
																														insert(yytext);
																														printf("<id: %s>\n", yytext);
																														}

<NORMAL_MODE>0																							|
<NORMAL_MODE>[1-9][0-9]*																		{
																														LIST;
																														printf("<integer: %s>\n", yytext);
																														}

<NORMAL_MODE>"true"																					|
<NORMAL_MODE>"false"																				{
																														LIST;
																														printf("<boolean: %s>\n", yytext);
																														}

<NORMAL_MODE>\+?\-?[1-9][0-9]*\.[0-9]*E?										{
																														LIST;
																														if (buf[strlen(buf) - 1] == 'E')
																														{
																															BEGIN REAL_MODE;
																															tempString[0] = '\0';
																															strcat(tempString, yytext);
																														}
																														else
																														{
																															printf("<real: %s>\n", yytext);
																														}
																														}

<REAL_MODE>[1-9][0-9]*																			{
																														LIST;
																														strcat(tempString, yytext);
																														printf("<real: %s>\n", tempString);
																														BEGIN NORMAL_MODE;
																														}

<NORMAL_MODE>\"																							{
																														LIST;
																														BEGIN STRING_MODE;
																														tempString[0] = '\0';
																														}

\n      																										{
        																										LIST;
																														printBuf();
																														}

[ \t]*  																										{LIST;}

.       																										{
																														LIST;
																														printf("%d:%s\n", linenum+1, buf);
																														printf("bad character:'%s'\n",yytext);
																														exit(-1);
																														}
%%
int main()
{
	BEGIN NORMAL_MODE;
	create();
	yylex();
	printf("\n");
	dump();
}

static printBuf()
{
		printf("%d: %s", linenum++, buf);
		buf[0] = '\0';
}

static void create()
{
	symbolTable = (node**)malloc(sizeof(node*) * TABLE_SIZE);
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		symbolTable[i] = NULL;
	}
}

static long long int lookup(char* s)
{
	long long int index = hash(s) % TABLE_SIZE;
	while(index < 0)
	{
		index += TABLE_SIZE;
	}
	if (symbolTable[index] != NULL)
	{
		node* currentNode = symbolTable[index];
		if (strcmp(currentNode -> string, s) == 0)
		{
			return index;
		}
		while(currentNode -> next != NULL)
		{
			currentNode = currentNode -> next;
			if (strcmp(currentNode -> string, s) == 0)
			{
				return index;
			}
		}
	}
	return -1;
}

static long long int insert(char* s)
{
	long long int foundIndex = lookup(s);
	if (foundIndex == -1)
	{
		foundIndex = hash(s) % TABLE_SIZE;
		while(foundIndex < 0)
		{
			foundIndex += TABLE_SIZE;
		}
		node* newNode = (node*)malloc(sizeof(node));
		newNode -> string = (char*)malloc(sizeof(char) * MAX_LINE_LENG);
		newNode -> string[0] = '\0';
		strcat(newNode -> string, s);
		newNode -> next = NULL;

		node* currentNode = symbolTable[foundIndex];
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
			symbolTable[foundIndex] = newNode;
		}
	}
	return foundIndex;
}

static void dump()
{
	printf("Symbol Table:\n");
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		node* currentNode = symbolTable[i];
		while (currentNode != NULL)
		{
			printf("%s\n", currentNode -> string);
			node* lastNode = currentNode;
			currentNode = currentNode -> next;
			free(lastNode);
		}
	}
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
