
#include <sys/types.h>
#include "lecteur_csv.h"
#include "includes.h"
#include "game_structures.h"
#include "affichage.h"
#include "ANSI-color-codes.h"
#include "pion.h"
#define j_max 5

struct tuile_s pioche[72];
struct tuile_s tab_jeu[143][143];
int ig = 72, id = 72, jg = 72, jd = 72;
int nb_jr = 0, nb_ia = 0, currentj = 0;
struct joueur_s joueuria[5];

void creer_joueuria()
{
    int i, j, encore = 1;
    while (encore != 0)
    {
        if (encore == 2)
        {
            printf("Il doit y avoir entre 1 et 5 joueur/ia : \n");
        }
        printf("Entrer le nombre de joueur stp : ");
        scanf("%d", &nb_jr);
        printf("Entrer le nombre d'ia stp : ");
        scanf("%d", &nb_ia);
        if (nb_jr + nb_ia <= 5)
        {
            encore = 0;
        }
        else
        {
            encore = 2;
        }
    }
    for (i = 0; i < nb_jr + nb_ia; ++i)
    {
        joueuria[i].points = 0;
        joueuria[i].pions_restants = 6;
        if (i < nb_jr)
        {
            joueuria[i].IA = 0;
            encore = 1;
            while (encore == 1)
            {
                encore = 0;
                printf("Entrer une couleur pour le joueur %d\n(1 = rouge ; 2 = bleu ; 3 = vert ; 4 = violet ; 5 = jaune)\nCouleur choisie :", i);
                scanf("%d", &joueuria[i].id);
                for (j = 0; j < i; ++j)
                {
                    if (joueuria[j].id == joueuria[i].id)
                    {
                        encore = 1;
                    }
                }
                if (encore == 1)
                {
                    printf("Cette couleur est déjà choisie ou invalide, réessayer :\n");
                }
            }
        }
        else
        {
            joueuria[i].IA = 1;
            joueuria[i].id = 0;
            encore = 1;
            while (encore == 1)
            {
                encore = 0;
                joueuria[i].id += 1;
                for (j = 0; j < i; ++j)
                {
                    if (joueuria[j].id == joueuria[i].id)
                    {
                        encore = 1;
                    }
                }
            }
        }
    }
}

int tourner_tuile(struct tuile_s *t, int encore)
{
    char reponse[10], tmp;
    int i, j, valide = 0, k;
    if (encore == 2)
    {
        printf("Voulez vous tournez la tuile de 90° dans le sens anti-horaire ?\n(Répondre 'oui' ou 'non') : ");
        scanf("%s", reponse);
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
        printf("Combien de fois ? \n(Entrer un chiffre entre 1 et 3) :");
        scanf("%d", &k);
        for (i = 0; i < k; ++i)
        {
            tmp = t->cotes[0];
            for (j = 0; j < 3; ++j)
            {
                t->cotes[j] = t->cotes[j + 1];
            }
            t->cotes[3] = tmp;
        }
        return 1;
    }
    else
    {
        printf("La réponse n'est pas valide, entrez une réponse valide svp : \n");
        return tourner_tuile(t, encore);
    }
}

int tourner_encore()
{
    int valide = 0;
    char reponse[10];
    while (valide == 0)
    {
        printf("Voulez-vous encore tourner la tuile ? ('oui' ou 'non') : ");
        scanf("%s", reponse);
        valide = 1;
        if (strcmp("non", reponse) == 0)
        {
            return 0;
        }
        else
        {
            if (strcmp("oui", reponse) != 0)
            {
                printf("La réponse n'est pas valide, entrez une réponse valide svp : \n");
                valide = 0;
            }
            else
            {
                return 1;
            }
        }
    }
    return 0;
}

int compatible(struct tuile_s *t1, struct tuile_s *t2, int face1, int face2)
{
    if (t2->posee == 0)
    {
        return 1;
    }
    else
    {
        if (((t1->cotes[face1] == 'b' || t1->cotes[face1] == 'v') && (t2->cotes[face2] == 'b' || t2->cotes[face2] == 'v')) || ((t1->cotes[face1] == 'r') && (t2->cotes[face2] == 'r')) || ((t1->cotes[face1] == 'p') && (t2->cotes[face2] == 'p')))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

void f_posable(struct tuile_s *t)
{
    int i, j;
    for (i = ig - 1; i <= id + 1; ++i)
    {
        for (j = jg - 1; j <= jd + 1; ++j)
        {
            if (tab_jeu[i][j].posee == 0)
            {
                if ((tab_jeu[i - 1][j].posee == 0) && (tab_jeu[i][j + 1].posee == 0) && (tab_jeu[i + 1][j].posee == 0) && (tab_jeu[i][j - 1].posee == 0))
                {
                    tab_jeu[i][j].posable = 0;
                }
                else
                {
                    if ((compatible(t, &tab_jeu[i - 1][j], 0, 2) == 1) && (compatible(t, &tab_jeu[i][j + 1], 1, 3) == 1) && (compatible(t, &tab_jeu[i + 1][j], 2, 0) == 1) && (compatible(t, &tab_jeu[i][j - 1], 3, 1) == 1))
                    {
                        tab_jeu[i][j].posable = 1;
                    }
                    else
                    {
                        tab_jeu[i][j].posable = 0;
                    }
                }
            }
            else
            {
                tab_jeu[i][j].posable = 0;
            }
        }
    }

    return;
}

void poser_tuile(int y, int x, int i)
{
    /*
    Lorsque l'on rentre des coordonnées, on est habitué à les rentrer
    sous la forme (x,y), cependant pour la vision humaine de la grille
    x correspond à la colonne et y à la ligne alors que dans le programme
    pour tab[i][j] on a i qui correspond à la ligne et j à la colonne,
    on part donc du principe dans l'entête de la fonction que
    l'on rentre les coordonées sous la forme (y,x) pour faciliter
    l'insertion et la mise à jour des coins gauche et droit.
    */
    int k;
    tab_jeu[x][y].identifiant = pioche[i].identifiant;
    tab_jeu[x][y].centre = pioche[i].centre;
    for (k = 0; k < 4; ++k)
    {
        tab_jeu[x][y].cotes[k] = pioche[i].cotes[k];
    }
    tab_jeu[x][y].posee = 1;
    pioche[i].posee = 1;
    // On met à jour le coin gauche (jg,ig) et le coin droit (jd,id) ;
    if (y < jg)
    {
        jg = y;
    }
    else
    {
        if (y > jd)
        {
            jd = y;
        }
    }
    if (x < ig)
    {
        ig = x;
    }
    else
    {
        if (x > id)
        {
            id = x;
        }
    }

    return;
}

int moteur_jeu()
{
    int i, x, y, encore;
    // Initialisation :
    creer_joueuria();
    poser_tuile(72, 72, 0);
    // Boucle de jeu :
    for (i = 1; i < 72; ++i)
    { // Chaque itération de cette boucle est un tour de jeu
        currentj = (i - 1) % (nb_jr + nb_ia);
        encore = 2;
        while (encore != 0)
        {
            f_posable(&pioche[i]);
            afficher_grille(i);
            printf("Tuile en main :\n");
            affiche_tuile(&pioche[i]);
            encore = tourner_tuile(&pioche[i], encore);
            f_posable(&pioche[i]);
            afficher_grille(i);
            printf("Tuile en main :\n");
            affiche_tuile(&pioche[i]);
            if (encore == 1)
            {
                encore = tourner_encore();
            }
        }
        encore = 2;
        while (encore != 0)
        {
            afficher_grille(i);
            printf("Tuile en main :\n");
            affiche_tuile(&pioche[i]);
            if (encore == 1)
            {
                printf("La tuile n'est pas posable à ces coordonnées, veuillez en entrer des nouvelles :\nx (la colonne) = ");
            }
            else
            {
                printf("Entrer les coordonnées de l'emplacement où vous voulez poser la tuile : \nx (la colonne) = ");
            }
            scanf("%d", &x);
            printf("y (la ligne) = ");
            scanf("%d", &y);
            if (tab_jeu[y][x].posable == 1)
            {
                poser_tuile(x, y, i);
                encore = 0;
            }
            else
            {
                encore = 1;
            }
        }
        if(joueuria[currentj].pions_restants > 0){
            afficher_grille(i);
            encore = poser_pion(x,y,2);
            printf("For pity :");
            scanf("%d", &x);
        }
    }
    return 1;
}

int main(int argc, char *argv[])
{
    parseur_csv("tuiles.csv");
    melange_tuiles();
    moteur_jeu();
    // Détail d'un tour de jeu :
    /*
    int game_loop(){
        //1 - déterminer un joueur
        //2 - piocher une tuile
        //	2a - tuile posable ?
        //	2b - pioche vide ?
        //3 - poser la tuile
        //	3a - tuile posable ?
        //4 - vérification de l'état des éléments (ex:route)
        //	4a - élément créé ?
        //	4b - élément fini ?
        //	4c - élément continué ?
        //5 - pion posé ?
        //	5a - posé où ?
        //	5b - points à attribuer ?
        //6 - màj classement
    }
    */
    return 0;
}
