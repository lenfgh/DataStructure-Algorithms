#include<stack>
#include<vector>
using namespace std;

stack<int> s; // renamed variable to avoid ambiguity with the type name

typedef struct ListNode {
    ListNode * next;
    int val;
    ListNode(int x) : val(x), next(NULL) {}
};

class LinkedListStack {
private:
    ListNode * stackTop;
    int stkSize;

public:
    LinkedListStack() {
        stackTop = NULL;
        stkSize = 0;
    }

    ~LinkedListStack() {
        freeMemoryLinkedList(stackTop);
    }

    int size() {
        return stkSize;
    }

    bool isEmpty() {
        return size() == 0;
    }

    void push(int num) {
        ListNode * node = new ListNode(num);
        node->next = stackTop;
        stackTop = node;
        stkSize++;
    }

    int pop() {
        int num = top();
        ListNode * tmp = stackTop;
        stackTop = stackTop->next;
        delete tmp;
        stkSize--;
        return num;
    }

    int top() {
        if (isEmpty())
            __throw_out_of_range("Empty Stack");
        return stackTop->val;
    }

    vector<int> toVector() {
        ListNode * node = stackTop;
        vector<int> res(size());
        for (int i = res.size()-1; i>=0; i--) {
            res[i] = node->val;
            node = node->next;
        }
        return res;
    }
};


int main() {
	// Push an element into the stack
	s.push(1);

	// Return the top of the stack
	int topElement = s.top();

    // Get the size of the stack
    int size = s.size();

    // Justify whether the stack is empty
    bool empty = s.empty();

	return 0;
}