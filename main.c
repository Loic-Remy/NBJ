
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonctions.h"


int main(int argc, char *argv[]) 
{
size_t bufSize=50;
char *fichierFeries=NULL;
struct datevent *tabFeries=NULL;

int tailleTab=0;
int *ptrTailleTab=&tailleTab;


do {

if (argc==1) {
	recupererLigneCmde(&argv,bufSize);
	}

/*DEBUT ZONE DE TEST
size_t i=0;
for (i=0; i<=argc; i++) {
	printf("\nArgument [%d] : %s",i, argv[i]);
	}

printf("\n");
system("PAUSE");
FIN ZONE DE TEST */

//printf("Cmde: %s\tCanton: %s\tDebut: %s\tFin: %s",argv[1], argv[2], argv[3], argv[4]);

if (strcmp(argv[1],"calc")==0) {
	
	validerEtFormaterFeries(&fichierFeries,argv[2]);
	printf("\nFichier a ouvrir: %s",fichierFeries);
	tabFeries=chargerListeFeries(&fichierFeries,ptrTailleTab);
	comparerDates(argv[3],argv[4],tabFeries,tailleTab);
	argc=1;
	}
else if (strcmp(argv[1],"loc")==0) {
	
	argc=1;	
	}
else if (strcmp(argv[1],"edit")==0) {
	
	argc=1;	
	}
else if (strcmp(argv[1],"help")==0) {
		
	aide();
	argc=1;
	}	
else if (strcmp(argv[1],"exit")==0) {
		
	exit(EXIT_SUCCESS);
	}		
else {
		
	printf("\nCommande inconnue. Tapez la commande 'help' pour obtenir de l'aide.\n");
	argc=1;
	}		

//printf("\n");
//system("PAUSE");

}
while (strcmp(argv[1],"exit")!=0);

return 0;
}
