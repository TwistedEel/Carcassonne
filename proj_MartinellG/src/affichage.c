#include "includes.h"
#include "game_structures.h"
#include "affichage.h"
#include "ANSI-color-codes.h"

extern struct tuile_s pioche[72];
extern struct tuile_s tab_jeu[143][143];
extern int ig,jg,id,jd;
extern int nb_jr,nb_ia,currentj;
extern struct joueur_s joueuria[5];

void affiche_tuile(struct tuile_s *t)
{
	printf("  %c \n", t->cotes[0]);
	printf("%c %c %c\n", t->cotes[3],t->centre,t->cotes[1]);
	printf("  %c \n", t->cotes[2]);
}



void afficher_grille(int ipioche){
    int i,j;
    system("clear");
    for(i=0;i<nb_jr+nb_ia;++i){
        if(joueuria[i].IA==0){
            if(i == currentj){
                switch(joueuria[i].id){
                    case 1 :
                        printf(RED "Joueur %d : %d points\t" reset,i+1,joueuria[i].points);
                        break;
                    case 2 :
                        printf(BLU "Joueur %d : %d points\t" reset,i+1,joueuria[i].points);
                        break;
                    case 3 :
                        printf(GRN "Joueur %d : %d points\t" reset,i+1,joueuria[i].points);
                        break;
                    case 4 :
                        printf(MAG "Joueur %d : %d points\t" reset,i+1,joueuria[i].points);
                        break;
                    case 5 :
                        printf(YEL "Joueur %d : %d points\t" reset,i+1,joueuria[i].points);
                        break;
                    }
            }else{
            printf("Joueur %d : %d points\t",i+1,joueuria[i].points);
            }
        }else{
            if(i == currentj){
                switch(joueuria[i].id){
                    case 1 :
                        printf(RED "IA %d : %d points\t\t" reset,i+1,joueuria[i].points);
                        break;
                    case 2 :
                        printf(BLU "IA %d : %d points\t\t" reset,i+1,joueuria[i].points);
                        break;
                    case 3 :
                        printf(GRN "IA %d : %d points\t\t" reset,i+1,joueuria[i].points);
                        break;
                    case 4 :
                        printf(MAG "IA %d : %d points\t\t" reset,i+1,joueuria[i].points);
                        break;
                    case 5 :
                        printf(YEL "IA %d : %d points\t\t" reset,i+1,joueuria[i].points);
                        break;
                    }
            }else{
            printf("IA %d : %d points\t\t",i+1,joueuria[i].points);
            }
        }
    }
    printf("\n");
    for(i=0;i<nb_jr+nb_ia;++i){
        if(i == currentj){
            switch(joueuria[i].id){
                case 1 :
                    printf(RED "   pions : %d/6\t\t" reset,joueuria[i].pions_restants);
                    break;
                case 2 :
                    printf(BLU "   pions : %d/6\t\t" reset,joueuria[i].pions_restants);
                    break;
                case 3 :
                    printf(GRN "   pions : %d/6\t\t" reset,joueuria[i].pions_restants);
                    break;
                case 4 :
                    printf(MAG "   pions : %d/6\t\t" reset,joueuria[i].pions_restants);
                    break;
                case 5 :
                    printf(YEL "   pions : %d/6\t\t" reset,joueuria[i].pions_restants);
                    break;
                }
        }else{
        printf("   pions : %d/6\t\t",joueuria[i].pions_restants);
        }
    }
    printf("\n");
    printf("\t -------------------------------------------------------------------------------------------\n");
    printf("\t| r : routes\tv : villes\tb : blason\tp : prés\to : villages\ta : abbayes |\n" reset);
    printf("\t -------------------------------------------------------------------------------------------\n");
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
                if(tab_jeu[i][j].pcotes[0] == 0){
                    printf("  %c  |",tab_jeu[i][j].cotes[0]);
                }else{
                    switch(tab_jeu[i][j].pcotes[0]){
                        case 1 :
                            printf("  " REDB"%c"reset"  |",tab_jeu[i][j].cotes[0]);
                            break;
                        case 2 :
                            printf("  " BLUB"%c"reset"  |" ,tab_jeu[i][j].cotes[0]);
                            break;
                        case 3 :
                            printf("  " GRNB"%c"reset"  |" ,tab_jeu[i][j].cotes[0]);
                            break;
                        case 4 :
                            printf("  " MAGB"%c"reset"  |" ,tab_jeu[i][j].cotes[0]);
                            break;
                        case 5 :
                            printf("  " YELB"%c"reset"  |" ,tab_jeu[i][j].cotes[0]);
                            break;
                    }
                }
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
                if(tab_jeu[i][j].pcotes[3] == 0){
                    printf("%c",tab_jeu[i][j].cotes[3]);
                }else{
                    switch(tab_jeu[i][j].pcotes[3]){
                        case 1 :
                            printf(REDB"%c"reset,tab_jeu[i][j].cotes[3]);
                            break;
                        case 2 :
                            printf(BLUB"%c"reset,tab_jeu[i][j].cotes[3]);
                            break;
                        case 3 :
                            printf(GRNB"%c"reset,tab_jeu[i][j].cotes[3]);
                            break;
                        case 4 :
                            printf(MAGB"%c"reset,tab_jeu[i][j].cotes[3]);
                            break;
                        case 5 :
                            printf(YELB"%c"reset,tab_jeu[i][j].cotes[3]);
                            break;
                    }
                }
                if(tab_jeu[i][j].pcentre == 0){
                    printf(" %c",tab_jeu[i][j].centre);
                }else{
                    switch(tab_jeu[i][j].pcentre){
                        case 1 :
                            printf(" "REDB"%c"reset,tab_jeu[i][j].centre);
                            break;
                        case 2 :
                            printf(" "BLUB"%c"reset,tab_jeu[i][j].centre);
                            break;
                        case 3 :
                            printf(" "GRNB"%c"reset,tab_jeu[i][j].centre);
                            break;
                        case 4 :
                            printf(" "MAGB"%c"reset,tab_jeu[i][j].centre);
                            break;
                        case 5 :
                            printf(" "YELB"%c"reset,tab_jeu[i][j].centre);
                            break;
                        }
                }
                if(tab_jeu[i][j].pcotes[1] == 0){
                    printf( " %c|",tab_jeu[i][j].cotes[1]);
                }else{
                    switch(tab_jeu[i][j].pcotes[1]){
                        case 1 :
                            printf(" " REDB"%c"reset"|",tab_jeu[i][j].cotes[1]);
                            break;
                        case 2 :
                            printf(" " BLUB"%c"reset"|",tab_jeu[i][j].cotes[1]);
                            break;
                        case 3 :
                            printf(" " GRNB"%c"reset"|",tab_jeu[i][j].cotes[1]);
                            break;
                        case 4 :
                            printf(" " MAGB"%c"reset"|",tab_jeu[i][j].cotes[1]);
                            break;
                        case 5 :
                            printf(" " YELB"%c"reset"|",tab_jeu[i][j].cotes[1]);
                            break;
                        }
                }
            }
        }
        printf(" %d\n",i);
        printf("|");
        for(j=jg-1;j<=jd+1;j++){
            if(tab_jeu[i][j].posee==0){
                printf("     |");
            }else{
                if(tab_jeu[i][j].pcotes[2] == 0){
                    printf("  %c  |",tab_jeu[i][j].cotes[2]);
                }else{
                    switch(tab_jeu[i][j].pcotes[2]){
                        case 1 :
                            printf("  " REDB"%c"reset"  |",tab_jeu[i][j].cotes[2]);
                            break;
                        case 2 :
                            printf("  " BLUB"%c"reset"  |" ,tab_jeu[i][j].cotes[2]);
                            break;
                        case 3 :
                            printf("  " GRNB"%c"reset"  |" ,tab_jeu[i][j].cotes[2]);
                            break;
                        case 4 :
                            printf("  " MAGB"%c"reset"  |" ,tab_jeu[i][j].cotes[2]);
                            break;
                        case 5 :
                            printf("  " YELB"%c"reset"  |" ,tab_jeu[i][j].cotes[2]);
                            break;
                        }
                }
            }
        }
        printf("\n");
        printf(" ");
        for(j=jg-1;j<=jd+1;j++){
            printf("----- ");
        }
        printf("\n");
    }
    return;
}

