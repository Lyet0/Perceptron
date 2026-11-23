#include <stdio.h>
#include <stdlib.h>
#include "../include/perceptron.h"
#include "../include/dataset.h"

int main (int argc, char *argv[]){
    if (arc==0){
        return 1; 
    }
    struct dataset *d=creation_dataset(10,4);
    liberation_dataset(d);
    charge_dataset(argv[0]);
    return 0; 
}
