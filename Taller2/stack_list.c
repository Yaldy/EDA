#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

typedef struct stacknode
{
    int val;
    struct stacknode *next;
}STACK;

static STACK *head = NULL;

void STACKclean()
{
    STACK *current = head;
    STACK *next;

    while (current != NULL)
    {
       next = current->next;
       free(current);
       current = next;
    }

    head = NULL;
}

void STACKinit(N)
{
    if (head != NULL){
        STACKclean();
    } 
        
}

int STACKempty()
{
    return(head==NULL);
}

void STACKpush(int var, int MAX_SIZE)
{
    if ( STACKsize( head ) <= MAX_SIZE ){
        STACK *newNode = malloc(sizeof(STACK));
        newNode -> val = var;
        newNode -> next = head;
        head = newNode;
    }
    else{
        printf("Error: el stack está lleno. No se añadió ningún valor.\n");
    }
}

int STACKpop()
{
    STACK *temp;
    if (STACKempty())
        printf("Error: el stack está vacío.\n");
    else {
        int res = head -> val;
        temp = head;
        head = head -> next;
        free(temp);
        
        return res;
    }

}

int STACKsize(STACK *head)
{
    int largo = 0;
    while ( head!= NULL ){
        largo++;
        head = head -> next;
    }
    return largo;
}