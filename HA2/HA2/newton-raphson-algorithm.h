#pragma once
double newton_raphson_algorithm(double (*function)(double), double (*functionderivative)(double), double startvalue);