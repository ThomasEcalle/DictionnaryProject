#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../constantes.h"
#include "../view_main_menu.h"

/*
*   Input : *isAFileSelected - 0 si aucun fichier selectionne, sinon 1
*           *path - chemin du fichier qui est utilisé
*   Return : -
*   Purpose : Fonction d'initialisation du controller de dictionnaire actif.
*/
void initActiveDico(int* isAFileSelected, char* path){
    int userChoice;
    char *choicesArray[] = {"List the words of the dictionary",
                            "Insert a word in the dictionary",
                            "Search a word in the dictionary",
                            "Return to the main menu"
                            };
    printMenu (choicesArray, &userChoice);
    switch(userChoice){
        case 1:

            break;
        case 2:
            insertWordChoice(isAFileSelected, path);
            break;
        case 3:
            break;
        case 4:
            free(path);
            *isAFileSelected = 0;
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("This is not a valid option\n");
            break;
    }
}

void insertWordChoice(int* isAFileSelected, char* path){
    char* word = malloc(sizeof(char) * 255);
    do{
        printf("Please type the word you want to insert in the dictionary (e to exit).\nYour choice : ");
        scanf("%s", word);
        if(strcmp(word, "e") == 0){
            clearConsole();
            free(word);
            break;
        }
    }while(strcmp(word, "") == 0);
    if(strcmp(word, "e") != 0){
        insertWord(path, word);
        printf("\nYour word has been added to the dictionary !\n");
    }
}
