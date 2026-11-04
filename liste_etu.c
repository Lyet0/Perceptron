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
	if (rechercher_objet(nom)==NULL&&freeblocks<=taille/BLOCSIZE +1){
		objet *bj=obj;
		if (bj!=NULL){
			while (bj->next!=NULL){
				bj=bj->next;
			}
			bj->next=malloc(sizeof(objet));
		}
		else{
			bj=malloc(sizeof(objet));
		}
		strcpy(bj->nom,nom); 
		bj->taille=taille; 
		bj->auteur=auteur; 
		int indicepres=-1;
		unsigned int taille_s = 0; 
		for (int i =0; i<BLOCNUM; i++) {
			if (FAT[i]==FREE){
				if (taille_s==taille){
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
					volume[i*BLOCSIZE+j]= data[taille_s];
					j++; taille_s++;
				}
				}
			}
		}
	return NULL;
}
