#include "includes.h"
#include "game_structures.h"
#include "pion.h"

extern struct tuile_s pioche[72];
extern struct tuile_s tab_jeu[143][143];
extern int ig,jg,id,jd;
extern int nb_jr,nb_ia,currentj;
extern struct joueur_s joueuria[5];

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
				printf("Il y a déjà un pion du joueur %d sur cette structure !\n",valide);
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
            if(tab_jeu[x][y].centre== ('v' ||'b')){
                occupe = parcours_pion_ville(i,x,y);
            }
        }
    }else{
        if(tab_jeu[x][y].cotes[i]=='r'){
            occupe = parcours_pion_route(i,x,y);
        }else{
            if(tab_jeu[x][y].cotes[i]== ('v' ||'b')){
                occupe = parcours_pion_ville(i,x,y);
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

int parcours_pion_ville(int pos, int x, int y){
    return 0;
}

int parcours_pion_route(int pos,int x,int y){
	struct issue issue1,issue2;
	int nbissue,i,fini;
	//On vérifie si il y a une ou deux issues
	if(tab_jeu[x][y].centre == 'r'){
		nbissue = 2;
	}else{
		nbissue = 1;
	}
	printf("%d \n",nbissue);
	// On initalise la ou les issue.s :
	if(pos ==4){
		for(i=0;i<4;++i){
			if(tab_jeu[x][y].cotes[i] == 'r'){
				issue1.pos = i;
			}
		}
	}else{
		issue1.pos = pos;
	}
	if(nbissue == 2){
		for(i=0;i<4;++i){
			if(tab_jeu[x][y].cotes[i] == 'r' && i!=issue1.pos){
				issue2.pos = i;
			}
		}
		issue2.x=x;
		issue2.y=y;
		printf("issue2 pos : %d x : %d y : %d \n",issue2.pos,issue2.x,issue2.y);
		switch(issue2.pos){
			case 0 :
				issue2.pos = 2;
				issue2.x --;
				break;
			case 1 :
				issue2.pos = 3;
				issue2.y ++;
				break;
			case 2 :
				issue2.pos = 0;
				issue2.x ++;
				break;
			case 3 :
				issue2.pos = 1;
				issue2.y --;
				break;
		}
	}
	printf("issue2 après pos : %d x : %d y : %d \n",issue2.pos,issue2.x,issue2.y);
	issue1.x = x;
	issue1.y = y;
	printf("issue1 pos : %d x : %d y : %d \n",issue1.pos,issue1.x,issue1.y);
	switch(issue1.pos){
		case 0 :
			issue1.pos = 2;
			issue1.x --;
			break;
		case 1 :
			issue1.pos = 3;
			issue1.y ++;
			break;
		case 2 :
			issue1.pos = 0;
			issue1.x ++;
			break;
		case 3 :
			issue1.pos = 1;
			issue1.y --;
			break;
	}
	printf("issue1 après pos : %d x : %d y : %d \n",issue1.pos,issue1.x,issue1.y);
	fini =0;
	//On continue tant qu'il y a bien une route et qu'il n'y a pas eu de fin de route
	while(tab_jeu[issue1.x][issue1.y].posee == 1 && fini == 0){
		printf("while1\n");
		//On vérifie qu'il n'y a pas de pion là où on arrive :
		if(tab_jeu[issue1.x][issue1.y].pcotes[issue1.pos] != 0){
			return tab_jeu[issue1.x][issue1.y].pcotes[issue1.pos];
		}
		//On vérifie qu'il n'y ai pas de fin de route
		if(tab_jeu[issue1.x][issue1.y].centre == 'r'){
			if(tab_jeu[issue1.x][issue1.y].pcentre != 0){
				return tab_jeu[issue1.x][issue1.y].pcentre;
			}
			//On cherche ou la route va :
			for(i=0;i<4;++i){
				if(i!=issue1.pos && tab_jeu[issue1.x][issue1.y].cotes[i] == 'r'){
					issue1.pos = i;
				}
			}
			if(tab_jeu[issue1.x][issue1.y].pcotes[issue1.pos] != 0){
				return tab_jeu[issue1.x][issue1.y].pcotes[issue1.pos];
			}
			switch(issue1.pos){
				case 0 :
					issue1.pos = 2;
					issue1.x --;
					break;
				case 1 :
					issue1.pos = 3;
					issue1.y ++;
					break;
				case 2 :
					issue1.pos = 0;
					issue1.x ++;
					break;
				case 3 :
					issue1.pos = 1;
					issue1.y --;
					break;
			}
		}else{
			fini = 1;
		}
	}
	if(nbissue == 2){
		fini =0;
		//On continuer tant qu'il y a bien une route et qu'il n'y a pas eu de fin de route
		while(tab_jeu[issue2.x][issue2.y].posee == 1 && fini == 0){
			printf("while2");
			//On vérifie qu'il n'y a pas de pion là où on arrive :
			if(tab_jeu[issue2.x][issue2.y].pcotes[issue2.pos] != 0){
				return tab_jeu[issue2.x][issue2.y].pcotes[issue2.pos];
			}
			//On vérifie qu'il n'y ai pas de fin de route
			if(tab_jeu[issue2.x][issue2.y].centre == 'r'){
				if(tab_jeu[issue2.x][issue2.y].pcentre != 0){
					return tab_jeu[issue2.x][issue2.y].pcentre;
				}
				//On cherche ou la route va :
				for(i=0;i<4;++i){
					if(i!=issue2.pos && tab_jeu[issue2.x][issue2.y].cotes[i] == 'r'){
						issue2.pos = i;
					}
				}
				if(tab_jeu[issue2.x][issue2.y].pcotes[issue2.pos] != 0){
					return tab_jeu[issue2.x][issue2.y].pcotes[issue2.pos];
				}
				switch(issue2.pos){
					case 0 :
						issue2.pos = 2;
						issue2.x --;
						break;
					case 1 :
						issue2.pos = 3;
						issue2.y ++;
						break;
					case 2 :
						issue2.pos = 0;
						issue2.x ++;
						break;
					case 3 :
						issue2.pos = 1;
						issue2.y --;
						break;
				}
			}else{
				fini = 1;
			}
		}
	}
	return 0;
}