#include <stdio.h>
#include <stdlib.h>
#include "../headers/carte.h"

struct Card {
  char speciality;
  int cost;
  int id; //permet de donner un identifiant à la carte, chaque carte à un identifiant unique
};



Board *AE1(Board *board, int n){
    board->activePlayer->DDfise += n;
    return board;
};

Board *AE2(Board *board, int n){
    board->activePlayer->durabilityfise += n;
    return board;
};

Board *AA1(Board *board,int n){
    board->activePlayer->DDfisa += n;
    return board;
};

Board *AA2(Board *board, int n){
board->activePlayer->durabilityfisa += n;
    return board;
};


Board *RE1(Board *board, int n){
    
    board->unactivePlayer->DDfise -= n;
    if (board->unactivePlayer->DDfise<0){board->unactivePlayer->DDfise=0;};
    return board;
};

Board *RE2(Board *board, int n){

    board->unactivePlayer->durabilityfise -= n;
    if (board->unactivePlayer->durabilityfise<0){board->unactivePlayer->durabilityfise=0;};
    return board;
};

Board *RA1(Board *board, int n){

    board->unactivePlayer->DDfisa -= n;
    if (board->unactivePlayer->DDfisa<0){board->unactivePlayer->DDfisa=0;};
    return board;
};

Board *RA2(Board *board, int n){
    
    board->unactivePlayer->durabilityfisa -= n;
    if (board->unactivePlayer->durabilityfisa<0){board->unactivePlayer->durabilityfisa=0;};
    return board;
};

Board *ADD(Board *board, int n){
    board->activePlayer->DD +=n;
    return board;
};

Board *RDD(Board *board, int n){
    
    board->unactivePlayer->DD -=n;
    if (board->unactivePlayer->DD<0){board->unactivePlayer->DD=0;};
    return board;
};



Board *personnalCardEffect(Board *board,  int id){
    

    switch(id){
case 0: 
break;
        case 1:
            board = AE1(board,1);
            break;
        
        case 2:
            board = AE2(board,1);
            break;
        
        case 3:
            board = AA1(board,1);
            break;
        
        case 4:
            board = AA2(board,1);
            break;
        
        case 5:
            board = RE1(board,1);
            break;
        
        case 6:
            board = RE2(board,1);
            break;
        
        case 7:
            board = RA1(board,1);
            break;
        
        case 8:
            board = RA2(board,1);
            break;
        
        case 9:
            board = AE1(board,1);
            board = AA1(board,1);
            break;

        case 10: 
            board = AE2(board,1);
            board = AA2(board,1);
            break;

        case 11:
            board = RE1(board,1);
            board = RA1(board,1);
            break;

        case 12:
            board = RE2(board,1);
            board = RA2(board,1);
            break;

        case 14:
            board = ADD(board,2);
            break;

        case 15:
            board = RDD(board,2);
            break;

        case 16:
            board = AE1(board,1);
            board = AE2(board,1);
            board = RE2(board,1);
            board = RDD(board,1);
            break;

        case 17:
            board = AA1(board,1);
            board = AA2(board,1);
            board = RA2(board,1);
            board = RDD(board,1);
            break;

        case 18:
            board = AE1(board,2);
            board = AE2(board,2);            
            break;

        case 19:
            board = AA1(board,2);
            board = AA2(board,2);
            break;

        case 20:
            board = AA1(board,1);
            board = AA2(board,1);
            board = AA1(board,2);
            board = AA2(board,2);
            board = ADD(board,1);
            board = RDD(board,1);
            break;


    };
    return board;
};

void shuffle(Board *board){
for (int i=0; i<getCardStackSize(board->activePlayer->discard); i++) {
pushCardToStack(board->activePlayer->deck, pullCardFromStack(board->activePlayer->discard));
}
   shuffleCardStack(board->activePlayer->deck);

}

void sendToDiscard(Player *player){
  pushCardToStack(player->discard, removeCardFromQueue(player->personnel));
}
    

Board *actionCardEffect(Board *board, int id){
   
    
    
    switch(id){
        case 21:
            board->activePlayer->DD +=1;
            break;
        
        case 22:
            addCardToList(board->activePlayer->main,draw(board->activePlayer));
            break;
        
        case 23:
            addFISE(board->activePlayer);
            break;
        
        case 24:
            addFISA(board->activePlayer);
            break;
        
        case 25:
            board->activePlayer->PE +=6;
            break;
        
        case 26:
            if(board->unactivePlayer->fise > 0)
            {board->unactivePlayer->fise -= 1;};
            if(board->unactivePlayer->fisa > 0)
            {board->unactivePlayer->fisa -= 1;};
            break;
        
        case 27:
            sendToDiscard(board->unactivePlayer);
            break;
        
        // Il faut faire une fonction qui mélange directement de la manière qui est donnée ici
        case 28:
            shuffle(board);
            break;
        
        case 29:
            board->activePlayer->DDfise +=1;
            board->activePlayer->DDfisa +=1;
            break;

        case 30:
            board->activePlayer->durabilityfise +=1;
            board->activePlayer->durabilityfisa +=1;
            break;

        case 31:
            board->unactivePlayer->fise = 0;
            board->activePlayer->fise = 0;
            board->unactivePlayer->fisa = 0;
            board->activePlayer->fisa = 0;
            break;
    };
    return board;
}

bool areSameCard(void *card3, void *card4){
  Card *card1=(Card *)card3;
  Card *card2=(Card *)card4;
    return (card1->id==card2->id);
}


Card *createCard(char speciality, int id, int cost){
    Card * card = (Card*)malloc(sizeof(Card));
    card->speciality = speciality;
    card->id = id;
    card->cost = cost;
    return card;
}

void freeCard(Card *card){
free(card); 
}


int getCardCost(Card *card){
    return card->cost;
}



int getCardID(Card *card){
    return card->id;
}


Card *find(int i){
Card *card;
  switch(i){
  case 1:
    card=createCard('p',1,3);
    break;
 case 2:
card=createCard('p',2,3);
    break;
  case 3:
card=createCard('p',3,3);
    break;
  case 4:
card=createCard('p',4,3);
    break;
  case 5:
card=createCard('p',5,3);
    break;
  case 6:
card=createCard('p',6,3);
    break;
  case 7:
card=createCard('p',7,3);
    break;
  case 8:
card=createCard('p',8,3);
    break;
  case 9:
card=createCard('p',9,5);
    break;
  case 10:
card=createCard('p',10,5);
    break;
  case 11:
card=createCard('p',11,5);
    break;
  case 12:
card=createCard('p',12,5);
    break;
  case 13:
card=createCard('p',13,7);
    break;
  case 14:
card=createCard('p',14,8);
    break;
  case 15:
card=createCard('p',15,8);
    break;
  case 16:
card=createCard('p',16,10);
    break;
  case 17:
card=createCard('p',17,10);
    break;
  case 18:
card=createCard('p',18,15);    
    break;
  case 19:
card=createCard('p',19,15);
    break;
  case 20:
card=createCard('p',20,20);
    break;
  case 21:
card=createCard('a',21,2);
    break;
  case 22:
card=createCard('a',22,2);
    break;
  case 23:
card=createCard('a',23,3);
    break;
  case 24:
card=createCard('a',24,3);
    break;
  case 25:
card=createCard('a',25,4);
    break;
  case 26:
card=createCard('a',26,5);
    break;
  case 27:
card=createCard('a',27,5);
    break;
  case 28:
card=createCard('a',28,10);
    break;
  case 29:
card=createCard('a',29,10);
    break;
  case 30:
card=createCard('a',30,10);
    break;
  case 31:
card=createCard('a',31,10);
    break;
};
  return card;
}

void printCard (Card *card){
  printf("type=%c,",card->speciality);
  printf("cout=%i,", card->cost);
  printf("id=%i",card->id);
}
