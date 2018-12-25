
/* DONE (#1#): Problème avec la structure datevent */

struct datevent {
	time_t date;
	char event[30];
};

int recupererLigneCmde(char ***ptrTabArguments, size_t tailleTampon);

int validerEtFormaterFeries(char **listeFeries, char *canton);

int validerEtFormaterDate(struct tm *date, char *saisie, int formatEntree);

struct datevent *chargerListeFeries(char **fichierFeries, int *ptrTailleTab);

int comparerDates(char premierJour[11], char dernierJour[11], struct datevent tabFeries[], int tailleTabFeries);



void aide(void);
