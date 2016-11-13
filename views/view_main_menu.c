#include <stdio.h>
#include <stdlib.h>
#include "../constantes.h"


void propositions(int *userChoice)
{
    printf("\nWhat would you like to do ?\n"
       "1- Create a dictionary\n"
       "2- Use an existing dictionary\n"
       "3- Make a dictionary from a text file\n"
       "4- Destroy a dictionary\n"
       "5- Quit application now");
       scanf("%d", userChoice);
       emptyBuffer();
    if(*userChoice < 1 || *userChoice > 5){
        *userChoice = NULL;
    }
}

void askForSring (char * string, char * question, char * errorMessage, int minSize,int maxSize)
{
    int error = 0;
    int check = 0;
    while (!check)
        {
        if (error)
        {
            printf("%s\n",errorMessage);
        }else{
            printf("%s\n",question);
        }

        scanf("%s",string);
        emptyBuffer();
        int i;
        int size = strlen(string);
        if (size <= maxSize && size >= minSize)
        {
            check++;
        }else{
            error++;
        }
        for (i = 0; i < size; i++)
        {
            if ((string[i] < 65 || string[i] > 90) && (string[i] <97 || string[i] > 122))
            {
                // il y a d'autres caraactères qui ne sont pas des 'lettres'
                check = 0;
                error++;
            }
        }
        if (check){
            clearConsole();
        }
    }
}

void clearConsole()
{
    system("cls");
}

void askForNumber (int * numberAsked, char * question, char * errorMessage, int min, int max)
{
    int error = 0;
    int check = 0;
    while (!check)
    {
        if (error)
        {
            printf("%s\n",errorMessage);
        }
        else
        {
            printf("%s\n",question);
        }
        scanf("%d",numberAsked);
        emptyBuffer();
        if (*numberAsked >= min && *numberAsked <= max)
        {
            check++;
            clearConsole();
        }
        else
        {
            error++;
        }
    }
}

void printMenu (char ** stringArray,int * userChoice)
{
    int size = strlen(stringArray);
    int i;
    int check = 0;
    while (!check){
       for (i = 0; i < size; i++){
        printf("%d)%s\n",i+1,stringArray[i]);
        }
        printf("%d)Quit application\n",size+1);
        scanf("%d",userChoice);
        emptyBuffer();
        if (*userChoice >= 1 && *userChoice <= size+1){
            check++;
            clearConsole();
        }
    }
}

void emptyBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}
