#include "../headers/structure.h"
#include "../headers/plateau.h"
#include "../headers/interface.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


//faire dans structure.h une fonction que retire le ieme élément, ici le premier élément dans une pile
Card *draw(Player *activePlayer){
  return pullCardFromStack(activePlayer->deck);
}


CardList* initializeMain(Player *activePlayer){
  activePlayer->main=createCardList();
  for (int i=0; i<2;i++)
    //fonction qui permet d'ajouter une carte à une liste de cartes
    addCardToList(activePlayer->main,draw(activePlayer));
  return activePlayer->main;
}

CardStack *initializeDiscard(){
  CardStack *discard=createCardStack();
  return discard;
}

CardQueue *initializePersonnel(){
  CardQueue *personnel=createCardQueue();
  return personnel;
}

CardList *allCard(){
  CardList *Card=createCardList();
  for (int i=1; i<32;i++){
    if (i==21){
      addCardToList(Card,find(i));
      addCardToList(Card,find(i));
      addCardToList(Card,find(i));
    }
    
    else if (i==22) {
      addCardToList(Card,find(i));
       addCardToList(Card,find(i));
       addCardToList(Card,find(i));
    }
    else  if (i==23){
       addCardToList(Card,find(i));
       addCardToList(Card,find(i));
    }
    
    else if (i==24) {
    addCardToList(Card,find(i));
    addCardToList(Card,find(i));
  }

    else if (i== 25) {
    addCardToList(Card,find(i));
    addCardToList(Card,find(i));
  }

    else if (i==26) {
    addCardToList(Card,find(i));
    addCardToList(Card,find(i));
  }
    else if (i==27) {
       addCardToList(Card,find(i));
       addCardToList(Card,find(i));
       addCardToList(Card,find(i));
       addCardToList(Card,find(i));
    }
    else {
      addCardToList(Card,find(i));
    }
  }
  return Card;
}

CardStack *createDeck(){
  CardStack* deck=createCardStack();
  CardList *AllCard= allCard();
  while (getCardListSize(AllCard)!=0) {
    int index=rand()%getCardListSize(AllCard);
    pushCardToStack(deck,removeCardFromList(AllCard,index));
  }
  freeCardList(AllCard);
  shuffleCardStack(deck);
  return deck;
}

Player *createPlayer(){
  Player * activePlayer=(Player *)malloc(sizeof(Player));
  activePlayer->fise=0;
  activePlayer->fisa=0;
  activePlayer->DD=0;
  activePlayer->PE=0;
  activePlayer->durability=0;
  activePlayer->DDfise=1;
  activePlayer->DDfisa=2;
  activePlayer->durabilityfise=1;
  activePlayer->durabilityfisa=1;
  activePlayer->deck=createDeck();
  activePlayer->main=initializeMain(activePlayer);
  activePlayer->personnel=createCardQueue();
  activePlayer->discard=createCardStack();
 
  return activePlayer;
}

Board *newBoard(){
  Board *board=(Board *)malloc(sizeof(Board));
  board->activePlayer=createPlayer();
  board->unactivePlayer=createPlayer();
  board->lapcounter=1;
  return board;
}

void switch_player(Board *board){
    Player *tmp=board->activePlayer;
  board->activePlayer=board->unactivePlayer;
  board->unactivePlayer=tmp;
 }

Board *majBoard(Board *board){
   for (int j=0;j<getCardQueueSize(board->activePlayer->personnel);j++) {
     board= personnalCardEffect(board,getCardID(getCardFromQueue(board->activePlayer->personnel,j)));
   }
   return board;
}


int drawCard(Player *PlayeractivePlayer){
  for (int i=0; i<getCardQueueSize(PlayeractivePlayer->personnel); i++){
    if (getCardID(getCardFromQueue(PlayeractivePlayer->personnel,i))==13)
      {
	return 3;
      }
    else if (getCardID(getCardFromQueue(PlayeractivePlayer->personnel,i))==14){
      return 2;
    }
    else if (getCardID(getCardFromQueue(PlayeractivePlayer->personnel,i))==15){
      return 2;
    }
    else if (getCardID(getCardFromQueue(PlayeractivePlayer->personnel,i))==20) {
      return 2;
    }
  }
  return 1;
}



int studentCardsDrawn(Player *PlayeractivePlayer){
  for(int i=0; i<getCardQueueSize(PlayeractivePlayer->personnel); i++){
    if (getCardID(getCardFromQueue(PlayeractivePlayer->personnel,i))==14) {
      return 2;
    }
    if (getCardID(getCardFromQueue(PlayeractivePlayer->personnel,i))==15) {

	    return 2;
    }
    else if (getCardID(getCardFromQueue(PlayeractivePlayer->personnel,i))==18) {

	    return 2;}
    else if (getCardID(getCardFromQueue(PlayeractivePlayer->personnel,i))==19){

	    return 2;}
    else if (getCardID(getCardFromQueue(PlayeractivePlayer->personnel,i))==20){
	    return 3;
    }
  }
  return 1;
}


Player addFISE(Player *player){
  player->fise+=1;
  return *player;
}

Player addFISA(Player *player){
  player->fisa+=1;
  return *player;
}

int availablePE(Player player){
  return player.PE;
}


Board *playCard(Board* board, Card *card){
  int i=getCardListSize(board->activePlayer->main);
  for(int j=0;j<i;j++){
    if (areSameCard(card,getCardFromList(board->activePlayer->main,j))){
      if ( getCardCost(card) <= (board->activePlayer->PE)){
	    if (getCardID(card)< 21){
	      if (getCardQueueSize(board->activePlayer->personnel)>=1 && board->lapcounter <6){
                
		Card *cardperso=removeCardFromQueue(board->activePlayer->personnel);
		pushCardToStack(board->activePlayer->discard,cardperso);
	        addCardToQueue(board->activePlayer->personnel,card);
	      }
	      else if (getCardQueueSize(board->activePlayer->personnel)>=2 && board->lapcounter <11 && board->lapcounter>5){
              ;
		Card *cardperso=removeCardFromQueue(board->activePlayer->personnel);
		pushCardToStack(board->activePlayer->discard,cardperso);
	        addCardToQueue(board->activePlayer->personnel,card);
	      }
	      else if (getCardQueueSize(board->activePlayer->personnel)>=3 && board->lapcounter >10){ 
		Card *cardperso=removeCardFromQueue(board->activePlayer->personnel);
		pushCardToStack(board->activePlayer->discard,cardperso);
	        addCardToQueue(board->activePlayer->personnel,card);
	       }
	       else addCardToQueue(board->activePlayer->personnel,card);
	      
	    }
	    if (getCardID(card)==28) {
	      actionCardEffect(board,28);
	      pushCardToStack(board->activePlayer->deck,card);
	      shuffle(board);
	    }
	    else {
	      actionCardEffect(board,getCardID(card));
	      pushCardToStack(board->activePlayer->discard,card);
	    }
	    removeCardFromList(board->activePlayer->main,j);
	    board->activePlayer->PE -= getCardCost(card);
            infoPE(board->activePlayer);
	    return board;
	 }
	 else {printCout();
      freeCard(card);

	   return board;}
    }
  }
  freeCard(card);
  printNoCard();
  return board;
}

Board *endTurn(Board *board){
    int i;
    for(i=0; i<getCardQueueSize(board->activePlayer->personnel);i++){
      Card *card = getCardFromQueue(board->activePlayer->personnel,i);
      board = personnalCardEffect(board, getCardID(card));
    }
    printEndTurn(board);
    return board;
}


int endGame(Board *board){
  if (board->activePlayer->DD>20 && board->activePlayer->DD>board->unactivePlayer->DD) {
    return 1;
  }
  else if (board->unactivePlayer->DD>20 && board->unactivePlayer->DD>board->activePlayer->DD)
    return 2;
  else if (board->lapcounter==30 || (board->activePlayer->DD>20 && board->unactivePlayer->DD>20 && board->activePlayer->DD==board->unactivePlayer->DD))
    return 3;
  return 0;      
}

int getLap(Board *board){
  return board->lapcounter;
}


void freePlayer (Player *player){
  freeCardStack(player->deck);
	freeCardList(player->main);
	freeCardQueue(player->personnel);
	freeCardStack(player->discard);
  free(player);
}

void freeBoard(Board *board){
	freePlayer(board->activePlayer);
	freePlayer(board->unactivePlayer);
  free(board);
}

void calculPE(Board *board){
  if (board->lapcounter %2 ==0){
    board->activePlayer->PE=board->activePlayer->fise + 2*board->activePlayer->fisa;
    board->unactivePlayer->PE=board->unactivePlayer->fise + 2*board->unactivePlayer->fisa;
  }
  else {
    board->activePlayer->PE=board->activePlayer->fise;
    board->unactivePlayer->PE=board->unactivePlayer->fise;
  }
}

void calculDD(Board * board) {
  if (board->lapcounter %2  ==0 ){
    int developpementA= board->activePlayer->fise*board->activePlayer->DDfise+board->activePlayer->fisa*board->activePlayer->DDfisa;
    int developpementU= board->unactivePlayer->fise*board->unactivePlayer->DDfise+board->unactivePlayer->fisa*board->unactivePlayer->DDfisa;
    board->activePlayer->durability=board->activePlayer->durabilityfise*board->activePlayer->fise+board->activePlayer->durabilityfisa*board->activePlayer->fisa;
    board->unactivePlayer->durability=board->unactivePlayer->durabilityfise*board->unactivePlayer->fise+board->unactivePlayer->durabilityfisa*board->unactivePlayer->fisa;
    if (developpementA-board->unactivePlayer->durability>0) {
    board->activePlayer->DD+=developpementA-board->unactivePlayer->durability;
    }
    else board->activePlayer->DD+=0;
    if (developpementU-board->activePlayer->durability>0) {
    board->unactivePlayer->DD+=developpementU-board->activePlayer->durability;
    }
    else board->unactivePlayer->DD+=0;
  }
  else {
    int developpementA= board->activePlayer->fise*board->activePlayer->DDfise;
    int developpementU= board->unactivePlayer->fise*board->unactivePlayer->DDfise;
    board->activePlayer->durability=board->activePlayer->durabilityfise*board->activePlayer->fise;
    board->unactivePlayer->durability=board->unactivePlayer->durabilityfise*board->unactivePlayer->fise;
    if (developpementA-board->unactivePlayer->durability>0) {
    board->activePlayer->DD+=developpementA-board->unactivePlayer->durability;
    }
    else board->activePlayer->DD+=0;
    if (developpementU-board->activePlayer->durability>0) {
    board->unactivePlayer->DD+=developpementU-board->activePlayer->durability;
    }
    else board->unactivePlayer->DD+=0;
  }
}
    

  
  
