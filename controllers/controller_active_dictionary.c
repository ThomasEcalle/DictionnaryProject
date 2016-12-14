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
                            "Search if a word is in the dictionary",
                            "Search the more close word in the dictionary of a word",
                            "Get the list of the closest words in the dictionary of a word",
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
            break;
        case 5:
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

void researchCloseWordChoice(char* path){
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
        printf("Please choose the number of the threshold (number of letters differents) of your research.\nThreshold : ");
        scanf("%s", threshold);
        realThreshold = strtol(threshold, &ptr, 10);
    }while(realThreshold == NULL && strlen(ptr) > 0);
    char* closeWord = researchWordInFIle(path, word, realThreshold);
    if(strlen(closeWord) == 0){
        printf("There is no result for this word and threshold in the dictionary. Maybe try with another !\n");
    }
    else{
        printf("The word has been find in the file with the threshold ! Result : %s\n", closeWord);
    }
}

void researchClosestWordChoice(char* path){
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
        printf("Please choose the number of the threshold (number of letters differents) of your research.\nThreshold : ");
        scanf("%s", threshold);
        realThreshold = strtol(threshold, &ptr, 10);
    }while(realThreshold == NULL && strlen(ptr) > 0);
    char* closeWord = researchWordInFIle(path, word, realThreshold);
    if(strlen(closeWord) == 0){
        printf("There is no result for this word and threshold in the dictionary. Maybe try with another !\n");
    }
    else{
        printf("The word has been find in the file with the threshold ! Result : %s\n", closeWord);
    }
}
