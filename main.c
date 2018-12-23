
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonctions.h"


int main(int argc, char *argv[]) 
{

char canton[3]={0};
char debut[11]={0};
char fin[11]={0};
char tampon[100]={0};
size_t bufSize=50;

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

char *fichierFeries=NULL;
struct datevent *tabFeries=NULL;

int tailleTab=0;
int *ptrTailleTab=&tailleTab;

printf("Cmde: %s\tCanton: %s\tDebut: %s\tFin: %s",argv[1], argv[2], argv[3], argv[4]);

validerEtFormaterFeries(&fichierFeries,argv[2]);

printf("\nFichier a ouvrir: %s",fichierFeries);

tabFeries=chargerListeFeries(&fichierFeries,ptrTailleTab);

comparerDates(argv[3],argv[4],tabFeries,tailleTab);



return 0;
}
