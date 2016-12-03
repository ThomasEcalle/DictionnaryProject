#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dictionnary.h"
int compare(char *a, char *b)
{
    int len1 = strlen(a);
    int len2 = strlen(b);
    if (len1 > len2)
        return compare(b, a);
    return len2 - len1;
}
char *substr(char *src, int len)
{
    if (len > strlen(src))
        return NULL;
    char *res = malloc(sizeof (char) * (len + 1));
    int i = 0;
    for (; i < len; ++i)
    {
        res[i] = src[i];
    }
    res[i] = '\0';
    return res;
}
void debugChar(char *msg, char *var)
{
    printf("%s    ", msg);
    printf("%s\n", var);
}
void debugInt(char *msg, int var)
{
    printf("%s    ", msg);
    printf("%d\n", var);
}
void createDictionary(){
}

void generateDictionary(){
}

void destroyDictionary(){
}

void insertWord(){
}

char *researchWord(List *List, char *word, int filter)
{
    char *closest = "";
    int len = strlen(word);
    Element *Element = malloc(sizeof (Element));
    Element = List->first;
    for (int i = 0; i < List->length; Element = Element->next)
    {
//        debugChar("Element", Element->chaine);
        if (len > Element->length)
        {
            ++i;
            continue;
        }

        char *tmp = substr(Element->chaine, len);

//        debugChar("word", word);
//        debugChar("TMP", tmp);
        if (strcmp(tmp, word) == 0)
        {
//            debugChar("Research word : on entre dans debut commun", Element->chaine);
            int diff = compare(Element->chaine,word);
//            debugChar(word, Element->chaine);
//            debugInt("DIFF : ", diff);
            if (diff == 0)
            {
                debugChar("RESULT :", Element->chaine);
                return Element->chaine;
            }
            else if (diff <= filter)
            {
                if ((strlen(closest) == 0 && diff <= filter) || diff < filter)
                {
                    filter = diff;
                    closest = Element->chaine;
                }

            }
        }
//        debugChar("CLOSEST :", closest);
        ++i;
    }
    debugChar("RESULT :", closest);
    return closest;

}
