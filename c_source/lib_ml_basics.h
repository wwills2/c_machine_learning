#ifndef C_MACHINE_LEARNING_LIB_ML_BASICS_H
#define C_MACHINE_LEARNING_LIB_ML_BASICS_H

#include <math.h>

#define SUCCESS 1
#define ERROR 0
#define DEFAULT_ECHELON 10e-5
#define NO_REGULARIZATION HUGE_VAL
#define TAG "lib_ml_basics:\0"


/**
 * Stores information about the learning problem and initializes buffers to store data
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
int init(unsigned int numFeatures, unsigned int numObservations, double echelon, double lambda,
         double **p_featureMatrix, double *p_responseVector, double *p_learnedTheta);

/**
 * Deallocates all dynamically allocated data and resets data fields to 0
 *
 * @return status of the operation
 */
int finalize();

/**
 * Entry point for learning a linear regression model via gradient descent. while loop controls descent iterations and
 * convergence condition
 *
 * @return status code of the operation
 */
int gradientDescentLinReg();

#endif //C_MACHINE_LEARNING_LIB_ML_BASICS_H
