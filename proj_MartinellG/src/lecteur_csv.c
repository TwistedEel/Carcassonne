#include "lecteur_csv.h"
#include "includes.h"
#include "game_structures.h"

extern struct tuile_s pioche[72];


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
            pioche[i].centre = 'o';
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


