#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 1000000

typedef struct {
    int *data;
    int size;
} ArrayStack;

ArrayStack * newArrayStack() {
    ArrayStack * stack = (ArrayStack *)malloc(sizeof(ArrayStack));
    stack->data = malloc(sizeof(int) * MAX_SIZE);
    stack->size = 0;
    return stack;
}

void delArrayStack(ArrayStack *s) {
    free(s->data);
    free(s);
}

int size(ArrayStack *s) {
    return s->size;
}

bool isEmpty(ArrayStack *s) {
    return s->size == 0;
}

void push(ArrayStack *stack, int num) {
    if (stack->size==MAX_SIZE) {
        printf("Stack is fulled.\n");
        return;
    }
    stack->data[stack->size] = num;
    stack->size++;
}

int peek(ArrayStack * stack) {
    if (stack->size==0) {
        printf("Empty Stack.\n");
        return INT_MAX;
    }
    return stack->data[stack->size - 1];
}

int pop(ArrayStack * stack) {
    int val = peek(stack);
    stack->size--;
    return val;
}

