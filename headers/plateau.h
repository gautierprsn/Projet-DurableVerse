#ifndef _PLATEAU
#define _PLATEAU

#include "structure.h"
#include "carte.h"
struct Player {
  CardStack *deck;
  CardList *main;
  CardStack *discard;
  int fise;
  int fisa;
  int durability;
  int DDfise;
  int DDfisa;
  int durabilityfise;
  int durabilityfisa;
  CardQueue *personnel;
  int DD; //pts de développement durable
  int PE; // pts d'énergie
};
typedef struct Player Player;
//permet de définir le plateau
struct board{
  Player *activePlayer;
  Player *unactivePlayer;
  int lapcounter;
};
typedef struct board Board;



//chaque joueur a un deck=paquet, une main de carte et une défausse qui sont des listes avec dans les listes les identifiants des cartes. La tête de liste de la list paquet correspond à la carte sur le haut du deck.




/* @requires nothing
   assigns nothing
   ensures créer un nouveau plateau */
Board *newBoard ();

/*@requires un plateau
  assigns libère la mémoire prise par le tableau
  ensures nothing */
void freeBoard(Board *board);

/*@requires un plateau
  assigns nothing
  ensures renvoie un plateau mis a jour, avec le compteur de tour incrémenté etc*/
Board *majBoard(Board *board);

/* @requires le joueur qui pioche
   assigns nothing
   ensures renvoie la carte piochée par l'ensiie */
Card *draw(Player *activePlayer);

/*@requires le joueur qui pioche
  assigns nothing
  ensures renvoie le nombre de cartes piochées par le joueur*/
int drawCard(Player *activePlayer);



/* @requires un élément de type Player valide
   assigns nothing
   ensures renvoie le nombre de cartes que le Player doit piocher au début de son tour */
int studentCardsDrawn(Player *activePlayer);


/* @requires un élément p de type Player valide
   assigns le Player p
   ensures renvoie p avec un FISE en plus */
Player addFISE(Player *activePlayer);


/* @requires un élément p de type Player valide
   assigns le Player p
   ensures renvoie p avec un FISA en plus */
Player addFISA(Player *player);

/*@requires un plateau
   assings nothing
   ensure renvoie le nombre de tour */
int getLap(Board *board);



/* @requires un élément p de type Player valide
   assigns nothing
   ensures renvoie le nombre de PE disponibles de p */
int availablePE(Player activePlayer);


/* @requires un élément de type Board valide, une carte valide
   assigns le Playerx p
   ensures renvoie le tableau après qu'il ait posé la carte de sa main */
Board *playCard(Board *board, Card* card);


/* @requires un board P valide
   assigns le board P
   ensures renvoie le board P mis à pour après la fin du tour */
Board *endTurn(Board *board);


/* @requires un board P valide
   assigns le board P
   ensures vérifie si la partie est fini et renvoie 0 si la partie n'est pas finie, 1 si p1 gagne, 2 si p2 gagne et 3 si il y a égalité */
int endGame(Board *board);


/*@requires nothing
  assigns alloue l'espace mémoire pour le deck
  ensures un deck initial */
CardStack *createDeck();

/*@requires un deck de départ
  assigns espacee mémoire pour la main
  ensures renvoie la main initiale*/
CardList* initializeMain(Player *activePlayer);

/*@requires nothing
  assigns espace  mémoire pour le personnel
  ensures renvoie l'espace personnel*/
CardQueue *initializePersonnel();

/*@requires nothing
  assigns espacee mémoire pour la défausse
  ensures renvoie la défausse initiale*/
CardStack *initializeDiscard();

/*@requires un board valide
  assigns nothing
  ensures inverse active et unactive Player */
void switch_player(Board *board);

/*@requires un board valide 
   assigns nothing
   ensure calcul le nombre de PE par tour*/ 
void calculPE(Board * board);

/*@requires un board valide 
   assigns nothing
   ensure calcul le nombre de DD gagnés au tour*/ 
void calculDD(Board *board);



#endif




