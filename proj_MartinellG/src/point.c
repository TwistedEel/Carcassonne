#include "includes.h"
#include "game_structures.h"
#include "point.h"
#include "pion.h"
extern struct tuile_s pioche[72];
extern struct tuile_s tab_jeu[143][143];
extern int ig,jg,id,jd;
extern int nb_jr,nb_ia,currentj;
extern struct joueur_s joueuria[5];
extern int pions_presents[5];

void vider_pions(){
    int i;
    for(i=0;i<5;i++){
        pions_presents[i] = -1;
    }
    for(i=0;i<nb_ia+nb_jr;i++){
        pions_presents[joueuria[i].id] = 0;
    }
}

void compter_point(int y,int x,int mode){
    int i,j,pos,score;
    //On regarde d'abord les abbayes :
    for(i=x-1;i<=x+1;i++){
        for(j=y-1;j<=y+1;j++){
            if(tab_jeu[i][j].posee == 1 && tab_jeu[i][j].centre=='a' && tab_jeu[i][j].pcentre != 0){
                point_abbaye(i,j,mode);
            }
        }
    }
    /*
    //Ensuite on regarde les routes puis les villes, en utilisant les mêmes parcours que pour les pions
    for(pos=0;pos<5;pos++){
        if(tab_jeu[x][y].traitee[pos] == 0){
            if(pos == 4){
                if(tab_jeu[x][y].centre=='v' || tab_jeu[x][y].centre=='b'){ 
                    score = parcours_pion_ville(pos,x,y,1);
                    if(score > 0){
                        parcours_pion_ville(pos,x,y,3);
                        joueuria[1].points += score;
                    }
                }
                if(tab_jeu[x][y].centre=='r'){
                    score = parcours_pion_route(pos,x,y,1);
                    if(score > 0){
                        parcours_pion_route(pos,x,y,3);
                        joueuria[1].points += score;
                    }
                }
            }else{
                if(tab_jeu[x][y].cotes[pos]=='v' || tab_jeu[x][y].cotes[pos]=='b'){
                    score = parcours_pion_ville(pos,x,y,1);
                    if(score > 0){
                        parcours_pion_ville(pos,x,y,3);
                        joueuria[1].points += score;
                    }
                }
                if(tab_jeu[x][y].cotes[pos]=='r'){
                    score = parcours_pion_route(pos,x,y,1);
                    if(score > 0){
                        parcours_pion_route(pos,x,y,3);
                        joueuria[1].points += score;
                    }
                }
            }
        }
    }
    */
}

void point_abbaye(int x,int y,int mode){
    //Mode : 1 = cours de la partie ; 2 = fin de partie
    int i,j,cnt=0;
    for(i=x-1;i<=x+1;i++){
        for(j=y-1;j<=y+1;j++){
            if(i!=x || j!=y){
                if(tab_jeu[i][j].posee == 1){
                    cnt++;
                }
            }
        }
    }
    if(cnt == 8 || mode == 2){
        for(i=0;i< nb_ia+nb_jr;i++){
            if(joueuria[i].id==tab_jeu[x][y].pcentre){
                joueuria[i].points += cnt;
                joueuria[i].pions_restants += 1;
                tab_jeu[x][y].traitee[5]=1;
                tab_jeu[x][y].pcentre=0;
            }
        }
    }
}
