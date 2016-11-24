#include <stdio.h>
#include <stdlib.h>
#include "../constantes.h"
#include "../view_main_menu.h"
#include "../models/gestbib.c"



/*
*   Input : *isAFileSelected - 0 si aucun fichier selectionne, sinon 1
*           *path - chemin du fichier qui sera choisi
*   Return : -
*   Purpose : Fonction d'initialisation du controller de menu principal.
*   Appelle la fonction proposition() recuperant le choix de l'utilisateur
*   puis renvoie via le switch a la fonction correspondant a ce choix.
*/
void initMainMenu(int* isAFileSelected, char* path){
    int userChoice;
    while(*isAFileSelected != 1){
        userChoice = NULL;
        propositions(&userChoice);
        switch(userChoice){
            case 1:
                createDictionaryChoice(isAFileSelected, path);
                break;
            case 2:
                useExistantDictionaryChoice(isAFileSelected, path);
                break;
            case 3:
                break;
            case 4:
                destroyDictionaryChoice(isAFileSelected, path);
                break;
            case 5:
                break;
            default:
                printf("This is not a valid option\n");
                break;
        }
    }
}

/*
*   Input : *isAFileSelected - 0 si aucun fichier selectionne, sinon 1
*           *path - chemin du fichier qui sera choisi
*   Return : -
*   Purpose : Permet d'appeller la fonction de creation d'un dictionnaire
*   presente dans gestbib.c en prenant en parametre le chemin precise par
*   l'utilisateur dans la fonction de view_main_menu appellee ici.
*   Si le fichier existe deja, appelle une fonction d'erreur et redemande un
*   chemin valide.
*/
void createDictionaryChoice(int* isAFileSelected, char* path){
    path = NULL;
    getSelectedPath(path); /// !----- fonction de la vue a faire qui doit retourner un path
    while(fopen(*path, "r") != NULL){ // Verifie que le fichier n'existe pas
        messageUser("There is already a file at this path."); /// !----- fonction a faire qui prend en param un message d'erreur
        getSelectedPath(path);
    }
    *isAFileSelected = 1;
    createDictionary(path); /// !----- fonction du model permettant la creation du dictionnaire
}

/*
*   Input : *isAFileSelected - 0 si aucun fichier selectionne, sinon 1
*           *path - chemin du fichier qui sera choisi
*   Return : -
*   Purpose : Demande le chemin a l'utilisateur, et si le fichier existe et est
*   formatte comme un dictionnaire, le considere comme un dictionnaire actif.
*/
void useExistantDictionaryChoice(int* isAFileSelected, char* path){
    path = NULL;
    checkNotNullAndFormatted(path);
    *isAFileSelected = 1;
}

/*
*   Input : *isAFileSelected - 0 si aucun fichier selectionne, sinon 1
*           *path - chemin du fichier qui sera choisi
*   Return : -
*   Purpose : Demande le chemin a l'utilisateur, et si le fichier existe et est
*   formatte comme un dictionnaire, le supprime.
*/
void destroyDictionaryChoice(int* isAFileSelected, char* path){
    path = NULL;
    checkNotNullAndFormatted(path);
    destroyDictionary(path);
    *isAFileSelected = 0;
}

/*
*   Input : *path - chemin du fichier qui sera choisi
*   Return : -
*   Purpose : Permet de verifier que le fichier au chemin indique existe
*   bien et qu'il est formatte comme un dictionnaire, sinon redemande
*   a l'utilisateur un nouveau chemin jusqu'a ce que ce soit le cas.
*/
void checkNotNullAndFormatted(char* path){
    do{
        getSelectedPath(path);
        while(fopen(*path, "r") == NULL){ // Verifie que le fichier existe bien
            messageUser("There is no file at this path.");
            getSelectedPath(path);
        }
        if(!dicoFormatted(path)){ /// !----- fonction du model ou controller vérifiant le bon formattage du fichier dictionnaire
            messageUser("The dictionary is not formatted.")
        }
    }while(!dicoFormatted(path));
}

/*
     int max = 10;
     char * question = "\n Find a name please \n";
     char * name = malloc(sizeof(char)*10);

     askForSring(name,max,question);
*/
