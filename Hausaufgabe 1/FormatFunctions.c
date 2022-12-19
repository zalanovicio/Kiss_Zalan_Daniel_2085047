#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FormatFunctions.h"

int checkIfCorrect(char** numPtr) {
	char checker[50];
	int marker = 0;
	int pluscount = 0;
	strcpy(checker, numPtr);
	int length = strlen(checker);
	for (int i = 0; i < length; i++) {
		if ((i > 0 && i < length-1)) {
			if ((checker[i] != '0' && checker[i] != '1' && checker[i] != '2' && checker[i] != '3' && checker[i] != '4' && checker[i] != '5' &&
				checker[i] != '6' && checker[i] != '7' && checker[i] != '8' && checker[i] != '9' && checker[i] != '.' && checker[i] != '+' &&
				checker[i] != '-')) {
				marker++;
				}
			if (checker[i] == '+') {
				pluscount++;
				if (checker[i + 1] == '.' || checker[i + 1] == 'i' || checker[i + 1] == '+') {
					marker++;
				}
			}
			if (checker[i] == '.' || checker[i] == '-') {
				if (checker[i + 1] == '+' || checker[i + 1] == 'i' || checker[i + 1] == '.') {
					marker++;
				}
			}

		}
		else if ((checker[i] == 'i' || checker[i] == '+' || checker[i] == '.' || checker[i] == '/') && i == 0) {
			marker++;
		}
		else if ((checker[i] != 'i') && i == (length - 1)) {
			marker++;
		}
	}
	if (marker == 0 && pluscount == 1) {
		return 1;
	}
	else {
		printf("Wrong format or character(s).\n");
		return 0;
	}
}

void getNumbers(char* nr1, char* nr2){
	char* nr1Ptr = nr1;
	char* nr2Ptr = nr2;


	printf("Welcome!\nPlease enter two complex numbers in the format 'a+bi'.\n");
	do {
		printf("First number: ");
		scanf("%s", nr1);
	} while (!checkIfCorrect(nr1Ptr));

	do {
		printf("Second number: ");
		scanf("%s", nr2);
	} while (!checkIfCorrect(nr2Ptr));


}

void formatNumbers(char* nr1, char* nr2, c array[]) {
	char num[50];
	int length1 = strlen(nr1);
	int length2 = strlen(nr2);
	int dindex = 0;
	char c;
	for (int i = 0; i < length1; i++) {
		c = nr1[i];
		if (c != '+' && c != 'i') {
			num[dindex] = c;
			num[dindex + 1] = '\0';
			dindex++;
		}
		else if (c == '+') {
			array[0].real = atof(num);
			dindex = 0;
		}
		else if (c == 'i') {
			array[0].imaginary = atof(num);
			dindex = 0;
		}
	}
	for (int i = 0; i < length2; i++) {
		c = nr2[i];
		if (c != '+' && c != 'i') {
			num[dindex] = c;
			num[dindex + 1] = '\0';
			dindex++;
		}
		else if (c == '+') {
			array[1].real = atof(num);
			dindex = 0;
		}
		else if (c == 'i') {
			array[1].imaginary = atof(num);
			dindex = 0;
		}
	}
}