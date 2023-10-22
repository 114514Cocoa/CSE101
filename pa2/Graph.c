/****************************************************************************
*Yiqi Li yli823
*2022 Winter CSE101 PA#2
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
    int* distance;//an array of ints whose ith element is the distance from the source to vertex i
    int order; //the orders of the field
    int size; //the size of the field
    int source; //used as source for BFS
}GraphObj;

//return the graph pointing to a newly graphobj
Graph newGraph(int n){
    Graph G = (GraphObj *)malloc(1 * sizeof(GraphObj)); //used malloc to set the memory to graph
    G -> source = NIL; //set the source to NIL
    G -> order = n; //the number of order
    G -> size = 0; //the size of graph
    G -> near = malloc((n+1) * sizeof(List)); // allocate memory for the element in near
    G -> color = malloc((n+1) * sizeof(int)); //allocate memory for the element is colors
    G -> parent = malloc((n+1) * sizeof(int)); //allocate memory for the element is parent
    G -> distance = malloc((n+1) * sizeof(int)); //allocate memory for the element is distance
    int i;
    for(i=0; i<=n+1; i++){
        G->near[i] = newList(); //make a new list for the neighor 
        G ->color[i] = 0;
        G -> parent[i] = NIL;
        G -> distance[i] = INF;
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
    free((*pG) -> distance); //delete the distance
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
int getSource(Graph G){
    if(G==NULL){
        printf("There was a error for g is null in getSource.\n");
        exit(EXIT_FAILURE);
    }
    return G -> source;//return the source of the graph
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
    
    return G->parent[u]; //return the parent of the graph
}

int getDist(Graph G, int u){
    if(G==NULL){
        printf("There was a error for g is null in getDist.\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G)){
    	printf("There was a error for g is arg in getDist.\n");
        exit(1);
    }
    if(G -> source ==NIL){
    	return INF;
    }
    return G -> distance[u]; //return the distance of the graph
}


void getPath(List L, Graph G, int u){
    if(G == NULL){
        printf("There was a error for g is null in getPath.\n");
        exit(EXIT_FAILURE);
    }
	if(u < 1 || getOrder(G) < u){
	    printf("There was a error for U  in getPath.\n");
        exit(EXIT_FAILURE);
    }
	if(getSource(G) == NIL){
        printf("There was a error for source is null in getPath.\n");
        exit(EXIT_FAILURE);
    }
	
	if(getSource(G) == u){
		append(L,u);
	}
	else if(G->distance[u] < 0){
		append(L,NIL);
	}else{
		getPath(L,G,getParent(G,u));
		append(L,u);
	}
}




void makeNull(Graph G){//earese all the list
    int i;
    int n = getOrder(G);
    for(i = 0; i < n; i++){
        clear(G->near[i]);
        G ->color[i] = 0;
        G -> parent[i] = NIL;
        G -> distance[i] = INF;
    }
    G -> source = NIL; //the source of graph
    G -> order = 0; //the number of order
    G -> size = 0; //the size of graph
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
    List L = G->near[u];
    moveFront(L); //start itlealtice the list 
    while(index(L) != -1){
    	if(get(L) < v){
    		moveNext(L);
    	}else{
    		insertBefore(L,v);
    		G->size++;
    		break;
    	}
    	//G -> size++; //increase the size
    }
    if(index(L) == -1){
    	append(L,v);
    	G -> size++; //increase the size
	 }
}
    


void BFS(Graph G, int s){
    if(G==NULL){
        printf("There was a error for g is null in BFS.\n");
        exit(EXIT_FAILURE);
    }
    G -> source = s; //the source of graph is the value
    int n = getOrder(G); //initial the n to store the order of graph
    for(int i = 0; i <= n; i++){
        G->color[i] = 0;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->color[s] = 1;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    
    List Q = newList();
    append(Q, s);
    
    while(length(Q) != 0){
    	int f = front(Q);
    	deleteFront(Q);
    	moveFront(G->near[f]);
    	for(int p=0; p<length(G->near[f]);p++){
    		int y = get(G->near[f]);
    		if (G->color[y] == 0) {
            	G->color[y] = 1;
            	G->distance[y]  = G->distance[f] + 1;
            	G->parent[y] = f;
            	append(Q, y);
        }
        moveNext(G->near[f]);

    }
       G->color[f] = 2;
	}
	free(Q); //free the memory
}


/*** Other operations ***/
void printGraph(FILE* out, Graph G){
    int i;
    for(i = 1;  i <= G->order;i++){
        List a = G->near[i];
        fprintf(out, "%d: ", i);
        printList(out, a); //output the value
        fprintf(out, "\n");
      //  i++;
    }
}
