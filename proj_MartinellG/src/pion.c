#include "includes.h"
#include "game_structures.h"
#include "pion.h"

extern struct tuile_s pioche[72];
extern struct tuile_s tab_jeu[143][143];
extern int ig,jg,id,jd;
extern int nb_jr,nb_ia,currentj;
extern struct joueur_s joueuria[5];

int poser_pion(int y,int x,int i){
    int occupe;
    if(i==5){ 
        if(tab_jeu[x][y].centre=='r'){
            occupe = parcours_pion_route(i,x,y);
        }else{
            if(tab_jeu[x].[y].centre== ('v' ||'b')){
                occupe = parcours_pion_ville(i,x,y);
            }else{
                occupe = 0;
            }
        }
    }else{
        if(tab_jeu[x][y].cotes[i]=='r'){
            occupe = parcours_pion_route(i,x,y);
        }else{
            if(tab_jeu[x].[y].cotes[i]== ('v' ||'b')){
                occupe = parcours_pion_ville(i,x,y);
            }
        }
    }
    if(occupe ==0){
        if(i==5){
            tab_jeu[x][y].pcentre = joueuria[currentj].id;
        }else{
            tab_jeu[x][y].pcotes[i] = joueuria[currentj].id;
        }
    }
}

int parcours_pion_ville(int pos, int x, int y){
    return 0;
}

int parcours_pion_route(int pos, int x, int y)
{   
	struct issue issue1, issue2;
	int i, init=1;
	issue1.pos = pos;
	issue1.x = x;
	issue1.y = y;
	issue2.pos = -1;

	while(issue1.pos != -2 || issue2.pos != -2){
		//D'abord issue1 !
		if(tab_jeu[issue1.x][issue1.y].centre == 'r')
		{
			if(tab_jeu[issue1.x][issue1.y].pcentre != 0){
				return tab_jeu[issue1.x][issue1.y].pcentre;
			}
			if(init == 1){
				if(issue1.pos == 5){
					i=0;
					while(tab_jeu[issue1.x][issue1.y].cotes[i]!='r'){
						i++;
					}
					issue1.pos=i;
				}
				for(i=0;i<4;++i){
					if(i!=issue1.pos && tab_jeu[issue1.x][issue1.y].cotes[i]=='r'){
                        issue2.pos= i;
                        issue2.x = x;
                        issue2.y = y;
					}
				}
			}else{
				for(i=0;i<4;++i){
					if(i!=issue1.pos && tab_jeu[issue1.x][issue1.y].cotes[i]=='r'){
						if(tab_jeu[issue1.x][issue1.y].pcotes[i] != 0){
							return tab_jeu[issue1.x][issue1.y].pcotes[i];
						}else{
							issue1.pos= i;
						}
					}
				}
			}

		}else{
			if(issue2.pos == -2){
				issue1.pos = -2;
			}else{
				issue2.pos = -2;
			}
		}
		//Ensuite issue 2 :
		if(init != 1){
			if(tab_jeu[issue2.x][issue2.y].centre == 'r'){
				if(tab_jeu[issue2.x][issue2.y].pcentre != 0){
					return tab_jeu[issue2.x][issue2.y].pcentre;
				}
				for(i=0;i<4;++i){
					if(i!=issue2.pos && tab_jeu[issue2.x][issue2.y].cotes[i]=='r'){
						if(tab_jeu[issue2.x][issue2.y].pcotes[i] != 0){
							return tab_jeu[issue2.x][issue2.y].pcotes[i];
						}else{
							issue2.pos= i;
						}
					}
				}
			}else{
				if(issue2.pos == -2){
					issue1.pos = -2;
				}else{
					issue2.pos = -2;
				}
			}
		}
		//Une fois qu'on a nos deux éventuelles extrémités on les propage à la tuile suivante :
		switch(issue1.pos){
        case 0 :
			issue1.pos = 2;
            issue1.x = x;
            issue1.y = y-1;
		case 1 :
			issue1.pos = 3;
			issue1.x = x+1;
			issue1.y = y;
		case 2 :
			issue1.pos = 0;
			issue1.x = x;
			issue1.y = y+1;
		case 3 :
			issue1.pos = 1;
			issue1.x = x-1;
			issue1.y = y;
		}
		if(tab_jeu[issue1.x][issue1.y].posee == 0){
			issue1.pos = -2;
		}else{
			if(tab_jeu[issue1.x][issue1.y].pcotes[issue1.pos] != 0){
				return tab_jeu[issue1.x][issue1.y].pcotes[issue1.pos];
			}
		}
		switch(issue2.pos){
        case 0 :
			issue2.pos = 2;
            issue2.x = x;
            issue2.y = y-1;
		case 1 :
			issue2.pos = 3;
			issue2.x = x+1;
			issue2.y = y;
		case 2 :
			issue2.pos = 0;
			issue2.x = x;
			issue2.y = y+1;
		case 3 :
			issue2.pos = 1;
			issue2.x = x-1;
			issue2.y = y;
		}
		if(tab_jeu[issue2.x][issue2.y].posee == 0){
			issue2.pos = -2;
		}else{
			if(tab_jeu[issue2.x][issue2.y].pcotes[issue2.pos] != 0){
				return tab_jeu[issue2.x][issue2.y].pcotes[issue2.pos];
			}
		}
		init = 0;
	}
    return 0;
}