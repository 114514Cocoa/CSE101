/****************************************************************************
*Yiqi Li yli823
*2022 Winter CSE101 PA#3
*Graph.c
****************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
//#include "List.h"

//private Graphobj type
typedef struct GraphObj{
    List* near; //an array of list whose ith element contains the neighors of vertex i 
    int* color; //an array of ints(or chars, or strings) whose ith element is the colors(white, gray
                 // black) of vertexi
    int* parent; //an array of ints whose ith element is the parent of vertex i
    int order; //the orders of the field
    int size; //the size of the field
    int* finish; //used as source for BFS
    int* discover; //an array of ints whose ith element is the discover time of vertex i
}GraphObj;

//return the graph pointing to a newly graphobj
Graph newGraph(int n){
    Graph G = (GraphObj *)malloc(1 * sizeof(GraphObj)); //used malloc to set the memory to graph
    G -> order = n; //the number of order
    G -> size = 0; //the size of graph
    G -> near = malloc((n+1) * sizeof(List)); // allocate memory for the element in near
    G -> color = malloc((n+1) * sizeof(int)); //allocate memory for the element is colors
    G -> parent = malloc((n+1) * sizeof(int)); //allocate memory for the element is parent
    G -> discover = malloc((n+1) * sizeof(int)); //allocate memory for the element is discover time 
    G -> finish = malloc((n+1) * sizeof(int)); //allocate memory for the element is finish time 
    int i;
    for(i=0; i<=n+1; i++){
        G->near[i] = newList(); //make a new list for the neighor 
        G ->color[i] = 0;
        G -> parent[i] = NIL;
        G -> discover[i] = UNDEF;
        G -> finish[i] = UNDEF;
    
    }
    return G;
}

void freeGraph(Graph* pG){
    if(pG != NULL && (*pG) != NULL){
       // freeList(*pG -> near);
    //}
    free((*pG) -> near); //delete the neighor
    free((*pG) -> color); //delete the color
    free((*pG) -> parent); //delete the parent
    free((*pG) -> discover); //delete the distance
    free(*pG);
    *pG = NULL; //set the pG to NULL
    }
}
/*** Access functions ***/



int getOrder(Graph G){
    if(G==NULL){
        printf("There was a error for g is null in getOrder.\n");
        exit(EXIT_FAILURE);
    }
    return G -> order; //return the order of the graph
}

int getSize(Graph G){    
    if(G==NULL){
        printf("There was a error for g is null in getSize.\n");
        exit(EXIT_FAILURE);
    }
    return G -> size; //return the size of the graph
}


int getParent(Graph G, int u){
    if(G==NULL){
        printf("There was a error for g is null in getParent.\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G)){
	    printf("There was a error for g is null in getParent.\n");
        exit(1);
    }
    int qige1 = G -> parent[u - 1];
    return qige1;
    //return G->parent[u]; //return the parent of the graph
}

int getDiscover(Graph G, int u){
    if(G==NULL){
        printf("There was a error for g is null in getDiscover.\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G)){
	    printf("There was a error for g is null in getDiscover.\n");
        exit(EXIT_FAILURE);
    }
    int qige2 = G -> discover[u - 1];
    return qige2;
    //return G->discover[u--]; //return the discover time of the graph
}


int getFinish(Graph G, int u){
    if(G==NULL){
        printf("There was a error for g is null in getFinish.\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G)){
	    printf("There was a error for g is null in getFinish.\n");
        exit(EXIT_FAILURE);
    }
    int qige3 = G -> finish[u - 1];
    return qige3;
    //return G->finish[u]; //return the finish time of the graph
}


//insert a new edge joining u to v 
void addEdge(Graph G, int u, int v){
    if(G==NULL){
        printf("There was a error for g is null in addEdge.\n");
        exit(EXIT_FAILURE);
    }
    addArc(G, u, v); //use addArc function to insert a new edge
    addArc(G, v, u);
    G -> size -=1;
}


//insert a new directed edge from u to v,
void addArc(Graph G, int u, int v){
    if(G==NULL){
        printf("There was a error for g is null in addArc.\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
        printf("Graph ERROR: Calling addArc() with invalid arguments.\n");
        exit(EXIT_FAILURE);
    }
    List L = G->near[u-1];


   if(length(L) == 0){
        append(G->near[u - 1], v);
        G->size++;
        return;
    }
	for (moveFront(L);  index(L) != -1; moveNext(L)) {
		if(v > get(L)){
			continue;
    } 
        else if(v == get(L)){
            return;
        }    
        else {
            break;
        }
	}
    if (index(L) == -1)
        append(L, v);
    else if (index(L) >= 0)
        insertBefore(L, v);
    G->size++;
} 



int Visit(Graph G,List S, int time, int x){
    G -> discover[x] = ++time; //increase the discover time 
    G -> color[x] = 1;  //set the color is grary
    for(moveFront(G->near[x]); index(G->near[x]) >= 0; moveNext(G->near[x])){ //iteralty the graph
        int y = get(G->near[x]); //get the valur of adj
        if (G -> color[y-1]  == 0){
            G -> parent[y-1]   = x + 1;
            time = Visit(G,S,time,y-1); //recursion
        }
    }
    G -> color[x] = 2; //the color of graph is white
    G -> finish[x] = ++time; //increase the finish time
    insertAfter(S,x+1);
    return time;
}



void DFS(Graph G, List S){ //use dfs to sort the graph
    if(G == NULL){
        printf("There was a error for g is null in DFE.\n");
        exit(EXIT_FAILURE);
    }
    if(S == NULL){
        printf("There was a error for l is null in DFS.\n");
        exit(EXIT_FAILURE);
    }
    int n = getOrder(G);
    if(length(S) != n){ //if the lenght of s not equal the order of n, return false
        printf("There was a error because the length s not equal n in DFS.\n");
        exit(EXIT_FAILURE);
    }
    int time = 0;
    for(int i = 0; i < G->order; i++){
        G->color[i] = 0;
        G->parent[i] = NIL;     
    }
    moveBack(S); //go to the back of the list
    for(int i = 0; i < G->order; i++){
        if(G->color[front(S) - 1] == 0){ //if the color of grade is white
            time = Visit(G,S, time, front(S) -1); 
         }
      deleteFront(S);    
    }
} 
    
    
Graph transpose(Graph G){ //reverse the graph and return a new graph
    if(G == NULL){
        printf("There was a error for g is null in transpose.\n");
        exit(EXIT_FAILURE);
    }
    Graph R = newGraph(G -> order); //make a new empty graph
    for(int i = 1; i <= G->order; i++){
        for(moveFront(G->near[i-1]); index(G->near[i-1]) >= 0; moveNext(G->near[i-1])){ //ilearlty the list 
            addArc(R, get(G->near[i-1]),i);
        }
    }
    return R;
}


Graph copyGraph(Graph G){ //copy the old graph and return a new graph
    if(G == NULL){
        printf("There was a error for g is null in copyGraph.\n");
        exit(EXIT_FAILURE);
    }
    Graph R = newGraph(G -> order); //make a new empty graph
    for(int i = 1; i <= G->order; i++){
        for(moveFront(G->near[i-1]); index(G->near[i-1]) >= 0; moveNext(G->near[i-1])){ //ilearlty the list
            addArc(R, i,get(G->near[i-1]));
        }
    }
    return R;
}

void printGraph(FILE* out, Graph G){//output the graph
    int i;
    for(i = 1;  i <= G->order;i++){
        List a = G->near[i-1];
        fprintf(out, "%d: ", i);
        printList(out, a); //output the value
      //  i++;
        fprintf(out, "\n");
    }
}

