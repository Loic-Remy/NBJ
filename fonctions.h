
/* DONE (#1#): Probl�me avec la structure datevent */

struct datevent {
	time_t date;
	char event[30];
};

void validerSaisie(char canton[3], char debut[11],char fin [11]);

int comparerDates(char premierJour[11], char dernierJour[11], struct datevent * tabFeries);

int chargerListeFeries(struct datevent tableau[], char canton[2]);

void aide(void);
