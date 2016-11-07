#include <stdio.h>
#include <stdlib.h>
#include "../constantes.h"
#include "../view_main_menu.h"


void initMainMenu(int* isAFileSelected){
   int userChoice = 0;
     while(*isAFileSelected != 1){
         propositions(&userChoice);
         *isAFileSelected = 1;
         clearConsole();

         printf("%d", userChoice);
     }

     int max = 10;
     char * question = "\n Find a name please \n";
     char * name = malloc(sizeof(char)*10);

     askForSring(name,max,question);

}
