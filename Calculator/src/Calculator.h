#ifndef __Calculator__
#define __Calculator__


int Calculate(void);

char* GetInput(void);
char** Tokenize(char* eq);
char** PostFixEquation(char** eq);
int CalculateEquation(char** eq);
void AllocateMemoryEquation(char** eq);

int OperatorPriority(char opt);
int CheckOperator(char opt);

int isDigit(char c);
int isOperator(char c);
int isWhiteSpace(char c);

#endif