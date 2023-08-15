#ifndef C_MACHINE_LEARNING_LIBRARY_H
#define C_MACHINE_LEARNING_LIBRARY_H

void hello(void);

int linearRegression(unsigned int numFeatures, unsigned int numObservations,
                     double **featureMatrix, double *responseVector, double *learnedTheta);

#endif //C_MACHINE_LEARNING_LIBRARY_H
