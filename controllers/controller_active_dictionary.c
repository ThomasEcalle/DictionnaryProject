#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../gestbib.h"
#include "../gesttorth.h"
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
                            "Search if a word is in the dictionary"/*,
                            "Get the list of the closest words in the dictionary of a word",
                            "Correct a file using words in the dictionary",*/
                            "Return to the main menu"
                            };
    printMenu (choicesArray, &userChoice, 6);
    switch(userChoice){
        case 1:
            listWordChoice(path);
            break;
        case 2:
            insertWordChoice(path);
            break;
        case 3:
            researchWordChoice(path);
            break;
        case 4:
            researchClosestWordsChoice(path);
            break;
        case 5:
            correctFile(path);
            break;
        case 6:
            free(path);
            path = malloc(sizeof(char) * 255);
            *isAFileSelected = 0;
            break;
        case 7:
            exit(0);
            break;
        default:
            printf("This is not a valid option\n");
            break;
    }
}

void listWordChoice(char* path){
    printWordsList(getWordsFromFile(path), 20);
    printf("\n\n");
}

void insertWordChoice(char* path){
    char* word = calloc(255, sizeof(char));
    do{
        printf("Please type the word you want to insert in the dictionary (e to exit).\nYour choice : ");
        fflush(stdin);
        fgets(word, 255, stdin);
        word[strlen(word) - 1] = '\0';
        if(strcmp(word, "e") == 0){
            clearConsole();
            free(word);
            return 0;
        }
        else if(isWord(word) == 0){
            printf("You try to enter something else than a word in the dictionary.\n");
            free(word);
            return 0;
        }
    }while(strcmp(word, "") == 0);
    if(strcmp(word, "e") != 0){
        insertWord(path, word);
        printf("\nYour word has been added to the dictionary !\n");
    }
    free(word);
}

void researchWordChoice(char* path){
    char* word = malloc(sizeof(char) * 255);
    printf("Please type the word you want to search (e to exit).\nYour word : ");
    scanf("%s", word);
    if(strcmp(word, "e") == 0){
        return 0;
    }
    char* closeWord = research(getWordsFromFile(path), word);
    if(strcmp(closeWord, "") == 0){
        printf("This word is not in the dictionary !\n");
    }
    else{
        printf("This word has been find in the dictionary.\n");
    }
}

void researchClosestWordsChoice(char* path){
    char* word = malloc(sizeof(char) * 255);
    printf("Please type the word you want to search (e to exit).\nYour word : ");
    scanf("%s", word);
    if(strcmp(word, "e") == 0){
        return 0;
    }
    char* threshold = malloc(sizeof(char) * 255);
    char* ptr;
    long realThreshold;
    do{
        printf("\nPlease choose the number of the threshold (number of letters differents) of your research.\nThreshold : ");
        scanf("%s", threshold);
        realThreshold = strtol(threshold, &ptr, 10);
    }while(realThreshold == NULL && strlen(ptr) > 0);

    List* list = researchWordList(getWordsFromFile(path), word, realThreshold);
    if(list->length == 0){
        printf("\nNo word match.\n");
    }
    else{
        printf("\nThere is %d which match your word with this threshold: \n", list->length);
        printWordsList(list, 20);
    }
}

void correctFile(char* path){
    printf("Please select the file you want to correct using this dictionary (e to exit).\nYour path : ");
    char* file = malloc(sizeof(char) * 255);
    scanf("%s", file);
    FILE* fp = fopen(file, "r");

    while(strcmp(file, "e") != 0 && fp == NULL){ // Verifie que le fichier n'existe pas)
        fclose(fp);
        free(file);
        file = malloc(sizeof(char) * 255);
        printErrorMessage ("The file doesn't exist.\nPlease select another path (e to exit).");
        printf("\nYour new path : ");
        scanf("%s", file);
        fp = fopen(file, "r");
    }
    fclose(fp);
    if(strcmp(file, "e") == 0){
        return 0;
    }
    clearConsole();
    printf("\nThe words which has not been find in the dictionary are : \n");

    printDifferentsWords(file, path);

    printf("\nDo you want to see the correction of unknown words ? (y or n)\nYour answer : ");

    char* answer = askForYorN();
    if(answer == 1){
        printCloseList(file, path);
    }

    printf("\nDo you want to correct the file with the words of the dictionary ? (every unknown word will be replaced if a word "
           "with a threshold of 2 is find in the dictionary)\nYour answer : ");
    answer = askForYorN();
    clearConsole();
    if(answer == 1){
        putCorrectWordsInFIle(file, path);
        printf("\nThe file has been corrected !\n");
    }
}

int askForYorN(){
    char* answer = malloc(sizeof(char) * 255);
    scanf("%s", answer);
    while(strcmp(answer, "n") != 0 && strcmp(answer, "y") != 0){
        printf("\nPlease answer with y or n.\nYour answer : ");
        free(answer);
        char* answer = malloc(sizeof(char) * 255);
        scanf("%s", answer);
    }
    if(strcmp(answer, "n") == 0){
        free(answer);
        return 0;
    }
    else if(strcmp(answer, "y") == 0){
        free(answer);
        return 1;
    }
}
