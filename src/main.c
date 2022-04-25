#include <stdio.h>
#include <stdlib.h>
#include "Calculator.h"




/*
TODO
1. check if memory is freed after allocating
2. Create Stack


*/

int main(void) {
	char* input;
	input = GetInput();
	PostFixEquation(input);
	
	
	free(input);
	return 0;
}

