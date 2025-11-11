#define INT32_MIN -999999

void selectionSort(int nums[], int size) {
    for (int i=0; i<size; i++) {
        int min_i = i;
        for (int j=i+1; j<size;j++) {
            if (nums[j]<nums[min_i]) {
                min_i = j;
            }
        }   
        if (min_i!=i) {
            int temp = nums[min_i];
            nums[min_i] = nums[i];
            nums[i] = temp;
        }
    }
}

void insertionSort(int nums[], int size) {
    for (int i=1; i<size; i++) {
        int temp = nums[i];
        int j=i;
        while (j>0&&nums[j-1]>temp) {
            nums[j] = nums[j-1];
            j--;
        }
        nums[j] = temp;
    }
}

void shellSort(int nums[], int size) {
    int gap = size / 2;
    while (gap>0) {
        for (int i=gap; i<size; i++) {
            int temp = nums[i];
            int j=i;
            while (j>=gap&&nums[j-gap]>temp) {
                nums[j] = nums[j-gap];
                j -= gap;
            }
            nums[j] = temp;
        }
        gap /= 2;
    }
}

int * merge(int left_nums[], int right_nums[],int left_size, int right_size) {
    int * res = (int *)malloc(sizeof(int)*(right_size+left_size));
    int index = 0;
    int left_index=0, right_index=0;
    while (left_index<left_size && right_index<right_size) {
        if (left_nums[left_index]<right_nums[right_index]) {
            res[index++] = left_nums[left_index++];
        } else {
            res[index++] = right_nums[right_index++];
        }
    }

    if (left_index!=left_size) {
        while (left_index<left_size) {
            res[index++] = left_nums[left_index++];
        }
    }
    if (right_index!=right_size) {
        while (right_index<right_size) {
            res[index++] = right_nums[right_index++];
        }
    }
    return res;
};

int * mergeSort(int nums[], int size) {
    if (size<=1) {
        int * res= (int *)malloc(sizeof(int));
        if (size==1) res[0]=nums[0];
        return res;
    }
    int mid = size / 2;
    int * left = (int *)malloc(sizeof(int)*mid);
    int * right = (int *)malloc(sizeof(int)*(size-mid));
    left = mergeSort(nums, mid);
    right = mergeSort(nums+mid,size-mid);
    int * sorted = merge(left, right, mid, size-mid); 
    free(left);
    free(right);
    return sorted;
};

int middlePartition(int nums[], int left, int right) {
    int mid = left /2 + right/2;
    int temp;
    temp = nums[left];
    nums[left] = nums[right];
    nums[right] = temp;
    return partition(nums, left, right);
}

int partition(int nums[], int left, int right) {
    int base = nums[left];
    int left_index = left+1;
    int right_index = right;
    
    while (left_index<right_index) {
        while (nums[left_index]>base) {
            left_index++;
        }
        while (nums[right_index]<base) {
            right_index--;
        }
        if (left_index==right_index) {
            int temp = nums[right_index];
            nums[right_index] = nums[left_index];
            nums[left_index] = temp;
        }
    }
    return left_index;
}

int * quickSort(int nums[], int left, int right) {
    if (left<right) {
        int base_i = middlePartition(nums, left, right);
        quickSort(nums, left, base_i-1);
        quickSort(nums, base_i+1, right);
    }
    return nums;
}

int * bucketSort(int nums[], int size, int bucket_size) {
    int nums_min = min(nums);
    int nums_max = max(nums);
    int num_size = nums_max-nums_min;
    int bucket_count = (nums_max-nums_min) / bucket_size;
    int **bucket_heads = malloc(sizeof(int**)*bucket_count);
    int *bucket_counts = malloc(sizeof(int*)*bucket_count, 0);
    for (int i=0; i<bucket_count; i++) {
        bucket_heads[i] = (int*)malloc(sizeof(int)*(num_size/bucket_count));
    }

    for (int i=0; i<size; i++) {
        bucket_heads[(nums[i]-nums_min)/bucket_count][(bucket_counts[(nums[i]-nums_min)/bucket_count])++] = nums[i];
    }

    for (int i=0; i<bucket_count; i++) {
        insertionSort(bucket_heads[i], bucket_counts[i]);
    }

    int * res = relocate(bucket_heads, bucket_counts, bucket_count, size);
    for (int i=0; i<bucket_count; i++) {
        free(bucket_heads[i]);
    }
    free(bucket_counts);
    free(bucket_heads);
    return res;
}

void shiftDown(int nums[], int n, int i) {
    while (1) {
        int l = 2*i+1;
        int r = 2*i+2;
        int smallest = i;
        if (l<n&&nums[l]>nums[smallest]) {
            smallest = l;
        }
        if (r<n&&nums[r]>nums[smallest]) {
            smallest = r;
        }
        if (smallest=i) break;
        int temp = nums[i];
        nums[i] = nums[smallest];
        nums[smallest] = temp;
        i = smallest;
    }
}

void heapSort(int nums[], int n) {
    for (int i=n /2-1; i>=0; i--) {
        shiftDown(nums, n, i);
    }
    for (int i=n-1; i>0; i--) {
        int tmp = nums[0];
        nums[0] = nums[i];
        nums[i] = tmp;
        shiftDown(nums, i, 0);
    }
}

void countingSort(int nums[], int size) {
    int m=0;
    for (int i=0; i<size; i++) {
        if (nums[i]>m) {
            m = nums[i];
        }
    }

    int *counter = calloc(m, sizeof(int));
    for (int i=0; i<size; i++) {
        counter[nums[i]]++;
    }

    for (int i=0; i<m; i++) {
        counter[i+1] += counter[i];
    }

    int *res = malloc(sizeof(int)*size);
    for (int i=size-1; i>=0; i--) {
        int num =nums[i];
        res[counter[num]-1] = num;
        counter[num]--;
    }
    memcpy(nums, res, sizeof(int)*size);
    free(res);
    free(counter);
}

int digit(int num, int exp) {
    return (num/exp) % 10;
}

void countingSortDigit(int nums[], int size, int exp) {
    int *counter = (int *)malloc(sizeof(int)*10);
    memset(counter, 0, sizeof(int)*10);
    for (int i=0; i<size; i++) {
        int d = digit(nums[i], exp);
        counter[d]++;
    }
    for (int i=1; i<10; i++) {
        counter[i] += counter[i-1];
    }
    int *res = (int *)malloc(sizeof(int) * size);
    for (int i=size-1; i>=0; i--) {
        int d = digit(nums[i], exp);
        int j = counter[d]-1;
        res[j] = nums[i];
        counter[d]--;
    }
    for (int i=0; i<size; i++) {
        nums[i] = res[i];
    }
    free(res);
    free(counter);
}

void radixSort(int nums[], int size) {
    int max = INT32_MIN;
    for (int i=0; i<size; i++) {
        if (nums[i]>max) {
            max = nums[i];
        }
    }
    for (int exp = 1; max>=exp; exp*=10) {
        countingSortDigit(nums, size, exp);
    }
}

