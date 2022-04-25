#include "Calculator.h"
#include "algorithm/Stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define NUM_SIZE 50
#define MAX_LEN 100
#define True 1
#define False 0

void iflush(void){
	char c;
	while(c != '\n'){
		c = getchar();
	}
}
// Get Input from the user. Have to free the input later.
char* GetInput(void){
	// Variable
	char* input = (char*)malloc(MAX_LEN*sizeof(char));
	int i=0;
	int c;
	
	// Get Input
	printf("Input equation, '.' to exit: \n");
	while((c = getchar()) != '.'){
		*(input+i) = (char)c;
		i++;
	}
	*(input+i) = ' ';
	printf("%send\n", input);
	iflush();
	return input;
}

/*

후위표기식
1+2/5-6*3
1 2 5 / +
-

1. operator 스택
2. 숫자면 equation에 넣는다,
3. operator이면 스택에 넣는다
4. priority를 비교해서 더 새로 들어오는 놈이 높으면 유지, 같으면 pop 낮으면 pop
5. )를 만나면 ( 가 나올때까지 pop, 순서대로 equation에 넣는다.

*/
void PostFixEquation(char* eq){
	int i=0, num_size=0, eq_num=0;
	char temp_num[NUM_SIZE];
	char c;
	char (*equation)[MAX_LEN] = {0};
	Stack opt_stack = StackInit();
	
	
	for(i=0; i<strlen(eq); i++){
		// read one char from equation
		c = *(eq+i);
		char str[2];
		str[0] = (char)c;
		str[1] = 0;
		
		printf("%c", c);
		// if operator or whitespace, put atoi(temp_num) into numbers 
		// clear temp_num, increase num
		// put operator into operators, increase opt
		if(isOperator(c)){
			temp_num[num_size] = 0;
			strcpy(equation[eq_num++], temp_num);
			memset(temp_num, 0, sizeof(temp_num));
			num_size = 0;
			
			char* top = StackTop(opt_stack);
			if(strcmp(top, ")") == 0){
				StackPop(opt_stack);
				while(strcmp(top=StackPop(opt_stack), "(") != 0){
					strcpy(equation[eq_num++], top);
				}
			}
			else{
				int priority;
				while((priority = OperatorPriority(top, str))==1){
					strcpy(equation[eq_num++], top);
					StackPop(opt_stack);
					top = StackTop(opt_stack);
				}
			}
			StackPush(opt_stack, str);
			printf("%s",str);
		}
		else if(isWhiteSpace(c)&&num_size!=0){
			temp_num[num_size] = 0;
			strcpy(equation[eq_num++], temp_num);
			memset(temp_num, 0, sizeof(temp_num));
			num_size = 0;
		}
		// else, put char in temp_num
		else{
			temp_num[num_size] = c;
			num_size++;
		}
		
		
		
	}
	while(StackLen(opt_stack)){
			strcpy(equation[eq_num++], StackPop(opt_stack));
	}
	
	for(i=0; i<eq_num; i++){
		printf("%s", equation[eq_num]);
	}
}

// Compare Operator (Same, Small = 1)
int OperatorPriority(char* opt1, char* opt2){
	if(opt1==NULL || opt2==NULL){
		return 0;
	}
	if(CheckOperator(*opt1) <= CheckOperator(*opt2)){
		return 1;
	}
	return -1;
}

int CheckOperator(char opt){
	switch(opt){
		case '*':
		case '/':
			return 2;
		case '+':
		case '-':
			return 1;
	}
}
// Check if char is operator (+, -, *, /)
int isOperator(char c){
	switch(c){
		case '+':
			return True;
		case '-':
			return True;
		case '*':
			return True;
		case '/':
			return True;
		default:
			return False;
	}
}

// Check if whitespace (space, tab)
int isWhiteSpace(char c){
	switch(c){
		case ' ':
			return True;
		case '\t':
			return True;
		default:
			return False;
	}
}
