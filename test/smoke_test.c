//
// Created by zan on 9/23/23.
//
#include <stdio.h>

#include "../c_source/lib_ml_basics.h"

int main(){

    printf("starting smoke test\n\n");

    int featNum = 4;
    int obNum = 4;
    double **featMat = 0;
    double *responseVec = 0;
    double *learnedTheta = 0;

    //invoke init
    int ret = init(featNum, obNum, DEFAULT_ECHELON, NO_REGULARIZATION,
                   &featMat, &responseVec, &learnedTheta);

    if (!ret){
        perror("init failed\n");
        return -1;
    }

    int i;
    int j;
    for (i = 0; i < obNum; i++){
        for (j = 0; j < featNum; j++){
            if (i == j){
                featMat[j][i] = 1;
                break;
            }
        }

        responseVec[i] = 1;
    };

    /*
     * test feature array:
     * [1, 0, 0, 0]
     * [0, 1, 0, 0]
     * [0, 0, 1, 0]
     * [0, 0, 0, 1]
     *
     * test response vector:
     * [1,
     *  1,
     *  1,
     *  1]
     */

    ret = gradientDescentLinReg();

    if (!ret){
        perror("gradient descent function returned error\n");
    }

    finalize();

    return 0;
}