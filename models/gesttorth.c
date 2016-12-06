#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../gestbib.h"
#include "../gesttorth.h"
List * getDifferentWords(char * file, char * dico)
{
    List * fileWords = getWordsFromFile(file);

    List * dicoWords = getWordsFromFile(dico);

    List * newList = compareList(fileWords,dicoWords);

    return newList;

}

List * compareList(List * first, List * second)
{
    List * newList = NULL;
    newList = initialisationList();


    int found = 0;
    Element * word1 = first->first;
    while (word1->next != NULL)
    {
        Element * word2 = second->first;
        while(word2->next != NULL)
        {
            if (strcmp(word1->chaine,word2->chaine) != 0)
            {
                found++;
            }
            word2 = word2->next;
        }
        if (found >= second->length)
        {
            insertion(newList,word1->chaine,word1->lineNumber,word1->firstChar);

        }
        found = 0;

        word1 = word1->next;
    }
    return newList;

}

List * generateFakeList()
{
    List * fake = NULL;
    fake = initialisationList();
    insertion(fake,"mytharda",0,0);
    insertion(fake,"paignoiro",0,0);
    insertion(fake,"bouton",0,0);
    return fake;
}

void replaceWordsInFile (char * file, char * dico)
{
    List * list = getDifferentWords(file, dico);
    List * fake = generateFakeList();



    Element * w1 = list->first;
    Element * w2 = fake->first;
    while (w1->next != NULL)
    {
        w2->firstChar = w1->firstChar;
//        w2->length = w1->length;
        w2->lineNumber = w1->lineNumber;
        w1 = w1->next;
        w2 = w2->next;
    }



    putInFile(fake,file);

}

void putInFile (List * newList, char * filePath)
{
    FILE * file = fopen(filePath, "r+");
    int count = 0;
    int lines = 0;
    if (file != NULL)
    {
        char c = fgetc(file);
        while (c != EOF)
        {

            printf("count : %d char = %c\n",count,c);
            int i,j;
            if (c >= 97 && c <= 122)
            {

                Element * actual = newList->first;

                while (actual->next != NULL)
                {

                    if (count == actual->firstChar && lines == actual->lineNumber)
                    {
                        fseek(file, -1, SEEK_CUR);
                        for (j = 0; j < actual->length; j++)
                        {
                            fprintf(file,"%c",actual->chaine[j]);
                            printf("%c",actual->chaine[j]);

                        }
                        count += actual->length+1;
                        fseek(file, actual->length+1, SEEK_CUR);
                        printf("\n");
                    }
                    actual = actual->next;
                }
            }


            if (c == '\n')
            {
                count = 0;
                lines++;
                printf("line : %d   count = %d\n",lines,count);
                c = fgetc(file);
            }
            else
            {
                c = fgetc(file);
                count++;
            }
        }
    }
    else
    {
        printf("erreur lors de l'ouverture du fichier");
    }
    fclose(file);
}
