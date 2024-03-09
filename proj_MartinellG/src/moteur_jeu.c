#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>

extern ssize_t getline();
struct tuile_s{
	int identifiant;
	char cotes[4];
	char centre;
    int posee;
};

struct joueur_s{
	int points;
	short pions_restants;

};

struct tuile_s pioche[72];
struct tuile_s tab_jeu[143][143];
int nb_joueur,nb_ia,cur_joueur,ig = 72,id=72,jg=72,jd=72;

void affiche_tuile(struct tuile_s *t)
{
	printf("  %c \n", t->cotes[0]);
	printf("%c %c %c\n", t->cotes[3],t->centre,t->cotes[1]);
	printf("  %c \n", t->cotes[2]);
}


int parseur_csv(char* fname){
	FILE * mon_fic = fopen(fname,"r");
	if (mon_fic == NULL){
		return -1;
	}
	char* ligne;
	size_t len = 0;
	char *sub_str;
	int i,j;
	for(i=0;i<72;++i){
		getline(&ligne,&len,mon_fic);
		sub_str=strtok(ligne, ",");
		pioche[i].identifiant = i;
		pioche[i].cotes[0]= sub_str[0];
		for(j=1;j<4;++j){
			sub_str=strtok(NULL, ",");
            pioche[i].cotes[j] = sub_str[0];
        }
        sub_str=strtok(NULL, ",");
        if(strcmp(sub_str,"village\n")==0){
            pioche[i].centre = 'V';
        }else{
            pioche[i].centre = sub_str[0];
        }
    }
	return 0;
}

void melange_tuiles(){
    int i,j,alea,temp;
    srand(time(NULL));
    for(i=0;i<70;i++){
		alea=rand()%(71-i);
        while(alea==0){
			alea = rand()%(71-i);
		}
        temp = pioche[71-i].identifiant;
        pioche[71-i].identifiant = pioche[alea].identifiant;
        pioche[alea].identifiant = temp;
        for(j=0;j<4;j++){
            temp = pioche[71-i].cotes[j];
            pioche[71-i].cotes[j] = pioche[alea].cotes[j];
            pioche[alea].cotes[j] = temp;
        }
        temp = pioche[71-i].centre;
        pioche[71-i].centre = pioche[alea].centre;
        pioche[alea].centre = temp;
    }
}

void afficher_grille(){
    int i,j;
    for(i=jg-1;i<=jd+1;++i){
        printf("  %2d  ",i);
    }
    printf("\n ");
    for(j=jg-1;j<=jd+1;j++){
            printf("----- ");
    }
    printf("\n");
    for(i=ig-1;i<=id+1;i++){
        printf("|");
        for(j=jg-1;j<=jd+1;j++){
            if(tab_jeu[i][j].posee==0){
                printf("     |");
            }else{
                printf("  %c  |",tab_jeu[i][j].cotes[0]);
            }
        }
        printf("\n");
        printf("|");
        for(j=jg-1;j<=jd+1;j++){
            if(tab_jeu[i][j].posee==0){
                printf("     |");
            }else{
                printf("%c %c %c|",tab_jeu[i][j].cotes[3],tab_jeu[i][j].centre,tab_jeu[i][j].cotes[1]);
            }
        }
        printf(" %d\n",i);
        printf("|");
        for(j=jg-1;j<=jd+1;j++){
            if(tab_jeu[i][j].posee==0){
                printf("     |");
            }else{
                printf("  %c  |",tab_jeu[i][j].cotes[2]);
            }
        }
        printf("\n");
        printf(" ");
        for(j=jg-1;j<=jd+1;j++){
            printf("----- ");
        }
        printf("\n");
    }
}

void tourner_tuile(struct tuile_s *t){
    char reponse[10],tmp;
    int i,j,encore=1,valide=0,k;
    printf("Voulez vous tournez la tuile de 90° dans le sens anti-horaire ?\n(Répondre 'oui' ou non') : ");
    scanf("%s", reponse);
    if(strcmp("non",reponse)==0){
        return;
    }
    if(strcmp("oui",reponse)==0){
            valide = 1;
    }
    if(valide!=0){
        while(encore==1){
            printf("Combien de fois ? \n(Entrer un chiffre entre 1 et 3) :");
            scanf("%d",&k);
            for(i=0;i<k;++i){
                tmp = t->cotes[0];
                for(j=0;j<3;++j){
                    t->cotes[j] = t->cotes[j+1];
                }
                t->cotes[3]=tmp;
            }
            printf("Tuile tournée : \n");
            affiche_tuile(t);
            valide = 0;
            while(valide==0){
                printf("Voulez-vous encore tourner la tuile ? (oui ou non) : ");
                scanf("%s", reponse);
                valide = 1;
                if(strcmp("non",reponse)==0){
                    encore = 0;
                }else{
                    if(strcmp("oui",reponse)!=0){
                        printf("La réponse n'est pas valide, entrez une réponse valide svp : \n");
                        valide = 0;
                    }
                }
            }
        }
    }else{
        printf("La réponse n'est pas valide, entrez une réponse valide svp : \n");
        tourner_tuile(t);
        return;
    }
}

void posable(struct tuile_s t){
	
	
	
	
	return;
}

void poser_tuile(int y, int x, int i){
    /*
    Lorsque l'on rentre des coordonnées, on est habitué à les rentrer
    sous la forme (x,y), cependant pour la vision humaine de la grille
    x correspond à la colonne et y à la ligne alors que dans le programme
    pour tab[i][j] on a i qui correspond à la ligne et j à la colonne,
    on échange part donc du principe dans l'entête de la fonction que
    l'on rentre les coordonées sous la forme (y,x) pour faciliter
    l'insertion et la mise à jour des coins gauche et droit.
    */
    int k;
    tab_jeu[x][y].identifiant = pioche[i].identifiant;
    tab_jeu[x][y].centre = pioche[i].centre;
    for(k=0;k<4;++k){
        tab_jeu[x][y].cotes[k] = pioche[i].cotes[k];
    }
    tab_jeu[x][y].posee = 1;
    pioche[i].posee = 1;
    // On met à jour le coin gauche (jg,ig) et le coin droit (jd,id) ;
    if(y<jg){
        jg = y;
    }else{
        if(y>jd){
            jd = y;
        }
    }
    if(x<ig){
        ig = x;
    }else{
        if(x>id){
            id = x;
        }
    }

    return;
}
int moteur_jeu(){
	// Initialisation :
	printf("Entrer le nombre de joueur stp : ");
	scanf("%d",&nb_joueur);
	printf("Entrer le nombre d'ia stp : ");
	scanf("%d",&nb_ia);
    poser_tuile(72,72,0);
    //Boucle de jeu :
    int i,x,y;
    for(i=1;i<72;++i){ // Chaque itération de cette boucle est un tour de jeu
        system("clear");
        printf("Plateau actuel :\n");
        afficher_grille();
        printf("Tuile piochée :\n");
        affiche_tuile(&pioche[i]);
        tourner_tuile(&pioche[i]);
        system("clear");
        printf("Plateau actuel :\n");
        afficher_grille();
        printf("Tuile piochée :\n");
        affiche_tuile(&pioche[i]);
        printf("Entrer les coordonnées de l'emplacement où vous voulez poser la tuile : \nx (la colonne) = ");
        scanf("%d",&x);
        printf("y (la ligne) = ");
        scanf("%d",&y);
        poser_tuile(x,y,i);
    }
	return 1;
}

int main(int argc, char * argv[])
{
	parseur_csv("tuiles.csv");
	melange_tuiles();
	moteur_jeu();
	//Détail d'un tour de jeu :
	/*
	int game_loop(){
		//1 - déterminer un joueur
		//2 - piocher une tuile
		//	2a - tuile posable ?
		//	2b - pioche vide ?
		//3 - poser la tuile
		//	3a - tuile posable ?
		//4 - vérification de l'état des éléments (ex:route)
		//	4a - élément créé ?
		//	4b - élément fini ?
		//	4c - élément continué ?
		//5 - pion posé ?
		//	5a - posé où ?
		//	5b - points à attribuer ?
		//6 - màj classement
	}
	*/

	return 0;
}





























