#include "Calculator.h"

char* GetInput(){
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

void AnalyzeEquation(char[] eq){
	
}

int CalculateBasicEquation(char[] eq){
	int n_eq = 20, i=0, num=0;
	char* numbers[50] = malloc(n_eq*sizeof(int));
	char temp_num[50];
	
	for(i=0; i<MAX_LEN; i++){
		// read one char from equation
		char c = *(eq+i);
		
		// if operator, put atoi(temp_num) into numbers 
		// clear temp_num, and move pointer to the next one
		if(isOperator(c)){
			temp_num[i] = 0;
			*(numbers+num) = atoi(temp_num);
			printf("%d", *(numbers+num));
			num++;
			memset(temp_num, 0, 50*sizeof(int));
		}
		// if blank, move to next
		else if(isWhiteSpace(c)){
			continue;
		}
		// else, put char in temp_num
		else{
			temp_num[i] = c;
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
