#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "FormatFunctions.h"
#include "OperationsnResult.h"

void getOperationDone(c array[]) {
	char operation = '0';
	while (operation != '+' && operation != '-' && operation != '/' && operation != '*') {
		printf("Enter the symbol of the operation you'd like to do. ( + | - | / | * ): ");
		scanf(" %c", &operation);
		if (operation != '+' && operation != '-' && operation != '/' && operation != '*') {
			printf("There is no such operation. Enter again.\n");
		}
	}
	switch (operation) {
	case '+':	array[2].real = array[0].real + array[1].real;
				array[2].imaginary = array[0].imaginary + array[1].imaginary;
		break;
	case '-':	array[2].real = array[0].real - array[1].real;
				array[2].imaginary = array[0].imaginary - array[1].imaginary;
		break;
	case '/':	array[2].real = array[0].real / array[1].real;
				array[2].imaginary = array[0].imaginary / array[1].imaginary;
		break;	
	case '*':	array[2].real = array[0].real * array[1].real;
				array[2].imaginary = array[0].imaginary * array[1].imaginary;
		break;
	default:
		break;
	}
}

void getResultFormat(c array []) {
	int result = 0;
	while (result != 1 && result != 2 && result != 3) {
		printf("In which format would you like to see the result?\n1. Cartesian | 2. Polar 1 | 3. Polar 2 : ");
		scanf("%d", &result);
		if (result != 1 && result != 2 && result != 3) {
			("There is no such format. Enter again.\n");
		}

	}
	switch (result) {
	case 1: printf("z = %.2lf+%.2lfi", array[2].real, array[2].imaginary);
		break;
	case 2: showPolar1(array[2].real, array[2].imaginary);
		break;
	case 3: showPolar2(array[2].real, array[2].imaginary);
		break;
	default:
		break;
	}
}

void showPolar1(double real, double imaginary) {
	double r, theta;
	r = sqrt(pow(real, 2) + pow(imaginary, imaginary));
	if (real < 0 && imaginary < 0) {
		theta = atan((imaginary/real)) - 3.1414926;
	}
	else if (real < 0) {
		theta = atan((imaginary / real)) + 3.1414926;
	}
	else {
		theta = atan((imaginary / real));
	}
	printf("z = %.2lf*e^(i%.2lf)\n", r, theta);
}

void showPolar2(double real, double imaginary) {
	double r, theta;
	r = sqrt(pow(real, 2) + pow(imaginary, 2));
	if (real < 0 && imaginary < 0) {
		theta = atan((imaginary / real)) - 3.1414926;
	}
	else if (real < 0) {
		theta = atan((imaginary / real)) + 3.1414926;
	}
	else {
		theta = atan((imaginary / real));
	}
	printf("z = %.2lf*(cos(%.2lf)+i*sin(%.2lf))", r, theta, theta);
}