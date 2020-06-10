#include <stdlib.h>
#include <time.h>
#include "../headers/structureEngine.h"


static bool isRandomSeedInitiate = false;
typedef struct _Node{
    void * data;
    struct _Node * next;
    struct _Node * previous;
}Node;

struct _List{
    int size;
    Node * first;
    Node * last;// en vue d'optimisation de parcours de liste //TODO optimiser le parcours des listes
};

struct _Stack{
    int size;
    Node * first;
    Node * last;
};

struct _Queue{
    int size;
    Node * first;
    Node * last;
};

/************************************
 * 
 * Gestion des maillons
 * 
 * **********************************/

Node * createNode(void * data){
    Node * newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->previous = NULL;
    return newNode;
}

void freeNode(Node * node){
    free(node);
}

/************************************
 * 
 * Gestion des listes
 * 
 * **********************************/

List * createList(){
    List * newList = (List*)malloc(sizeof(List));
    if(newList != NULL){
        newList->size = 0;
        newList->first = NULL;
        newList->last = NULL;
    }
    return newList;
}


void freeList(List * list){
    free(list);
}


bool addToList(List * list, void * data){
    Node * newNode = createNode(data);
    if(newNode != NULL){
        if(list->last == NULL){
            list->last = newNode;
        }

        if(list->first != NULL){
            list->first->previous = newNode;
        }
        
        newNode->next = list->first;
        list->first = newNode;
        list->size = list->size + 1;
        return true;
    }
    return false;
}


void * get(List * list, int index){
    if(list->size <= index || index < 0){
        return NULL;
    }
    Node * actualNode = list->first;
    for(int i = 0; i != index; i++){
        actualNode = actualNode->next;
    }

    return actualNode->data;
}


void * removeListData(List * list, int index){
    if(list->size <= index || index < 0){
        return NULL;
    }
    void * dataToReturn;
    Node * actualNode = list->first;

    if(index == 0){
        list->first = actualNode->next;
        dataToReturn = actualNode->data;

        if(actualNode->next != NULL){
            actualNode->next->previous = NULL;
        }
    }

    else{
        actualNode = actualNode->next;
        for(int i = 1; i != index; i++){
            actualNode = actualNode->next;
        }
        actualNode->previous->next = actualNode->next;
        if(actualNode->next != NULL){
            actualNode->next->previous = actualNode->previous;
        }
        
        dataToReturn = actualNode->data;
    }    
    if(list->size - 1 == index){ //si on retire le dernier élément de la liste
        list->last = actualNode->previous;
    }
    list->size = list->size - 1;
    free(actualNode);    

    return dataToReturn;
}


int getListSize(List * list){
    return list->size;
}

bool listContains(List * list, void * data, bool equals(void *, void*)){
    if(list == NULL){
        return false;
    }
    if(getListSize(list) == 0){
        return false;
    }
    Node * actualNode = list->first;
    for(int i = 0; i < getListSize(list); i++){
        
        if(equals(data, actualNode->data)){
            return true;
        }
        actualNode = actualNode->next;
    }
    return false;
}

/************************************
 * 
 * Gestion des piles
 * 
 * **********************************/

Stack * createStack(){
    Stack * newStack = (Stack*)malloc(sizeof(Stack));
    if(newStack != NULL){
        newStack->size = 0;
        newStack->first = NULL;
        newStack->last = NULL;
    }
    return newStack;
}


void freeStack(Stack * stack){
    free(stack);
}


bool stackPush(Stack * stack, void * data){
    Node * newNode = createNode(data);

    if(newNode != NULL){

        if(stack->last == NULL){
            stack->last = newNode;
        }
        
        if(stack->first != NULL){
            stack->first->previous = newNode;
        }

        newNode->next = stack->first;
        stack->first = newNode;
        stack->size = stack->size +1;

        return true;
    }
    return false;
}


void * getStackData(Stack * stack, int index){
    if(stack->size <= index || index < 0){
        return NULL;
    }
    Node * actualNode = stack->first;
    for(int i = 0; i != index; i++){
        actualNode = actualNode->next;
    }

    return actualNode->data;
}


void * stackPull(Stack * stack){
    if(stack->size == 0){
        return NULL;
    }
    Node * nodeToRemove = stack->first;
    void * dataToReturn = nodeToRemove->data;

    stack->first = nodeToRemove->next;
    if(stack->first != NULL){
        stack->first->previous = NULL;
    }

    stack->size = stack->size - 1;

    if(stack->size == 0){
        stack->last = NULL;
    }

    free(nodeToRemove);
    return dataToReturn;
}


int getStackSize(Stack * stack){
    return stack->size;
}


//ajoute la pile topStack au debut de la pile bottomStack
//renvoie le pointeur de bottomStack qui contient les deux piles
//desalloue topStack
Stack * addStackToStack(Stack * topStack, Stack * bottomStack){
    if(topStack == NULL){
        return bottomStack;
    }
    else if(bottomStack == NULL){
        return topStack;
    }
   
    topStack->last->next = bottomStack->first;
    bottomStack->first = topStack->first;
    bottomStack->size = bottomStack->size + topStack->size;

    freeStack(topStack);

    return bottomStack;
}

//mélange la pile de manière aléatoire
void shuffleStack(Stack * stack){
    if(!isRandomSeedInitiate){
        srand(time(NULL));
        isRandomSeedInitiate = true;
    }

    //transfert du contenu de la pile dans une liste
    List * copyList = createList();
    copyList->first = stack->first;
    copyList->last = stack->last;
    copyList->size = stack->size;
    stack->first = NULL;
    stack->last = NULL;
    stack->size = 0;

    for(int i = copyList->size; i > 0 ; i--){
        int randomNumber = (int)(rand() / (double)RAND_MAX * (i));
        void * randomData = removeListData(copyList, randomNumber);
        stackPush(stack, randomData);
    }

    freeList(copyList);
}

/************************************
 * 
 * Gestion des files
 * 
 * **********************************/

Queue * createQueue(){
    Queue * newQueue = (Queue*)malloc(sizeof(Queue));
    if(newQueue != NULL){
        newQueue->size = 0;
        newQueue->first = NULL;
        newQueue->last = NULL;
    }
    return newQueue;
}


void freeQueue(Queue * queue){
    free(queue);
}


bool addToQueue(Queue * queue, void * data){
    Node * newNode = createNode(data);

    if(newNode != NULL){

        if(queue->size == 0){//si liste vide le dernier est aussi le premier
            queue->first = newNode;
        }
        else{
            queue->last->next = newNode;
        }

        newNode->previous = queue->last;
        queue->last = newNode;

    queue->size = queue->size + 1;
        return true;
    }
    return false;
}


void * getQueueData(Queue * queue, int index){
    if(queue->size <= index || index < 0){
        return NULL;
    }
    Node * actualNode = queue->first;
    for(int i = 0; i != index; i++){
        actualNode = actualNode->next;
    }

    return actualNode->data;
}


void * removeQueueData(Queue * queue){
    if(queue->size == 0){
        return NULL;
    }
    Node * nodeToRemove = queue->first;
    void * dataToReturn = nodeToRemove->data;
    queue->first = nodeToRemove->next;

    if(queue->first == NULL){
        queue->last = NULL;
    }
    queue->size = queue->size - 1;
    freeNode(nodeToRemove);
    return dataToReturn;
}


int getQueueSize(Queue * queue){
    return queue->size;
}