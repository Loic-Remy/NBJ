
/* DONE (#1#): Problème avec la structure datevent */

struct datevent {
	time_t date;
	char event[30];
};

int recupererSaisie(void);

int validerEtFormaterFeries(char **listeFeries, char *canton);

int validerEtFormaterDate(char **DateValide, char *Saisie);

struct datevent *chargerListeFeries(struct datevent tabFeries[], char **fichierFeries, int *ptrTailleTab);

int comparerDates(char premierJour[11], char dernierJour[11], struct datevent tabFeries[], int tailleTabFeries);



void aide(void);
