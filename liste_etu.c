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
