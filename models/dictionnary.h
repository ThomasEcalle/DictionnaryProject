#ifndef DICTIONNARY_H_INCLUDED
#define DICTIONNARY_H_INCLUDED

typedef struct Element Element;
struct Element
{
    char * chaine;
    Element *next;
    int length;
};
typedef struct List List;
struct List
{
    int length;
    Element *first;
};
void putInDictionnary(char * src, char * destination);
int removeElement(List * list, char * value);
Element * recursiveSort (Element * a, Element * b);
void afficherListe(List * list);
void getWordsFromFile(char * path, List * elementsList);
List *initialisationList();
void insertion(List *list, char * string);
void reinitialisationString(char * string, int size);

#endif // CONSTANTES_H_INCLUDED




