#ifndef _STRUCTURE_ENGINE_
#define _STRUCTURE_ENGINE_

#include <stdbool.h>

typedef struct _List List; //Type générique permetant la gestion de listes

typedef struct _Stack Stack; //Type générique permetant la gestion de piles

typedef struct _Queue Queue; //Type générique permetant la gestion de files

/************************************
 * 
 * Gestion des listes
 * 
 * **********************************/

//retourne un pointeur sur une liste vide 
List * createList();

//desalloue la mémoire associée à la liste
//attention à bien vider la liste avant
void freeList(List * list);

//ajoute un nouvelle élement en tete de liste
//retourne true si l'élément a bien été ajouté
bool addToList(List * list, void * data);

//retourne un pointeur sur l'élément d'indice i
void * get(List * list, int index);

//supprime de la liste l'élément d'indice i et
//retourne un pointeur sur sur celui-ci
void * removeListData(List * list, int index);

//retourne le nombre d'éléments présents dans la liste
int getListSize(List * list);

bool listContains(List * list, void * data, bool equals(void *, void*));


/************************************
 * 
 * Gestion des piles
 * 
 * **********************************/


Stack * createStack();
void freeStack(Stack * stack);
bool stackPush(Stack * stack, void * data);
void * getStackData(Stack * stack, int index);
void * stackPull(Stack * stack); 
int getStackSize(Stack * stack);

//ajoute la pile topStack au debut de la pile bottomStack
//renvoie le pointeur de bottomStack qui contient les deux piles
//desalloue topStack
Stack * addStackToStack(Stack * topStack, Stack * bottomStack);

//mélange la pile de manière aléatoire
void shuffleStack(Stack * data);



/************************************
 * 
 * Gestion des files
 * 
 * **********************************/

Queue * createQueue();
void freeQueue(Queue * queue);
bool addToQueue(Queue * queue, void * data);
void * getQueueData(Queue * queue, int index);
void * removeQueueData(Queue * queue);
int getQueueSize(Queue * queue);

#endif