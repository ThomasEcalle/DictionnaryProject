#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "constantes.h"
#include "controller_main_menu.h"
#include "controller_active_dictionary.h"
#include "gestbib.h"



int main()
{
    printf("WELCOME IN THE DICTIONARIES ADMINISTRATOR\n"
           "-----------------------------------------\n");
    int isAFileSelected = 0;
    char* path = malloc(sizeof(char) * 255);
    while(1 == 1){
        printf("\nWhat do you want to do ?\n");
        if(isAFileSelected){
            initActiveDico(&isAFileSelected, path);
        }
        else{
            initMainMenu(&isAFileSelected, path);
        }
    }
    return 0;
}




