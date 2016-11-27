#include <stdio.h>
#include <stdlib.h>
#include "../constantes.h"

/*
 NE PLUS UTILISER JEAN ! UTILISER FONCTION POUR MENU OU POUR STRING
 JE LA LAISSE POUR POUVOIR COMPILER SANS CHANGER TON CODE MAIS IL FAUDRA L EFFACER
 ET APPELER LES AUTRES FONCTIONS A LA PLACE !
*/
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

/*
*   Input : char * answer -> the String we want the user to fill
            char * question -> the question we want to ask him
            int min -> minimum size
            int max -> maximum size
*   Return : -
*   Purpose : this function ask a question to the user and want him to answer with a String (ONLY LETTERS)
    inside the function is a process to handle size errors
*/
void askForSring (char * answer, char * question, int minSize,int maxSize)
{
    char * errorMessage = malloc(sizeof(char)*50);
    sprintf(errorMessage, "Please enter between %d et %d characters", minSize,maxSize);

    int error = 0;
    int check = 0;
    while (!check)
        {
        if (error)
        {
            printf("%s\n",errorMessage);
        }else
        {
            printf("%s\n",question);
        }

        scanf("%s",answer);
        emptyBuffer();
        int i;
        int size = strlen(answer);
        if (size <= maxSize && size >= minSize)
        {
            check++;
        }else{
            error++;
        }
        for (i = 0; i < size; i++)
        {
            if ((answer[i] < 65 || answer[i] > 90) && (answer[i] <97 || answer[i] > 122))
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


/*
*   Input : int * numberAsked -> the number to fill
            char * question -> the question we want to ask
            int min -> minimum size
            int max -> maximum size
*   Return : -
*   Purpose : this function ask a question to the user and want him to answer with an integer
    inside the function is a process to handle size errors
*/
void askForNumber (int * numberAsked, char * question, int min, int max)
{
    char * errorMessage = malloc(sizeof(char)*50);
    sprintf(errorMessage, "Please enter a number between %d and %d", minSize,maxSize);
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

/*
*   Input : char ** stringArray -> An array of String which represent all the choices in the menu
            int * userChoice -> the int variable which will be change by the user
*   Return : -
*   Purpose : this function can display any menu we want to show to the user
            the function add a LAST choice (size + 1) that represents the willing of quitting the menu (EXIT)
*/
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

/*
*   Input : char * error -> The error message you want the user to see
*   Return : -
*   Purpose : This function just show a "beautiful" error message (developers are artists first)
*/
void printErrorMessage (char * error)
{
    int size = strlen(error);
    int i;
     printf("\n");
    for (i = 0; i < size + 9; i++)
    {
        printf("*");
    }
    printf("\n\nERROR :  %s\n\n",error);
    for (i = 0; i < size+9; i++)
    {
        printf("*");
    }
    printf("\n");
}
/*
*   Input : char * warning -> The warning message you want the user to see
*   Return : -
*   Purpose : This function just show a "beautiful" warning message
    (developers are artists first and yes, it is an arrow)
*/
void printWarning(char * warning)
{
    int i,j;
    printf("\n\n");
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if ((i == 0 || i == 2 || i ==4) && j < 4)
            {
                printf(" ");
            }
            else if (i == 2 && j == 8)
            {
               printf("*    %s",warning);
            }
            else if ((i == 0 || i == 4)&& j == 5)
            {
                printf("*");
            }
            else if (j <= 6)
            {
                printf("*");
            }
            else if (j == 7 && (i >= 1 && i <=3))
            {
                printf("*");
            }
        }
        printf("\n");
    }
    printf("\n\n");


}


/*
*   Input : char ** array -> An array of representing all the words to display
            int size -> the array's size
            int interval -> this interval represents the number of words you want to display by block
            (5 by 5, 3 by 3, 38 by 38, ....)
*   Return : -
*   Purpose : This function can display all words of an array a good looking way
            it add a number to the word and then display them by "block" in order not to diplay a too big number
            of word in one time
*/
void printWordsList (char ** array, int size, int interval)
{
    char * warning = "You have seen all the words";
    int i;
    int check = 0;
    int actual = 0;
    char choice = 0;
    if (size > interval)
    {
        while (!check)
        {
            printf("\n");
           for (i = actual; i < actual + interval; i++)
            {
                if (i < size)
                {
                     printf("%d)%s\n",i+1,array[i]);
                }
            }
            actual = i;
            if (actual >= size)
            {
                 printWarning(warning);
                 check++;
            }
            else
            {
                printf("\nPress any key to continue or 'n' to stop\n");
                scanf("%c",&choice);
                emptyBuffer();
                if (choice == 'n')
                {
                    check++;
                }
            }
        }
    }
    else
    {
        for (i = 0; i < size; i++)
        {
            printf("*%s\n",array[i]);
        }
        printWarning(warning);
    }
}


void clearConsole()
{
    system("cls");
}

void emptyBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}
