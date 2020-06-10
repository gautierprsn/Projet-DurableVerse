#ifndef _CARTE_ 
#define _CARTE_
#include "plateau.h"


typedef struct Card Card;
typedef struct board Board;

/*@requires un entier id et un plateau board
@assigns board
@ensures réaliser l'effet AE1 sur le board*/
Board *AE1(Board *board, int n);

/*@requires un entier id et un plateau board
@assigns board
@ensures réaliser l'effet AE2 sur le board*/
Board *AE2(Board *board, int n);

/*@requires un entier id et un plateau board
@assigns board
@ensures réaliser l'effet AA1 sur le board*/
Board *AA1(Board *board, int n);

/*@requires un entier id et un plateau board
@assigns board
@ensures réaliser l'effet AA2 sur le board*/
Board *AA2(Board *board, int n);

/*@requires un entier id et un plateau board
@assigns board
@ensures réaliser l'effet RE1 sur le board*/
Board *RE1(Board *board, int n);

/*@requires un entier id et un plateau board
@assigns board
@ensures réaliser l'effet RE2 sur le board*/
Board *RE2(Board *board, int n);

/*@requires un entier id et un plateau board
@assigns board
@ensures réaliser l'effet RA1 sur le board*/
Board *RA1(Board *board, int n);

/*@requires un entier id et un plateau board
@assigns board
@ensures réaliser l'effet RA2 sur le board*/
Board *RA2(Board *board, int n);

/*@requires un entier id et un plateau board
@assigns board
@ensures réaliser l'effet ADD sur le board*/
Board *ADD(Board *board, int n);

/*@requires un entier id et un plateau board
@assigns board
@ensures réaliser l'effet RDD sur le board*/
Board *RDD(Board *board, int n);

/*@requires une carte card de type personnel et un plateau board
@assigns board
@ensures réaliser les effets de card sur le board*/
Board *personnalCardEffect(Board *board, int i);


/*@requires une carte card de type action et un plateau board
@assigns board
@ensures réaliser les effets de card sur le board*/
Board *actionCardEffect(Board *board, int id);


/*@requires deux cartes
@assigns nothing
@ensures retourne True si les deux cartes sont la même*/
bool areSameCard(void *card1, void *card2);


/*@requires char speciality, int id, int cost
@assigns nothing
@ensures retourne un pointeur sur une carte carte avec les caractéristiques données en arguments*/
Card *createCard(char speciality, int id, int cost);

/*@requires Card 
@assigns nothing
@ensures retourne le coût en PE de la carte*/
int getCardCost(Card *card);


/*@requires Card 
@assigns nothing
@ensures retourne l'ID' de la carte*/
int getCardID(Card *card);



/*@requires Card card
@assigns card
@ensures nothing*/
void freeCard(Card *card);


/*@requires entier i
@assigns nothing
@ensures renvoie la carte associée à l'id i*/
Card *find(int i);

void printCard (Card *card);

void shuffle(Board *board);
#endif
