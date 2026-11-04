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
	/* recherche de l'objet à supprimer */
	objet *obj_sup = rechercher_objet(nom);
	if(obj_sup == NULL){
		return 0;
	}

	/* on libère les blocks occupés par l'objet à supprimer */
	unsigned short i = FAT[obj_sup->index];
	while(i != END){
		FAT[obj_sup->index] = FREE; freeblocks += 1;
		obj_sup->index = i;
		i = FAT[obj_sup->index];
	}
	FAT[(*obj_sup).index] = FREE; freeblocks += 1;

	/* on redirige l'objet précédent vers l'objet suivant notre objet à supprimer*/
	objet *obj_pre = obj;
	if(strcmp(obj->nom, obj_sup->nom) != 0){
		while (strcmp((obj_pre->next)->nom, obj_sup->nom) != 0) {
			obj_pre = obj_pre->next;
		}
		obj_pre->next = obj_sup->next;
	}
	else{
		obj = obj_sup->next;
	}
	free(obj_sup);

	return 1;
}

/***********************************************************/
void supprimer_tout()
{
	while((*obj).next != NULL){
		/* on remplace l'objet actuel par le suivant */
		objet *obj_suiv = (*(*obj).next).next;
		free((*obj).next);
		(*obj).next = obj_suiv;
	}
	/* on libère tous les blocks */
	initialiser_fat();
}

int main()
{
	initialiser_fat();
	char data1[2000]; char data2[1000]; char data3[3000]; char data4[1000]; 
	for(int i = 0; i < 2000; i++){
		data1[i] = 'h';
	}
	for(int i = 0; i < 1000; i++){
		data2[i] = 'e';
	}
	for(int i = 0; i < 3000; i++){
		data3[i] = 'l';
	}
	for(int i = 0; i < 1000; i++){
		data4[i] = 'o';
	}

	objet *obj1 = creer_objet("fichier1", 12, 2000, data1);
	objet *obj2 = creer_objet("fichier2", 43, 1000, data2);
	afficher_objet(obj1);
	afficher_objet(obj2);

	afficher_objet(rechercher_objet("fichier2"));

	supprimer_objet("fichier1");

	for(int i = 0; i < 20; i++){
		printf("%d ; ", FAT[i]);
	}
	printf("\n");

	objet *obj3 = creer_objet("fichier3", 25, 3000, data3);
	afficher_objet(obj3);
	objet *obj4 = creer_objet("fichier4", 2, 1000, data4);
	afficher_objet(obj4);

	for(int i = 0; i < 20; i++){
		printf("%d ; ", FAT[i]);
	}
	printf("\n");

	supprimer_objet("fichier3");

	for(int i = 0; i < 20; i++){
		printf("%d ; ", FAT[i]);
	}
	printf("\n");

	supprimer_tout();

	for(int i = 0; i < 20; i++){
		printf("%d ; ", FAT[i]);
	}
	printf("\n");

	return EXIT_SUCCESS;
}
