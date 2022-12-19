#pragma once
typedef struct complexnumber {
	double real;
	double imaginary;
} c;

int checkIfCorrect(char** numPtr);
void getNumbers(char* nr1, char* nr2);
void formatNumbers(char* nr1, char* nr2, c array[]);