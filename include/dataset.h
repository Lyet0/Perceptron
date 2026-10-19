struct dataset { 
    int n;                               // nombre de champignons
    int dim;                             // nombre de caracteristiques (ici 4)
    int **caracteristiques;              // tableau des caracteristiques de chaque element
    int *labels;                         // tableau du label de chaque element
}dataset;
struct dataset *creation_dataset(int n,int dim);
void liberation_dataset(struct dataset* del);