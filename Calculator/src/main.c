#include <stdio.h>
#include <stdlib.h>
#include "Calculator.h"




/*
TODO
1. check if memory is freed after allocating
2. Create Stack


*/


// Basic Function Declaration



int main(int argc, char* argv[]) {
	char* input = GetInput();
	PostFixEquation(input);
	
	return 0;
}

