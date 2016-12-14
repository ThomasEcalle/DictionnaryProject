void emptyBuffer();
void clearConsole();
void propositions(int *userChoice);
void printWarning(char * warning);
void printErrorMessage (char * error);
void printMenu (char ** stringArray,int * userChoice, int size);
void askForNumber (int * numberAsked, char * question, int min, int max);
void askForSring (char * answer, char * question, int minSize,int maxSize);
void printWordsList (struct List * listToPrint, int interval);
struct List * putListInOrder (struct List * listToSort);
int main();


