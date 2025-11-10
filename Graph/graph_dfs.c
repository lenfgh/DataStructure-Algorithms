#define MAX_SIZE 1000000

#include<stdlib.h>
#include<stdio.h>

typedef struct Vertex {
    int val;
} Vertex;

typedef struct AdjListNode {
    Vertex * vertex;
    struct AdjListNode * next;
} AdjListNode; 

AdjListNode * findNode(GraphAdjList * graph, Vertex *vet) {
    for (int i=0; i<graph->size; i++) {
        if (graph->heads[i]->vertex == vet) {
            return graph->heads[i];
        }
    }
    return NULL;
}

typedef struct GraphAdjList {
    AdjListNode * heads[MAX_SIZE];
    int size;
} GraphAdjList;

int isVisited(Vertex **res, int size, Vertex *vet) {
    for (int i=0; i<size; i++) {
        if (res[i]==vet) {
            return 1;
        }
    }
    return 0;
}


void dfs(GraphAdjList * graph, Vertex **res, int *resSize, Vertex *vet) {
    res[(*resSize)++] = vet;
    AdjListNode * node = findNode(graph, vet);
    while (node!=NULL) {
        if (!isVisited(res, *resSize, node->vertex)) {
            dfs(graph, res, resSize, node->vertex);
        }
        node = node->next;
    } 
}

void graphDFS(GraphAdjList *graph, Vertex *startVet, Vertex **res, int *resSize) {
    dfs(graph, res, resSize, startVet);
}
