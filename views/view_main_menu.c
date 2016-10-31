#include <stdio.h>
#include <stdlib.h>
#include "../constantes.h"

void propositions(int *userChoice){
    do{
        printf("\nWhat do you want to do ?\n"
               "1- create a dictionary\n"
               "2- use an existing dictionary\n"
               "4- make a dictionary from a text file\n"
               "5- destroy a dictionary\n");
        scanf("%d", userChoice);
    }while(1);
}


