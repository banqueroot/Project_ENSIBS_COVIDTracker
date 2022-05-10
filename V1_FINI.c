/* R.LATASTE PROJET COVID2020 L2*/

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>


//======================================AFFICHAGE======================================
	void gotoligcol( int lig, int col )
	{
		COORD mycoord;
		
		mycoord.X = col;
		mycoord.Y = lig;
		SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
	}

	void affiche(HANDLE hConsole, char c,int fond, int couleur){
		int i;
		
		i=16*fond+couleur;
		SetConsoleTextAttribute(hConsole, i);
	      printf("%c ", c);
	}

	void afficheMenu(HANDLE hConsole){
		
		system("cls");
		SetConsoleTextAttribute(hConsole, 16*3+4);
		gotoligcol(5,5);printf("*********************************");
		gotoligcol(6,5);printf("*        COVID CONTACT          *");
		gotoligcol(7,5);printf("*********************************");	
		SetConsoleTextAttribute(hConsole, 16*0+15);			
		gotoligcol(10,9);printf("1 - Afficher la liste des citoyens");	
		gotoligcol(11,9);printf("2 - Afficher la liste des lieux de fetes");
		gotoligcol(12,9);printf("3 - Ajouter un citoyen");
		gotoligcol(13,9);printf("4 - Ajouter un lieu de fetes");
		gotoligcol(14,9);printf("5 - Remplir les participants a une fete");
		gotoligcol(15,9);printf("6 - Afficher tous ceux qui ont rencontré un citoyen");
		gotoligcol(16,9);printf("7 - Enregistrer un fichier situation");
		gotoligcol(17,9);printf("8 - Ouvrir un ficher situation");
		gotoligcol(18,9);printf("9 - Supprimer tous les evenements anterieur a une date");
		gotoligcol(19,9);printf("0 - Quit");		
	}
//======================================AFFICHAGE======================================	


//======================================STRUCTURES======================================

typedef struct Date {
	int jour;
	int mois;
	int an;
} Date; 

typedef struct citoyen {
	char nom [40];
	char prenom [40];
	struct citoyen * pnext;
	struct citoyen * pprevious;
} Tcitoyen;

typedef struct participant {
	Date date;
	Tcitoyen * ppersonne;
	struct participant * psuivant;
} Tparticipant;

typedef struct lieu {
	char nomLieu [40];
	Tparticipant * pliste;
	struct lieu * pavant;
	struct lieu * pprecedent;
} Tlieu;


//======================================MANUADDS======================================
//						Fonctions d'ajout aux listes chainées						//
//====================================================================================
void manuaddc(Tcitoyen * pdebutc, char prenomin[40], char nomin[40]){
  		Tcitoyen * px;
  		px = (Tcitoyen *)malloc(sizeof(Tcitoyen));
  		px = pdebutc;
  		while((px->pnext)->pnext != NULL){
  			px=px->pnext;
		  }
		Tcitoyen * py;
  		py = (Tcitoyen *)malloc(sizeof(Tcitoyen));
  		strcpy (py->prenom,prenomin);
  		strcpy (py->nom,nomin);
  		py->pprevious = px;
  		py->pnext = px->pnext;
  		px->pnext = py;
}

void manuaddl(Tlieu * pdebutl, char lieu[40]){
		Tlieu * px;
  		px = (Tlieu *)malloc(sizeof(Tlieu));
  		px = pdebutl;
  		while((px->pavant)->pavant != NULL){
  			px=px->pavant;
		}
		Tlieu * py;
  		py = (Tlieu *)malloc(sizeof(Tlieu));
  		strcpy (py->nomLieu,lieu);
  		py->pprecedent = px;
  		py->pavant = px->pavant;
  		px->pavant = py;
  		Tparticipant * pdebutp;
  		Tparticipant * pfinp;
  		pdebutp = (Tparticipant *)malloc(sizeof(Tparticipant));
  		pfinp = (Tparticipant *)malloc(sizeof(Tparticipant));
  		pdebutp->psuivant = pfinp;
  		pfinp->psuivant = NULL;
  		py->pliste = pdebutp;
}

manuadp(Tlieu * pdebutl, Tcitoyen  * pdebutc, char fete[40], char prenomin[40], char nomin[40], Date date){
	Tlieu * pl;
	pl = pdebutl;
	while(strcmp(pl->nomLieu, fete) != 0){
  		pl=pl->pavant;
		  }
	Tparticipant * py;
	Tparticipant * pz;
	pz=(Tparticipant *)malloc(sizeof(Tparticipant));
	py=pl->pliste;
	while((py->psuivant)->psuivant != NULL){
  		py=py->psuivant;
	}
	Tcitoyen * pw;
	pw = pdebutc;
	pz->psuivant = py->psuivant;
	py->psuivant = pz;
	while(strcmp(pw->prenom, prenomin) != 0 & strcmp(pw->nom, nomin) != 0 & pw->pnext != NULL){
  		pw=pw->pnext;
	}
	pz->ppersonne = pw;
	pz->date.an = date.an;
	pz->date.mois = date.mois;
	pz->date.jour = date.jour;
}
//======================================PGRMS MENU======================================
void listecitoyen(Tcitoyen * pdebutc){
system ("cls"); 
  		int lig = 8;
		gotoligcol(5,9);printf("Liste citoyens");
		gotoligcol(6,9);printf("Prenom");
		gotoligcol(6,25);printf("|");
		gotoligcol(6,40);printf("Nom");
		gotoligcol(7,9);printf("-----------------------------------------------");
  		Tcitoyen * px;
  		px = pdebutc->pnext;
  		while(px->pnext != NULL){
  			gotoligcol(lig,9);printf("%s", px->nom);
			gotoligcol(lig,25);printf("|");
			gotoligcol(lig,40);printf("%s\n", px->prenom);
			lig = lig + 1;
  			px=px->pnext;
		}
}

void listelieu(Tlieu * pdebutl){
	int lig = 7;
	Tlieu * px;
	system ("cls"); 
  	gotoligcol(5,9);printf("Liste des lieux");gotoligcol(6,9);printf("-----------------------------------------------");
  	px = pdebutl->pavant;
  	while(px->pavant != NULL){
  		gotoligcol(lig,9);printf("%s \n", px->nomLieu);
  		lig = lig + 1;
  		px=px->pavant;
}
}
void ajoutcitoyen(Tcitoyen * pdebutc){
		char nomin[40];
  		char prenomin[40];
  		system ("cls"); 
		gotoligcol(5,9);printf("Ajouter un citoyen");
  		gotoligcol(6,9);printf("Prénom : ");
  		scanf("%s", &prenomin);
  		gotoligcol(7,9);printf("nom : ");
  		scanf("%s", &nomin);
  		manuaddc(pdebutc, prenomin, nomin);
}

void ajoutlieufete(Tlieu * pdebutl){
	char lieu[40];
  		system ("cls"); 
		gotoligcol(5,9);printf("Ajouter un lieu de fête");
  		gotoligcol(6,9);printf("Nom du lieu : ");
  		scanf("%s", &lieu);
  		manuaddl(pdebutl, lieu);
}

void recherchecontact(Tlieu * pdebutl){
	char nomin[40];
	char prenomin[40];
	Tlieu * pLlecture;
	Tparticipant * pPlecture;
	Tparticipant * pPlecturedouble;
	int lig;
	lig = 8;
	
	system ("cls"); 
	gotoligcol(5,9);printf("Rechercher les personnes en contact");
	gotoligcol(6,9);printf("Nom :");
	scanf("%s", &nomin);
	gotoligcol(7,9);printf("Prénom :");
	scanf("%s", &prenomin);
	pLlecture = pdebutl->pavant;
	while(pLlecture->pavant != NULL){
		pPlecture = pLlecture->pliste;
		pPlecture = pPlecture->psuivant;
		while(pPlecture->psuivant != NULL){
			if(strcmp(prenomin, (pPlecture->ppersonne)->prenom) == 0 & strcmp(nomin, (pPlecture->ppersonne)->nom) == 0)
			{
				pPlecturedouble = pLlecture->pliste;
				pPlecturedouble = pPlecturedouble->psuivant;
				gotoligcol(lig,9);printf("===========|%s|=========== ", (pLlecture->nomLieu));
				lig = lig + 1;
				while(pPlecturedouble->psuivant != NULL){
					gotoligcol(lig,9);printf("%s", (pPlecturedouble->ppersonne)->nom);
					gotoligcol(lig,25);printf("|");
					gotoligcol(lig,40);printf("%s\n", (pPlecturedouble->ppersonne)->prenom);
					lig = lig + 1;
					pPlecturedouble = pPlecturedouble->psuivant;
				}
			}
			pPlecture = pPlecture->psuivant;
		}
		pLlecture = pLlecture->pavant;
	}
	
}

void ajoutfete(Tlieu * pdebutl, Tcitoyen * pdebutc){
		system ("cls"); 
		gotoligcol(5,9);printf("Ajouter les participants d'une fete");
		char  fete[40];
		Date date;
		char nomin[40];
		char prenomin[40];
		int get = 1;
		
		gotoligcol(6,9);printf("Nom de la fete :");
		scanf("%s", &fete);
		gotoligcol(7,9);printf("Date de la fete :");
		gotoligcol(8,9);printf("Annee :");
		scanf("%i", &(date.an));
		gotoligcol(9,9);printf("Mois :");
		scanf("%i", &(date.mois));
		gotoligcol(10,9);printf("Jour :");
		scanf("%i", &(date.jour));
		Tlieu * pl;
		pl = pdebutl;
		while(strcmp(pl->nomLieu, fete) != 0 & pl->pavant != NULL){
  			pl=pl->pavant;
			  }
		Tparticipant * py;
		Tparticipant * pz;
		pz=(Tparticipant *)malloc(sizeof(Tparticipant));
		py=pl->pliste;
		while((py->psuivant)->psuivant != NULL){
  			py=py->psuivant;
		  }
		  //On se place a la fin de la liste de participant
		while(get != '0')
		{
			system ("cls");
			gotoligcol(5,9);printf("Ajouter les participants d'une fete");
			gotoligcol(8,9);printf("Prenom de la personne a ajouter :");
			scanf("%s", &prenomin);
			gotoligcol(9,9);printf("Nom de la personne a ajouter :");
			scanf("%s", &nomin);
			Tcitoyen * pw;
			pw = pdebutc;
			py->psuivant = pz;
			while(strcmp(pw->prenom, prenomin) != 0 & strcmp(pw->nom, nomin) != 0 & pw->pnext != NULL){
  				pw=pw->pnext;
			  }
			pz->ppersonne = pw;
			pz->date.an = date.an;
			pz->date.mois = date.mois;
			pz->date.jour = date.jour;
			pz->psuivant = (Tparticipant *)malloc(sizeof(Tparticipant));
			pz = pz->psuivant;
			
			gotoligcol(20,9);printf("Pressez 0 pour quitter, n'importe quelle autre touche pour continuer'"); 
			get = getch();
		}
		pz->psuivant = NULL;
		system ("cls");
}
void savfichier(Tcitoyen * pdebutc, Tlieu * pdebutl){
	//Sauvegarde citoyens
		FILE* fichier = NULL;
		fichier = fopen("citoyens.txt", "w");
		Tcitoyen * px;
  		px = pdebutc->pnext;
  		while(px->pnext != NULL){
  			fprintf(fichier, "%s\n", px->nom);
  			fprintf(fichier, "%s\n", px->prenom);
  			px=px->pnext;
    	}
    	fclose(fichier);
    	//Fin Sauvegarde citoyens
    	
    	//Sauvegarde fêtes et participants
    	fichier = fopen("fetes.txt", "w");
    	FILE* fichier2 = NULL;
    	Tparticipant * py;
    	fichier2 = fopen("participants.txt", "w");
    	Tlieu * pu;
  		pu = pdebutl->pavant;
  		while(pu->pavant != NULL){
  			fprintf(fichier, "%s\n", pu->nomLieu);
  			py=(pu->pliste)->psuivant;
  			fprintf(fichier2, "%i\n", py->date.an);
  			fprintf(fichier2, "%i\n", py->date.mois);
  			fprintf(fichier2, "%i\n", py->date.jour);
			while(py->psuivant != NULL){
				fprintf(fichier2, "%s\n", (py->ppersonne)->nom);
				fprintf(fichier2, "%s\n", (py->ppersonne)->prenom);
  				py=py->psuivant;
		 	}
		 	fprintf(fichier2, "========================\n");
  			pu=pu->pavant;
		}
		fclose(fichier);
		fclose(fichier2);
    	//Fin Sauvegarde fêtes et participants
    	system ("cls"); 
		gotoligcol(5,9);printf("Situation enregistree");
}

void lecturefichier(Tcitoyen * pdebutc, Tlieu * pdebutl){
	//Lecture fichier situation
		
		//Declaration des fichiers
		system("cls");
		gotoligcol(0,0);
		FILE* fichierc = NULL;
		fichierc = fopen("citoyens.txt", "rb");
		FILE* fichierl = NULL;
		fichierl = fopen("fetes.txt", "rb");
		FILE* fichierp = NULL;
		fichierp = fopen("participants.txt", "rb");
		//fin
		
		//Lecture citoyens
		char buf[40];
		char prenomin[40];
		char nomin[40];
		char fete[40];
		Date tempdate;
		Tcitoyen * py;
		Tcitoyen * px;
		px = pdebutc;
		py = (Tcitoyen *)malloc(sizeof(Tcitoyen));
		
		while(fscanf(fichierc,"%s",&buf) != EOF){
  			strcpy (nomin,buf);
  			fscanf(fichierc,"%s",&buf);
  			strcpy (prenomin,buf);
  			manuaddc(pdebutc, prenomin, nomin);
			}
		while(fscanf(fichierl,"%s",&buf) != EOF){
  			manuaddl(pdebutl, buf);
  			strcpy (fete,buf);
			//Ajout participants
			fscanf(fichierp,"%s",&buf);
			tempdate.an = atoi(buf); //conversion en int
			fscanf(fichierp,"%s",&buf);
			tempdate.mois = atoi(buf);
			fscanf(fichierp,"%s",&buf);
			tempdate.jour = atoi(buf);
			fscanf(fichierp,"%s",&buf);
			while(strcmp(buf, "========================")!= 0) {
				strcpy (nomin,buf);
				fscanf(fichierp,"%s",&buf);
				strcpy (prenomin,buf);
				manuadp(pdebutl, pdebutc, fete, prenomin, nomin, tempdate);
				fscanf(fichierp,"%s",&buf);
				}
		}
		fclose(fichierc);
		fclose(fichierl);
		fclose(fichierp);
		//Fin lecture citoyen
		//Fin Lecture fichier situation
		
		
		system ("cls"); 
		gotoligcol(5,9);printf("Situation chargee");
}

void supprdate(Tlieu * pdebutl){
	char  fete[40];
	Date date;
	Tlieu * pLlecture;
	Tlieu * pprec;
	Tlieu * psuiv;
	Tparticipant * pPlecture;
	int del = 0;

	system ("cls"); 
	gotoligcol(5,9);printf("Supprimer les evenements anterieurs a une date");
	gotoligcol(7,9);printf("Date :");
	gotoligcol(8,9);printf("Annee :");
	scanf("%i", &(date.an));
	gotoligcol(9,9);printf("Mois :");
	scanf("%i", &(date.mois));
	gotoligcol(10,9);printf("Jour :");
	scanf("%i", &(date.jour));
	
	pLlecture = pdebutl->pavant;
	while(pLlecture->pavant != NULL){
		pPlecture = pLlecture->pliste;
		pPlecture = pPlecture->psuivant;
		if(pPlecture->date.an < date.an){
			del = 1;
		}
		if(pPlecture->date.mois < date.mois & pPlecture->date.an == date.an){
			del = 1;
		}
		if(pPlecture->date.jour < date.jour & pPlecture->date.an == date.an & pPlecture->date.mois == date.mois){
			del = 1;
		}
		if(del == 1){
			pprec = pLlecture->pprecedent;
			psuiv = pLlecture->pavant;
			pprec->pavant = psuiv;
			psuiv->pprecedent = pprec;
			pLlecture = pprec;
		}
		del = 0;
		pLlecture = pLlecture->pavant;
	}
}
//=============================================================================================

void main(void){
	
  //======================================VARIABLES======================================
  int i=32;
  char c=32;
  Tcitoyen * pdebutc;
  Tcitoyen * pfinc;
  pdebutc = (Tcitoyen *)malloc(sizeof(Tcitoyen));
  pfinc = (Tcitoyen *)malloc(sizeof(Tcitoyen));
  
  pdebutc->pnext = pfinc;
  pdebutc->pprevious = NULL;
  pfinc->pnext = NULL;
  pfinc->pprevious = pdebutc;


  Tlieu * pdebutl;
  Tlieu * pfinl;
  pdebutl = (Tlieu *)malloc(sizeof(Tlieu));
  pfinl = (Tlieu *)malloc(sizeof(Tlieu));
  pdebutl->pavant = pfinl;
  pdebutl->pprecedent = NULL;
  pfinl->pprecedent = pdebutl;
  pfinl->pavant = NULL;
  
  HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
  
  
  //======================================Boucle du MENU======================================
  i=1;
  while(i!=0){
  	afficheMenu(hConsole);
  	gotoligcol(20,9);printf("Appuyer sur une touche pour continuer"); 
	c= getch();
  	if(c=='1') {
  		listecitoyen(pdebutc);
		  }
	if(c=='2') {
  		listelieu(pdebutl);
		  }
	if(c=='3') {
  		ajoutcitoyen(pdebutc);
	  }
	if(c=='4') {
		ajoutlieufete(pdebutl);
	  }
	if(c=='5') {
		ajoutfete(pdebutl, pdebutc);
	}
	if(c=='6') {
		recherchecontact(pdebutl);
	}
	if(c=='7') {
		savfichier(pdebutc, pdebutl);
	}
	if(c=='8') {
		lecturefichier(pdebutc, pdebutl);
	}
	if(c=='9') {
		supprdate(pdebutl);
	}
	
	if(c=='0')	break;
	gotoligcol(20,9);printf("Appuyer sur une touche pour continuer"); 
	c= getch();
  }
  //======================================Fin Boucle du MENU======================================
  
}

