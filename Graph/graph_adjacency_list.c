#define MAX_SIZE 100000

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

void addEdgeHelper(AdjListNode * head, Vertex * vet) {
    AdjListNode * node = (AdjListNode *)malloc(sizeof(AdjListNode));
    node->vertex = vet;
    node->next = head->next;
    head->next = node;
}

void removeEdgeHelper(AdjListNode * head, Vertex * vet) {
    AdjListNode * pre = head;
    AdjListNode * cur = head->next;
    while ( cur!=NULL && cur->vertex!=vet) {
        pre = cur;
        cur = cur->next;
    }
    if (cur==NULL) {
        return;
    }
    pre->next = cur->next;
    free(cur);
}

typedef struct GraphAdjList {
    AdjListNode * heads[MAX_SIZE];
    int size;
} GraphAdjList;

GraphAdjList * newGraphAdjList() {
    GraphAdjList * graph = (GraphAdjList *)malloc(sizeof(GraphAdjList));
    if (!graph) {
        return NULL;
    }
    graph->size = 0;
    for (int i=0; i<MAX_SIZE; i++) {
        graph->heads[i] = NULL;
    }
    return graph;
}

void delGraphAdjList(GraphAdjList * graph) {
    for (int i=0; i<graph->size; i++) {
        AdjListNode * cur = graph->heads[i];
        while(cur!=NULL) {
            AdjListNode * next = cur->next;
            if(cur!=graph->heads[i]) {
                free(cur);
            }
            cur = next;
        }
        free(graph->heads[i]->vertex);
        free(graph->heads[i]);
    }
    free(graph);
}

void addEdge(GraphAdjList * graph, Vertex * vet1, Vertex * vet2) {
    AdjListNode *head1 = findNode(graph, vet1);
    AdjListNode *head2 = findNode(graph, vet2);
    assert(head1!=NULL && head2!=NULL&&head1!=head2);
    addEdgeHelper(head1, vet2);
    addEdgeHelper(head2, vet1); // For undirected graph.
}


void removeEdge(GraphAdjList *graph, Vertex *vet1, Vertex *vet2) {
    AdjListNode *head1 = findNode(graph, vet1);
    AdjListNode *head2 = findNode(graph, vet2);
    assert(head1!=NULL&&head2!=NULL&&head1!=head2);
    removeEdgeHelper(head1, head2->vertex);
    removeEdgeHelper(head2, head1->vertex);// For undirecgted graph
}

void addVertex(GraphAdjList *graph, Vertex *vet) {
    assert(graph!=NULL&&graph->size<MAX_SIZE);
    AdjListNode *head = (AdjListNode*)malloc(sizeof(AdjListNode));
    head->vertex = vet;
    head->next = NULL;
    graph->heads[graph->size++] = head;
}

void removeVertex(GraphAdjList *graph, Vertex *vet) {
    AdjListNode *node = findNode(graph, vet);
    assert(node!=NULL);
    AdjListNode *cur = node, *pre=NULL;
    while(cur) {
        pre=cur;
        cur=cur->next;
        free(cur);
    }
    for (int i=0; i<graph->size; i++) {
        cur = graph->heads[i];
        pre = NULL;
        while(cur) {
            pre=cur;
            cur = cur->next;
            if (cur==node) {
                pre->next = cur->next;
                free(cur);
                break;
            }
        }
    }
    int i;
    for (i=0; i<graph->size; i++) {
        if(graph->heads[i]==node) {
            break;
        }
    }
    for (int j=i; j<graph->size-1; j++) {
        graph->heads[j] = graph->heads[j+1];
    }
    graph->size--;
    // free(vet);
}