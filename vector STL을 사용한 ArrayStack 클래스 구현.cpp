#include <iostream>
#include <vector>

using namespace std;

class ArrayStack {
private:
    vector<int> theArray;
    int topOfStack;

public:
    ArrayStack() : topOfStack(-1) {}

    void push(int x) {
        theArray.push_back(x);
        topOfStack++;
    }

    void pop() {
        if (isEmpty())
            throw "Stack is empty";
        theArray.pop_back();
        topOfStack--;
    }

    int top() {
        if (isEmpty())
            throw "Stack is empty";
        return theArray[topOfStack];
    }

    bool isEmpty() {
        return topOfStack == -1;
    }
};