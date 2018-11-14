
/* TODO (#1#): Problème avec la structure datevent */

struct datevent {
	char date;
	char event;
};

void validerSaisie(char canton[2], char debut[10],char fin [10]);

int comparerDates(char premierJour[10], char dernierJour [10]);

int chargerListeFeries(datevent tableau[]);

void aide(void);
