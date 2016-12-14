#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../gestbib.h"
#include "../gestexpr.h"
int isSeparator(char a)
{
    if (a == '*')
        return 1;
    return 0;
}
int getNextSeparator(char *pattern)
{

   // debugChar("patternSEP: ", pattern);


    int i = 0;
    for (; i < strlen(pattern); ++i)
    {
        if (isSeparator(pattern[i]) == 1)
        {
      //      debugInt("nextsep: ", i + 1);
            return i + 1;
        }

    }
    return -1;
}
int pointstar(char *pattern, char *word)
{
  //  debugChar("patternPOINTSTAR: ", pattern);
   // debugChar("wordPOINTSTAR: ", word);
    if (strlen(pattern) == 1)
        return 1;
    else
    {
      /* int i = 0;
        for (; i < strlen(word) ++i)
        {
            if (pattern[1] == word[0])
            return match(pattern + 2, word + 1);
        }*/
      //  printf("PAT: %c\n", pattern[1]);
      //  printf("MOT: %c\n", word[strlen(word) - 1]);
      for (int i = 0; i < strlen(word); ++i)
      {
        int check = 0;
        while (pattern[1] == word[i] && i < strlen(word))
        {
            check = 1;
            ++i;
        }
        if (i == strlen(word) && check == 1 && getNextSeparator(pattern + 1) == -1)
            return 1;
        else if ((check == 1 && pattern[1] == word[i - 1]))
        {
            return match(pattern + getNextSeparator(pattern + 1), word + i);
        }

      }


    }
    return 0;
}
int star(char *pattern, char *word, char prev)
{
   // debugChar("","STAR");
    if (prev == '.')
        return pointstar(pattern, word);
    int i = 0;
    while (i < strlen(word) - 1 && word[i] == prev)
    {
        ++i;
    }
    //printf("PAT%c\n",pattern[getNextSeparator(pattern)]);
  //  printf("PAT%c\n",word[i]);
    if (pattern[getNextSeparator(pattern)] == word[i])
        return 1;
    return 0;
}
int match(char *pattern, char *word)
{

    int i = 0;
    for (; i < strlen(pattern); ++i)
    {
       // debugInt("i = ", i);
        if ((isSeparator(pattern[i]) == 0 || pattern[i] == '.') && (i < strlen(pattern) - 1 && pattern[i + 1] != '*'))
        {
          //  printf("carracIF: %c\n", pattern[i]);
            if (pattern[i] == '.')
                continue;
          //  if (i < strlen(pattern) - 1 && pattern[i + 1] == '*')
            if (pattern[i] != word[i])
                return 0;
        }
        else if (pattern[i] == '.' && (i < strlen(pattern) - 1 && pattern[i + 1] != '*') || i == strlen(pattern) - 1)
        {
        //    printf("carracElseIF: %c\n", pattern[i]);
            continue;
        }
        else if (isSeparator(pattern[i]) == 1)
        {
          //  printf("carracELSE: %c\n", pattern[i]);
            return star(pattern + i, word + i, pattern[i - 1]);
        }
        else if (pattern[i] != '.')
        {
         //   printf("carracDEHORS: %c\n", pattern[i]);
            return 0;
        }


    }
    return 1;
}
void getExp(List *dico, char *pattern)
{
    int i = 0;
    Element *element = dico->first;
  //  debugChar("pattern: ", pattern);
    for (; i < dico->length; ++i)
    {

     //   debugChar("wordMATCH: ", element->chaine);
        if (match(pattern, element->chaine) == 1)
            printf("%s\n", element->chaine);
        element = element->next;
    }
   return;
}
