#ifndef __STACK__
#define __STACK__

#define True 1
#define False 0
#define MAX_STACK_SIZE 500
#define MAX_STRING_LEN 20

struct __stack {
	char *stack[MAX_STACK_SIZE];
	int len;
};
typedef struct __stack* Stack;


Stack StackInit(void);
Stack StackPush(Stack _Stack, char* str);
char* StackPop(Stack _Stack);
char* StackTop(Stack _Stack);
int StackDel(Stack _Stack);

int StackEmpty(Stack _Stack);
int StackLen(Stack _Stack);

#endif