#ifndef _STRUCTURE_
#define _STRUCTURE_

#include <stdbool.h>

typedef struct Card Card;

typedef struct _CardList CardList; //Liste de carte

typedef struct _CardStack CardStack; //Pile de carte

typedef struct _CardQueue CardQueue; //File de carte


/************************************
 * 
 * Gestion des listes
 * 
 * **********************************/

//retourne un pointeur sur une liste de carte vide 
CardList * createCardList();

//desalloue la liste et son contenu
void freeCardList(CardList * cardList);

//ajoute une carte en tete de liste
//retourne true si la carte a bien été ajouté
bool addCardToList(CardList * cardList, Card * card);

//retourne un pointeur sur la carte d'indice index
Card * getCardFromList(CardList * cardList, int index);

//supprime de la liste la carte d'indice index et
//retourne un pointeur sur la carte supprimé
Card * removeCardFromList(CardList * cardList, int index);

//retourne le nombre de cartes de la liste
int getCardListSize(CardList * cardList);


//Retourne true si la carte est presente dans la liste
bool listContainsCard(CardList * cardList, Card * card);


/************************************
 * 
 * Gestion des piles
 * 
 * **********************************/

//retourne un pointeur sur une pile de carte vide 
CardStack * createCardStack();

//desalloue la pile et son contenu
void freeCardStack(CardStack * cardStack);

//ajoute une carte en tete de pile
//retourne true si la carte a bien été ajouté
bool pushCardToStack(CardStack * cardStack, Card * card);

//retourne un pointeur sur la carte d'indice index
Card * getCardFromStack(CardStack * cardStack, int index);

//supprime la premiere carte de la pile
//retourne un pointeur sur la carte supprimé
Card * pullCardFromStack(CardStack * cardStack); 

//retourne le nombre de cartes de la pile
int getCardStackSize(CardStack * cardStack);

//ajoute la pile topStack au debut de la pile bottomStack
//renvoie le pointeur de bottomStack qui contient les deux piles
//desalloue topStack
CardStack * addCardStackToCardStack(CardStack * topStack, CardStack * bottomStack);

//mélange la pile de carte
void shuffleCardStack(CardStack * cardStack);



/************************************
 * 
 * Gestion des files
 * 
 * **********************************/

//retourne un pointeur sur une file de carte vide 
CardQueue * createCardQueue();

//desalloue la file et son contenu
void freeCardQueue(CardQueue * cardQueue);

//ajoute une carte en fin de file
//retourne true si la carte a bien été ajouté
bool addCardToQueue(CardQueue * cardQueue, Card * card);

//retourne un pointeur sur la carte d'indice index
Card * getCardFromQueue(CardQueue * cardQueue, int index);

//supprime la premiere carte de la file
//retourne un pointeur sur la carte supprimé
Card * removeCardFromQueue(CardQueue * cardQueue);

//retourne le nombre de cartes de la file
int getCardQueueSize(CardQueue * cardQueue);



#endif