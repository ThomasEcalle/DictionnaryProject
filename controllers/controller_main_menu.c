#include <stdio.h>
#include <stdlib.h>
#include "../constantes.h"
#include "../view_main_menu.h"


void initMainMenu(int* isAFileSelected){
    int userChoice;
    while(*isAFileSelected != 1){
        propositions(&userChoice);
        printf("%d", userChoice);
    }
}
