#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../gestbib.h"
#include "../gesttorth.h"

/*
*   Input : char * file- Path of the .txt file
*           char * dico - Path of the dictionnary
*   Return : -
*   Purpose : This function will read the source file and then return a List of the words
 that are not in the dictionary.
*/
List * getDifferentWords(char * file, char * dico)
{
    List * fileWords = getWordsFromFile(file);

    List * dicoWords = getWordsFromFile(dico);

    List * newList = compareList(fileWords,dicoWords);

    return newList;

}



/*
*   Input : char * file- Path of the .txt file
*           char * dico - Path of the dictionnary
*   Return : -
*   Purpose : This function will read the source file and then return a List of the words
 that are not in the dictionary with a list of words (inside the dictionary) that could be a good correction.
*/
void printCloseList (char * file, char * dico)
{
    List * test = getDifferentWords(file,dico);
    List * dicoWords = getWordsFromFile(dico);

    Element * actual = test->first;
    while (actual->next != NULL)
    {
        printf("%s\n",actual->chaine);
        List *e = researchWordList(dicoWords,actual->chaine,2);
        int i = 0;
        if (e->length > 0)
        {
            while (i < e->length)
            {
                printf("  Close word : %s\n",e->first->chaine);
                e->first = e->first->next;
                ++i;
            }
        }
        else
        {
            printf("  No close word found\n");
        }

        actual = actual->next;
    }
}


void putCorrectWordsInFIle (char * filePath, char * dico)
{
    List * differents = getDifferentWords(filePath,dico);

    ListOfChar * listOfChar = putInOrder(getListOfCharFromFile(filePath));

    List * newone = putInOrderList(getNewWords(differents,dico));

    //afficherListe(newone);

    Charac * actual = listOfChar->first;
    Element * correct = newone->first;
    while (actual->next != NULL && correct->next != NULL)
    {

        if(correct->firstChar == actual->position
           && correct->lineNumber == actual->line)
        {
            printf("okok : %c\n",actual->character);
            int diff = fabs(differents->first->length - newone->first->length);
            int i;
            for (i = 0; i < newone->first->length; i++)
            {
                if (i >= newone->first->length - diff)
                {
                    Charac * e = malloc(sizeof(Charac));
                    e->character = newone->first->chaine[i];
                    e->line = newone->first->lineNumber;
                    e->position = newone->first->firstChar;

                    e->next = actual->next;
                    actual->next = e;
                    actual = actual->next;
                }
                else
                {
                    actual->character = newone->first->chaine[i];
                    actual = actual->next;
                }

            }
            continue;
        }
        correct = correct->next;
        actual = actual->next;
    }



    Charac * a = listOfChar->first;
    while (a->next != NULL)
    {
        printf("%c",a->character);
        a = a->next;
    }


}

List * getNewWords (List * list, char * dico)
{
    List * dicoWords = getWordsFromFile(dico);
    Element * actual = list->first;
    List * newone = initialisationList();
    while (actual->next != NULL)
    {
        List * e = researchWordList(dicoWords,actual->chaine,2);
        Element * tmp = malloc(sizeof(Element));

        tmp->chaine = e->first->chaine;
        tmp->firstChar = actual->firstChar;
        tmp->lineNumber = actual->lineNumber;
        tmp->length = actual->length;


        tmp->next = newone->first;
        newone->first = tmp;
        actual = actual->next;
    }
    return newone;
}

ListOfChar * putInOrder (ListOfChar * list)
{
    Charac * actual = list->first;
    ListOfChar * newone = initialisationListOfChar();
    while (actual->next != NULL)
    {
        Charac * tmp = malloc(sizeof(Charac));
        tmp->character = actual->character;
        tmp->line = actual->line;
        tmp->position = actual->position;

        tmp->next = newone->first;;
        newone->first = tmp;
        actual = actual->next;
    }

    return newone;
}

List * putInOrderList(List * list)
{
    Element * actual = list->first;
    List * newone = initialisationList();
    while (actual->next != NULL)
    {
        Element * tmp = malloc(sizeof(Element));
        tmp->chaine = actual->chaine;
        tmp->lineNumber = actual->lineNumber;
        tmp->firstChar = actual->firstChar;
        tmp->length = actual->length;


        tmp->next = newone->first;;
        newone->first = tmp;
        actual = actual->next;
    }

    return newone;
}


ListOfChar * getListOfCharFromFile (char * path)
{
     ListOfChar * list = initialisationListOfChar();
    int line = 1;
    int position = 0;

    FILE * file = fopen(path,"r");
    if (file != NULL)
    {
        char c = fgetc(file);
        while (1)
        {
            Charac * charac = malloc(sizeof(Charac));

            charac->character = c;
            charac->line = line;
            charac->position = position;
            charac->next = list->first;

            list->first = charac;

            position++;
            if (c == '\n')
            {
                line++;
                position = 0;
            }
            if (c == EOF) break;
            c = fgetc(file);
        }
        fclose(file);
    }
    return list;
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




