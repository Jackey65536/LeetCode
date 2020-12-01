#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <cstring>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>

void test_stack() {
    std::stack<int> s;
    if (s.empty()) {
        printf("s is empty\n");
    }
    s.push(5);
    s.push(6);
    s.push(10);
    printf("s.top = %d\n", s.top());
    s.pop();
    s.pop();
    printf("s.top = %d\n", s.top());
    printf("s.size = %lu\n", s.size());
}

void test_queue() {
    std::queue<int> q;
    if (q.empty()) {
        printf("q is empty!\n");
    }
    q.push(5);
    q.push(6);
    q.push(10);
    printf("q.front = %d\n", q.front());
    q.pop();
    q.pop();
    printf("q.front = %d\n", q.front());
    q.push(1);
    printf("q.back = %d\n", q.back());
    printf("q.size = %lu\n", q.size());
}

class MyStack {
   public:
    MyStack() {}
    void push(int x) {
        std::queue<int> temp_queue;
        temp_queue.push(x);
        while (!_data.empty()) {
            temp_queue.push(_data.front());
            _data.pop();
        }
        while (!temp_queue.empty()) {
            _data.push(temp_queue.front());
            temp_queue.pop();
        }
    }
    int pop() {
        int x = _data.front();
        _data.pop();
        return x;
    }
    int top() { return _data.front(); }
    bool empty() { return _data.empty(); }

   private:
    std::queue<int> _data;
};

void test_mystack() {
    MyStack ms;
    ms.push(1);
    ms.push(2);
    ms.push(3);
    while (!ms.empty()) {
        int x = ms.pop();
        printf("x = %d\n", x);
    }
}

class MyQueue {
   public:
    MyQueue() {}
    void push(int x) {
        std::stack<int> temp_stack;
        while (!_data.empty()) {
            temp_stack.push(_data.top());
            _data.pop();
        }
        temp_stack.push(x);
        while (!temp_stack.empty()) {
            _data.push(temp_stack.top());
            temp_stack.pop();
        }
    }
    int pop() {
        int x = _data.top();
        _data.pop();
        return x;
    }
    int peek() { return _data.top(); }
    bool empty() { return _data.empty(); }

   private:
    std::stack<int> _data;
};

void test_myqueue() {
    MyQueue mq;
    mq.push(1);
    mq.push(2);
    mq.push(3);
    while (!mq.empty()) {
        printf("x = %d\n", mq.pop());
    }
}

class MinStack {
   public:
    MinStack() {}
    void push(int x) {
        _data.push(x);
        if (_min.empty()) {
            _min.push(x);
        } else {
            if (x > _min.top()) {
                x = _min.top();
            }
            _min.push(x);
        }
    }
    void pop() {
        _data.pop();
        _min.pop();
    }
    int top() { return _data.top(); }
    int getMin() { return _min.top(); }

   private:
    std::stack<int> _data;  // 数据栈
    std::stack<int> _min;   // 最小值栈
};

void test_minstack() {
    MinStack ms;
    ms.push(0);
    printf("top = %d, min = %d\n", ms.top(), ms.getMin());
    ms.push(5);
    printf("top = %d, min = %d\n", ms.top(), ms.getMin());
    ms.push(1);
    printf("top = %d, min = %d\n", ms.top(), ms.getMin());
    ms.push(-2);
    printf("top = %d, min = %d\n", ms.top(), ms.getMin());
    ms.push(-4);
    printf("top = %d, min = %d\n", ms.top(), ms.getMin());
}

bool check_is_valid_order(std::queue<int>& order) {
    std::stack<int> s;
    int n = order.size();
    for (size_t i = 1; i <= n; i++) {
        s.push(i);
        while (!s.empty() && order.front() == s.top()) {
            s.pop();
            order.pop();
        }
    }
    if (!s.empty()) {
        return false;
    }
    return true;
}

void test1() {
    int n;
    int train;
    scanf("%d", &n);
    while (n) {
        scanf("%d", &train);
        while (train) {
            std::queue<int> order;
            order.push(train);
            for (size_t i = 1; i < n; i++) {
                scanf("%d", &train);
                order.push(train);
            }
            if (check_is_valid_order(order)) {
                printf("Yes\n");
            } else {
                printf("No\n");
            }
            scanf("%d", &train);
        }
        printf("\n");
        scanf("%d", &n);
    }
}

void test_heap() {
    std::priority_queue<int> big_heap;
    std::priority_queue<int, std::vector<int>, std::greater<int> > small_heap;
    std::priority_queue<int, std::vector<int>, std::less<int> > big_heap2;
    if (big_heap.empty()) {
        printf("big_heap is empty!\n");
    }
    int test[] = {6, 10, 1, 7, 99, 4, 33};
    for (size_t i = 0; i < 7; i++) {
        big_heap.push(test[i]);
    }
    printf("big_heap.top = %d\n", big_heap.top());
    big_heap.push(1000);
    printf("big_heap.top = %d\n", big_heap.top());
    for (size_t i = 0; i < 3; i++) {
        big_heap.pop();
    }
    printf("big_heap.top = %d\n", big_heap.top());
    printf("big_heap.size = %lu\n", big_heap.size());
}

void compute(std::stack<int>& number_statck,
             std::stack<char>& operation_stack) {
    if (number_statck.size() < 2) {
        return;
    }
    int num2 = number_statck.top();
    number_statck.pop();
    int num1 = number_statck.top();
    number_statck.pop();
    if (operation_stack.top() == '+') {
        number_statck.push(num1 + num2);
    } else if (operation_stack.top() == '-') {
        number_statck.push(num1 - num2);
    }
    operation_stack.pop();
}

class Solution {
   public:
    // 计算器
    int calculate(std::string s) {
        static const int STATE_BEGIN = 0;
        static const int NUMBER_STATE = 1;
        static const int OPERATION_STATE = 2;
        std::stack<int> number_stack;
        std::stack<char> operation_stack;
        int number = 0;
        int STATE = STATE_BEGIN;
        // 是否要计算
        int compute_flag = 0;
        for (size_t i = 0; i < s.length(); i++) {
            if (s[i] == ' ') {
                continue;
            }
            switch (STATE) {
                case STATE_BEGIN:
                    if (s[i] >= '0' && s[i] <= '9') {
                        STATE = NUMBER_STATE;
                    } else {
                        STATE = OPERATION_STATE;
                    }
                    i--;
                    break;
                case NUMBER_STATE:
                    if (s[i] >= '0' && s[i] <= '9') {
                        number = number * 10 + s[i] - '0';
                    } else {
                        number_stack.push(number);
                        if (compute_flag == 1) {
                            compute(number_stack, operation_stack);
                        }
                        number = 0;
                        i--;
                        STATE = OPERATION_STATE;
                    }
                    break;
                case OPERATION_STATE:
                    if (s[i] == '+' || s[i] == '-') {
                        operation_stack.push(s[i]);
                        compute_flag = 1;
                    } else if (s[i] == '(') {
                        STATE = NUMBER_STATE;
                        compute_flag = 0;
                    } else if (s[i] >= '0' && s[i] <= '9') {
                        STATE = NUMBER_STATE;
                        i--;
                    } else if (s[i] == ')') {
                        compute(number_stack, operation_stack);
                    }
                    break;
            }
        }
        if (number != 0) {
            number_stack.push(number);
            compute(number_stack, operation_stack);
        }
        if (number == 0 && number_stack.empty()) {
            return 0;
        }
        return number_stack.top();
    }

    // 查找第K大的数
    int findKthLargest(std::vector<int>& nums, int k) {
        std::priority_queue<int, std::vector<int>, std::greater<int> > q;
        for (size_t i = 0; i < nums.size(); i++) {
            if (q.size() < k) {
                q.push(nums[i]);
            } else if (q.top() < nums[i]) {
                q.pop();
                q.push(nums[i]);
            }
        }
        return q.top();
    }

    // 查找中位数（动态维护一个最大堆与一个最小堆，最大堆存储一半数据，最小堆存储一半数据，维持最大堆的堆顶比最小堆的堆顶小）
    double findMedian(std::vector<int>& nums) {
        std::priority_queue<int, std::vector<int>, std::less<int> > big_heap;
        std::priority_queue<int, std::vector<int>, std::greater<int> >
            small_heap;
        for (size_t i = 0; i < nums.size(); i++) {
            int k = nums[i];
            if (big_heap.empty()) {
                big_heap.push(k);
                continue;
            }
            if (big_heap.size() == small_heap.size()) {
                if (k < big_heap.top()) {
                    big_heap.push(k);
                } else {
                    small_heap.push(k);
                }
            } else if (big_heap.size() > small_heap.size()) {
                if (k > big_heap.top()) {
                    small_heap.push(k);
                } else {
                    small_heap.push(big_heap.top());
                    big_heap.pop();
                    big_heap.push(k);
                }
            } else if (big_heap.size() < small_heap.size()) {
                if (k < small_heap.top()) {
                    big_heap.push(k);
                } else {
                    big_heap.push(small_heap.top());
                    small_heap.pop();
                    small_heap.push(k);
                }
            }
        }
        printf("big_heap.size = %lu, big_heap.top = %d\n", big_heap.size(),
               big_heap.top());
        printf("small_heap.size = %lu, small_heap.top = %d\n",
               small_heap.size(), small_heap.top());
        if (big_heap.size() == small_heap.size()) {
            return (big_heap.top() + small_heap.top()) / 2.0;
        } else if (big_heap.size() > small_heap.size()) {
            return big_heap.top();
        } else {
            return small_heap.top();
        }
    }
};

int main() {
    std::string s = "1+121 - (14+(5-6) )";
    Solution solve;
    printf("%d\n\n", solve.calculate(s));
    test_heap();
    printf("\n");
    int test[] = {6, 10, 1, 7, 99, 4, 33};
    std::vector<int> nums;
    for (size_t i = 0; i < 7; i++) {
        nums.push_back(test[i]);
    }
    double m = solve.findMedian(nums);
    printf("find median num = %f", m);

    return 0;
}