#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "eulerLib.h"

#define NUMOFSTATES 2

void RHS_MSD(double* rhs, double* y)
{ // mass spring damper

    double m = 1.0;  // mass of object
    double c = 2;    // feder constant
    double d = 2.9; // damper constant
    //     d is 2.8~2.9 for aperiodic boundary case 

    double x = y[0]; // position
    double v = y[1]; // speed

    /*calc derivatives and store in rhs*/

    rhs[0] = v;
    rhs[1] = -((d * v / m) + (c * x / m));
}

void eulerSettings_MSD(simHandle* handle)
{

    int size;
    /*num of states*/
    handle->numOfStates = (int)NUMOFSTATES;

    /*right hand site*/
    handle->f = &RHS_MSD;

    /*reserve storage for init state vec*/
    handle->stateVecInit = malloc(sizeof(double) * (handle->numOfStates));

    /* get user defined Simtime*/
    printf("Simtime (in s): \n");
    scanf("%lf", &handle->simTime);

    if (handle->simTime <= 0) {
        printf("Simtime must be greater than 0.");
        return;
    }

    

    /*get user defined StepSize*/
    printf("StepSize (in s): \n");
    scanf("%lf", &handle->stepSize);

    if (handle->stepSize <= 0) {
        printf("Stepsize must be greater than 0.");
        return;
    }

    /*get init state position*/
    printf("position(t = 0): \n");
    scanf("%lf", &handle->stateVecInit[0]);

    /*get init state speed*/
    printf("speed(t = 0): \n");
    scanf("%lf", &handle->stateVecInit[1]);



    /*reserve storage for states and derivatives*/
    size = ceil(handle->simTime / handle->stepSize);
    handle->stateVec = malloc(sizeof(double) * handle->numOfStates * size);
    handle->derivStateVec = malloc(sizeof(double) * handle->numOfStates * size);

    /*init states and derivatives with zero*/
    for (int i = 2; i < size * 2; i++) {
        handle->stateVec[i] = 0;
        handle->derivStateVec[i] = 0;
    }


    
}

void eulerForward(simHandle* handle)
{ // this is called only once
    int numOfStates = handle->numOfStates;
    int integratorSteps = (int)ceil(handle->simTime / handle->stepSize);
    double stepSize = handle->stepSize;
    double* derivativeTemp;
    double* statesTemp;

    derivativeTemp = malloc(sizeof(double) * handle->numOfStates);
    statesTemp = malloc(sizeof(double) * handle->numOfStates);

    /*write init states*/
    for (int i = 0; i < numOfStates; i++)
    {
        handle->stateVec[i] = handle->stateVecInit[i];
    }
    for (int i = 0; i < integratorSteps; i++)
    {
        /*get derivatives*/
        for (int j = 0; j < numOfStates; j++) {
            statesTemp[j] = handle->stateVec[2 * i + j];
        }
        handle->f(derivativeTemp, statesTemp);
        for (int k = 0; k < numOfStates; k++) {
            handle->derivStateVec[2 * i + k] = derivativeTemp[k];
        }
        for (int j = 0; j < numOfStates; j++)
        {
            handle->stateVec[i * 2 + 2 + j] = handle->stateVec[i * 2 + j] + stepSize * handle->derivStateVec[i * 2 + j];
        }
    }
}

void showResults_MSD(simHandle* handle)
{
    int integratorSteps = (int)ceil(handle->simTime / handle->stepSize);
    FILE* fp;

    /*print data to text file*/
    fp = fopen("data.txt", "w");

    if (fp == NULL) {
        printf("Cant open file.\n");
        return;
    }
    for(int i = 0; i < integratorSteps; i++){
        fprintf(fp, "%lf ", i * handle->stepSize);
        fprintf(fp, "%lf ", handle->stateVec[i*2]);
        fprintf(fp, "%lf\n", handle->stateVec[i*2+1]);
    }
    fclose(fp);


    /*call gnuplot*/
    char* gnuPlotInput[] = { "set title 'Results of simulation'", "set xlabel 'time in s'", "plot 'data.txt' using 1:2 title 'position',\ 'data.txt' using 1:3 title 'speed'" };
    /*FILE* gnuPlotPtr = _popen("gnuplot -presistent", "w"); for VS*/
    FILE* gnuPlotPtr = popen("gnuplot -presistent", "w");

    if (gnuPlotPtr == NULL) {
        printf("There was a problem opening gnuplot");
        return;
    }

    for (int i = 0; i < 3; i++) {
        fprintf(gnuPlotPtr, "%s\n", gnuPlotInput[i]);
    }

    fprintf(gnuPlotPtr, "exit");
    /*_pclose(gnuPlotPtr); for VS*/
    pclose(gnuPlotPtr);
}