/****************************************************************************
*Yiqi Li yli823
*2022 Winter CSE101 PA#2
*List.c
****************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#include "List.h"

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   void* data; //inital the data of node
   Node previous;
   Node next;
} NodeObj;

typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length; //inital the length
   int index; //inital the index
} ListObj;


//Returns referece to new node object
Node newNode(void* data){
   Node N = malloc(sizeof(NodeObj)); //allocate memory for the node;
   N->data = data; //set the data
   N->previous = NULL;
   N->next = NULL;
   return(N);
}

// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
      pN = NULL;
   }
}

// Returns reference to new empty List object.
List newList(){
   List L;
   L = (List)malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0; //the lenth is 0
   L->index = -1; //set the index is -41
   return(L);
}

// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      clear(*pL);
      free(*pL);
      *pL = NULL;
      pL = NULL;
   }
}


int length(List L){
   if (L == NULL){
      printf("There is a erro in length()\n");
      exit(EXIT_FAILURE);
   }
   return(L->length); //return the length of the list
}

int index(List L){
   if (L == NULL){
      printf("There is a erro in index()\n");
      exit(EXIT_FAILURE);
   }
   return(L->index); //return the index of the list
}

void* front(List L){
   if (L == NULL){
      printf("There is a erro in front()\n");
      exit(EXIT_FAILURE);
   }
   return(L->front->data); //return the date from the front of the list
}

void* back(List L){
   if (L == NULL){
      printf("There is a erro in back()\n");
      exit(EXIT_FAILURE);
   }
   return(L->back->data); //return the date from the back of the list
}

void* get(List L){
   if (L == NULL){
      printf("There is a erro in get()\n");
      exit(EXIT_FAILURE);
   }
   return(L->cursor->data); //return the data from the cursor of the list
}

void clear(List L){
   if (L == NULL){
      printf("There is a erro in clear()\n");
      exit(EXIT_FAILURE);
   }
   if(L->length == 0){
      return;
   }
   Node node1;
   Node node = L->front;
   while(node != L->back){
      node1 = node->next;
      freeNode(&node); //free the node
      node = node1;
   }
   free(L->back); //free the back pointer
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
}


void set(List L, void* x){ //set the value to list
   L->cursor->data = x;
}

void moveFront(List L){
   if(L->length > 0){
      L->index = 0;
      L->cursor = L->front;
   }
}

void moveBack(List L){
   if(L->length > 0){
      L->index = L->length - 1;
      L->cursor = L->back;
   }
}

void movePrev(List L){
   if(L->cursor != NULL){
      if(L->cursor != L->front){
         L->index -= 1;
         L->cursor = L->cursor->previous;
      }else{
         L->cursor = NULL;
         L->index = -1;
      }
   }
}

void moveNext(List L){
   if(L->cursor != NULL){
      if(L->cursor != L->back){
         L->index += 1;
         L->cursor = L->cursor->next;
      }else{
         L->cursor = NULL;
         L->index = -1;
      }
   }
}

void prepend(List L, void* x){
   Node X = newNode(x);
   if(L->length > 0){
      X->next = L->front;
      L->front->previous = X;
      L->front = X;
      if(L->index != -1){
         L->index += 1;
      }
   }else{
      L->front = L->back = X;
   }
   L->length += 1;
}

void append(List L, void* x){
   Node X = newNode(x);
   if(L->length > 0){
      X->previous = L->back;
      L->back->next = X;
      L->back = X;
   }else{
      L->front = L->back = X;
   }
   L->length += 1;
}

void insertBefore(List L, void* x){
   if(L->cursor == L->front){
      prepend(L, x);
      return;
   }
   Node X = newNode(x);
   Node node_before_cursor = L->cursor->previous;
   X->next = L->cursor;
   X->previous = node_before_cursor;
   L->cursor->previous = X;
   node_before_cursor->next = X;
   L->length += 1;
   L->index += 1;
}

void insertAfter(List L, void* x){
   if(L->cursor == L->back){
      append(L, x);
      return;
   }
   Node X = newNode(x);
   Node node_after_cursor = L->cursor->next;
   X->previous = L->cursor;
   X->next = node_after_cursor;
   L->cursor->next = X;
   node_after_cursor->previous = X;
   L->length += 1;
}

void deleteFront(List L){
   if(L->length == 1){
      clear(L);
      return;
   }
   if(index(L) >= 0){
      L->index -= 1;
   }
   if(L->cursor == L->front){
      L->cursor = NULL;
   }
   Node oldFront = L->front;
   L->front = oldFront->next;
   freeNode(&oldFront);
   L->length -= 1;
}

void deleteBack(List L){
   if(L->length == 1){
      clear(L);
      return;
   }
   if(L->cursor == L->back){
      L->cursor = NULL;
      L->index = -1;
   }
   Node back = L->back;
   L->back = NULL;
   L->back = back->previous;
   freeNode(&back);
   L->length -= 1;
}

//delete the list
void delete(List L){
   if(L->cursor == L->front){
      deleteFront(L);
      return;
   }
   if(L->cursor == L->back){
      deleteBack(L);
      return;
   }
   Node cursor = L->cursor;
   Node node_before_cursor = cursor->previous;
   Node node_after_cursor = cursor->next;
   if(node_before_cursor) node_before_cursor->next = node_after_cursor;
   if(node_after_cursor) node_after_cursor->previous = node_before_cursor;
   L->cursor = NULL;
   L->index = -1;
   freeNode(&cursor);
   L->length -= 1;
}

List copyList(List L){
   List a = newList(); //make the new list
   int b = index(L); //get the index of list
   moveFront(L);
   for(moveFront(L);index(L) >= 0;moveNext(L)){
      void* x = get(L);
      append(a, x);
   }
   moveFront(L); 
   while(index(L) != b)
   {
      moveNext(L);
   }
   return a;
}
