#include <stdio.h>
#include <stdlib.h>
#include "../include/perceptron.h"
#include "../include/dataset.h"

int main (){
    struct dataset *d = charge_dataset("/home/userir/Downloads/Perceptron-main/data/champignons.csv");
    struct dataset *d_80 = creation_dataset((d->n / 5)*4, d->dim);
    struct dataset *d_20 = creation_dataset(d->n / 5, d->dim);
    for(int i = 0; i < d->n; i++){
        for(int j = 0; j < d->dim; j++){
            if(i < d_80->n){
                d_80->caracteristiques[i][j] = d->caracteristiques[i][j];
            }
            else{
                d_20->caracteristiques[i - d_80->n][j] = d->caracteristiques[i][j];
            }
        }
        if(i < d_80->n){
            d_80->labels[i] = d->labels[i];
        }
        else{
            d_20->labels[i - d_80->n] = d->labels[i];
        }
    }
    printf("\n\n\n");
    for(int i = 0; i < d_80->n; i++){
        for(int j = 0; j < d_80->dim; j++){
            printf("%f, ", d_80->caracteristiques[i][j]);
        }
        printf("   %d\n", d_80->labels[i]);
    }
    printf("\n\n\n");
    for(int i = 0; i < d_20->n; i++){
        for(int j = 0; j < d_20->dim; j++){
            printf("%f, ", d_20->caracteristiques[i][j]);
        }
        printf("   %d\n", d_20->labels[i]);
    }
    printf("\n\n\n");

    liberation_dataset(d); liberation_dataset(d_20); liberation_dataset(d_80);
    return 0; 
}
