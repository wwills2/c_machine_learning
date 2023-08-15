#include "library.h"

#include <stdio.h>

void hello(void) {
    printf("Hello, World!\n");
}

struct {

    unsigned int numFeatures;
    unsigned int numObservations;
    double **featureMatrix;
    double *responseVector;
    double *learnedTheta;

} typedef problemData_t;

/**
 * Entry point for learning a multiple linear regression model
 * @param featureMatrix pointer to an 2 dim array representing and unscaled feature matrix
 * @param responseVector pointer to a 1 dim array representing the response vector
 * @param learnedTheta
 * @return
 */
int linearRegression(unsigned int numFeatures, unsigned int numObservations,
                     double **featureMatrix, double *responseVector, double *learnedTheta){

    return 0;
}