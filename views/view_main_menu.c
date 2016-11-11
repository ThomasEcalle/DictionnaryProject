#include <stdio.h>
#include <stdlib.h>
#include "../constantes.h"


void propositions(int *userChoice)
{
    while (*userChoice < 1 || *userChoice > 4)
    {
        printf("\nWhat would you like to do ?\n"
           "1- Create a dictionary\n"
           "2- Use an existing dictionary\n"
           "3- Make a dictionary from a text file\n"
           "4- Destroy a dictionary\n");
           scanf("%d", userChoice);
           emptyBuffer();
    }
}

void askForSring (char * name, int maxSize, char * question)
{
    int check = 0;
    while (!check){
        printf("%s",question);
        scanf("%s",name);
        emptyBuffer();
        int i;
        int size = strlen(name);
        if (size <= maxSize)
        {
            check++;
        }
        for (i = 0; i < size; i++)
        {
            if ((name[i] < 65 || name[i] > 90) && (name[i] <97 || name[i] > 122))
            {
                // il y a d'autres caraactères qui ne sont pas des 'lettres'
                check = 0;
            }
        }
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
