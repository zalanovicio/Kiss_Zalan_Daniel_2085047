#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "FormatFunctions.h"
#include "OperationsnResult.h"

int main() {
	char nr1[50];
	char nr2[50];
	c numbers[3] = {0,0,0,0,0,0};
	getNumbers(&nr1, &nr2);
	formatNumbers(&nr1, &nr2, &numbers);
	getOperationDone(&numbers);
	getResultFormat(&numbers);
	return 1;
}