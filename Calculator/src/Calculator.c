#include "Calculator.h"
#include "algorithm/Stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define NUM_SIZE 50
#define MAX_LEN 100
#define True 1
#define False 0


// Get Input from the user. Have to free the input later.
char* GetInput(void){
	// Variable
	char* input = malloc(MAX_LEN*sizeof(char));
	int i=0, c;
	
	// Get Input
	printf("Input equation, '.' to exit: \n");
	while((c = getchar()) != '.'){
		*(input+i) = c;
		printf("%c", *(input+i));
	}
	return input;
}


int PostFixEquation(char* eq){
	int i=0, num=0, opt=0, num_size=0;
	int numbers[NUM_SIZE];
	char operators[NUM_SIZE];
	char temp_num[NUM_SIZE];
	
	for(i=0; i<MAX_LEN; i++){
		// read one char from equation
		char c = *(eq+i);
		
		// if operator or whitespace, put atoi(temp_num) into numbers 
		// clear temp_num, increase num
		// put operator into operators, increase opt
		if(isOperator(c) || (isWhiteSpace(c)&&num_size!=0)){
			temp_num[i] = 0;
			numbers[num] = atoi(temp_num);
			printf("%d", numbers[num]);
			
			memset(temp_num, 0, sizeof(temp_num));
			num_size = 0;
			num++;
			
			if(isOperator(c)){
				operators[opt] = c;
				opt++;
			}
		}
		// else, put char in temp_num
		else{
			temp_num[num_size] = c;
			num_size++;
		}
		
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
