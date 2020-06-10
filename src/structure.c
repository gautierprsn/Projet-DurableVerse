#include <stdlib.h>
#include "../headers/structureEngine.h"
#include "../headers/structure.h"
#include "../headers/carte.h"

struct _CardList{
    List * cardList;
};

struct _CardStack{
    Stack * cardStack;
};

struct _CardQueue{
    Queue * cardQueue;
};


/************************************
 * 
 * Gestion des listes
 * 
 * **********************************/

//retourne un pointeur sur une liste de carte vide 
CardList * createCardList(){
    CardList * newCardList = (CardList*)malloc(sizeof(CardList));
    List * newList = createList();

    newCardList->cardList = newList;

    return newCardList;
}

//desalloue la liste et son contenu
void freeCardList(CardList * cardList){

    while(getCardListSize(cardList) > 0){
        freeCard((Card *)removeCardFromList(cardList, 0));
    }

    freeList(cardList->cardList);

    free(cardList);
}

//ajoute une carte en tete de liste
//retourne true si la carte a bien été ajouté
bool addCardToList(CardList * cardList, Card * card){
    return addToList(cardList->cardList, card);
}

//retourne un pointeur sur la carte d'indice index
Card * getCardFromList(CardList * cardList, int index){
    return (Card *)get(cardList->cardList, index);
}

//supprime de la liste la carte d'indice index et
//retourne un pointeur sur la carte supprimé
Card * removeCardFromList(CardList * cardList, int index){
    return (Card *)removeListData(cardList->cardList, index);
}

//retourne le nombre de cartes de la liste
int getCardListSize(CardList * cardList){
    return getListSize(cardList->cardList);
}

//Retourne true si la carte est presente dans la liste
bool listContainsCard(CardList * cardList, Card * card){

    return listContains(cardList->cardList, card, areSameCard);

}

/************************************
 * 
 * Gestion des piles
 * 
 * **********************************/

//retourne un pointeur sur une pile de carte vide 
CardStack * createCardStack(){
    CardStack * newCardStack = (CardStack *)malloc(sizeof(CardStack));
    Stack * newStack = createStack();

    newCardStack->cardStack = newStack;

    return newCardStack;
}

//desalloue la pile et son contenu
void freeCardStack(CardStack * cardStack){
    while(getCardStackSize(cardStack) > 0){
        freeCard((Card *)pullCardFromStack(cardStack));
    }

    freeStack(cardStack->cardStack);
    free(cardStack);
}

//ajoute une carte en tete de pile
//retourne true si la carte a bien été ajouté
bool pushCardToStack(CardStack * cardStack, Card * card){
    return stackPush(cardStack->cardStack, card);
}

//retourne un pointeur sur la carte d'indice index
Card * getCardFromStack(CardStack * cardStack, int index){
    return (Card *)getStackData(cardStack->cardStack, index);
}

//supprime la premiere carte de la pile
//retourne un pointeur sur la carte supprimé
Card * pullCardFromStack(CardStack * cardStack){
    return (Card *)stackPull(cardStack->cardStack);
}

//retourne le nombre de cartes de la pile
int getCardStackSize(CardStack * cardStack){
    return getStackSize(cardStack->cardStack);
}

//ajoute la pile topStack au debut de la pile bottomStack
//renvoie le pointeur de bottomStack qui contient les deux piles
//desalloue topStack
CardStack * addCardStackToCardStack(CardStack * topStack, CardStack * bottomStack){
    bottomStack->cardStack = addStackToStack(topStack->cardStack, bottomStack->cardStack);
    return bottomStack;
}

//mélange la pile de carte
void shuffleCardStack(CardStack * cardStack){
    shuffleStack(cardStack->cardStack);
}



/************************************
 * 
 * Gestion des files
 * 
 * **********************************/

//retourne un pointeur sur une file de carte vide 
CardQueue * createCardQueue(){
    CardQueue * newCardQueue = (CardQueue *)malloc(sizeof(CardQueue));
    Queue * newQueue = createQueue();

    newCardQueue->cardQueue = newQueue;

    return newCardQueue;
}

//desalloue la file et son contenu
void freeCardQueue(CardQueue * cardQueue){
    while(getCardQueueSize(cardQueue) > 0){
        freeCard((Card *)removeCardFromQueue(cardQueue));
    }

    freeQueue(cardQueue->cardQueue);
    free(cardQueue);
}

//ajoute une carte en fin de file
//retourne true si la carte a bien été ajouté
bool addCardToQueue(CardQueue * cardQueue, Card * card){
    return addToQueue(cardQueue->cardQueue, card);
}

//retourne un pointeur sur la carte d'indice index
Card * getCardFromQueue(CardQueue * cardQueue, int index){
    return (Card *)getQueueData(cardQueue->cardQueue, index);
}

//supprime la premiere carte de la file
//retourne un pointeur sur la carte supprimé
Card * removeCardFromQueue(CardQueue * cardQueue){
    return (Card *)removeQueueData(cardQueue->cardQueue);
}

//retourne le nombre de cartes de la file
int getCardQueueSize(CardQueue * cardQueue){
    return getQueueSize(cardQueue->cardQueue);
}