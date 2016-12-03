<<<<<<< HEAD
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

=======
#include "models/dictionnary.h"
>>>>>>> origin/master
void createDictionary();
void useDictionary();
void generateDictionary();
void destroyDictionary();
void insertWord();
<<<<<<< HEAD
void researchWord();
int removeElement(List * list, char * value);
void afficherListe(List * list);
void getWordsFromFile(char * path, List * elementsList);
List *initialisationList();
void insertion(List *list, char * string);
=======
char *researchWord(List *List, char *word, int filter);
>>>>>>> origin/master
