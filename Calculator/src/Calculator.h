#ifndef __Calculator__
#define __Calculator__


char* GetInput(void);
void PostFixEquation(char* eq);

int OperatorPriority(char* opt1, char* opt2);
int CheckOperator(char opt);


int isOperator(char c);
int isWhiteSpace(char c);

#endif