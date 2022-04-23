#include "Stack.h"
#include <string.h>
#include <stdlib.h>

Stack* StackInit(void){
	Stack *_Stack = (Stack*)malloc(sizeof(Stack));
	_Stack->len = 0;
	return _Stack;
}

Stack* StackPush(Stack *_Stack, char* str){
	strcpy(_Stack->stack[_Stack->len], str);
	return _Stack;
}

char* StackPop(Stack *_Stack){
	char *last = _Stack->stack[_Stack->len - 1];
	_Stack->len -= 1;
	return last;
}

int isEmpty(Stack *_Stack){
	if(_Stack->len == 0){
		return True;
	}
	return False;
}

