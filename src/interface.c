#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/interface.h"

/*
  Retourne un nouveau pointeur sur l'entrée utilisateur
  L'entrée est considéré terminé au premier \n rencontré
*/
char * getUserEntry(){
  char * userEntry = (char*)malloc(sizeof(char)*16);
  int userEntryMaxSize = 16;
  int userEntrySize = 0;
  userEntry[userEntrySize] = '\0';

  char c;
  while((c = getc(stdin)) != '\n'){

    if(userEntryMaxSize <= userEntrySize + 1 ){
      userEntryMaxSize *= 2;
      userEntry = realloc(userEntry, sizeof(char) * userEntryMaxSize);
    }
    userEntry[userEntrySize] = c;
    userEntrySize++;
    userEntry[userEntrySize] = '\0';
  }
  return userEntry;
}

void printNewTurn(Board *board){
  printf("Le tour %i commence \n", board->lapcounter);
  printf("Le joueur actif %i points de DD, %i fisa et %i fise \n", board->activePlayer->DD,board->activePlayer->fisa,board->activePlayer->fise);
  printf("Le joueur inactif a %i points de DD , %i fisa et %i fise \n", board->unactivePlayer->DD,board->unactivePlayer->fisa,board->unactivePlayer->fise);
  printMain(board->activePlayer);
  printf("\n");
  printPersonnel(board->activePlayer);
  printf("\n");
  if (board->lapcounter%2==0){
    printf("Le tour est pair donc les FISA compte \n");
  }
  else{
    printf("Le tour est impair donc les FISA ne sont pas pris en compte \n");
  }
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
}

void printMain(Player *player)
{
  printf("Sa main est : ");
    if (player->main == NULL)
    {
        exit(EXIT_FAILURE);
    }
    int i=getCardListSize(player->main);
      printf("[");
    for (int j=0;j<i;j++){
      printf("(");
          printCard(getCardFromList(player->main,j));
	  printf(")");
	}
    printf("]\n");
    }

void printPersonnel(Player *player)
{
  printf("Ses personnels sont : ");
if (player->personnel == NULL)
    {
        exit(EXIT_FAILURE);
    }
    
    int i=getCardQueueSize(player->personnel);
      printf("[");
    for (int j=0;j<i;j++){
      printf("(");
          printCard(getCardFromQueue(player->personnel,j));
	  printf(");");
	}
    printf("]\n");
    }


void changementdephase(Board *board){
  printf("\n");
        printf("\n");
        printf("\n");
        printf("************* Changement de Phase ********************** \n");
        printf("\n");
        printf("\n");
        printf("\n");
printf("Voici l'état du joueur actif.");
  printMain(board->activePlayer);
printf("\n");
  printPersonnel(board->activePlayer);
printf("\n");
  printf(" Il possède %i points de DD et %i d'énergie, %i fisa et %i fise \n", board->activePlayer->DD, board->activePlayer->PE ,board->activePlayer->fisa,board->activePlayer->fise);
}

void fintour(){
  printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("************ fin du tour ************** \n");
    printf("\n");
    printf("\n");
    printf("\n");
}

void debuttour() {
  printf("\n");
    printf("\n");
    printf("--------------Nouveau tour-------------- \n");
    printf("\n");
    printf("\n");
    printf("\n");
}

void printDiscard(Player *player)
{
printf ("Voici la defausse du joueur actif : \n");
if (player->discard == NULL)
    {
        exit(EXIT_FAILURE);
    }
    
    int i=getCardStackSize(player->discard);
      printf("[");
    for (int j=0;j<i;j++){
      printf("(");
          printCard(getCardFromStack(player->discard,j));
	  printf(");");
	}
    printf("]\n");
    }

void printDeck(Player *player)
{
printf ("Voici le deck du joueur actif : \n");
if (player->deck == NULL)
    {
        exit(EXIT_FAILURE);
    }
    
    int i=getCardStackSize(player->deck);
      printf("[");
    for (int j=0;j<i;j++){
      printf("(");
          printCard(getCardFromStack(player->deck,j));
	  printf(");");
	}
    printf("]\n");
    }


void printBoard(Board *board){
  printf("\n");
  printf("\n");
  printf("Voici l'état du joueur qui a fini son tour.");
  printMain(board->activePlayer);
printf("\n");
  printPersonnel(board->activePlayer);
printf("\n");
  printf(" Il possède %i points de DD et %i d'énergie, %i fisa et %i fise \n", board->activePlayer->DD, board->activePlayer->PE ,board->activePlayer->fisa,board->activePlayer->fise);
  }

void printEndTurn(Board *board){
printf ("Le tour %i est terminé\n. Voici l'état dans lequel nous sommes au moment du combat : \n", getLap(board));
if (getLap(board) %2==0) {
    int developpementA= board->activePlayer->fise*board->activePlayer->DDfise+board->activePlayer->fisa*board->activePlayer->DDfisa;
    int developpementU= board->unactivePlayer->fise*board->unactivePlayer->DDfise+board->unactivePlayer->fisa*board->unactivePlayer->DDfisa;
     board->activePlayer->durability=board->activePlayer->durabilityfise*board->activePlayer->fise+board->activePlayer->durabilityfisa*board->activePlayer->fisa;
    board->unactivePlayer->durability=board->unactivePlayer->durabilityfise*board->unactivePlayer->fise+board->unactivePlayer->durabilityfisa*board->unactivePlayer->fisa;
printf("Le joueur actif à %i points de dévelopement et %i points de durabilité \n", developpementA, board->activePlayer->durabilityfise*board->activePlayer->fise+board->activePlayer->durabilityfisa*board->activePlayer->fisa);
printf("Le joueur inactif à %i points de développement et %i points de durabilité \n",developpementU, board->unactivePlayer->durabilityfise*board->unactivePlayer->fise+board->unactivePlayer->durabilityfisa*board->unactivePlayer->fisa);
if (developpementA-board->unactivePlayer->durability >0 )
printf("Le joueur actif gagne %i points de DD \n", developpementA-board->unactivePlayer->durability);
if (developpementU-board->activePlayer->durability >0) 
printf("Le joueur inactif gagne %i points de DD \n", developpementU-board->activePlayer->durability);
}
else {
     int developpementA= board->activePlayer->fise*board->activePlayer->DDfise;
    int developpementU= board->unactivePlayer->fise*board->unactivePlayer->DDfise;
     board->activePlayer->durability=board->activePlayer->durabilityfise*board->activePlayer->fise;
    board->unactivePlayer->durability=board->unactivePlayer->durabilityfise*board->unactivePlayer->fise;
printf("Le joueur actif à %i points de dévelopement et %i points de durabilité \n", developpementA, board->activePlayer->durabilityfise*board->activePlayer->fise);
printf("Le joueur inactif à %i points de développement et %i points de durabilité \n",developpementU, board->unactivePlayer->durabilityfise*board->unactivePlayer->fise);
if (developpementA-board->unactivePlayer->durability >0 )
printf("Le joueur actif gagne %i points de DD \n", developpementA-board->unactivePlayer->durability);
if (developpementU-board->activePlayer->durability >0) 
printf("Le joueur inactif gagne %i points de DD \n", developpementU-board->activePlayer->durability);
}
printf("Voici le nombre de DD après ce tour: \n");
printf("Le joueur actif à %i points de DD \n", board->activePlayer->DD);
printf("Le joueur inactif à %i points de DD \n", board->unactivePlayer->DD);
}


int chooseStudentCard(){
  printf("Veuillez entrer 1 si vous souhaitez jouer un FISA, 0 sinon \n");
  
  char * c = getUserEntry();

  if (strcmp(c, "0") != 0 && strcmp(c, "1") != 0) {
    printf("Veuillez rentrer 0 ou 1! \n");
    free(c);
    return chooseStudentCard();
  }

  int userChoise = atoi(c);
  free(c);
  return userChoise;
}

int actionTurn() {
  
 printf("Rentrez 0 si vous voulez finir votre tour ou le numero de la carte à jouer \n");
 char * c = getUserEntry();
 if (strcmp(c,"0")!=0 && strcmp(c,"1")!=0 &&strcmp(c,"2")!=0 && strcmp(c,"3")!=0 && strcmp(c,"4")!=0 && strcmp(c,"5")!=0 && strcmp(c,"6")!=0 && strcmp(c,"7")!=0 && strcmp(c,"8")!=0 && strcmp(c,"9")!=0 && strcmp(c,"10")!=0 && strcmp(c,"11")!=0 && strcmp(c,"12")!=0 && strcmp(c,"13")!=0 &&strcmp(c,"14")!=0 && strcmp(c,"15")!=0 && strcmp(c,"16")!=0 && strcmp(c,"17")!=0 && strcmp(c,"18")!=0 && strcmp(c,"19")!=0 && strcmp(c,"20")!=0 && strcmp(c,"21")!=0 && strcmp(c,"22")!=0 && strcmp(c,"23")!=0 && strcmp(c,"24")!=0 && strcmp(c,"25")!=0 && strcmp(c,"26")!=0 && strcmp(c,"27")!=0 && strcmp(c,"28")!=0 && strcmp(c,"29")!=0 && strcmp(c,"30")!=0 && strcmp(c,"31")!=0) {
   printf("Veuillez rentrer un entier entre 0 et 31 \n");
   free(c);
   return actionTurn();
 }
 int userChoice=atoi(c);
 free(c);
 return userChoice;
}


void printWinner(Board *board){
  if (endGame(board)==1) printf("Le joueur qui était actif en dernier a gagné!");
  if (endGame(board)==2) printf("Le joueur qui était inactif en dernier a gagné!");
  if (endGame(board)==3) printf("Match nul!");
}

void printPE(Board *board) {
printf("Vous avez %i point d'énergie disponibles \n", board->activePlayer->PE);
}

int printPlayer(int i){
if (i==1) 
i=i-1;
if (i==0) i=i+1;
if (i==0) {
printf ("Le joueur actif  est l'ENSIIE A \n");
}
else {
printf("Le joueur actif  est l'ENSIIE B \n");
i=i-1;
}
return i;
}

void infoDrawCard(Player *PlayeractivePlayer){
for (int i=0; i<getCardQueueSize(PlayeractivePlayer->personnel); i++){
    if (getCardID(getCardFromQueue(PlayeractivePlayer->personnel,i))==13)
      {
	printf("Grace à vos cartes personnels, vous pouvez piocher 2 cartes en plus! \n");
      }
    if (getCardID(getCardFromQueue(PlayeractivePlayer->personnel,i))==14){
      printf("Grace à vos cartes personnels, vous pouvez piocher 1 carte en plus! \n");
 
    }
    if (getCardID(getCardFromQueue(PlayeractivePlayer->personnel,i))==15){
      printf("Grace à vos cartes personnels, vous pouvez piocher 1 carte en plus! \n");
    }
    if (getCardID(getCardFromQueue(PlayeractivePlayer->personnel,i))==20) {
      printf("Grace à vos cartes personnels, vous pouvez piocher 1 carte en plus! \n");

    }
}
}

void infoStudentCardsDrawn(Player *PlayeractivePlayer){
   for(int i=0; i<getCardQueueSize(PlayeractivePlayer->personnel); i++){
    if (getCardID(getCardFromQueue(PlayeractivePlayer->personnel,i))==14) {
      printf("Grace à vos cartes personnels, vous pouvez ajouter 1 carte élève en plus! \n");
    }
    if (getCardID(getCardFromQueue(PlayeractivePlayer->personnel,i))==15) {
            printf("Grace à vos cartes personnels, vous pouvez ajouter 1 carte élève en plus! \n");
    }
    if (getCardID(getCardFromQueue(PlayeractivePlayer->personnel,i))==18) {
            printf("Grace à vos cartes personnels, vous pouvez ajouter 1 carte élève en plus! \n");
}
    if (getCardID(getCardFromQueue(PlayeractivePlayer->personnel,i))==19){
            printf("Grace à vos cartes personnels, vous pouvez ajouter 1 carte élève en plus! \n");}
    if (getCardID(getCardFromQueue(PlayeractivePlayer->personnel,i))==20){
            printf("Grace à vos cartes personnels, vous pouvez ajouter 2 carte élève en plus! \n");
    }
  }
}

void infoPE(Player *player){
   printf("Il vous reste %i points d'énergie \n",player->PE);
}

void printDD(Board *board){
  printf("Le nombre de DD du joueur actif est %i \n", board->activePlayer->DD);
  printf("Le nombre de DD du joueur inactif est %i \n", board->unactivePlayer->DD);
}

void printCout(){
    printf("le cout est trop élevé!\n");
}

void printNoCard(){
   printf("Vous n'avez pas la carte en main \n");
}



