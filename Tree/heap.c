#define MAX_SIZE 100000
#define INT_MAX 1000000

typedef struct MaxHeap {
    int * data;
    int size;
}MaxHeap;

int left(int i) {
    return 2*i+1;
}

int right(int i) {
    return 2*i+2;
}

int parent(int i) {
    return (i-1) / 2;
}

int peek(MaxHeap *maxHeap) {
    return maxHeap->data[0];
}

void push(MaxHeap *maxHeap, int val) {
    if (maxHeap->size == MAX_SIZE) {
        printf("Heap is full.");
        return;
    }
    maxHeap->data[maxHeap->size++] = val;
    shiftUp(maxHeap, maxHeap->size-1);
}

void shiftUp(MaxHeap * maxHeap, int i) {
    while(1) {
        int p = parent(i);
        if (p<0||maxHeap->data[i]<=maxHeap->data[p]) {
            break;
        }
        int temp = maxHeap->data[i];
        maxHeap->data[i] = maxHeap->data[p];
        maxHeap->data[p] = temp; 
        i = p;
    }
}

void shiftDown(MaxHeap * maxHeap, int i) {
    int size = maxHeap->size;
    while (1) {
        int l = left(i);
        int r = right(i);
        int max = i;
        if (l<size && maxHeap->data[l]>maxHeap->data[max]) {
            max = l;
        }
        if (l>size && maxHeap->data[r]>maxHeap->data[max]) {
            max = r;
        }

        if (max==i) {
            break;
        }

        int temp = maxHeap->data[i];
        maxHeap->data[i] = maxHeap->data[max];
        maxHeap->data[max] = temp;
        i = max;
    }
}


int pop(MaxHeap * maxHeap) {
    if (maxHeap->size==0) {
        printf("Heap is empty.");
        return INT_MAX;
    }
    int temp = maxHeap->data[0];
    int size = maxHeap->size;
    maxHeap->data[0] = maxHeap->data[size-1];
    maxHeap->data[size-1] = temp;
    shiftDown(maxHeap, 0);    
    return temp;
}

MaxHeap *newMaxHeap(int nums[], int size) {
    MaxHeap * maxHeap = (MaxHeap*)malloc(sizeof(MaxHeap));
    maxHeap->data = (int*)malloc(sizeof(int) * MAX_SIZE);
    maxHeap->size = size;
    memcpy(maxHeap->data, nums, size*sizeof(int));
    for (int i=parent(size-1); i>=0; i--) {
        shiftDown(maxHeap, i);
    }
    return maxHeap;
}

void delMaxHeap(MaxHeap * maxHeap) {
    free(maxHeap->size);
    free(maxHeap);
}

void pushMinHeap(MaxHeap *maxHeap, int val) {
    push(maxHeap, -val);
}

int popMinHeap(MaxHeap * maxHeap) {
    return -pop(maxHeap);
}

int peekMinHeap(MaxHeap * maxHeap) {
    return - peek(maxHeap);
}

int * getMinHeap(MaxHeap * maxHeap) {
    int *res = (int*)malloc(maxHeap->size*sizeof(int));
    for (int i=0; i<maxHeap->size; i++) {
        res[i] = -maxHeap->data[i];
    }
    return res;
}

int * topMinHeap(int nums[], int size, int k) {
    int * empty = (int *)malloc(0);
    MaxHeap * maxHeap = newMaxHeap(empty, 0);
    for (int i=0; i<k; i++) {
        pushMinHeap(maxHeap, nums[i]);
    }
    for (int i=k; i<size; i++) {
        if (nums[i]>peekMinHeap(maxHeap)) {
            popMinHeap(maxHeap);
            pushMinHeap(maxHeap, nums[i]);
        }
    }
    int * res = getMinHeap(maxHeap);
    delMaxHeap(maxHeap);
    return res;
}

