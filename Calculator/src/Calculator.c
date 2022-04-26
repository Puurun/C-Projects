#include "Calculator.h"
#include "algorithm/Stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define NUM_SIZE 50
#define MAX_LEN 100
#define TOK_LEN 100
#define True 1
#define False 0

int Calculate(void){
	char* input;
	char** tokenized_equation;
	char** post_equation;
	int answer, i;
	
	// get input
	input = GetInput();
	
	// tokenize input and free input
	tokenized_equation = Tokenize(input);
	free(input);
	
	// make tokenized equation into postfix equation
	// free tokenized equation
	post_equation = PostFixEquation(tokenized_equation);
	for(i=0; tokenized_equation[i][0]!='='; i++)
		free(tokenized_equation[i]);
	free(tokenized_equation[i]);
	free(tokenized_equation);
	
	// calculate postfix equation
	// free postfix equation
	answer = CalculateEquation(post_equation);
	for(i=0; post_equation[i][0]!='='; i++)
		free(post_equation[i]);
	free(post_equation[i]);
	free(post_equation);
	
	// print answer
	printf("\n\n");
	printf("answer: %.2lf \n", (double)answer);
	
	
	return 1;
}
// flush input
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
	printf("Input equation, '=' to exit: \n");
	while((c = getchar()) != '='){
		*(input+i) = (char)c;
		i++;
	}
	*(input+i) = '=';
	iflush();
	return input;
}

char** Tokenize(char* eq){
	unsigned int len = strlen(eq);
	char** token_array = (char**)malloc(sizeof(char*) * TOK_LEN);
	int i, num_len, cur_pos=0;
	char c;
	
	for(i=0; i<TOK_LEN; i++){
		c = eq[cur_pos];
		token_array[i] = (char*)malloc(sizeof(char) * 30);
		
		// if =, end tokenizing
		if(c == '='){
			strcpy(token_array[i], "=");
			break;
		}
		
		// case 1. digit
		if(isDigit(c)){
			num_len = 0;
			c = eq[cur_pos+num_len]; 
			// check digit length
			while(isDigit(c)){
				num_len++;
				c = eq[cur_pos+num_len];
			}
			// copy cur_pos + num_len to token_array[i], end with \0, increase cur_pos by num_len
			strncpy(token_array[i], eq+cur_pos, sizeof(char) * num_len);
			token_array[i][num_len] = 0;
			cur_pos = cur_pos + num_len;
			continue;
		}
		// case 2. single operator
		else if(isOperator(c)){
			c = eq[cur_pos];
			token_array[i][0] = c;
			token_array[i][1] = 0;
			cur_pos++;
			continue;
		}
		// case 3. whitespace
		else if(isWhiteSpace(c)){
			free(token_array[i]);
			i--;
			cur_pos++;
		}
		// case inf. equation error
		else{
			printf("The equation has something wrong inside!!!!!!");
			cur_pos++;
		}
	}
	return token_array;
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


char** PostFixEquation(char** eq){
	char ** post_eq = (char**)malloc(sizeof(char*) * TOK_LEN);
	Stack opt_stack = StackInit();
	int count_eq=0, count_post=0;
	int len=0;

	for(len=0; eq[len][0]!='='; len++);
	
	while(count_eq<len){
		
		
		// if number, put into post_eq
		if(isDigit(eq[count_eq][0])){
			AllocateMemoryEquation(&post_eq[count_post]);
			strcpy(post_eq[count_post], eq[count_eq]);
			count_post++;
			count_eq++;
			continue;
		}
		// if operator, check priority
		// if stack top priority >= cur priority, pop and put into post_eq
		if(isOperator(eq[count_eq][0])){
			// ( => put into stack immediately
			if(eq[count_eq][0] == '('){
				StackPush(opt_stack, eq[count_eq]);
				count_eq++;
				continue;
			}
			// ) => pop until ( and put them into post_eq
			else if(eq[count_eq][0] == ')'){
				while(True){
					if(StackTop(opt_stack)[0] == '('){
						break;
					}
					AllocateMemoryEquation(&post_eq[count_post]);
					strcpy(post_eq[count_post], StackPop(opt_stack));
					count_post++;
				}
				//pop (
				StackPop(opt_stack);
				count_eq++;
				continue;
			}
			else{
				// While Stack isn't empty, check priority and put into post_eq if necessary
				while(True){
					if(StackEmpty(opt_stack) || StackTop(opt_stack)[0] == '('){
						break;
					}
					else if(OperatorPriority(StackTop(opt_stack)[0]) >= OperatorPriority(eq[count_eq][0])){
						AllocateMemoryEquation(&post_eq[count_post]);
						strcpy(post_eq[count_post], StackPop(opt_stack));
						count_post++;
					}
					else{
						break;
					}
				}
				StackPush(opt_stack, eq[count_eq]);
				count_eq++;
			}
		}
	}
	// put all opt_stack into post_eq
	while(!StackEmpty(opt_stack)){
		AllocateMemoryEquation(&post_eq[count_post]);
		// copy stack opt into post_eq
		strcpy(post_eq[count_post], StackPop(opt_stack));
		count_post++;
	}
	AllocateMemoryEquation(&post_eq[count_post]);
	strcpy(post_eq[count_post], "=");
	
	for(int i=0; i<count_post; i++){
		printf("%s ", post_eq[i]);
	}
	
	// free memory allocated in stack
	StackDel(opt_stack);
	return post_eq;
	
}

int CalculateEquation(char** eq){
	int len=0, step=0, temp;
	char c;
	for(len=0; eq[len][0] != '='; len++);
	double numbers[200];
	int cur_pos=0;
	
	while(step<len){
		c = eq[step][0];
		
		if(isDigit(c)){
			temp = strtol(eq[step], NULL, 10);;
			if(temp == 0){
				numbers[cur_pos] = strtof(eq[step], NULL);
			}else{
				numbers[cur_pos] = (double)temp;
			}
			cur_pos++;
			step++;
			continue;
		}
		else if(isOperator(c)){
			switch(c){
				case '+':
					numbers[cur_pos-2] = numbers[cur_pos-2] + numbers[cur_pos-1];
					break;
				case '-':
					numbers[cur_pos-2] = numbers[cur_pos-2] - numbers[cur_pos-1];
					break;
				case '*':
					numbers[cur_pos-2] = numbers[cur_pos-2] * numbers[cur_pos-1];
					break;
				case '/':
					numbers[cur_pos-2] = numbers[cur_pos-2] / numbers[cur_pos-1];
					break;
			}
			cur_pos--;
			step++;
		}
	}
	return numbers[0];
}

void AllocateMemoryEquation(char** eq){
	// allocate memory
	*eq = (char*)malloc(sizeof(char) * 30);	
}

int isDigit(char c){
	if( '0' <= c && c <= '9'){
		return True;
	}
	return False;
}



// Compare Operator (Same, Small = 1)
int OperatorPriority(char opt){
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
		case '-':
		case '*':
		case '/':
		case '(':
		case ')':
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
