#ifndef GAME_STRUCTURES
#define GAME_STRUCTURES

struct tuile_s{
	int identifiant;
	char cotes[4];
	char centre;
};

struct joueur{
	int points;
	short pions_restants;
	 
};





#endif // GAME_STRUCTURES
