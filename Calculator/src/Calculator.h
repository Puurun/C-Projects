#ifndef __Calculator__
#define __Calculator__


char* GetInput(void);
int PostFixEquation(char* eq);
int isOperator(char c);
int isWhiteSpace(char c);

#endif