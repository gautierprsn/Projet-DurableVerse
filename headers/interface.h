#ifndef _INTERFACE_ 
#define _INTERFACE_
#include "carte.h"

/* @requires un élément de type board valide
   assigns nothing
   ensures renvoie les informations nécessaires aux joueurs pour le début d'un tour */
void printNewTurn(Board *board);
/* @requires un élément de type board valide
   assigns nothing
   ensures renvoie les informations de la nouvelle phase et le player associé */
Player *newPhase (Board *board);
/* @requires un élément de type board valide
   assigns nothing
   ensures renvoie l'état actuel du board */
void printBoard (Board *board);
/* @requires nothing
   assigns nothing
   ensures renvoie 1 si le player veut un FISA, 0 si c'est un FISE */
int chooseStudentCard ();
/* @requires un élément de type player valide
   assigns nothing
   ensures renvoie le numéro de la carte à jouer ou 0 si on finit le tour, -1 si c'est impossible */
int actionTurn ();
/* @requires un élément de type board valide
   assigns nothing
   ensures affiche le résultat d'une partie */
void printWinner (Board *board);

/*@requires un joueur valide
  assigns nothing
  ensures affiche la main d'un joueur */
void printMain(Player *player);


/*@requires un joueur valide
  assigns nothing
  ensures affiche les personnels d'un joueur */
void printPersonnel(Player *player);

/*@requires tableau valide
   assigns nothing
   ensures affiche la fin d'un tour */
void printEndTurn(Board *board);

/*@requires un tableau valide
   assigns nothing
   ensures affiche les PE d'un joueur actif*/
void printPE(Board *board);

/*@requires un joueur valide
   assigns nothing
   ensures affiche la défausse d'un joueur */
void printDiscard(Player *player);

/*@requires un joueur valide
   assigns nothing
ensure affiche le deck d'un joueur */
void printDeck(Player *player);

/*@requires un entier 0 ou 1
    assigns nothing
    ensures un nouvel entier et affiche quel ensiie joue*/
int printPlayer(int i);

/*@requires un plateau
   assigns nothing
   ensures indique un changement de phase */
void changementdephase(Board *board);

/*@requires nothing
   assigns nothin
   ensures indique la fin d'un tour */
void fintour();

/*@requires un joueur
   assigns nothin
   ensures indique le debut d'un tour */
void debuttour();

/*@requires nothing
   assigns nothing
   ensure indique le nombre de carte a piocher */
void infoDrawCard(Player *player);

/*@requires un joueur
   assigns nothing
   ensure indique le nombre d'élève à jouer */
void infoStudentCardsDrawn(Player *player);

/*@requires un joueur valide
   assigns nothing
   ensure indique le nombre de PE */
void infoPE(Player *player);

/*@requires un board valide
   assigns nothing
   ensure indique le nombre de DD */
void printDD(Board *board);

/*@requires nothing
   assigns nothing
   ensure indique le cout trop eleve */
void printCout();

/*@requires nothing
   assigns nothing
   ensure indique qu'on ne possède pas la carte */
void printNoCard();
#endif
