#include <stdio.h>
#include <stdlib.h>
#include "algorithm/Stack.h"
#include "Calculator.h"
#define True 1
#define False 0
#define MAX_LEN 100


/*
TODO
1. check if memory is freed after allocating
2. Create Stack


*/


// Basic Function Declaration



int main(int argc, char* argv[]) {
	char* input = GetInput();
	CalculateBasicEquation(input);
	
	return 0;
}

