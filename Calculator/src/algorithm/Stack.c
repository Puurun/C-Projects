#include "Stack.h"
#include <string.h>
#include <stdlib.h>

Stack StackInit(void){
	int i=0;
	Stack _Stack = (Stack)malloc(sizeof(struct __stack));
	for(i=0; i<MAX_STACK_SIZE; i++){
		_Stack->stack[i] = (char*)malloc(sizeof(char) * MAX_STRING_LEN);
	}
	_Stack->len = 0;
	return _Stack;
}

Stack StackPush(Stack _Stack, char* str){
	strcpy(_Stack->stack[_Stack->len], str);
	(_Stack->len) += 1;
	return _Stack;
}

char* StackPop(Stack _Stack){
	char *last = _Stack->stack[_Stack->len - 1];
	(_Stack->len) -= 1;
	return last;
}

char* StackTop(Stack _Stack){
	if(_Stack->len == 0){
		return NULL;
	}
	return _Stack->stack[_Stack->len-1];
}

int StackDel(Stack _Stack){
	int i=0;
	for(i=0; i<MAX_STACK_SIZE; i++){
		free(_Stack->stack[i]);
	}
	free(_Stack);
	return 1;
}


int StackLen(Stack _Stack){
	return _Stack->len;
}

int StackEmpty(Stack _Stack){
	if(_Stack->len == 0){
		return True;
	}
	return False;
}

