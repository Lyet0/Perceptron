#ifndef DATASET_H
#define DATASET_H
struct dataset { 
    int n;                               // nombre de champignons
    int dim;                             // nombre de caracteristiques (ici 4)
    double **caracteristiques;              // tableau des caracteristiques de chaque element
    int *labels;                         // tableau du label de chaque element
};
struct dataset *creation_dataset(int n,int dim);
void liberation_dataset(struct dataset* del);
struct dataset *charge_dataset(const char *source);
#endif