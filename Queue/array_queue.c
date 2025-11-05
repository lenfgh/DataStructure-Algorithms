#include<stdlib.h>
#include<stdbool.h>

typedef struct {
    int *nums;
    int front;
    int queSize;
    int queCapacity;
}ArrayQueue;


ArrayQueue *newArrayQueue(int capacity) {
    ArrayQueue * queue = (ArrayQueue *)malloc(sizeof(ArrayQueue));
    queue->queCapacity = capacity;
    queue->nums = (int *)malloc(sizeof(int) * capacity);
    queue->front = queue->queSize = 0;
    return queue;
} 

void delArrayQueue(ArrayQueue *queue) {
    free(queue->nums);
    free(queue);
}

int capacity(ArrayQueue * queue) {
    return queue->queCapacity;
}

int size(ArrayQueue * queue) {
    return queue->queSize;
}

bool empty(ArrayQueue * queue) {
    return queue->queSize == 0;
}

int peek(ArrayQueue * queue) {
    assert(size(queue) != 0);
    return queue->nums[queue->front];
}

void push(ArrayQueue * queue, int num) {
    if (size(queue) == capacity(queue)) {
        printf("Queue is full");
        return;
    }
    int rear = (queue->front + queue->queSize) % queue->queCapacity;
    queue->nums[rear] = num;
    queue->queSize++;
}

int pop(ArrayQueue * queue) {
    int num = peek(queue);
    queue->front = (queue->front + 1) % queue->queCapacity;
    queue->queSize--;
    return num;
}


