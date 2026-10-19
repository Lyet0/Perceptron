#include <stdio.h>

typedef struct element {
    int c1;            // taille du chapeau
    int c2;            // hauteur du pied
    int c3;            // intensite de la couleur
    int c4;            // taille du pied
    int label;         // comestible
}elem;

struct dataset { 
    int n;                               // nombre de champignons
    int dim;                             // nombre de caracteristiques (ici 4)
    elem *tab;                 // tableau d'elements
}dataset;
