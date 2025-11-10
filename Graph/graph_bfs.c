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

typedef struct Queue {
    Vertex *vertices[MAX_SIZE];
    int front, rear, size;
} Queue;

Queue *newQueue() {
    Queue * q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = q->size = 0;
    return q;
}

int isEmpty(Queue *q) {
    return q->size == 0;
}

void enqueue(Queue * q, Vertex *vet) {
    q->vertices[q->rear] = vet;
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->size++;
}

Vertex *dequeue(Queue *q) {
    Vertex *vet = q->vertices[q->front];
    q->front = (q->front + 1)%MAX_SIZE;
    q->size--;
    return vet;
}

int isVisited(Vertex **visited, int size, Vertex *vet) {
    for (int i=0; i<size; i++) {
        if (visited[i]==vet) {
            return 1;
        }
    }
    return 0;
}

void graphBFS(GraphAdjList *graph, Vertex *startVet, Vertex **res, int *resSize, Vertex **visited, int *visitedSize) {
    Queue *queue = newQueue();
    enqueue(queue, startVet);
    visited[(*visitedSize)++] = startVet;
    while (!isEmpty(queue)) {
        Vertex *vet = dequeue(queue);
        res[(*resSize)++] = vet;
        AdjListNode * node = findNode(graph, vet);
        while (node!=NULL) {
            if (!isVisited(visited, *visitedSize, node->vertex)) {
                enqueue(queue, node->vertex);
                visited[(*visitedSize)++] = node->vertex;
            }
            node = node->next;
        }
    }
    free(queue);
}
