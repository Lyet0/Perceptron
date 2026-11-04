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
objet *creer_objet(char *nom, unsigned short auteur, unsigned int taille,
		   char *data)
{
	if (rechercher_objet(nom)==NULL||freeblocks<taille/512){
		objet *bj=obj;
		while (bj->next!=NULL){
			bj=bj->next;
		}
		bj->next=malloc(sizeof(objet));
		bj=bj->next; 
		strcpy(bj->nom,nom); 
		bj->taille=taille; 
		bj->auteur=auteur; 
		short bloc_restant=taille/512;
		int indicepres=-1;
		int taille_s = 0; 
		for (int i =0; i<BLOCNUM; i++) {
			if (FAT[i]==FREE){
				if (taille_s==taille_s){
					FAT[indicepres]=i; 
					FAT[i]=END;
					return bj; 
				}
				if (indicepres==-1){
					bj->index=i;
					indicepres=i;}
				else {
					FAT[indicepres]=i;
					indicepres=i; }
				int j=0; 
				while ((taille_s!=taille)&&(j!=512)){
					volume[i+j]= data[taille_s];
					j++; taille_s;
				}
				}
			}
		}
	return NULL;
}
