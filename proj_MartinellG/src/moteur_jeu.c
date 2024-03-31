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
    int posable;
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

void afficher_grille(int ipioche){
    int i,j;
    system("clear");
    printf("Plateau actuel :\n");
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
                if(tab_jeu[i][j].posable==1){
                    printf("  X  |");
                }else{
                    printf("     |");
                }
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
    printf("Tuile en main :\n");
    affiche_tuile(&pioche[ipioche]);
    return;
}

int tourner_tuile(struct tuile_s *t,int encore){
    char reponse[10],tmp;
    int i,j,valide=0,k;
    if (encore == 2){
        printf("Voulez vous tournez la tuile de 90° dans le sens anti-horaire ?\n(Répondre 'oui' ou non') : ");
        scanf("%s", reponse);
        if(strcmp("non",reponse)==0){
            return 0;
        }
        if(strcmp("oui",reponse)==0){
                valide = 1;
        }
    }
    if(valide!=0 || encore!=2){
            printf("Combien de fois ? \n(Entrer un chiffre entre 1 et 3) :");
            scanf("%d",&k);
            for(i=0;i<k;++i){
                tmp = t->cotes[0];
                for(j=0;j<3;++j){
                    t->cotes[j] = t->cotes[j+1];
                }
                t->cotes[3]=tmp;
            }
            return 1;
    }else{
        printf("La réponse n'est pas valide, entrez une réponse valide svp : \n");
        return tourner_tuile(t,encore);
    }
}

int f_encore(){
    int valide = 0;
    char reponse[10];
    while(valide==0){
        printf("Voulez-vous encore tourner la tuile ? (oui ou non) : ");
        scanf("%s", reponse);
        valide = 1;
        if(strcmp("non",reponse)==0){
            return 0;
        }else{
            if(strcmp("oui",reponse)!=0){
                printf("La réponse n'est pas valide, entrez une réponse valide svp : \n");
                valide = 0;
            }else{
                return 1;
            }
        }
    }
    return 0;
}

int compatible(struct tuile_s * t1,struct tuile_s * t2, int face1, int face2){
    if(t2->posee == 0){
        return 1;
    }else{
        if(((t1->cotes[face1]=='b' || t1->cotes[face1]=='v') && (t2->cotes[face2]=='b' || t2->cotes[face2]=='v')) || ((t1->cotes[face1]=='r') && (t2->cotes[face2]=='r')) || ((t1->cotes[face1]=='p') && (t2->cotes[face2]=='p'))){
            return 1;
        }else{
            return 0;
        }
    }
}

void f_posable(struct tuile_s * t){
    int i,j;
    for(i=ig-1;i<=id+1;++i){
        for(j=jg-1;j<=jd+1;++j){
            if(tab_jeu[i][j].posee == 0){
                if((tab_jeu[i-1][j].posee == 0) && (tab_jeu[i][j+1].posee == 0) && (tab_jeu[i+1][j].posee == 0) && (tab_jeu[i][j-1].posee == 0)){
                    tab_jeu[i][j].posable = 0;
                }else{
                    if((compatible(t,&tab_jeu[i-1][j],0,2) == 1) && (compatible(t,&tab_jeu[i][j+1],1,3) == 1) && (compatible(t,&tab_jeu[i+1][j],2,0) == 1) && (compatible(t,&tab_jeu[i][j-1],3,1) == 1)){
                        tab_jeu[i][j].posable = 1;
                    }else{
                        tab_jeu[i][j].posable = 0;
                    }
                }
            }else{
                tab_jeu[i][j].posable = 0;
            }
        }
    }


	return;
}

void poser_tuile(int y, int x, int i){
    /*
    Lorsque l'on rentre des coordonnées, on est habitué à les rentrer
    sous la forme (x,y), cependant pour la vision humaine de la grille
    x correspond à la colonne et y à la ligne alors que dans le programme
    pour tab[i][j] on a i qui correspond à la ligne et j à la colonne,
    on part donc du principe dans l'entête de la fonction que
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
    int i,x,y,encore;
    for(i=1;i<72;++i){ // Chaque itération de cette boucle est un tour de jeu
        encore=2;
        while(encore!=0){
            f_posable(&pioche[i]);
            afficher_grille(i);
            encore = tourner_tuile(&pioche[i],encore);
            f_posable(&pioche[i]);
            afficher_grille(i);
            if(encore==1){
                encore = f_encore();
            }
        }
        encore = 2;
        while(encore != 0){
            afficher_grille(i);
            if(encore == 1){
                printf("La tuile n'est pas posable à ces coordonnées, veuillez en entrer des nouvelles :\nx (la colonne) = ");
            }else{
                printf("Entrer les coordonnées de l'emplacement où vous voulez poser la tuile : \nx (la colonne) = ");
            }
            scanf("%d",&x);
            printf("y (la ligne) = ");
            scanf("%d",&y);
            if(tab_jeu[y][x].posable == 1){
                poser_tuile(x,y,i);
                encore = 0;
            }else{
                encore = 1;
            }
        }
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





























