#include <stdio.h>
#include <stdlib.h>
#include "../include/perceptron.h"
#include "../include/dataset.h"

int main (){
    struct dataset *d = charge_dataset("/home/userir/Downloads/Perceptron-main/data/champignons.csv");
    for(int i = 0; i < d->n; i++){
        for(int j = 0; j < d->dim; j++){
            printf("%f, ", d->caracteristiques[i][j]);
        }
        printf("\n");
    }
    return 0; 
}
