// https://www.enjoyalgorithms.com/blog/min-stack-problem/

#include <iostream>
#include <stack>
#include <climits>

using namespace std;
class MinStack {
public: 
    MinStack(): mStack{} {}
    ~MinStack() {}

    void push(int x) {
        int minimum;
        if(mStack.empty()) {
            minimum = x;
        }
        else {
            minimum = min(mStack.top().second, x);
        }
        mStack.push({x, minimum});
    }

    void pop() {
        mStack.pop();
    }

    int top() {
        return mStack.top().first;
    }

    int getMin() const {
        return mStack.top().second;
    }

private:
    std::stack<std::pair<int, int>> mStack;
};

int main() {
    MinStack minStack;
    minStack.push(15);
    minStack.push(-1);
    minStack.push(-10);

    std::cout << "current minimum:" << minStack.getMin() << "\n";
    minStack.pop();
    minStack.push(10);
    minStack.push(-5);
    minStack.push(-20);
    minStack.push(100);
    std::cout << "current minimum:" << minStack.getMin() << "\n";
    minStack.pop();
    std::cout << "current minimum:" << minStack.getMin() << "\n";
    minStack.pop();
    std::cout << "current minimum:" << minStack.getMin() << "\n";
}     