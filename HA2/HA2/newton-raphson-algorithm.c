#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double newton_raphson_algorithm(double (*function)(double), double (*functionderivative)(double), double startvalue) {
	double x0 = startvalue;
	double x1;
	for (int i = 0; i < 1000; i++) {
		x1 = x0 - (function(x0)) / (functionderivative(x0));
		printf("%.16f\n", x1);
		x0 = x1;

		if (function(x1) < pow(10, -8)) {
			printf("Solution found after %d iterations.\n", i + 1);
			printf("X at the value %.16f is the closest to null.", x1);
			break;
		}
		else if (i == 999){
			printf("No solution was found after maximal amount of iterations.\n");
			printf("X at the value %.16f was the last approximation.", x1);
			break;
		}
	}
	/*double f = function(startvalue);
	printf("%f", f);*/
}