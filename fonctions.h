
/* DONE (#1#): Probl�me avec la structure datevent */

struct datevent {
	time_t date;
	char event[30];
};

char *validerCanton(char canton[3]);

struct datevent *chargerListeFeries(struct datevent tabFeries[], char canton[2], int *ptrTailleTab);

int comparerDates(char premierJour[11], char dernierJour[11], struct datevent tabFeries[], int tailleTabFeries);



void aide(void);
