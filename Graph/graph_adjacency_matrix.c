#define MAX_SIZE 100000


typedef struct {
    int vertices[MAX_SIZE];
    int adjMat[MAX_SIZE][MAX_SIZE];
    int size;
} GraphAdjMat;

GraphAdjMat * newGraphAdjMat() {
    GraphAdjMat * graph = (GraphAdjMat *)malloc(GraphAdjMat);
    graph->size = 0;
    for (int i=0; i<=MAX_SIZE; i++) {
        for (int j=0; j<=MAX_SIZE; j++) {
            graph->adjMat[i][j]=0;
        }
    }
    return graph;
}

void delGraphAdjMat(GraphAdjMat * graph) {
    free(graph);
}

void addVertex(GraphAdjMat * graph, int val) {
    if (graph->size == MAX_SIZE) {
        fprintf(stderr, "Maximum node\n");
        return;
    }
    int n = graph->size;
    graph->vertices[n] = val;
    for (int i=0; i<=n; i++) {
        graph->adjMat[i][n] = graph->adjMat[n][i] = 0;
    } 
    graph->size++;
}

void removeVertex(GraphAdjMat * graph, int index) {
    if (index<0 || index>=graph->size) {
        fprintf(stderr, "Error index node");
        return;
    }

    for (int i=index; i<graph->size; i++) {
        graph->vertices[i] = graph->vertices[i+1];
    }

    for (int i=index; i<graph->size; i++) {
        for (int j=0; j<index; j++) {
            graph->adjMat[i][j] = graph->adjMat[i+1][j];
        }
    }

    for (int i=0; i<graph->size; i++) {
        for (int j=index; j<graph->size-1; j++) {
            graph->adjMat[i][j] = graph->adjMat[i][j+1];
        }
    }
    graph->size--;
}

void addEdge(GraphAdjMat * graph, int i, int j) {
    graph->adjMat[i][j] = 1;
    graph->adjMat[j][i] = 1;
}

void removeEdge(GraphAdjMat * graph, int i, int j) {
    graph->adjMat[i][j] = 0;
    graph->adjMat[j][i] = 0;
}



