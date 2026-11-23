#include <stdio.h>
#include <stdlib.h>


struct perceptron {
    int *poids;
    float b;
    int dim;
    float lr;
};