#include<stdlib.h>
#include<stdbool.h>

typedef struct {
    ListNode * next;
    int val;
} ListNode;

typedef struct {
    ListNode *front, *rear;
    int queSize;
} LinkedListQueue;

LinkedListQueue *newLinkedListQueue() {
    LinkedListQueue * queue = (LinkedListQueue *)malloc(sizeof(LinkedListQueue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->queSize = 0;
    return queue;
}

void delLinkedListQueue(LinkedListQueue *queue) {
    while (queue->front != NULL) {
        ListNode * tmp = queue->front;
        queue->front = queue->front->next;
        free(tmp);
    }
    free(queue);
}

int size(LinkedListQueue * queue) {
    return queue->queSize;
}

bool empty(LinkedListQueue * queue) {
    return size(queue) == 0;
}

void push(LinkedListQueue * queue, int num) {
    ListNode * n = (ListNode *)malloc(sizeof(ListNode));
    n->val = num;
    n->next = NULL;
    if (empty(queue)) {
        queue->front->next = n;
        queue->rear = n;
    } else {
        queue->rear->next = n;
        queue->rear = n;
    }
    queue->queSize++;
}

int peek(LinkedListQueue *queue) {
    assert(size(queue) && queue->front);
    return queue->front->next->val;
}

int pop(LinkedListQueue *queue) {
    int num = peek(queue);
    ListNode * tmp = queue->front->next;
    queue->front->next = tmp->next;
    free(tmp);
    queue->queSize--;
    return num;
}


void printLinkedListQueue(LinkedListQueue *queue) {
    int *arr = malloc(sizeof(int) * queue->queSize);

    int i;
    ListNode *node;
    for (i = 0, node = queue->front; i < queue->queSize; i++) {
        arr[i] = node->val;
        node = node->next;
    }
    printArray(arr, queue->queSize);
    free(arr);
}
