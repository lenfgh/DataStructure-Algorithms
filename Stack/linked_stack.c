#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct ListNode {
    int val;
    ListNode * next;
} ListNode;

typedef struct {
    ListNode * top;
    int size;
} LinkedListStack;

LinkedListStack * newLinkedListStack() {
    LinkedListStack * s = malloc(sizeof(LinkedListStack));
    s->top = NULL;
    s->size = 0;
    return s;
}

void delLinkedListStack(LinkedListStack * s) {
    while (s->top) {
        ListNode *n = s->top->next;
        free(s->top);
        s->top = n;
    }
    free(s);
}


int size(LinkedListStack *s) {
    return s->size;
}

bool isEmpty(LinkedListStack *s) {
    return s->size == 0;
}

void push(LinkedListStack *s, int num) {
    ListNode * n = (ListNode *)malloc(sizeof(ListNode));
    n->next = s->top;
    n->val = num;
    s->top = n;
    s->size++;
}

int peek(LinkedListStack *s) {
    if (s->size==0) {
        printf("Empty Stack\n");
        return 9999999;
    }
    return s->top->val;
} 

int pop(LinkedListStack *s) {
    int val = peek(s);
    LinkedListStack * tmp = s->top;
    s->top = s->top->next;
    free(tmp);
    s->size--;
    return val;
}



