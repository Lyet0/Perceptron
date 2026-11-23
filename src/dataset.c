#include <stdio.h>
#include <stdlib.h>
#include "../include/dataset.h"

struct dataset *creation_dataset(int n,int dim){
    struct dataset *d; 
    if ((d=malloc(sizeof(struct dataset)))==NULL){return NULL;}
    d->n=n;
    d->dim=dim;
    if((d->caracteristiques = malloc(sizeof(double *) * n))==NULL){return NULL;}
    if((d->labels=malloc(sizeof(int)*n))==NULL){return NULL;}
    
    for (int i = 0; i < n; i++) {
        d->caracteristiques[i] = malloc(sizeof(double) * dim);
        if (d->caracteristiques[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(d->caracteristiques[j]);
            }
            free(d->caracteristiques);
            free(d->labels);
            free(d);
            return NULL;
        }
    }
    return d;
}


void liberation_dataset(struct dataset* del){
    if (del == NULL) {
        return ;
    }
    free(del->labels);
    for (int d=0; d<del->n;d++){
        free(del->caracteristiques[d]);
    }
    free(del->caracteristiques);
    free(del);
}


void charge_dataset(char* source){
    FILE *f = fopen(source, "r") ;
    if(f==NULL){
        fprintf(stderr,"error opening file\n");
        exit(EXIT_FAILURE);
    }
    int dim = 0; int n = 1; 
    char c = fgetc(f);
    while(c != EOF){
        if(c == ',' && n < 1){      // compte le nombre de virgules de la premiere ligne (ce qui correspond au nombre de colonnes -1)
            dim++;
        }
        if(c == '\n'){              // compte le nombre de sauts de ligne +1 ce qui donne le nombre de lignes
            n++;
        }
        c = fgetc(f);
    }
    struct dataset set1;
    set1.dim = dim; set1.n = n;

    // finir la lecture des fichiers et remplir les tableaux

    fclose(f);
}

