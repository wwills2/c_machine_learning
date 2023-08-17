#include "lib_ml_basics.h"
#include "log.h"

#include <stdio.h>
#include <malloc.h>

/**
 * struct holding general information and data about the learning problem
 */
struct {

    unsigned int numFeatures;
    unsigned int numObservations;
    double echelon;
    double lambda;
    double **p_featureMatrix;
    double *p_responseVector;
    unsigned int lenTheta;

} typedef problemData_t;

static problemData_t g_data;

/**
 * calculates all partial derivatives of the cost function for each value of theta
 * @param p_theta
 * @param p_derivativeValues
 * @return
 */
int getDerivativeValues(const double *p_theta, double *p_derivativeValues){

    int i;
    int j;
    int k;
    double currEstimateSum;

    for (i = 0; i < g_data.lenTheta; i++){
        for (j = 0; i < g_data.numObservations; j++){

            currEstimateSum = 0;
            for (k = 0; k < g_data.numFeatures; k++){

                currEstimateSum += g_data.p_featureMatrix[j][k] * p_theta[k];
            }

            //todo: add if to apply sigmoid for logistic regression

            currEstimateSum -= g_data.p_responseVector[j];

            if(j == 0){
                p_derivativeValues[i] += currEstimateSum;
            }else{
                p_derivativeValues[i] += currEstimateSum * g_data.p_responseVector[i];
            }
        }
    }

    return SUCCESS;
}

/**
 * Entry point for learning a linear regression model via gradient descent. while loop descent iterations and
 * convergence condition
 *
 * @param numFeatures the number of features per observation
 * @param numObservations the number of observations in the dataset
 * @param echelon the learning rate for gradient descent
 * @param lambda regularization constant
 * @param p_featureMatrix pointer to an 2 dim array representing and unscaled feature matrix
 * @param p_responseVector pointer to a 1 dim array representing the response vector
 * @param p_learnedTheta pointer to a 1 dim array representing the learned theta
 * @return status code of the operation
 */
int gradientDescentLinearRegression(unsigned int numFeatures, unsigned int numObservations, double echelon, double lambda,
                                    double **p_featureMatrix, double *p_responseVector, double *p_learnedTheta){

    logInit();

    // todo: check that the size of the matrices matches the given dimensions

    g_data.numFeatures = numFeatures;
    g_data.numObservations = numObservations;
    g_data.echelon = echelon;
    g_data.lambda = lambda;
    g_data.p_featureMatrix = p_featureMatrix;
    g_data.p_responseVector = p_responseVector;
    g_data.lenTheta = numFeatures + 1;

    //static variables
    int i;
    int j;
    int status;
    unsigned int converged = 0;
    unsigned int descentIterationNum = 0;
    const unsigned int LEN_THETA = g_data.lenTheta;

    //dynamic variables
    double *p_derivativeValues = calloc(LEN_THETA, sizeof (double));
    double *p_prevTheta = calloc(LEN_THETA, sizeof (double));
    double *p_updatedTheta = calloc(LEN_THETA, sizeof (double));


    while (!converged){

        descentIterationNum++;

        status = getDerivativeValues(p_prevTheta, p_derivativeValues);
        if (!status){
            LOG(p_logStream , "failed to get derivative values on iteration %i ", descentIterationNum);
            return ERROR;
        }

        for (i = 0; i < LEN_THETA; i++){


        }
    }



    return SUCCESS;
}


