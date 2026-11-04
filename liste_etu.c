objet *rechercher_objet(char *nom)
{
	objet *bj=obj; 
	while (bj->nom!=nom) {
		bj=bj->next; 
		if (bj==NULL){
			return 0;
		}
	}
	return bj;
}
