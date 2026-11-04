{
	if (bj==NULL){return NULL;}
	objet *bj=obj; 
	while (objet->nom!=nom) {
		objet=objet->next; 
		if (objet==NULL){
			return 0;
		}
	}
	return objet;
}
