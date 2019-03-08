

struct datevent {
	time_t date;
	char event[30];
};

struct settings {
	char language[3]; /*language : en, fr, it...*/
	char dateType[3]; /*Date system: us, eu,...*/
	char *pathHoliday; /*Path to holiday directory : /data,...*/
	int autoYear; /*Defined year for auto-completion : 2016, 2018,...*/
};

void freeP (void * pointer);
void freePpChar (char ** pPointer);

int initSettigns(struct settings *settings);

int complYear(int userChoice, int *varOption);
int setPath(char* userChoice, char **path);

int validerEtFormaterFeries(char **listeFeries, struct settings *settings, char *canton);

int validerEtFormaterDate(struct tm *date, char *saisie, int autoYear, int formatEntree);

struct datevent *chargerListeFeries(char **fichierFeries, int *ptrTailleTab);

int comparerDates(struct tm *debut, struct tm *fin, struct datevent tabFeries[], int tailleTabFeries);



void help(void);
