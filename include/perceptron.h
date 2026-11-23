#ifndef PERCEPTRON_H
#define PERCEPTRON_H
struct perceptron {
    int *poids;
    float b;
    int dim;
    float lr;
};
void liberation_perceptron(struct perceptron* del);
struct perceptron *creation_perceptron(float lr,int dim);

#endif