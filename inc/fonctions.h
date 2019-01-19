

struct datevent {
	time_t date;
	char event[30];
};

void freeP (void * pointer);
void freePpChar (char ** pPointer);

int complYear(int userChoice, int *varOption);
int setPath(char* userChoice, char **path);

int validerEtFormaterFeries(char **listeFeries, char *canton);

int validerEtFormaterDate(struct tm *date, char *saisie, int autoYear, int formatEntree);

struct datevent *chargerListeFeries(char **fichierFeries, int *ptrTailleTab);

int comparerDates(struct tm *debut, struct tm *fin, struct datevent tabFeries[], int tailleTabFeries);



void help(void);
