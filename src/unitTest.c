#include "CUnit/Basic.h"
#include "CUnit/CUnit.h"
#include "../headers/structureEngine.h"
#include "../headers/plateau.h"
#include "../headers/carte.h"
#include "../headers/interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct testStruct{
    int val;
}TestStruct;

bool areEquals(void * a, void * b){
    return ((TestStruct*)a)->val == ((TestStruct*)b)->val;
}

/************************************
 * 
 * Tests des listes
 * 
 * **********************************/

void testCreateList(){
    List * listTest = createList();
    CU_ASSERT(getListSize(listTest) == 0);
    freeList(listTest);
}

void testInsertDataInList(){
    List * listTest = createList();
    TestStruct * x = (TestStruct *)malloc(sizeof(TestStruct));
    x->val = 1;
    TestStruct * y = (TestStruct *)malloc(sizeof(TestStruct));
    y->val = 2;
    TestStruct * z = (TestStruct *)malloc(sizeof(TestStruct));
    z->val = 3;
    addToList(listTest, x);
    addToList(listTest, y);
    addToList(listTest, z);

    CU_ASSERT(getListSize(listTest) == 3);
    CU_ASSERT(((TestStruct*)get(listTest, 3)) == NULL);//cas out of bound
    CU_ASSERT(((TestStruct*)get(listTest, 2))->val == 1);//cas fin
    CU_ASSERT(((TestStruct*)get(listTest, 1))->val == 2);//cas milieu
    CU_ASSERT(((TestStruct*)get(listTest, 0))->val == 3);//cas fin

    removeListData(listTest, 0);
    removeListData(listTest, 0);
    removeListData(listTest, 0);

    free(x);
    free(y);
    free(z);
    freeList(listTest);
}

void testRemoveDataInList(){
    List * listTest = createList();
    TestStruct * w = (TestStruct *)malloc(sizeof(TestStruct));
    w->val = 0;
    TestStruct * x = (TestStruct *)malloc(sizeof(TestStruct));
    x->val = 1;
    TestStruct * y = (TestStruct *)malloc(sizeof(TestStruct));
    y->val = 2;
    TestStruct * z = (TestStruct *)malloc(sizeof(TestStruct));
    z->val = 3;
    addToList(listTest, w);
    addToList(listTest, x);
    addToList(listTest, y);
    addToList(listTest, z);

    CU_ASSERT(getListSize(listTest) == 4);
    CU_ASSERT(removeListData(listTest,4) == NULL); //cas indice trop grand 
    CU_ASSERT(((TestStruct*)removeListData(listTest, 1))->val == 2);//cas au milieu de la liste
    CU_ASSERT(((TestStruct*)removeListData(listTest, 0))->val == 3);//cas premier de la liste
    CU_ASSERT(((TestStruct*)removeListData(listTest, 1))->val == 0);//cas dernier de la liste
    CU_ASSERT(((TestStruct*)removeListData(listTest, 0))->val == 1);//cas seul élément de la liste (premier et dernier)
    CU_ASSERT(removeListData(listTest,0) == NULL);//cas liste vide
    CU_ASSERT(getListSize(listTest) == 0);
    
    free(w);
    free(x);
    free(y);
    free(z);
    freeList(listTest);
}

void testListContains(){
    List * listTest = createList();
    TestStruct * w = (TestStruct *)malloc(sizeof(TestStruct));
    w->val = 0;
    TestStruct * x = (TestStruct *)malloc(sizeof(TestStruct));
    x->val = 1;
    TestStruct * y = (TestStruct *)malloc(sizeof(TestStruct));
    y->val = 2;
    TestStruct * z = (TestStruct *)malloc(sizeof(TestStruct));
    z->val = 0;
    addToList(listTest, w);
    addToList(listTest, y);
    printf("%d",listContains(listTest, x, areEquals));
    CU_ASSERT(listContains(listTest, x, areEquals) == false);
    
    CU_ASSERT(listContains(listTest, z, areEquals) == true);
printf("%d",listContains(listTest, z, areEquals));
    free(w);
    free(x);
    free(y);
    free(z);
    freeList(listTest);

}

/************************************
 * 
 * Tests des piles
 * 
 * **********************************/

void testCreateStack(){
    Stack * stackTest = createStack();
    CU_ASSERT(getStackSize(stackTest) == 0);
    freeStack(stackTest);
}


void testInsertDataInStack(){
    Stack * stackTest = createStack();
    TestStruct * x = (TestStruct *)malloc(sizeof(TestStruct));
    x->val = 1;
    TestStruct * y = (TestStruct *)malloc(sizeof(TestStruct));
    y->val = 2;
    TestStruct * z = (TestStruct *)malloc(sizeof(TestStruct));
    z->val = 3;
    stackPush(stackTest, x);
    stackPush(stackTest, y);
    stackPush(stackTest, z);

    CU_ASSERT(getStackSize(stackTest) == 3);
    CU_ASSERT(((TestStruct*)getStackData(stackTest, 3)) == NULL);//cas out of bound
    CU_ASSERT(((TestStruct*)getStackData(stackTest, 2))->val == 1);//cas fin
    CU_ASSERT(((TestStruct*)getStackData(stackTest, 1))->val == 2);//cas milieu
    CU_ASSERT(((TestStruct*)getStackData(stackTest, 0))->val == 3);//cas debut

    stackPull(stackTest);
    stackPull(stackTest);
    stackPull(stackTest);

    free(x);
    free(y);
    free(z);
    freeStack(stackTest);
}

void testRemoveDataInStack(){
    Stack * stackTest = createStack();
    
    TestStruct * x = (TestStruct *)malloc(sizeof(TestStruct));
    x->val = 1;
    TestStruct * y = (TestStruct *)malloc(sizeof(TestStruct));
    y->val = 2;
    
    stackPush(stackTest, x);
    stackPush(stackTest, y);

    CU_ASSERT(getStackSize(stackTest) == 2);
    CU_ASSERT(((TestStruct*)stackPull(stackTest))->val == 2);//cas multiples éléments
    CU_ASSERT(((TestStruct*)stackPull(stackTest))->val == 1);//cas un seul élément
    CU_ASSERT(stackPull(stackTest) == NULL);//cas pile vide
    CU_ASSERT(getStackSize(stackTest) == 0);

    free(x);
    free(y);
    freeStack(stackTest);
}

void testMergeStacks(){
    Stack * topStack = createStack();
    Stack * bottomStack = createStack();

    TestStruct * w = (TestStruct *)malloc(sizeof(TestStruct));
    w->val = 1;
    TestStruct * x = (TestStruct *)malloc(sizeof(TestStruct));
    x->val = 2;
    TestStruct * y = (TestStruct *)malloc(sizeof(TestStruct));
    y->val = 3;
    TestStruct * z = (TestStruct *)malloc(sizeof(TestStruct));
    z->val = 4;

    stackPush(topStack, x);
    stackPush(topStack, w);
    stackPush(bottomStack, z);
    stackPush(bottomStack, y);

    addStackToStack(topStack, bottomStack);

    CU_ASSERT(getStackSize(bottomStack) == 4);//taille correcte
    CU_ASSERT(((TestStruct*)stackPull(bottomStack))->val == 1
        && ((TestStruct*)stackPull(bottomStack))->val == 2
        && ((TestStruct*)stackPull(bottomStack))->val == 3
        && ((TestStruct*)stackPull(bottomStack))->val == 4
    );//données cohérentes

    free(w);
    free(x);
    free(y);
    free(z);
    freeStack(bottomStack);
}

void testPullCardFromStack(){
    Stack * stackTest = createStack();
    
    TestStruct * x = (TestStruct *)malloc(sizeof(TestStruct));
    x->val = 1;
    TestStruct * y = (TestStruct *)malloc(sizeof(TestStruct));
    y->val = 2;

    stackPush(stackTest, x);
    stackPush(stackTest, y);
    CU_ASSERT(((TestStruct*)stackPull(stackTest))->val == 2
        && ((TestStruct*)stackPull(stackTest))->val == 1
	      );

    free(x);
    free(y);
    freeStack(stackTest);
}





  
void testShuffleStack(){
    Stack * stackTest = createStack();
    
    TestStruct * x = (TestStruct *)malloc(sizeof(TestStruct));
    x->val = 1;
    TestStruct * y = (TestStruct *)malloc(sizeof(TestStruct));
    y->val = 2;
    TestStruct * z = (TestStruct *)malloc(sizeof(TestStruct));
    z->val = 3;


    stackPush(stackTest, x);
    stackPush(stackTest, y);
    stackPush(stackTest, z);    

    printf("\nPile avant mélange :\n");
    printf("%d, %d, %d\n", ((TestStruct *)getStackData(stackTest, 0))->val, ((TestStruct *)getStackData(stackTest, 1))->val, ((TestStruct *)getStackData(stackTest, 2))->val);

    shuffleStack(stackTest);
    

    CU_ASSERT(getStackSize(stackTest) == 3);//taille correcte


    printf("Pile après mélange :\n");
    printf("%d, %d, %d\n", ((TestStruct *)getStackData(stackTest, 0))->val, ((TestStruct *)getStackData(stackTest, 1))->val, ((TestStruct *)getStackData(stackTest, 2))->val);   
    stackPull(stackTest);
    stackPull(stackTest);
    stackPull(stackTest);

    free(x);
    free(y);
    free(z);
    freeStack(stackTest);
}


/************************************
 * 
 * Tests des piles
 * 
 * **********************************/

void testCreateQueue(){
    Queue * queueTest = createQueue();
    CU_ASSERT(getQueueSize(queueTest) == 0);
    freeQueue(queueTest);
}


void testInsertDataInQueue(){
    Queue * queueTest = createQueue();
    TestStruct * x = (TestStruct *)malloc(sizeof(TestStruct));
    x->val = 1;
    TestStruct * y = (TestStruct *)malloc(sizeof(TestStruct));
    y->val = 2;
    TestStruct * z = (TestStruct *)malloc(sizeof(TestStruct));
    z->val = 3;
    addToQueue(queueTest, x);
    addToQueue(queueTest, y);
    addToQueue(queueTest, z);

    CU_ASSERT(getQueueSize(queueTest) == 3);
    CU_ASSERT(((TestStruct*)getQueueData(queueTest, 3)) == NULL);//cas out of bound
    CU_ASSERT(((TestStruct*)getQueueData(queueTest, 2))->val == 3);//cas fin
    CU_ASSERT(((TestStruct*)getQueueData(queueTest, 1))->val == 2);//cas milieu
    CU_ASSERT(((TestStruct*)getQueueData(queueTest, 0))->val == 1);//cas debut

    removeQueueData(queueTest);
    removeQueueData(queueTest);
    removeQueueData(queueTest);

    free(x);
    free(y);
    free(z);
    freeQueue(queueTest);
}

void testRemoveDataInQueue(){
    Queue * queueTest = createQueue();
    
    TestStruct * x = (TestStruct *)malloc(sizeof(TestStruct));
    x->val = 1;
    TestStruct * y = (TestStruct *)malloc(sizeof(TestStruct));
    y->val = 2;
    
    addToQueue(queueTest, x);
    addToQueue(queueTest, y);

    CU_ASSERT(getQueueSize(queueTest) == 2);
    CU_ASSERT(((TestStruct*)removeQueueData(queueTest))->val == 1);//cas multiples éléments
    CU_ASSERT(((TestStruct*)removeQueueData(queueTest))->val == 2);//cas un seul élément
    CU_ASSERT(removeQueueData(queueTest) == NULL);//cas pile vide
    CU_ASSERT(getQueueSize(queueTest) == 0);

    free(x);
    free(y);
    freeQueue(queueTest);
}

void testAddCardToQueue(){
   CardQueue * queueTest = createCardQueue();
   char p='a';
   Card * card=createCard(p,1,1);

   addCardToQueue(queueTest,card);
   CU_ASSERT(getCardQueueSize(queueTest) == 1);
}
/********************************************************
Test du plateau 
*************************************************/

void testSwitch() {
  Board *board=newBoard();
  printf("La main du joueur actif est :\n");
  printMain(board->activePlayer);
  CardList *main1=board->activePlayer->main;
  printf("\n");
  switch_player(board);
  printf("La main du joueur actif est :\n");
  printMain(board->activePlayer);
  printf("\n");
  CardList *main2=board->activePlayer->main;
  if (main1 != main2) {
    printf("Les joueurs ont bien été changés\n");
  }
  else printf("joueur inchangés!\n");
  freeBoard(board);
}

void testAddFise() {
  Board *board=newBoard();
  int fise=board->activePlayer->fise;
  printf("Voici le nombre de fise : %i \n", board->activePlayer->fise);
  if (chooseStudentCard()==0) {
    addFISE(board->activePlayer);
    printf("on a ajouté un fise, il y en a %i \n", board->activePlayer->fise);
  }
  int fise2=board->activePlayer->fise;
  if (fise2 == fise +1)
    printf("L'ajout de fise a fonctionné \n");
  else printf("échec de l'ajout de fise \n");
  freeBoard(board);
}


void testAddFisa() {
  Board *board=newBoard();
  int fisa=board->activePlayer->fisa;
  printf("Voici le nombre de fisa : %i \n", board->activePlayer->fisa);
  if (chooseStudentCard()==1) {
    addFISA(board->activePlayer);
    printf("on a ajouter un fisa, il y en a %i \n", board->activePlayer->fisa);
  }
  int fisa2=board->activePlayer->fisa;
  if (fisa2 == fisa +1)
    printf("L'ajout de fisa a fonctionné \n");
  else printf("échec de l'ajout de fisa \n");
  freeBoard(board);
}

void testSupFisa(){
  Board *board=newBoard();
  board->activePlayer->fisa=1;
  board->activePlayer->fise=1;
  printf("Il y a %i fise et %i fisa \n", board->activePlayer->fise, board->activePlayer->fisa);
  calculPE(board);
  int PE_impair=board->activePlayer->PE;
  printf("Tour numero %i \n",board->lapcounter);
  printf("Le joueur a  %i pts d'energie, on ne prend pas en compte le fisa \n", board->activePlayer->PE);
  board->lapcounter=2;
  printf("Tour numéro %i \n", board->lapcounter);
  calculPE(board);
  int PE_pair=board->activePlayer->PE;
  printf("Le joueur a  %i pts d'energie, on prend en compte le fisa \n", board->activePlayer->PE);
  if (PE_pair !=PE_impair) printf("Le fisa a bien été enlevé \n");
  else printf("LE fisa est toujours pris en compte");
  freeBoard(board);
}


void testSizePersonnel() {
   printf("\n");
    printf("\n");
    printf("*********** test size personnel ***********");
    printf("\n");
  Board *board=newBoard();
  int size=getCardQueueSize(board->activePlayer->personnel)+1;
  printf("au tour %i, on a une queue personnel de taille %i \n", board->lapcounter, size);
  board->lapcounter=6;
  majBoard(board);
  int size2=getCardQueueSize(board->activePlayer->personnel)+1;
  printf("au tour %i, on a une queue personnel de taille %i \n", board->lapcounter, size2);
  board->lapcounter=11;
  majBoard(board);
  int size3=getCardQueueSize(board->activePlayer->personnel)+1;
  printf("au tour %i, on a une queue personnel de taille %i \n", board->lapcounter, size3);
  if (size2==size+1 && size3==size2+1)
    printf("La taille varie bien au tour 6 et 11\n");
  else printf("la taille change mal!\n");
  freeBoard(board);
}


void testCard1() {
  printf("\n");
    printf("\n");
    printf("*********** test carte 1  ***********");
    printf("\n");
  Board *board=newBoard();
  printf("Il faut avoir au moins 1 fise pour avoir l'effet esconté, sinon cela ne change rien \n");
  board->activePlayer->fise=1;
  int ddfise=board->activePlayer->DDfise;
  personnalCardEffect(board,1);
  int ddfise2=board->activePlayer->DDfise;
  if (ddfise2== ddfise+1) printf ("l'effet de la carte 1 fonctionne \n");
  else printf("L'effet de la carte 1 ne fonctionne pas \n");
  freeBoard(board);
}


void testCard2() {
  printf("\n");
    printf("\n");
    printf("*********** test carte 2  ***********");
    printf("\n");
  Board *board=newBoard();
  printf("Il faut avoir au moins 1 fisa pour avoir l'effet esconté, sinon cela ne change rien \n");
  board->activePlayer->fise=1;
  int durabilityfise=board->activePlayer->durabilityfise;
  personnalCardEffect(board,2);
  int durabilityfise2=board->activePlayer->durabilityfise;
  if (durabilityfise2== durabilityfise+1) printf ("l'effet de la carte 2 fonctionne \n");
  else printf("L'effet de la carte 1 ne fonctionne pas \n");
  freeBoard(board);
}



void testCard4() {
  printf("\n");
    printf("\n");
    printf("*********** test carte 4  ***********");
    printf("\n");
  Board *board=newBoard();
  printf("Il faut avoir au moins 1 fisa pour avoir l'effet esconté, sinon cela ne change rien \n");
  board->activePlayer->fisa=1;
  int durabilityfise=board->activePlayer->durabilityfisa;
  personnalCardEffect(board,4);
  int durabilityfise2=board->activePlayer->durabilityfisa;
  if (durabilityfise2== durabilityfise+1) printf ("l'effet de la carte 4 fonctionne \n");
  else printf("L'effet de la carte 4 ne fonctionne pas \n");
  freeBoard(board);
}

void testCard3() {
  printf("\n");
    printf("\n");
    printf("*********** test carte 3  ***********");
    printf("\n");
  Board *board=newBoard();
  printf("Il faut avoir au moins 1 fisa pour avoir l'effet esconté, sinon cela ne change rien \n");
  board->activePlayer->fisa=1;
  int durabilityfise=board->activePlayer->DDfisa;
  personnalCardEffect(board,3);
  int durabilityfise2=board->activePlayer->DDfisa;
  if (durabilityfise2== durabilityfise+1) printf ("l'effet de la carte 3 fonctionne \n");
  else printf("L'effet de la carte 3 ne fonctionne pas \n");
  freeBoard (board);
  //freeCard(card);
}

void testCard5() {
  printf("\n");
    printf("\n");
    printf("*********** test carte 5  ***********");
    printf("\n");
  Board *board=newBoard();
  printf("Il faut avoir au moins 1 fise pour avoir l'effet esconté, sinon cela ne change rien \n");
  board->unactivePlayer->fise=1;
  int ddfise=board->unactivePlayer->DDfise;
  personnalCardEffect(board,5);
  int ddfise2=board->unactivePlayer->DDfise;
  if (ddfise2== ddfise-1) printf ("l'effet de la carte 5 fonctionne \n");
  else printf("L'effet de la carte 5 ne fonctionne pas \n");
  freeBoard (board);
}



void testCard6() {
  printf("\n");
    printf("\n");
    printf("*********** test carte 6  ***********");
    printf("\n");
  Board *board=newBoard();
  printf("Il faut avoir au moins 1 fise pour avoir l'effet esconté, sinon cela ne change rien \n");
  board->unactivePlayer->fise=1;
  int durabilityfise=board->unactivePlayer->durabilityfise;
  personnalCardEffect(board,6);
  int durabilityfise2=board->unactivePlayer->durabilityfise;
  if (durabilityfise2== durabilityfise-1) printf ("l'effet de la carte 6 fonctionne \n");
  else printf("L'effet de la carte 6 ne fonctionne pas \n");
  freeBoard (board);
}

void testCard7() {
  printf("\n");
    printf("\n");
    printf("*********** test carte 7  ***********");
    printf("\n");
  Board *board=newBoard();
  printf("Il faut avoir au moins 1 fisa pour avoir l'effet esconté, sinon cela ne change rien \n");
  board->unactivePlayer->fisa=1;
  int ddfise=board->unactivePlayer->DDfisa;
  personnalCardEffect(board,7);
  int ddfise2=board->unactivePlayer->DDfisa;
  if (ddfise2== ddfise-1) printf ("l'effet de la carte 7 fonctionne \n");
  else printf("L'effet de la carte 7 ne fonctionne pas \n");
  freeBoard (board);
}


void testCard8() {
  printf("\n");
    printf("\n");
    printf("*********** test carte 8  ***********");
    printf("\n");
  Board *board=newBoard();
  printf("Il faut avoir au moins 1 fisa pour avoir l'effet esconté, sinon cela ne change rien \n");
  board->unactivePlayer->fisa=1;
  int durabilityfise=board->unactivePlayer->durabilityfisa;
  personnalCardEffect(board,8);
  int durabilityfise2=board->unactivePlayer->durabilityfisa;
  if (durabilityfise2== durabilityfise-1) printf ("l'effet de la carte 8 fonctionne \n");
  else printf("L'effet de la carte 8 ne fonctionne pas \n");
  freeBoard (board);
}

void testEffet9(){
   printf("\n");
    printf("\n");
    printf("*********** test effet 9  ***********");
    printf("\n");
    Board *board=newBoard();
    int DD_ini=board->activePlayer->DD;
    personnalCardEffect(board,14);
    int DD_end=board->activePlayer->DD;
    if(DD_end==DD_ini+2) printf("L'effet ADD fonctionne \n");
    else printf("L'effet ADD ne fonctionne pas \n");
    freeBoard(board);
}

void testEffet10(){
   printf("\n");
    printf("\n");
    printf("*********** test effet 10  ***********");
    printf("\n");
    Board *board=newBoard();
    int DD_gagne=2;
    board->unactivePlayer->DD+=DD_gagne;
    personnalCardEffect(board,15);
    if(board->unactivePlayer->DD==0) printf("L'effet RDD fonctionne \n");
    else printf("L'effet RDD ne fonctionne pas \n");
     freeBoard(board);
}

void testAction1(){
   printf("\n");
    printf("\n");
    printf("*********** test action 1***********");
    printf("\n");
    Board *board=newBoard();
    int DD_ini=board->activePlayer->DD;
    actionCardEffect(board,21);
    int DD_end=board->activePlayer->DD;
    if (DD_end== DD_ini+1 ) printf("L'action 1 fonctionne \n");
    else printf("L'action 1 ne fonctionne pas \n");
    freeBoard(board);
}

void testAction2(){
   printf("\n");
    printf("\n");
    printf("*********** test action 2***********");
    printf("\n");
    Board *board=newBoard();
    CardList *main1=board->activePlayer->main;
    int taille1=getCardListSize(main1);
    printMain(board->activePlayer);
    printf("\n");
    actionCardEffect(board,22);
    printMain(board->activePlayer);
    CardList *main2=board->activePlayer->main;
    printf("\n");
    int taille2=getCardListSize(main2);
    if (taille1 == taille2-1) printf("L'action 2 fonctionne \n");
    else printf("L'action 2 ne fonctionne pas \n");
freeBoard(board);
}

void testAction3(){
  printf("\n");
    printf("\n");
    printf("*********** test action 3***********");
    printf("\n");
    Board *board=newBoard();
    int fise_ini=board->activePlayer->fise;
    actionCardEffect(board,23);
    int fise_end=board->activePlayer->fise;
    if (fise_end==fise_ini+1) printf("L'action 3 fonctionne \n");
    else printf("L'action 3 ne fonctionne pas \n");
    freeBoard(board);
}


void testAction4(){
  printf("\n");
    printf("\n");
    printf("*********** test action 4***********");
    printf("\n");
    Board *board=newBoard();
    int fisa_ini=board->activePlayer->fisa;
    actionCardEffect(board,24);
    int fisa_end=board->activePlayer->fisa;
    if (fisa_end==fisa_ini+1) printf("L'action 4 fonctionne \n");
    else printf("L'action 4 ne fonctionne pas \n");
    freeBoard(board);
}

void testAction5(){
  printf("\n");
    printf("\n");
    printf("*********** test action 5***********");
    printf("\n");
    Board *board=newBoard();
    int PE_ini=board->activePlayer->PE;
    actionCardEffect(board,25);
    int PE_end=board->activePlayer->PE;
    if (PE_end==PE_ini+6) printf("L'action 5 fonctionne \n");
    else printf("L'action 5 ne fonctionne pas \n");
    freeBoard(board);
}


void testAction6(){
  printf("\n");
    printf("\n");
    printf("*********** test action 6***********");
    printf("\n");
    Board *board=newBoard();
    board->unactivePlayer->fise=1;
    board->unactivePlayer->fisa=1;
    int fise_ini=board->unactivePlayer->fise;
    int fisa_ini=board->unactivePlayer->fisa;
    actionCardEffect(board,26);
    int fise_end=board->unactivePlayer->fise;
    int fisa_end=board->unactivePlayer->fisa;
    if (fise_end==fise_ini-1 && fisa_end== fisa_ini-1) printf("L'action 6 fonctionne \n");
    else printf("L'action 6 ne fonctionne pas \n");
    freeBoard(board);
}

void testAction7(){
   printf("\n");
    printf("\n");
    printf("*********** test action 7***********");
    printf("\n");
    Board *board=newBoard();
    Card *card1=createCard('p',1,1);
    Card *card2=createCard('p',2,2);
    addCardToQueue(board->unactivePlayer->personnel,card1);
    addCardToQueue(board->unactivePlayer->personnel,card2);
    int size_ini=getCardQueueSize(board->unactivePlayer->personnel);    printPersonnel(board->unactivePlayer);
    printf("\n");
    actionCardEffect(board,27);
    printPersonnel(board->unactivePlayer);
    printf("\n");
    int size_end=getCardQueueSize(board->unactivePlayer->personnel);
    if (size_end==size_ini-1) printf("L'action 7 fonctionne \n");
    else printf("Laction 7 ne fonctionne pas \n");
    freeBoard(board);
    //  free(card1);
    //free(card2);
}

void testAction8() {
   printf("\n");
    printf("\n");
    printf("*********** test action 8***********");
    printf("\n");
    Board *board=newBoard();
    Card *test=createCard('o',0,0);
    pushCardToStack(board->activePlayer->discard,test);
    CardStack *discard=board->activePlayer->discard;
    printDiscard(board->activePlayer);
    int t1=getCardStackSize(discard);
    printf("\n");
    board->activePlayer->PE=1;
    printf("\n");
    Card *card=createCard('o',28,0);
    addCardToList(board->activePlayer->main,card);
    playCard(board,card);
    printf("\n");
    CardStack *discard2=board->activePlayer->discard;
    int t2=getCardStackSize(discard2);
    printDiscard(board->activePlayer);
    printf("\n");

    if (t2 != t1) printf("L'action 8 fonctionne\n");
    else printf("L'action 8 ne fonctionne pas \n");
    freeBoard(board);
    //freeCard(card);
    // freeCard(test);
}

void testDeck(){
  printf("\n");
    printf("\n");
    printf("*********** test Deck**********");
    printf("\n");
    Board *board=newBoard();
    printf("Après vérification, le deck possède 1 carte 21 et 1 carte 22 en plus, mais chaque joueur possède les mêmes cartes dans le deck le jeu reste équitable \n");
    freeBoard(board);
}
    
  
  
  
    
  
  
  
      

int main()
{  
   
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

      /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", 0, 0);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

    /* add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "test of create list", testCreateList))
        || (NULL == CU_add_test(pSuite, "test add to list", testInsertDataInList))      
        || (NULL == CU_add_test(pSuite, "test remove to list", testRemoveDataInList))
        || (NULL == CU_add_test(pSuite, "test list contains", testListContains))
        || (NULL == CU_add_test(pSuite, "test create stack", testCreateStack))
        || (NULL == CU_add_test(pSuite, "test add to stack", testInsertDataInStack))
        || (NULL == CU_add_test(pSuite, "test remove to stack", testRemoveDataInStack))
        || (NULL == CU_add_test(pSuite, "test merge 2 stacks", testMergeStacks))
        || (NULL == CU_add_test(pSuite, "test shuffle stack", testShuffleStack))
        || (NULL == CU_add_test(pSuite, "test create queue", testCreateQueue))
        || (NULL == CU_add_test(pSuite, "test add to queue", testInsertDataInQueue))
        || (NULL == CU_add_test(pSuite, "test pull to stack", testPullCardFromStack))
	|| (NULL == CU_add_test(pSuite, "test remove to queue", testRemoveDataInQueue))
	|| (NULL == CU_add_test(pSuite, "test add card to queue", testAddCardToQueue))

        )
    {
        printf("error");
       CU_cleanup_registry();
       return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    printf("\n");
    printf("**************Test switch Player*************");
    printf("\n");
    printf("\n");
    testSwitch();
    printf("\n");
    printf("\n");
    printf("*********** test suppression fisa ***********");
    printf("\n");
    testSupFisa();
    printf("\n");
    printf("\n");
    printf("\n");
    testSizePersonnel();
    testCard1();
    testCard2();
    testCard3();
    testCard4();
    testCard5();
    testCard6();
    testCard7();
    testCard8();
    testEffet9();
    testEffet10();
    testAction1();
    testAction2();
    testAction3();
    testAction4();
    testAction5();
    testAction6();
    testAction7();
    testAction8();
    testDeck();
    return CU_get_error();
}


