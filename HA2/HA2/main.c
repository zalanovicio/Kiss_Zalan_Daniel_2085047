#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include "newton-raphson-algorithm.h"

int main() {
	double startValue;
	int checker = 0;
	int option = 1;
	double (*functionPtr)(double);
	functionPtr = &function;
	double (*functionderivativePtr)(double);

	functionderivativePtr = &functionapproximated;

	printf("Please give a start value: ");
	scanf("%lf", &startValue);

	while (checker == 0) {
		printf("Do you want to use the approximated or the analytic derivative for the approximation?\n(1 = approximated | 2 = analytic): ");
		scanf("%d", &option);
		if (option == 1) {
			printf("Using numeric approximation for derivative.\n");
			checker++;
		}
		else if (option == 2) {
			printf("Using analytic approximation for derivative.\n");
			functionderivativePtr = &functionanalyticderivative;
			checker++;
		}
	}

	

	/*double x = functionPtr(startValue);
	printf("%lf", x);*/
	newton_raphson_algorithm(functionPtr, functionderivativePtr, startValue);
}