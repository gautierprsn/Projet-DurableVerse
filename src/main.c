#include "../headers/interface.h"
#include <stdio.h>
#include <stdlib.h>



int main() {

  Board *boardGame=newBoard();
  int index;
  if (rand()%2==0){ 
    index=0;
    printPlayer(index);
  }
  else {
    index=1;
    printPlayer(index);
  }
  while(endGame(boardGame) == 0 && getLap(boardGame)!=30){
    printNewTurn(boardGame);
    boardGame->activePlayer->PE=0;
    boardGame->unactivePlayer->PE=0;
    //permet de jouer 2 phases pour 1 tour
    int j;

    for (j=0; j<2;j++){
      Player * playerWhoPlays=boardGame->activePlayer;
      int studentsDrawn=studentCardsDrawn(playerWhoPlays);
      infoStudentCardsDrawn(playerWhoPlays);
      for (int i=0 ; i<studentsDrawn; i++){    
        if (chooseStudentCard(playerWhoPlays)==1) {
          addFISA(playerWhoPlays);
          }
        else {
          addFISE(playerWhoPlays);
        }
      }
      calculPE(boardGame);
      printPE(boardGame);
      int cartesapiocher=drawCard(boardGame->activePlayer);
      infoDrawCard(playerWhoPlays);
      for (int i=0; i<cartesapiocher; i++ ){
          addCardToList(boardGame->activePlayer->main,draw(playerWhoPlays));
      }

      playerWhoPlays=boardGame->activePlayer;
      printMain(playerWhoPlays);
      printPersonnel(playerWhoPlays);
      int k=actionTurn();

      while (k!= 0 ){
        playerWhoPlays=boardGame->activePlayer;
        boardGame=playCard(boardGame,find(k));
        playerWhoPlays=boardGame->activePlayer;
        printMain(playerWhoPlays);
        printPersonnel(playerWhoPlays);
        k=actionTurn();
      }

      boardGame=majBoard(boardGame);
      printBoard(boardGame);

      if (j==0) {
        switch_player(boardGame);
        changementdephase(boardGame);
      }
    }

    fintour();

    calculDD(boardGame);
    printDD(boardGame);
    endTurn(boardGame);
    boardGame->lapcounter+=1;
    debuttour();

  }

  printWinner(boardGame);
  freeBoard(boardGame);
}
