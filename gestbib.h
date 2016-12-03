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

void createDictionary();
void useDictionary();
void generateDictionary();
void destroyDictionary();
void insertWord();


int removeElement(List * list, char * value);
void afficherListe(List * list);
void getWordsFromFile(char * path, List * elementsList);
List *initialisationList();
void insertion(List *list, char * string);
void fromListToDico (List * elements, char * destination);
char *researchWord(List *List, char *word, int filter);
