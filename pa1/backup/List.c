/****************************************************************************
*Yiqi Li yli823
*2022 Winter CSE101 PA#1
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
   int data; //inital the data of node
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
Node newNode(int data){
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

int front(List L){
   if (L == NULL){
      printf("There is a erro in front()\n");
      exit(EXIT_FAILURE);
   }
   return(L->front->data); //return the date from the front of the list
}

int back(List L){
   if (L == NULL){
      printf("There is a erro in back()\n");
      exit(EXIT_FAILURE);
   }
   return(L->back->data); //return the date from the back of the list
}

int get(List L){
   if (L == NULL){
      printf("There is a erro in get()\n");
      exit(EXIT_FAILURE);
   }
   return(L->cursor->data); //return the data from the cursor of the list
}

bool equals(List A, List B){
   if(A->length != B->length){ //check if the length is not equal
      return(false);
   }
   if(A->length == 0 && B->length == 0){
      return(true);
   }
   moveFront(A); //put the cursor to the front
   moveFront(B); //put the cursor to the front
   while( index(A)>=0 && index(B)>=0 ){
      int a = get(A);
      int b = get(B);
      if(a != b){
         return(false);
      }
      moveNext(A);
      moveNext(B);
   }
   return(true); //return true
}

void clear(List L){
   if (L == NULL){
      printf("There is a erro in clear()\n");
      exit(EXIT_FAILURE);
   }
   if(L->length == 0){
      return;
   }
   Node temp_node;
   Node node = L->front;
   while(node != L->back){
      temp_node = node->next;
      freeNode(&node);
      node = temp_node;
   }
   free(L->back);
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
}


void set(List L, int x){
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

void prepend(List L, int x){
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

void append(List L, int x){
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

void insertBefore(List L, int x){
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

void insertAfter(List L, int x){
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
      int x = get(L);
      append(a, x);
   }
   moveFront(L); 
   while(index(L) != b)
   {
      moveNext(L);
   }
   return a;
}


void printList(FILE* output, List L){
   for(moveFront(L); index(L) >= 0; moveNext(L)){
      int x = get(L);
      fprintf(output, "%d ", x);
   }
}
