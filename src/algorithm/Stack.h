#ifndef __STACK__
#define __STACK__

#define True 1
#define False 0
#define MAX_STACK_SIZE 500


typedef struct __stack {
	char *stack[MAX_STACK_SIZE];
	int len;
} __Stack__;
typedef __Stack__* Stack;
Stack StackInit(void);
Stack StackPush(Stack _Stack, char* str);
char* StackPop(Stack _Stack);
char* StackTop(Stack _Stack);

int isEmpty(Stack _Stack);
int StackLen(Stack _Stack);

#endif