void emptyBuffer();
void clearConsole();
void propositions(int *userChoice);
void printWarning(char * warning);
void printErrorMessage (char * error);
void printMenu (char ** stringArray,int * userChoice);
void askForNumber (int * numberAsked, char * question, int min, int max);
void askForSring (char * answer, char * question, int minSize,int maxSize);
void printWordsList (List * listToPrint, int interval);
List * putListInOrder (List * list);
int main();


