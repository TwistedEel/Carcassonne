#include "includes.h"
#include "game_structures.h"
#include "pion.h"

extern struct tuile_s pioche[72];
extern struct tuile_s tab_jeu[143][143];
extern int ig,jg,id,jd;
extern int nb_jr,nb_ia,currentj;
extern struct joueur_s joueuria[5];
int liste_ville[44];
int len=0;

int poser_pion(int y,int x,int encore){
	char reponse[10];
	int valide=0,emplacement;
	if(encore == 2){
		printf("Voulez vous poser un pion ? ('oui' ou 'non') : ");
		scanf("%s",reponse);
		if (strcmp("non", reponse) == 0)
        {
            return 0;
        }
        if (strcmp("oui", reponse) == 0)
        {
            valide = 1;
        }
    }
    if (valide != 0 || encore != 2)
    {
        printf("Choisir l'emplacement du pion :\n0 : nord\n1 : est\n2 : sud\n3 : ouest\n4 : centre\nEntrer le chiffre correspondant à l'emplacement choisi : ");
		scanf("%d",&emplacement);
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
	}else{
		printf("La réponse entrée n'est pas valide !\n");
		return poser_pion(y,x,2);
	}
	return 0;
}

int pion_posable(int y,int x,int i){
    int occupe=0;
    if(i==4){ 
        if(tab_jeu[x][y].centre=='r'){
            occupe = parcours_pion_route(i,x,y);
        }else{
            if(tab_jeu[x][y].centre=='v' || tab_jeu[x][y].centre== 'b'){
                occupe = parcours_pion_ville(i,x,y);
				liste_clear();
            }
        }
    }else{
        if(tab_jeu[x][y].cotes[i]=='r'){
            occupe = parcours_pion_route(i,x,y);
        }else{
            if(tab_jeu[x][y].cotes[i]=='v' || tab_jeu[x][y].cotes[i]=='b' ){
                occupe = parcours_pion_ville(i,x,y);
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

int parcours_pion_ville(int pos, int x, int y){
	int t[4]={0,0,0,0};
	int valide = 1, i;
	if(tab_jeu[x][y].posee == 0){
		return 0;
	}
	//On verifie que la ville n'a pas été traitée
	for(i=0;i<len;i++){
		if(tab_jeu[x][y].identifiant == liste_ville[i]){
			valide = 0;
		}
	}
	if(valide==1){
		//On ajoute la ville à la liste des villes traitées
		liste_ville[len]=tab_jeu[x][y].identifiant;
		len ++;
		//Cas ou le centre est une ville :
		if(tab_jeu[x][y].centre =='v' || tab_jeu[x][y].centre =='b'){
			if(tab_jeu[x][y].pcentre != 0){
				return tab_jeu[x][y].pcentre;
			}
			for(i=0;i<4;i++){
				if(tab_jeu[x][y].centre =='v' ||tab_jeu[x][y].centre == 'b'){
					if(tab_jeu[x][y].pcotes[i] != 0){
						return tab_jeu[x][y].pcotes[i];
					}
					switch(i){
						case 0 :
							t[i] = parcours_pion_ville(2,x-1,y);
							break;
						case 1 :
							t[i] = parcours_pion_ville(3,x,y+1);
							break;
						case 2 :
							t[i] = parcours_pion_ville(0,x+1,y);
							break;
						case 3 :
							t[i] = parcours_pion_ville(1,x,y-1);
							break;
					}
				}
			}
			return maxv(t);
		}else{
			if(tab_jeu[x][y].pcotes[pos] != 0){
				return tab_jeu[x][y].pcotes[pos];
			}
			switch(pos){
				case 0 :
					return parcours_pion_ville(2,x-1,y);
					break;
				case 1 :
					return parcours_pion_ville(3,x,y+1);
					break;
				case 2 :
					return parcours_pion_ville(0,x+1,y);
					break;
				case 3 :
					return parcours_pion_ville(1,x,y-1);
					break;
			}
		}
	}
    return 0;
}
int parcours_pion_route(int pos,int x,int y){
	int nbissue,i,fini,pos1,pos2,ix,iy,k;
	//On vérifie si il y a une ou deux issues
	if(tab_jeu[x][y].centre == 'r'){
		nbissue = 2;
	}else{
		nbissue = 1;
	}
	printf("x:%d y:%d nb:%d \n",x,y,nbissue);
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
	if(nbissue == 2){
		for(i=0;i<4;++i){
			if(tab_jeu[x][y].cotes[i] == 'r' && i!=pos1){
				pos2 = i;
			}
		}
	}
	printf("pos1:%d,pos2:%d\n",pos1,pos2);
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
			printf("on regarde %d %d et k = %d\n",ix,iy,k);
			//On vérifie qu'il n'y a pas de pion là où on arrive :
			if(tab_jeu[ix][iy].pcotes[pos1] != 0){
				return tab_jeu[ix][iy].pcotes[pos1];
			}
			//On vérifie qu'il n'y ai pas de fin de route
			if(tab_jeu[ix][iy].centre == 'r'){
				if(tab_jeu[ix][iy].pcentre != 0){
					return tab_jeu[ix][iy].pcentre;
				}
				//On cherche ou la route va :
				printf("On est là : %d \n",pos1);
				for(i=0;i<4;++i){
					printf("%d",i);
					if(i!=pos1 && tab_jeu[ix][iy].cotes[i] == 'r'){
						printf("C bon là ? \n");
						pos1 = i;
						i=5;
					}
				}
				printf(" On part par là : %d \n",pos1);
				if(tab_jeu[ix][iy].pcotes[pos1] != 0){
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
	}
	return 0;
}

void liste_clear(){
	int i;
	for(i=0;i<=len;++i){
		liste_ville[i]=0;
	}
	len=0;
}