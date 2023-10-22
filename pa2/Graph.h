/****************************************************************************
*Yiqi Li yli823
*2022 Winter CSE101 PA#2
*Graph.h
****************************************************************************/
#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#define INF -1
#define NIL 0

#include "List.h"

typedef struct GraphObj* Graph;
/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);
#endif
