#include "lib_ml_basics.h"
#include "log.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * struct holding parameters and data buffers for the learning problem. Intended to be used globally within the library
 */
struct {

    unsigned int numFeatures;
    unsigned int numObservations;
    double echelon;
    double lambda;
    double **p_featureMatrix;
    double *p_responseVector;
    unsigned int lenTheta;
    double *p_learnedTheta;

} typedef problemData_t;

static char g_initialized = 0;
static problemData_t g_data;

int i_getDerivativeValues(const double *p_theta, double *p_derivativeValues);

/**
 * Stores information about the learning problem and initializes buffers to store data
 *
 * @param numFeatures the number of features per observation
 * @param numObservations the number of observations in the dataset
 * @param echelon the learning rate for gradient descent
 * @param lambda regularization constant
 * @param p_featureMatrixRef pointer to an 2 dim array representing and unscaled feature matrix
 * @param p_responseVectorRef pointer to a 1 dim array representing the response vector
 * @param p_learnedThetaRef pointer to a 1 dim array representing the learned theta
 * @return status code of the operation
 */
int init(unsigned int numFeatures, unsigned int numObservations, double echelon, double lambda,
         double ***p_featureMatrixRef, double **p_responseVectorRef, double **p_learnedThetaRef){

    int i;
    int error = 0;
    double **p_featureMatrix;
    double *p_responseVector;
    double *p_learnedTheta;

    logInit();
    LOG(p_logStream, "%s checking buffer references\n", TAG);

    if (p_featureMatrixRef == NULL){
        LOG(p_logStream, "%s cannot initialize. Null reference to feature matrix\n", TAG);
        error = 1;
    }

    if (p_responseVectorRef == NULL){
        LOG(p_logStream, "%s cannot initialize. Null reference to response vector\n", TAG);
        error = 1;
    }

    if (p_learnedThetaRef == NULL){
        LOG(p_logStream, "%s cannot initialize. Null reference to learned theta vector\n", TAG);
        error = 1;
    }

    if (error){
        return ERROR;
    }

    LOG(p_logStream, "%s checking buffers are null prior to initialization\n", TAG);

    if (*p_featureMatrixRef != NULL){
        LOG(p_logStream, "%s cannot initialize. feature matrix could point to allocated data. try finalize()\n", TAG);
        error = 1;
    }

    if (*p_responseVectorRef != NULL){
        LOG(p_logStream, "%s cannot initialize. response vector could point to allocated data. try finalize()\n", TAG);
        error = 1;
    }

    if(*p_learnedThetaRef != NULL){
        LOG(p_logStream, "%s cannot initialize. theta could point to allocated data. try finalize()\n", TAG);
        error = 1;
    }

    if (error){
        return ERROR;
    }

    LOG(p_logStream, "%s initializing buffers\n", TAG);

    p_responseVector = calloc(numFeatures, sizeof (double));
    p_learnedTheta = calloc(numFeatures, sizeof (double));
    p_featureMatrix = calloc(numObservations, sizeof (double *));
    for (i = 0; i < numObservations; i++){
        p_featureMatrix[i] = calloc(numFeatures, sizeof (double));
    }

    // make buffers available to calling function
    *p_featureMatrixRef = p_featureMatrix;
    *p_responseVectorRef = p_responseVector;
    *p_learnedThetaRef = p_learnedTheta;

    LOG(p_logStream, "%s initializing library global data struct\n", TAG);
    g_data.numFeatures = numFeatures;
    g_data.numObservations = numObservations;
    g_data.echelon = echelon;
    g_data.lambda = lambda;
    g_data.p_featureMatrix = p_featureMatrix;
    g_data.p_responseVector = p_responseVector;
    g_data.lenTheta = numFeatures + 1;
    g_data.p_learnedTheta = p_learnedTheta;

    g_initialized = 1;

    return SUCCESS;
}

/**
 * Deallocates all dynamically allocated data and resets data fields to 0
 *
 * @return status of the operation
 */
int finalize(){

    int i;

    g_initialized = 0;

    free(g_data.p_responseVector);
    free(g_data.p_learnedTheta);

    for (i = 0; i < g_data.numObservations; i++){
        free(g_data.p_featureMatrix[i]);
    }
    free(g_data.p_featureMatrix);

    g_data.numFeatures = 0;
    g_data.numObservations = 0;
    g_data.echelon = 0;
    g_data.lambda = 0;
    g_data.lenTheta = 0;

    logFinalize();

    return SUCCESS;
}

/**
 * Entry point for learning a linear regression model via gradient descent. while loop controls descent iterations and
 * convergence condition
 * 
 * @return status code of the operation
 */
int gradientDescentLinReg(){

    int i;
    int status;
    unsigned int converged = 0;
    unsigned int descentIterationNum = 0;
    const unsigned int LEN_THETA = g_data.lenTheta;
    double *p_derivativeValues;
    double *p_prevTheta;

    if (!g_initialized){
        LOG(p_logStream, "data has not been initialized. try init()");
        return ERROR;
    }

    p_derivativeValues = calloc(LEN_THETA, sizeof (double));
    p_prevTheta = calloc(LEN_THETA, sizeof (double));

    while (!converged){

        descentIterationNum++;

        status = i_getDerivativeValues(p_prevTheta, p_derivativeValues);
        if (!status){
            LOG(p_logStream , "failed to get derivative values on iteration %i ", descentIterationNum);
            return ERROR;
        }

        if (g_data.lambda == NO_REGULARIZATION){
            for (i = 0; i < LEN_THETA; i++){
                g_data.p_learnedTheta[i] = p_prevTheta[i] - (g_data.echelon * p_derivativeValues[i]);
            }
        }else{
            //todo: implement regularization
        }

        converged = 1;
        for (i = 0; i < LEN_THETA; i++){
            if ((p_prevTheta[i] - g_data.p_learnedTheta[i]) > g_data.echelon){
                converged = 0;
                break;
            }
        }

        p_prevTheta = g_data.p_learnedTheta;
    }

    return SUCCESS;
}

/**
 * INTERNAL FUNCTION
 * calculates all partial derivatives of the cost function for each value of theta
 *
 * @param p_theta pointer to the current theta array
 * @param p_derivativeValues pointer to the buffer in which to place the theta derivative
 * @return status of the operation
 */
int i_getDerivativeValues(const double *p_theta, double *p_derivativeValues){

    //todo: decide on error conditions or remove return val

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
                p_derivativeValues[i] += currEstimateSum * g_data.p_featureMatrix[i][j];
            }
        }

        p_derivativeValues[i] /= g_data.numObservations;
    }

    return SUCCESS;
}
