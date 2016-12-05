typedef struct Element Element;
struct Element
{
    char * chaine;
    Element *next;
    int length;
    int lineNumber;
    int firstChar;
};
typedef struct List List;
struct List
{
    int length;
    Element *first;
};

void createDictionary(char * path);
void useDictionary();
void generateDictionary(char * formatText, char * dictionaryName);
void destroyDictionary(char * path);
void insertWord(char * path, char * word);


int removeElement(List * list, char * value);
void afficherListe(List * list);
List * getWordsFromFile(char * path);
List *initialisationList();
void insertion(List * list, char * stringToAdd, int line, int firstChar);
void fromListToDico (List * elements, char * destination);
char *researchWord(List *List, char *word, int filter);
