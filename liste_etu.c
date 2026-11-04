#include <stdlib.h>
#include <stdio.h>

/* Ici, on est obligé d'utiliser la notation struct xxx,
car la structure s'auto-référence!
  /!\  Attention il s'agit ici d'une redéfinition de type avec le mot clef typedef   /!\
 Lnode est donc un nouveau type de maillon de liste chaînée contenant uniquement un caractère 
*/

typedef struct node {
	char data;
	struct node *link;
} Lnode;

/* Insertion en "tête de liste" */
// ph est le pointeur vers la tête (Lnode *ph) passé par adresse 
// (donc la fonction  recoit un pointeur vers pointeur vers Lnode = Lnode **ph) 
void insertionTete(Lnode ** ph, char item)
{
	Lnode *Noeud = malloc(sizeof(Lnode));
	Lnode *tmp = *ph;
	Noeud->data = item;
	Noeud->link = tmp;
	*ph = Noeud;			
}

/* Insertion en "queue de liste" */
// ph est le pointeur vers la tête passé par adresse (donc la fonction  recoit un pointeur vers pointeur vers Lnode) 
void insertionQueue(Lnode ** ph, char item)
{
	Lnode *Noeud = malloc(sizeof(Lnode));
	Lnode *tmp = *ph;
	Noeud->data = item;
	Noeud->link = NULL;
	if (tmp == NULL) {
		*ph = Noeud;
	} else {
		while (tmp->link != NULL) {
			tmp = tmp->link;
		}
		tmp->link = Noeud;
	}	
}

/* Suppression en "tête de liste" */
// ph est le pointeur vers la tête passé par adresse (donc la fonction  recoit un pointeur vers pointeur vers Lnode) 
void suppressionTete(Lnode ** ph)
{
	Lnode *tmp = *ph;
	if (tmp != NULL) {
		*ph = tmp->link;
		free(tmp);
	}
}

/* Suppression en "Queue" de liste" */
// ph est le pointeur vers la tête passé par adresse (donc la fonction  recoit un pointeur vers pointeur vers Lnode) 
void suppressionQueue(Lnode ** ph)
{
	Lnode *tmp = *ph;
	if (tmp != NULL) {
		if (tmp->link == NULL) {
			*ph = NULL;
			free(tmp);
		} else {
			while (tmp->link->link != NULL) {
				tmp = tmp->link;
			}
			free(tmp->link);
			tmp->link = NULL;
		}
	}
}

/* Procédure d'affichage de la liste. Ne doit pas être modifiée!!! */
void listeAffiche(Lnode * ptr)
{
	if (NULL == ptr)
		printf("Liste vide!");
	else
		printf("Contenu de la liste : ");
	while (NULL != ptr) {
		printf("%c ", ptr->data);
		ptr = ptr->link;
	}
	printf("\n");
}

/* Programme principal. Ne doit pas être modifié!!! */
int main(void)
{
	Lnode *tete = NULL;
	for (char c = 'a'; c < 'z'; c++) {
		insertionTete(&tete, c);
		insertionQueue(&tete, c + 'A' - 'a');
	}
	listeAffiche(tete);
	for (char c = 'a'; c < 'z'; c++) {
		suppressionTete(&tete);
		listeAffiche(tete);
		suppressionQueue(&tete);
		listeAffiche(tete);
	}

	return EXIT_SUCCESS;
}
