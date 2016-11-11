#include <stdio.h>
#include <stdlib.h>
#include "../constantes.h"
#include "../view_main_menu.h"


void initMainMenu(int* isAFileSelected, char* path){
    char userChoice;
    while(*isAFileSelected != 1){
        propositions(&userChoice);
        switch(userChoice){
            case '1':
                printf("coucou");
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case '6':
                break;
            default:
                printf("This is not a valid option\n");
                break;
        }
    }
}
