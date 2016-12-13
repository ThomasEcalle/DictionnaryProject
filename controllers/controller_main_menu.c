#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../constantes.h"
#include "../view_main_menu.h"



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
    char *choicesArray[] = {"Create a dictionary",
                            "Use an existing dictionary",
                            "Make a dictionary from a text file",
                            "Destroy a dictionary"};
    printMenu (choicesArray, &userChoice);
    switch(userChoice){
        case 1:
            createDictionaryChoice(isAFileSelected, path);
            break;
        case 2:
            useExistantDictionaryChoice(isAFileSelected, path);
            break;
        case 3:
            convertFileIntoDictionaryChoice(isAFileSelected, path);
            break;
        case 4:
            destroyDictionaryChoice(isAFileSelected, path);
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("This is not a valid option\n");
            break;
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
    printf("Please select a path for the dictionary (e to exit).\nYour path : ");
    scanf("%s", path);
    FILE* fp = fopen(path, "r");
    while(strcmp(path, "e") != 0 && fp != NULL){ // Verifie que le fichier n'existe pas
        fclose(fp);
        free(path);
        path = malloc(sizeof(char) * 255);
        printErrorMessage ("This path already contain a file.\nPlease select another path (e to exit).");
        printf("\nYour new path : ");
        scanf("%s", path);
        fp = fopen(path, "r");
    }
    fclose(fp);
    createDictionary(path);


    if(strcmp(path, "e") != 0){
        *isAFileSelected = 1;
        clearConsole();
        fp = fopen(path, "r");
        if(fp != NULL){
            printf("\nYour dictionary has been created !\n\n");
        }
        else{
            printWarning("\nAn error occured, the file hasn't been created.\n\n");
        }
        fclose(fp);
    }

}

/*
*   Input : *isAFileSelected - 0 si aucun fichier selectionne, sinon 1
*           *path - chemin du fichier qui sera choisi
*   Return : -
*   Purpose : Demande le chemin a l'utilisateur, et si le fichier existe et est
*   formatte comme un dictionnaire, le considere comme un dictionnaire actif.
*/
void useExistantDictionaryChoice(int* isAFileSelected, char* path){
    printf("Please select the path of the dictionary (e to exit).\nYour path : ");
    scanf("%s", path);
    FILE* fp = fopen(path, "r");
    while(strcmp(path, "e") != 0 && fp == NULL){ // Verifie que le fichier n'existe pas)
        fclose(fp);
        free(path);
        path = malloc(sizeof(char) * 255);
        printErrorMessage ("The file doesn't exist.\nPlease select another path (e to exit).");
        printf("\nYour new path : ");
        scanf("%s", path);
        fp = fopen(path, "r");
    }
    fclose(fp);
    if(strcmp(path, "e") != 0){
        *isAFileSelected = 1;
        clearConsole();
    }
}

void convertFileIntoDictionaryChoice(int* isAFileSelected, char* path){
    printf("Please select the path of the file that your want to convert (e to exit).\nYour path : ");
    char* file = malloc(sizeof(char) * 255);
    scanf("%s", file);
    FILE* fp = fopen(file, "r");
    while(strcmp(file, "e") != 0 && fp == NULL){ // Verifie que le fichier n'existe pas
        free(file);
        fclose(fp);
        file = malloc(sizeof(char) * 255);
        printErrorMessage ("The file doesn't exist.\nPlease select another path (e to exit).");
        printf("\nYour new path : ");
        scanf("%s", file);
        fp = fopen(file, "r");
    }
    if(strcmp(path, "e") == 0){
        return 0;
    }
    fclose(fp);
    printf("Please select the path of the file to create (e to exit).\nYour path : ");
    scanf("%s", path);
    fp = fopen(path, "r");
    while(strcmp(path, "e") != 0 && fopen(path, "r") != NULL){ // Verifie que le fichier n'existe pas
        free(path);
        fclose(fp);
        path = malloc(sizeof(char) * 255);
        printErrorMessage ("There is already a file at the path.\nPlease select another path (e to exit).");
        printf("\nYour new path : ");
        scanf("%s", path);
        fp = fopen(path, "r");
    }
    fclose(fp);
    if(strcmp(path, "e") != 0){
        *isAFileSelected = 1;
        clearConsole();
        generateDictionary(file, path);
        fp = fopen(path, "r");
        if(fp != NULL){
            printf("The file has been created!\n");
        }
        else{
            printWarning("An error occured. The file hasn't been created.");
        }
        fclose(fp);
    }
}

/*
*   Input : *isAFileSelected - 0 si aucun fichier selectionne, sinon 1
*           *path - chemin du fichier qui sera choisi
*   Return : -
*   Purpose : Demande le chemin a l'utilisateur, et si le fichier existe et est
*   formatte comme un dictionnaire, le supprime.
*/
void destroyDictionaryChoice(int* isAFileSelected, char* path){
    printf("Please select the path for the dictionary (e to exit).\nYour path : ");
    scanf("%s", path);
    FILE* fp = fopen(path, "r");
    while(strcmp(path, "e") != 0 && fp == NULL){ // Verifie que le fichier n'existe pas
        free(path);
        fclose(fp);
        path = malloc(sizeof(char) * 255);
        printErrorMessage ("The file doesn't exist.\nPlease select another path (e to exit).");
        printf("\nYour new path : ");
        scanf("%s", path);
        fp = fopen(path, "r");
    }
    fclose(fp);
    if(strcmp(path, "e") != 0){
        clearConsole();
        destroyDictionary(path);
        fp = fopen(path, "r");
        if(fp == NULL){
            printf("\nThe dictionary has been destroyed !\n\n");
        }
        else{
            printWarning("An error occured, the file hasn't been destroyed.");
        }
        fclose(fp);
    }
}

/*
*   Input : *path - chemin du fichier qui sera choisi
*   Return : -
*   Purpose : Permet de verifier que le fichier au chemin indique existe
*   bien et qu'il est formatte comme un dictionnaire, sinon redemande
*   a l'utilisateur un nouveau chemin jusqu'a ce que ce soit le cas.
*/
void checkNotNullAndFormatted(char* path){
    /*do{
        getSelectedPath(path);
        while(fopen(*path, "r") == NULL){ // Verifie que le fichier existe bien
            messageUser("There is no file at this path.");
            getSelectedPath(path);
        }
        if(!dicoFormatted(path)){ /// !----- fonction du model ou controller vérifiant le bon formattage du fichier dictionnaire
            messageUser("The dictionary is not formatted.");
        }
    }while(!dicoFormatted(path));*/
}
