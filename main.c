#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"
#include "controller_main_menu.h"
#include "controller_active_dictionary.h"

int main()
{
    printf("WELCOME IN THE DICTIONARIES ADMINISTRATOR\n"
           "-----------------------------------------\n\n");
    int isAFileSelected = 0;

    if(isAFileSelected){

    }
    else{
        initMainMenu(&isAFileSelected);
    }
    return 0;
}
