#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/dataset.h"
#include "../include/perceptron.h"

struct perceptron *creation_perceptron(float lr,int dim){
    struct perceptron *d; 
    if ((d=malloc(sizeof(struct perceptron)))==NULL){return NULL;}
    d->lr=lr;
    d->dim=dim;
    d->b=0;
    if((d->poids=malloc(sizeof(int)*(d->dim)))==NULL){return NULL;}
    
    for (int i = 0; i < dim; i++) {
        d->poids[i]=0; 
        }
    return d;
}
void liberation_perceptron(struct perceptron* del){
    if (del == NULL) {
        return ;
    }
    free(del->poids);
    free(del);
}
double sig(double z){
    return (1/(1+exp(-z))); 
}
double prediction(struct perceptron* perce, double* x ){
    int d=perce->dim;
    double z=0; 
    for (int i = 0; i<d;i++){
        z=x[i]*(perce->poids[i]);
    }
    z+=perce->b;
    z=sig(z);
    return z;
}

