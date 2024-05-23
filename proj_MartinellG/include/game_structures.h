#ifndef GAME_STRUCTURES
#define GAME_STRUCTURES

struct tuile_s{
	int identifiant;
	char cotes[4];
	char centre;
	int traitee[5];
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

struct issue{
	int pos;
	int x;
	int y;
};

#endif // GAME_STRUCTURES
