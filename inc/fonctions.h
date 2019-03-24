

struct datevent {
	time_t date;
	char event[30];
};

struct settings {
	char *pathToLang;
	char lang[3]; /*lang : en, fr, it...*/
	char *pathToHoliday; /*Path to holiday directory : /data,...*/
	char defaultHoliday[3];
	char dateType[3]; /*Date system: us, eu,...*/
	int autoYear; /*Defined year for auto-completion : 2016, 2018,...*/
};

void freeP (void * pointer);
void freePpChar (char ** pPointer);

int initSettings(struct settings *settings);

int showSettings(struct settings *settings);


int complYear(int userChoice, struct settings *settings);
char * setPath(char* userChoice);

int validerEtFormaterFeries(char **listeFeries, struct settings *settings, char *canton);

int validerEtFormaterDate(struct tm *date, char *saisie, struct settings *settings);

struct datevent *chargerListeFeries(char **fichierFeries, int *ptrTailleTab);

int comparerDates(struct tm *debut, struct tm *fin, struct datevent tabFeries[], int tailleTabFeries);



void help(void);
