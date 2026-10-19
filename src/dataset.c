#include <stdio.h>
#include <stdlib.h>

struct dataset { 
    int n;                               // nombre de champignons
    int dim;                             // nombre de caracteristiques (ici 4)
    int **caracteristiques;              // tableau des caracteristiques de chaque element
    int *labels;                         // tableau du label de chaque element
}dataset;

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
