#include <stdio.h>
#include <stdlib.h>
#include "../include/perceptron.h"
#include "../include/dataset.h"

int main (){
    struct dataset *d=creation_dataset(10,4);
    liberation_dataset(d);
    return 0; 
}
