#ifndef GAME_STRUCTURES
#define GAME_STRUCTURES

struct tuile_s{
	int identifiant;
	char cotes[4];
	char centre;
    	int posee;
    	int posable;
    	int pcotes[4];
    	int pcentre;
};

struct joueur_s{
	int points;
	int pions_restants;
	int IA;
	int id;
	char* couleur; //0 = rouge ; 1 = bleu ; 2 = vert ; 3 = violet ; 4 = jaune
};

#endif // GAME_STRUCTURES
