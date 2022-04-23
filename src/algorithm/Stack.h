#ifndef __STACK__
#define __STACK__

#define True 1
#define False 0
#define MAX_STACK_SIZE 500
typedef struct __stack {
	char *stack[MAX_STACK_SIZE];
	int len;
} Stack;


#endif