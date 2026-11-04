#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fat.h"

// Attention quelques variables globales.... 
// la tête des objets
objet *obj = NULL;

// le volume de données DATA = disque 
char volume[BLOCSIZE * BLOCNUM];

// les METADATAs
unsigned short FAT[BLOCNUM];
unsigned short freeblocks;

/*******************************************/
void initialiser_fat()
{
	int i;
	// initialement on a BLOCNUM blocs libres. 
	freeblocks = BLOCNUM;
	// on va initialiser le tableau à FREE
	for (i = 0; i < BLOCNUM; i++)
		FAT[i] = FREE;
	// on allouera la memoire plus tard pour la structure des noeuds. 
	obj = NULL;
}

/*******************************************/
objet *rechercher_objet(char *nom)
{
	if (obj==NULL){return NULL;}
	objet *bj = obj;
    while (bj != NULL) {
        if (strcmp(bj->nom, nom) == 0) {
            return bj; 
        }
        bj = bj->next;
    }
	return NULL;
}

/**********************************************/

void afficher_objet(objet * o)
{
	unsigned int index;
	if (o == NULL)
		return;

	printf("==========================\nNOM: %s\n", o->nom);
	printf("AUTEUR: %d\n", o->auteur);
	printf("TAILLE: %d\n", o->taille);
	if (o->taille == 0)
		return;
	printf("BLOCS: ");
	index = o->index;
	do {
		printf("%d ", index);
		index = FAT[index];
	} while (index != END);
	printf("\n==========================\n");
}

/*******************************************/
objet *creer_objet(char *nom, unsigned short auteur, unsigned int taille,
		   char *data)
{
	if (rechercher_objet(nom)==NULL&&freeblocks>=taille/BLOCSIZE +1){
		objet *bj=obj;
		objet *noeud=malloc(sizeof(objet));
		if (bj!=NULL){
			while (bj->next!=NULL){
				bj=bj->next;
			}
			bj->next=noeud;
		}
		else{
			bj=noeud;
			obj=noeud;
		}
		strcpy(noeud->nom,nom); 
		noeud->taille=taille; 
		noeud->auteur=auteur; 
		int indicepres=-1;
		unsigned int taille_s = 0; 

		for (int i =0; i<BLOCNUM; i++) {
			if (FAT[i]==FREE){
				if (taille_s>=taille){
					FAT[indicepres]=i; 
					FAT[i]=END;
					freeblocks--;
					noeud->next=NULL;
					return noeud; 
				}
				if (indicepres==-1){
					noeud->index=i;
					indicepres=i;}
				else {
					FAT[indicepres]=i;
					indicepres=i; }
				int j=0; 
				while ((taille_s!=taille)&&(j!=512)){
					volume[i*BLOCSIZE+j]= data[taille_s];
					j++; taille_s++;
				}
				freeblocks--;
				}
			}
		}
	return NULL;
}

/********************************************/

int supprimer_objet(char *nom)
{
	//a completer 
	return 1;
}

/***********************************************************/
void supprimer_tout()
{
	// a completer 
}

int main()
{
	char data1[1000];
	for (int i =0; i<1000;i++){
		data1[i]='u';
	}
	initialiser_fat();
	afficher_objet(creer_objet("ok", 12, 1000, data1));
	afficher_objet(creer_objet("okd",12,1000,data1));
	return EXIT_SUCCESS;
}
