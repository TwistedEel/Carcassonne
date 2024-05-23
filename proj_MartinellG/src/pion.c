#include "includes.h"
#include "game_structures.h"
#include "pion.h"

extern struct tuile_s pioche[72];
extern struct tuile_s tab_jeu[143][143];
extern int ig,jg,id,jd;
extern int nb_jr,nb_ia,currentj;
extern struct joueur_s joueuria[5];
extern int liste_ville[44][2];
extern int len;
extern int pions_presents[5];

int poser_pion(int y,int x,int encore){
	int valide=0,emplacement;
	printf("Choisir l'emplacement du pion :\n0 : nord\n1 : est\n2 : sud\n3 : ouest\n4 : centre\n5 : annuler\nEntrer le chiffre correspondant à l'emplacement choisi : ");
	scanf("%d",&emplacement);
	if(emplacement == 5){
		return 0;
	}
	if(emplacement<5 && emplacement >= 0){
		valide =0;
		if(emplacement == 4){ 
			if(tab_jeu[x][y].centre=='p' || tab_jeu[x][y].centre=='o'){
				valide = 1;
			}
		}else{
			if(tab_jeu[x][y].cotes[emplacement]=='p' || tab_jeu[x][y].cotes[emplacement]=='p'){
				valide = 1;
			}
		}
		if(valide == 1){
			printf("Vous ne pouvez pas poser sur ce type de terrain\n");
			return poser_pion(y,x,1);
		}
		valide = pion_posable(y,x,emplacement);
		if(valide != 0){
			printf("Il y a déjà un pion du joueur sur cette structure !\n");
			return poser_pion(y,x,1);
		}
	}else{
		printf("La réponse entrée n'est pas valide !\n");
		return poser_pion(y,x,1);
	}
	return 0;
}

int pion_posable(int y,int x,int i){
    int occupe=0;
    if(i==4){ 
        if(tab_jeu[x][y].centre=='r'){
            occupe = parcours_pion_route(i,x,y,0);
        }else{
            if(tab_jeu[x][y].centre=='v' || tab_jeu[x][y].centre== 'b'){
                occupe = parcours_pion_ville(i,x,y,0);
				liste_clear();
            }
        }
    }else{
        if(tab_jeu[x][y].cotes[i]=='r'){
            occupe = parcours_pion_route(i,x,y,0);
        }else{
            if(tab_jeu[x][y].cotes[i]=='v' || tab_jeu[x][y].cotes[i]=='b' ){
                occupe = parcours_pion_ville(i,x,y,0);
				liste_clear();
            }
        }
    }
    if(occupe ==0){
        if(i==4){
            tab_jeu[x][y].pcentre = joueuria[currentj].id;
        }else{
            tab_jeu[x][y].pcotes[i] = joueuria[currentj].id;
        }
		joueuria[currentj].pions_restants --;
    }
	return occupe;
}

int maxv(int* t){
	int res = t[0];
	for(int i=1;i<4;i++){
		if(t[i]>res){
			res=t[i];
		}
	}
	return res;
}

int pointv(int* t){
	int res=0;
	for(int i=0;i<4;i++){
		if(t[i]!=-1){
			res += t[i];
		}
	}
	return res;
}

int parcours_pion_ville(int pos, int x, int y,int mode){
	//Le mode indique l'objectif du parcours, 0 : recherche d'un pion ; 1 : recherche si complétée
	//2 : fin de partie ; 3 : mettre toute la structure à l'étât "traitée" et retirer les pions
	int t[4]={-1,-1,-1,-1};
	int valide = 1, i,cnt=0;
	if(tab_jeu[x][y].posee == 0){
		return 0;
	}
	//On verifie que la ville n'a pas déjà été regardée
	for(i=0;i<len;i++){
		if(liste_ville[i][1]==4){
			if(tab_jeu[x][y].identifiant == liste_ville[i][0]){
				valide = 0;
			}
		}else{
			if(liste_ville[i][1] != 0){
				if(tab_jeu[x][y].identifiant == liste_ville[i][0] && pos == liste_ville[i][1]){
					valide = 0;
				}
			}
		}
	}
	if(valide==1){
		//On ajoute la ville à la liste des villes regardées
		liste_ville[len][0]=tab_jeu[x][y].identifiant;
		len ++;
		//Cas ou le centre est une ville :
		if(tab_jeu[x][y].centre =='v' || tab_jeu[x][y].centre =='b'){
			liste_ville[len][1]=4;
			if(mode == 1){
				if(tab_jeu[x][y].centre =='b'){
					cnt += 4;
				}else{
					cnt += 2;
				}
			}
			if(mode==2){
				if(tab_jeu[x][y].centre =='b'){
					cnt += 2;
				}else{
					cnt += 1;
				}
			}
			if(mode==3){
				tab_jeu[x][y].traitee[4] = 1;
				tab_jeu[x][y].pcentre = 0;
			}
			if(mode==0 && tab_jeu[x][y].pcentre != 0){
				return tab_jeu[x][y].pcentre;
			}
			for(i=0;i<4;i++){
				if(tab_jeu[x][y].cotes[i] =='v' ||tab_jeu[x][y].cotes[i] == 'b'){
					if(mode==3){
						tab_jeu[x][y].traitee[i] = 1;
						tab_jeu[x][y].pcotes[i] = 0;
					}
					if(mode==0 && tab_jeu[x][y].pcotes[i] != 0){
						return tab_jeu[x][y].pcotes[i];
					}
					switch(i){
						case 0 :
							t[i] = parcours_pion_ville(2,x-1,y,mode);
							break;
						case 1 :
							t[i] = parcours_pion_ville(3,x,y+1,mode);
							break;
						case 2 :
							t[i] = parcours_pion_ville(0,x+1,y,mode);
							break;
						case 3 :
							t[i] = parcours_pion_ville(1,x,y-1,mode);
							break;
					}
				}
				if(mode==1 && t[i]==0){
					return 0;
				}
			}
			if(mode==0) return maxv(t);
			if(mode==1 || mode==2) return pointv(t)+cnt;
		}else{
			if(liste_ville[len][1]!=0){
				liste_ville[len][1]=4;
			}else{
				liste_ville[len][1]=pos;
			}
			len++;
			if(mode == 1){
				cnt += 2;
			}
			if(mode==2){
				cnt += 1;
			}
			if(mode==3){
				tab_jeu[x][y].traitee[pos] = 1;
				tab_jeu[x][y].pcotes[pos] = 0;
			}
			if(mode==0 && tab_jeu[x][y].pcotes[pos] != 0){
				return tab_jeu[x][y].pcotes[pos];
			}
			switch(pos){
				case 0 :
					t[0]= parcours_pion_ville(2,x-1,y,mode);
					if(t[0] != 0){
						return t[0]+cnt;
					}else{
						return cnt;
					}
					break;
				case 1 :
					t[0]=parcours_pion_ville(3,x,y+1,mode);
					if(t[0] != 0){
						return t[0]+cnt;
					}else{
						return cnt;
					}
					break;
				case 2 :
					t[0]=parcours_pion_ville(0,x+1,y,mode);
					if(t[0] != 0){
						return t[0]+cnt;
					}else{
						return cnt;
					}
					break;
				case 3 :
					t[0]=parcours_pion_ville(1,x,y-1,mode);
					if(t[0] != 0){
						return t[0]+cnt;
					}else{
						return cnt;
					}
					break;
			}
		}
	}
	if(mode==0){
		return 0;
	}else{
		return -1;
	}
}
int parcours_pion_route(int pos,int x,int y,int mode){
	//Le mode indique l'objectif du parcours, 0 : recherche d'un pion ; 1 : recherche si complétée
	//2 : fin de partie ; 3 : mettre toute la structure à l'étât "traitée" et retirer les pions
	int nbissue,i,fini,pos1,pos2,ix,iy,k,score=1;
	//On vérifie si il y a une ou deux issues
	if(tab_jeu[x][y].centre == 'r'){
		nbissue = 2;
		if(mode == 3){
			tab_jeu[x][y].pcentre = 0;
			tab_jeu[x][y].traitee[4	] =1;
		}
	}else{
		nbissue = 1;
	}
	if(mode == 3){
		tab_jeu[x][y].traitee[pos] =1;
	}
	//On initalise les issues
	if(pos ==4){
		for(i=0;i<4;++i){
			if(tab_jeu[x][y].cotes[i] == 'r'){
				pos1 = i;
			}
			
		}
	}else{
		pos1 = pos;
	}
	if(mode == 3){
		tab_jeu[x][y].traitee[pos1] =1;
		tab_jeu[x][y].pcotes[pos1] = 0;
	}
	if(nbissue == 2){
		for(i=0;i<4;++i){
			if(tab_jeu[x][y].cotes[i] == 'r' && i!=pos1){
				pos2 = i;
			}
		}
		if(mode == 3){
			tab_jeu[x][y].traitee[pos2] =1;
			tab_jeu[x][y].pcotes[pos2] = 0;
		}
	}
	for(k=0;k<nbissue;k++){
		if(k==1){
			pos1=pos2;
		}
		ix = x;
		iy = y;
		switch(pos1){
			case 0 :
				pos1 = 2;
				ix --;
				break;
			case 1 :
				pos1 = 3;
				iy ++;
				break;
			case 2 :
				pos1 = 0;
				ix ++;
				break;
			case 3 :
				pos1 = 1;
				iy --;
				break;
		}
		fini =0;
		while(tab_jeu[ix][iy].posee == 1 && fini == 0 && (x!=ix || y!=ix)){
			//On vérifie qu'il n'y a pas de pion là où on arrive :
			if(mode==0 && tab_jeu[ix][iy].pcotes[pos1] != 0){
				return tab_jeu[ix][iy].pcotes[pos1];
			}
			if(mode == 3){
				tab_jeu[ix][iy].traitee[pos1] =1;
				tab_jeu[ix][iy].pcotes[pos1] = 0;
			}
			if(mode == 2 || mode == 1){
				score ++;
			}
			//On vérifie qu'il n'y ai pas de fin de route
			if(tab_jeu[ix][iy].centre == 'r'){
				if(mode==0 && tab_jeu[ix][iy].pcentre != 0){
					return tab_jeu[ix][iy].pcentre;
				}
				if(mode == 3){
					tab_jeu[ix][iy].traitee[4] =1;
					tab_jeu[ix][iy].pcentre = 0;
				}
				//On cherche ou la route va :
				for(i=0;i<4;++i){
					if(i!=pos1 && tab_jeu[ix][iy].cotes[i] == 'r'){
						pos1 = i;
						i=5;
					}
				}
				if(mode == 3){
					tab_jeu[ix][iy].traitee[pos1] =1;
					tab_jeu[ix][iy].pcotes[pos1] = 0;
				}
				if(mode==0 && tab_jeu[ix][iy].pcotes[pos1] != 0){
					return tab_jeu[ix][iy].pcotes[pos1];
				}
				switch(pos1){
					case 0 :
						pos1 = 2;
						ix --;
						break;
					case 1 :
						pos1 = 3;
						iy ++;
						break;
					case 2 :
						pos1 = 0;
						ix ++;
						break;
					case 3 :
						pos1 = 1;
						iy --;
						break;
				}
			}else{
				fini = 1;
			}
		}
		if(mode==1 && fini == 0){
			return 0;
		}
	}
	if(mode==0){
		return 0;
	}else{
		return score;
	}
}

void liste_clear(){
	int i,j;
	for(i=0;i<=len;++i){
		for(j=0;j<2;++j){
			liste_ville[i][j]=0;
		}
	}
	len=0;
}