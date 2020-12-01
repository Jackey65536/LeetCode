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

int strtoi(const char* s) {
    int num = 0;
    for (size_t i = 0; i < strlen(s); i++) {
        num = num * 10 + s[i] - '0';
    }
    return num;
}

void itostr(int num, std::string& str) {
    std::string tmp;
    while (num) {
        tmp += num % 10 + '0';
        num = num / 10;
    }
    for (int i = tmp.length() - 1; i >= 0; i--) {
        str += tmp[i];
    }
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

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

// Binary Tree
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void preorder_print1(TreeNode* node, int layer) {
    if (!node) {
        return;
    }
    for (size_t i = 0; i < layer; i++) {
        printf("-----");
    }
    printf("[%d]\n", node->val);
    preorder_print1(node->left, layer + 1);
    preorder_print1(node->right, layer + 1);
}
void preorder_print2(TreeNode* node, int layer) {
    if (!node) {
        return;
    }
    preorder_print2(node->left, layer + 1);
    for (size_t i = 0; i < layer; i++) {
        printf("-----");
    }
    printf("[%d]\n", node->val);
    preorder_print2(node->right, layer + 1);
}
void preorder_print3(TreeNode* node, int layer) {
    if (!node) {
        return;
    }
    preorder_print3(node->left, layer + 1);
    preorder_print3(node->right, layer + 1);
    for (size_t i = 0; i < layer; i++) {
        printf("-----");
    }
    printf("[%d]\n", node->val);
}

/**
 * 图（Graph）是由定点的有穷非空集合和顶点之间边的集合组成，通常表示为：G(V,E)，
 * 其中，G表示一个图，V是图G中顶点的集合，E是图G中边的集合。
 * 图分无向图与有向图，根据图的边长，又分带权图与不带权图。
 */
void createGraph() {
    // 邻接矩阵
    const int n = 5;
    int graph[n][n] = {0};
    graph[0][2] = 1;
    graph[0][4] = 1;
    graph[1][0] = 1;
    graph[1][2] = 1;
    graph[2][3] = 1;
    graph[3][4] = 1;
    graph[4][4] = 1;
    printf("graph:\n");
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            printf("%2d", graph[i][j]);
        }
        printf("\n");
    }
}

/**
 * 图的邻接表
 */
struct GraphNode {
    int label;
    std::vector<GraphNode*> neighbors;
    GraphNode(int x) : label(x){};
};

struct BSTNode {
    int val;
    int count;  // 记录左子树节点个数
    BSTNode* left;
    BSTNode* right;
    BSTNode(int x) : val(x), left(NULL), right(NULL), count(0) {}
};

bool cmp(const ListNode* a, const ListNode* b) { return a->val < b->val; }
bool cmp2(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return a.first < b.first;
}
bool cmp3(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return a.first > b.first;
}

int g_hash_map[1048576] = {0};  // 哈希太大了，需要全局数组
std::string change_int_to_DNA(int DNA) {
    char DNA_CHAR[] = {'A', 'C', 'G', 'T'};
    std::string str;
    for (int i = 0; i < 10; i++) {
        str += DNA_CHAR[DNA & 3];  // DNA % 4
        DNA = DNA >> 2;            // DNA / 4
    }
    return str;
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

    // 链表逆序
    ListNode* reverseList(ListNode* head) {
        ListNode* newhead = NULL;
        while (head) {
            ListNode* next = head->next;
            head->next = newhead;
            newhead = head;
            head = next;
        }
        return newhead;
    }

    ListNode* reverseBetween(ListNode* head, int m, int n) {
        int change_len = n - m + 1;  // 计算需要逆置的节点个数
        ListNode* pre_head = NULL;   // 初始化开始逆置的节点的前驱
        ListNode* result = head;  // 最终转换后的链表头节点，非特殊情况即为head
        while (head && --m)  // 将head向前移动 m-1 个位置
        {
            pre_head = head;  // 记录head的前驱
            head = head->next;
        }
        // 将 modify_list_tail 指向当前的head，即逆置后的链表尾
        ListNode* modify_list_tail = head;
        ListNode* new_head = NULL;
        while (head && change_len) {
            ListNode* next = head->next;
            head->next = new_head;
            new_head = head;
            head = next;
            // 每完成一个节点逆置，change_len--
            change_len--;
        }
        modify_list_tail->next =
            head;  // 连接逆置后的链表尾与逆置段的后一个节点
        if (pre_head)  // 如果pre_head不空，说明不是从第一个节点开始逆置的 m > 1
        {
            pre_head->next =
                new_head;  // 将逆置链表开始的节点前驱与逆置后的头节点连接
        } else {
            result =
                new_head;  // 如果pre_head为null，说明m==1从第一个节点开始逆置，结果即为逆置后的头结点
        }
        return result;
    }

    // 遍历链表，计算链表长度
    int get_list_length(ListNode* head) {
        int len = 0;
        while (head) {
            len++;
            head = head->next;
        }
        return len;
    }
    ListNode* forward_long_list(int long_len, int short_len, ListNode* head) {
        int delta = long_len - short_len;
        while (head && delta) {
            head = head->next;
            delta--;
        }
        return head;
    }
    // 求两个链表的交点
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        int len_a = get_list_length(headA);
        int len_b = get_list_length(headB);
        if (len_a > len_b) {
            headA = forward_long_list(len_a, len_b, headA);
        } else {
            headB = forward_long_list(len_b, len_a, headB);
        }
        while (headA && headB) {
            if (headA == headB) {
                return headA;
            }
            headA = headA->next;
            headB = headB->next;
        }
        return NULL;
    }

    // 求环起始节点(快慢指针)
    ListNode* detectCycle(ListNode* head) {
        ListNode* fast = head;  // 快指针
        ListNode* slow = head;  // 慢指针
        ListNode* meet = NULL;  // 相遇节点
        while (fast) {
            // slow与fast先各走一步
            slow = slow->next;
            fast = fast->next;
            if (!fast) {
                return NULL;
            }
            fast = fast->next;  // 快指针多走一步
            if (fast == slow) {
                meet = fast;
                break;
            }
        }
        if (meet == NULL) {
            return NULL;
        }
        while (head && meet) {
            if (head == meet) {
                return head;
            }
            head = head->next;
            meet = meet->next;
        }
        return NULL;
    }
    ListNode* detectCycle_set(ListNode* head) {
        std::set<ListNode*> node_set;
        while (head) {
            if (node_set.find(head) != node_set.end()) {
                return head;
            }
            node_set.insert(head);
            head = head->next;
        }
        return NULL;
    }

    // 链表划分
    ListNode* partition(ListNode* head, int x) {
        // 设置两个临时的头结点
        ListNode less_head(0);
        ListNode more_head(0);
        // 对应指针指向这两个头结点
        ListNode* less_ptr = &less_head;
        ListNode* more_ptr = &more_head;
        while (head) {
            // 如果节点值小于x，则将该节点插入less_ptr后
            if (head->val < x) {
                less_ptr->next = head;
                less_ptr = less_ptr->next;
            } else {  // 否则将该节点插入more_ptr后
                more_ptr->next = head;
                more_ptr = more_ptr->next;
            }
            head = head->next;
        }
        // 将less链表尾，与more链表头相连
        less_ptr->next = more_head.next;
        // 将more_ptr即链表尾节点next置空
        more_ptr->next = NULL;
        return less_head.next;
    }

    // 复杂链表深拷贝
    RandomListNode* copyRandomList(RandomListNode* head) {
        std::map<RandomListNode*, int> node_map;  // 地址节点位置的map
        std::vector<RandomListNode*>
            node_vec;  // 使用vector根据存储几点位置访问地址
        RandomListNode* ptr = head;
        int i = 0;
        while (ptr) {
            node_vec.push_back(new RandomListNode(ptr->label));
            node_map[ptr] = i;
            ptr = ptr->next;
            i++;
        }
        // 新链表最后指向NULL
        node_vec.push_back(0);
        ptr = head;
        i = 0;
        while (ptr) {
            // 连接新链表next指针
            node_vec[i]->next = node_vec[i + 1];
            if (ptr->random) {
                int index = node_map[ptr->random];
                node_vec[i]->random = node_vec[index];
            }
            ptr = ptr->next;
            i++;
        }
        return node_vec[0];
    }

    // 排序链表合并
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode temp_head(0);
        ListNode* pre = &temp_head;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                pre->next = l1;
                l1 = l1->next;
            } else {
                pre->next = l2;
                l2 = l2->next;
            }
            pre = pre->next;
        }
        if (l1) {
            pre->next = l1;
        }
        if (l2) {
            pre->next = l2;
        }
        return temp_head.next;
    }
    // 排序链表合并（多个）
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        std::vector<ListNode*> node_vec;
        // 遍历k个链表，将所有节点添加至node_vec
        for (size_t i = 0; i < lists.size(); i++) {
            ListNode* head = lists[i];
            while (head) {
                node_vec.push_back(head);
                head = head->next;
            }
        }
        if (node_vec.size() == 0) {
            return NULL;
        }
        std::sort(node_vec.begin(), node_vec.end(), cmp);
        // 连接新链表
        for (size_t i = 1; i < node_vec.size(); i++) {
            node_vec[i - 1]->next = node_vec[i];
        }
        node_vec[node_vec.size() - 1]->next = NULL;
        return node_vec[0];
    }
    // 分制法
    ListNode* mergeKLists2(std::vector<ListNode*>& lists) {
        if (lists.size() == 0) {
            return NULL;
        }
        if (lists.size() == 1) {
            return lists[0];
        }
        if (lists.size() == 2) {
            return mergeTwoLists(lists[0], lists[1]);
        }
        int mid = lists.size() / 2;
        // 拆分lists为两个子list
        std::vector<ListNode*> sub1_list;
        std::vector<ListNode*> sub2_list;
        for (size_t i = 0; i < mid; i++) {
            sub1_list.push_back(lists[i]);
        }
        for (size_t i = mid; i < lists.size(); i++) {
            sub2_list.push_back(lists[i]);
        }
        ListNode* l1 = mergeKLists(sub1_list);
        ListNode* l2 = mergeKLists(sub2_list);
        // 分制处理
        return mergeTwoLists(l1, l2);
    }

    // 分糖果，返回最大满足孩子数
    int findContentChildren(std::vector<int>& g, std::vector<int>& s) {
        std::sort(g.begin(), g.end());
        std::sort(s.begin(), s.end());
        int child = 0;
        int cookie = 0;
        while (child < g.size() && cookie < s.size()) {
            if (g[child] <= s[cookie]) {
                child++;
            }
            cookie++;
        }
        return child;
    }

    // 求最大摇摆子序列长度
    int wiggleMaxLength(std::vector<int>& nums) {
        if (nums.size() < 2) {
            return nums.size();
        }
        static const int BEGIN = 0;
        static const int UP = 1;
        static const int DOWN = 2;
        int STATE = BEGIN;
        int max_length = 1;
        for (size_t i = 1; i < nums.size(); i++) {
            switch (STATE) {
                case BEGIN:
                    if (nums[i - 1] < nums[i]) {
                        STATE = UP;
                        max_length++;
                    } else if (nums[i - 1] > nums[i]) {
                        STATE = DOWN;
                        max_length++;
                    }
                    break;
                case UP:
                    if (nums[i - 1] > nums[i]) {
                        STATE = DOWN;
                        max_length++;
                    }
                    break;
                case DOWN:
                    if (nums[i - 1] < nums[i]) {
                        STATE = UP;
                        max_length++;
                    }
                    break;
            }
        }
        return max_length;
    }

    // 去掉k个数求最小数值(利用栈来使得高位数值最小)
    std::string removeKdigits(std::string num, int k) {
        std::vector<int> s;
        std::string result = "";
        for (size_t i = 0; i < num.length(); i++) {
            int number = num[i] - '0';
            while (s.size() != 0 && s.back() > number && k > 0) {
                s.pop_back();
                k--;
            }
            if (number != 0 || s.size() != 0) {
                s.push_back(number);
            }
        }
        while (s.size() != 0 && k > 0) {
            s.pop_back();
            k--;
        }
        for (size_t i = 0; i < s.size(); i++) {
            result.append(1, '0' + s[i]);
            k--;
        }
        if (result == "") {
            return "0";
        }
        return result;
    }

    // 跳跃游戏
    bool canJump(std::vector<int>& nums) {
        std::vector<int> index;  // 最远可跳至的位置
        for (size_t i = 0; i < nums.size(); i++) {
            index.push_back(i + nums[i]);
        }
        int jump = 0;
        int max_index = index[0];
        while (jump < index.size() && jump <= max_index) {
            // 如果当前可以跳的更远，则更新max_index
            if (max_index < index[jump]) {
                max_index = index[jump];
            }
            jump++;
        }
        // 如果jump到达数组尾，则返回真
        if (jump == index.size()) {
            return true;
        }
        return false;
    }
    // 最少跳跃几次
    int jump(std::vector<int>& nums) {
        if (nums.size() < 2) {
            return 0;
        }
        int current_max_index = nums[0];
        int pre_max_max_index = nums[0];
        int jump_min = 1;
        for (size_t i = 1; i < nums.size(); i++) {
            // 若无法再向前移动了，才进行跳跃
            if (i > current_max_index) {
                jump_min++;
                current_max_index = pre_max_max_index;
            }
            if (pre_max_max_index < nums[i] + i) {
                pre_max_max_index = nums[i] + i;
            }
        }
        return jump_min;
    }

    // 射击气球
    int findMinArrowShots(std::vector<std::pair<int, int> >& points) {
        if (points.size() == 0) {
            return 0;
        }
        std::sort(points.begin(), points.end(), cmp2);
        int shoot_num = 1;
        int shoot_begin = points[0].first;
        int shoot_end = points[0].second;
        for (size_t i = 0; i < points.size(); i++) {
            if (points[i].first <= shoot_end) {
                shoot_begin = points[i].first;
                if (shoot_end > points[i].second) {
                    shoot_end = points[i].second;
                }
            } else {
                shoot_num++;
                shoot_begin = points[i].first;
                shoot_end = points[i].second;
            }
        }
        return shoot_num;
    }

    // L为起点到终点的距离，P为起点初始的汽油量，stop:<加油站至终点的距离，加油站汽油量>
    int get_minimum_stop(int L, int P,
                         std::vector<std::pair<int, int> >& stop) {
        std::priority_queue<int> Q;  // 存储油量的最大堆
        int result = 0;              // 记录加过几次油的变量
        // 将终点作为一个停靠点，添加至stop数组
        stop.push_back(std::make_pair(0, 0));
        // 以停靠点至终点距离从大到小进行排序
        std::sort(stop.begin(), stop.end(), cmp3);
        for (size_t i = 0; i < stop.size(); i++) {
            int dis = L - stop[i].first;
            while (!Q.empty() && P < dis) {
                P += Q.top();
                Q.pop();
                result++;
            }
            if (Q.empty() && P < dis) {
                return -1;
            }
            P = P - dis;
            L = stop[i].first;
            Q.push(stop[i].second);
        }
        return result;
    }

    /**
     * 回溯法：当探索到某一步时，发现原先选择打不到目标，就退回一步重新选择，
     * 这种走不通就退回再走的技术就是回溯法。
     */
    void generate(int i, std::vector<int>& nums, std::vector<int>& item,
                  std::vector<std::vector<int> >& result) {
        if (i > nums.size()) {
            return;
        }
        item.push_back(nums[i]);
        result.push_back(item);
        generate(i + 1, nums, item, result);
        item.pop_back();
        generate(i + 1, nums, item, result);
    }
    // 求所有子序列
    std::vector<std::vector<int> > subsets(std::vector<int>& nums) {
        std::vector<std::vector<int> > result;  // 存储最终结果的result
        std::vector<int> item;   // 回溯时，产生各个子集的数组
        result.push_back(item);  // 将空集push进入result
        generate(0, nums, item, result);  // 计算各个子集
        return result;
    }
    // 位运算实现
    std::vector<std::vector<int> > subsets2(std::vector<int>& nums) {
        std::vector<std::vector<int> > result;
        int all_set = 1 << nums.size();
        for (size_t i = 0; i < all_set; i++) {
            std::vector<int> item;
            for (size_t j = 0; j < nums.size(); j++) {
                if (i & (1 << j)) {
                    item.push_back(nums[j]);
                }
            }
            result.push_back(item);
        }
        return result;
    }

    // 剪枝
    void generate2(int i, std::vector<int>& nums,
                   std::vector<std::vector<int> >& result,
                   std::vector<int>& item, std::set<std::vector<int> >& res_set,
                   int sum, int target) {
        if (i >= nums.size() || sum > target) {
            return;
        }
        sum += nums[i];
        item.push_back(nums[i]);
        if (target == sum && res_set.find(item) == res_set.end()) {
            result.push_back(item);
            res_set.insert(item);
        }
        generate2(i + 1, nums, result, item, res_set, sum, target);
        sum -= nums[i];
        item.pop_back();
        generate2(i + 1, nums, result, item, res_set, sum, target);
    }
    std::vector<std::vector<int> > combinationSum(std::vector<int>& candidates,
                                                  int target) {
        std::vector<std::vector<int> > result;
        std::vector<int> item;
        std::set<std::vector<int> > res_set;
        std::sort(candidates.begin(), candidates.end());
        generate2(0, candidates, result, item, res_set, 0, target);
        return result;
    }

    // 所有合法括号组合
    void generate3(std::string item, int left, int right,
                   std::vector<std::string>& result) {
        if (left == 0 && right == 0) {
            result.push_back(item);
            return;
        }
        if (left > 0) {
            generate3(item + '(', left - 1, right, result);
        }
        // 必须先放左括号，才能再放右括号
        if (left < right) {
            generate3(item + ')', left, right - 1, result);
        }
    }

    /**
     * 放置皇后，计算棋盘攻击位
     * (-1,-1)  (-1,0)  (-1,1)
     * (0,-1)   (0,0)   (0,1)
     * (1,-1)   (1,0)   (1,1)
     */
    void put_down_the_queen(int x, int y,
                            std::vector<std::vector<int> >& mark) {
        // 方向数组
        static const int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
        static const int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};
        mark[x][y] = 1;  // (x,y)放置皇后，进行标记
        // 8个方向，每个方向向外延伸1至N-1
        for (size_t i = 1; i < mark.size(); i++) {
            for (size_t j = 0; j < 8; j++) {
                int new_x = x + i * dx[j];
                int new_y = y + i * dy[j];
                if (new_x >= 0 && new_x < mark.size() && new_y >= 0 &&
                    new_y < mark.size()) {
                    mark[new_x][new_y] = 1;
                }
            }
        }
    }
    void generate4(int k, int n,  // k代表完成了几个皇后的放置
                   std::vector<std::string>& location,
                   std::vector<std::vector<std::string> >& result,
                   std::vector<std::vector<int> >& mark) {
        if (k >= n) {
            result.push_back(location);
            return;
        }

        // 按顺序尝试第0至第n-1列
        for (size_t i = 0; i < n; i++) {
            if (mark[k][i] == 0) {
                std::vector<std::vector<int> > tmp_mark = mark;
                location[k][i] = 'q';
                put_down_the_queen(k, i, mark);
                generate4(k + 1, n, location, result, mark);
                mark = tmp_mark;
                location[k][i] = '.';
            }
        }
    }
    std::vector<std::vector<std::string> > solveNQueens(int n) {
        // 存储最终结果的数组
        std::vector<std::vector<std::string> > result;
        // 标记棋盘是否可以放置皇后的二维数组
        std::vector<std::vector<int> > mark;
        // 存储某个拜访结果，当完成一次递归找到结果后，将location push进入result
        std::vector<std::string> location;
        for (size_t i = 0; i < n; i++) {
            mark.push_back((std::vector<int>()));
            for (size_t j = 0; j < n; j++) {
                mark[i].push_back(0);
            }
            location.push_back("");
            location[i].append(n, '.');
        }
        generate4(0, n, location, result, mark);
        return result;
    }
    /**
     * 分治法：将一个规模为N的问题分解为K个规模较小的子问题，这些子问题相互独立且与原问题性质相同。
     * 求出子问题的解后进行合并，就可得到原问题的解。
     */
    void merge_sort_two_vec(std::vector<int>& sub_vec1,
                            std::vector<int>& sub_vec2, std::vector<int>& vec) {
        int i = 0;
        int j = 0;
        while (i < sub_vec1.size() && j < sub_vec2.size()) {
            if (sub_vec1[i] <= sub_vec2[j]) {
                vec.push_back(sub_vec1[i]);
                i++;
            } else {
                vec.push_back(sub_vec2[j]);
                j++;
            }
        }
        for (; i < sub_vec1.size(); i++) {
            vec.push_back(sub_vec1[i]);
        }
        for (; j < sub_vec2.size(); j++) {
            vec.push_back(sub_vec2[j]);
        }
    }
    void merge_sort(std::vector<int>& vec) {
        if (vec.size() < 2) {
            return;
        }
        int mid = vec.size() / 2;
        std::vector<int> sub_vec1;
        std::vector<int> sub_vec2;
        for (size_t i = 0; i < mid; i++) {
            sub_vec1.push_back(vec[i]);
        }
        for (size_t i = mid; i < vec.size(); i++) {
            sub_vec2.push_back(vec[i]);
        }
        merge_sort(sub_vec1);
        merge_sort(sub_vec2);
        vec.clear();
        merge_sort_two_vec(sub_vec1, sub_vec2, vec);
    }

    /**
     * 求逆序数
     */
    void merge_sort_two_vec2(std::vector<std::pair<int, int> >& sub_vec1,
                             std::vector<std::pair<int, int> >& sub_vec2,
                             std::vector<std::pair<int, int> >& vec,
                             std::vector<int>& count) {
        int i = 0;
        int j = 0;
        while (i < sub_vec1.size() && j < sub_vec2.size()) {
            if (sub_vec1[i].first <= sub_vec2[j].first) {
                // 当前位置累计j前移次数
                count[sub_vec1[i].second] += j;
                vec.push_back(sub_vec1[i]);
                i++;
            } else {
                vec.push_back(sub_vec2[j]);
                j++;
            }
        }
        for (; i < sub_vec1.size(); i++) {
            count[sub_vec1[i].second] += j;
            vec.push_back(sub_vec1[i]);
        }
        for (; j < sub_vec2.size(); j++) {
            vec.push_back(sub_vec2[j]);
        }
    }
    void merge_sort2(std::vector<std::pair<int, int> >& vec,
                     std::vector<int>& count) {
        if (vec.size() < 2) {
            return;
        }
        int mid = vec.size() / 2;
        std::vector<std::pair<int, int> > sub_vec1;
        std::vector<std::pair<int, int> > sub_vec2;
        for (size_t i = 0; i < mid; i++) {
            sub_vec1.push_back(vec[i]);
        }
        for (size_t i = mid; i < vec.size(); i++) {
            sub_vec2.push_back(vec[i]);
        }
        merge_sort2(sub_vec1, count);
        merge_sort2(sub_vec2, count);
        vec.clear();
        merge_sort_two_vec2(sub_vec1, sub_vec2, vec, count);
    }
    std::vector<int> countSmaller(std::vector<int>& nums) {
        std::vector<std::pair<int, int> > vec;
        std::vector<int> count;
        for (size_t i = 0; i < nums.size(); i++) {
            vec.push_back(std::make_pair(nums[i], i));
            count.push_back(0);
        }
        merge_sort2(vec, count);
        return count;
    }

    void preorder(TreeNode* node, int& path_value, int sum,
                  std::vector<int>& path,
                  std::vector<std::vector<int> >& result) {
        if (!node) {
            return;
        }
        path_value += node->val;
        path.push_back(node->val);
        if (!node->left && !node->right && path_value == sum) {
            result.push_back(path);
        }
        preorder(node->left, path_value, sum, path, result);
        preorder(node->right, path_value, sum, path, result);
        path_value -= node->val;
        path.pop_back();
    }
    std::vector<std::vector<int> > pathSum(TreeNode* root, int sum) {
        std::vector<std::vector<int> > result;
        std::vector<int> path;
        int path_value = 0;
        preorder(root, path_value, sum, path, result);
        return result;
    }

    /**
     * 求最近的公共祖先
     */
    void preorder2(TreeNode* node, TreeNode* search,
                   std::vector<TreeNode*>& path, std::vector<TreeNode*>& result,
                   int& finish) {
        if (!node || finish) {
            return;
        }
        path.push_back(node);
        if (node == search) {
            finish = 1;
            result = path;
        }
        preorder2(node->left, search, path, result, finish);
        preorder2(node->right, search, path, result, finish);
        path.pop_back();
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        std::vector<TreeNode*> path;
        std::vector<TreeNode*> node_p_path;
        std::vector<TreeNode*> node_q_path;
        int finish = 0;
        preorder2(root, p, path, node_p_path, finish);
        path.clear();
        finish = 0;
        preorder2(root, q, path, node_q_path, finish);
        int path_len = 0;
        if (node_p_path.size() < node_q_path.size()) {
            path_len = node_p_path.size();
        } else {
            path_len = node_q_path.size();
        }
        TreeNode* result = 0;
        for (size_t i = 0; i < path_len; i++) {
            if (node_p_path[i] == node_q_path[i]) {
                result = node_p_path[i];
            }
        }
        return result;
    }

    // 二叉树转链表
    void preorder3(TreeNode* node, TreeNode*& last) {
        if (!node) {
            return;
        }
        // 如果自己是一个叶子节点，直接返回
        if (!node->left && !node->right) {
            last = node;
            return;
        }
        // 备份左右指针
        TreeNode* left = node->left;
        TreeNode* right = node->right;
        TreeNode* left_last = NULL;
        TreeNode* right_last = NULL;
        // 若有左子树，递归将左子树转换单链表
        if (left) {
            preorder3(left, left_last);
            node->left = NULL;
            node->right = left;
            last = left_last;
        }
        // 若有左子树，递归将左子树转换单链表
        if (right) {
            preorder3(right, right_last);
            if (left_last) {
                left_last->right = right;
            }
            last = right_last;
        }
    }
    void flatten(TreeNode* root) {
        TreeNode* last = NULL;
        preorder3(root, last);
    }

    // 二叉树广度优先搜索（二叉树层次遍历）
    void BFS_print(TreeNode* root) {
        std::queue<TreeNode*> Q;
        Q.push(root);
        while (!Q.empty()) {
            TreeNode* node = Q.front();
            Q.pop();
            printf("[%d]\n", node->val);
            if (node->left) {
                Q.push(node->left);
            }
            if (node->right) {
                Q.push(node->right);
            }
        }
    }

    std::vector<int> rightSideView(TreeNode* root) {
        std::vector<int> view;
        std::queue<std::pair<TreeNode*, int> > Q;
        if (root) {
            Q.push(std::make_pair(root, 0));
        }
        while (!Q.empty()) {
            TreeNode* node = Q.front().first;
            int depth = Q.front().second;
            Q.pop();
            if (view.size() == depth) {
                view.push_back(node->val);
            } else {
                view[depth] = node->val;
            }
            if (node->left) {
                Q.push(std::make_pair(node->left, depth + 1));
            }
            if (node->right) {
                Q.push(std::make_pair(node->right, depth + 1));
            }
        }
        return view;
    }

    // 图的深度优先遍历(Depth First Search)（递归实现）
    void DFS_graph(GraphNode* node, int visit[]) {
        visit[node->label] = 1;
        printf("%2d", node->label);
        for (size_t i = 0; i < node->neighbors.size(); i++) {
            if (visit[node->neighbors[i]->label] == 0) {
                DFS_graph(node->neighbors[i], visit);
            }
        }
    }

    // 图的广度优先遍历(Breadth First Search)（队列实现）
    void BFS_graph(GraphNode* node, int visit[]) {
        std::queue<GraphNode*> Q;
        Q.push(node);
        visit[node->label] = 1;
        while (!Q.empty()) {
            GraphNode* node = Q.front();
            Q.pop();
            printf("%2d", node->label);
            for (size_t i = 0; i < node->neighbors.size(); i++) {
                if (visit[node->neighbors[i]->label] == 0) {
                    Q.push(node->neighbors[i]);
                    visit[node->neighbors[i]->label] = 1;
                }
            }
        }
    }

    bool DFS_graph2(GraphNode* node, std::vector<int>& visit) {
        visit[node->label] = 0;
        for (size_t i = 0; i < node->neighbors.size(); i++) {
            if (visit[node->neighbors[i]->label] == -1) {
                if (!DFS_graph2(node->neighbors[i], visit)) {
                    return false;
                }
            } else if (visit[node->neighbors[i]->label] == 0) {
                return false;
            }
        }
        visit[node->label] = 1;
        return true;
    }
    bool canFinish(int numCourses,
                   std::vector<std::pair<int, int> >& prerequisites) {
        std::vector<GraphNode*> graph;  // 邻接表
        // 节点访问状态，-1：没访问过，0：正在访问，1：访问过
        std::vector<int> visit;
        for (size_t i = 0; i < numCourses; i++) {
            graph.push_back(new GraphNode(i));
            visit.push_back(-1);
        }
        for (size_t i = 0; i < prerequisites.size(); i++) {
            GraphNode* begin = graph[prerequisites[i].second];
            GraphNode* end = graph[prerequisites[i].first];
            begin->neighbors.push_back(end);
        }
        for (size_t i = 0; i < graph.size(); i++) {
            if (visit[i] == -1 && !DFS_graph2(graph[i], visit)) {
                return false;
            }
        }
        for (size_t i = 0; i < numCourses; i++) {
            delete graph[i];
        }
        return true;
    }

    // prerequisites<课程1, 课程2> 课程2->课程1
    bool canFinish2(int numCourses,
                    std::vector<std::pair<int, int> >& prerequisites) {
        std::vector<GraphNode*> graph;
        std::vector<int> degree;  // 入度数组
        for (size_t i = 0; i < numCourses; i++) {
            degree.push_back(0);
            graph.push_back(new GraphNode(i));
        }
        for (size_t i = 0; i < prerequisites.size(); i++) {
            GraphNode* begin = graph[prerequisites[i].second];
            GraphNode* end = graph[prerequisites[i].first];
            begin->neighbors.push_back(end);
            degree[prerequisites[i].first]++;  // 课程1的入度++
        }
        std::queue<GraphNode*> Q;
        for (size_t i = 0; i < numCourses; i++) {
            if (degree[i] == 0) {
                Q.push(graph[i]);
            }
        }
        while (!Q.empty()) {
            GraphNode* node = Q.front();
            Q.pop();
            for (size_t i = 0; i < node->neighbors.size(); i++) {
                degree[node->neighbors[i]->label]--;
                if (degree[node->neighbors[i]->label] == 0) {
                    Q.push(node->neighbors[i]);
                }
            }
        }
        for (size_t i = 0; i < numCourses; i++) {
            delete graph[i];
        }
        for (size_t i = 0; i < degree.size(); i++) {
            if (degree[i]) {
                return false;
            }
        }
        return true;
    }

    /**
     * 二分查找(递归)
     */
    bool binary_search(std::vector<int>& sort_array, int begin, int end,
                       int target) {
        if (begin > end) {  // 区间不存在
            return false;
        }
        int mid = (begin + end) / 2;
        if (target == sort_array[mid]) {
            return true;
        } else if (target < sort_array[mid]) {
            return binary_search(sort_array, begin, mid - 1, target);
        } else if (target > sort_array[mid]) {
            return binary_search(sort_array, mid + 1, end, target);
        }
        return false;
    }
    /**
     * 二分查找(循环)
     */
    bool binary_search2(std::vector<int>& sort_array, int target) {
        int begin = 0;
        int end = sort_array.size() - 1;
        while (begin <= end) {
            int mid = (begin + end) / 2;
            if (target == sort_array[mid]) {
                return true;
            } else if (target < sort_array[mid]) {
                end = mid - 1;
            } else if (target > sort_array[mid]) {
                begin = mid + 1;
            }
        }
        return false;
    }

    // 插入位置
    int searchInsert(std::vector<int>& nums, int target) {
        int index = -1;
        int begin = 0;
        int end = nums.size() - 1;
        while (index == -1) {
            int mid = (begin + end) / 2;
            if (target == nums[mid]) {
                index = mid;
            } else if (target < nums[mid]) {
                if (mid == 0 || target > nums[mid - 1]) {
                    index = mid;
                }
                end = mid - 1;
            } else if (target > nums[mid]) {
                if (mid == nums.size() - 1 || target < nums[mid + 1]) {
                    index = mid + 1;
                }
                begin = mid + 1;
            }
        }
        return index;
    }

    // 区间查找
    int let_bound(std::vector<int>& nums, int target) {
        int begin = 0;
        int end = nums.size() - 1;
        while (begin <= end) {
            int mid = (begin + end) / 2;
            if (target == nums[mid]) {
                if (mid == 0 || nums[mid - 1] < target) {
                    return mid;
                }
                end = mid - 1;
            } else if (target < nums[mid]) {
                end = mid - 1;
            } else if (target > nums[mid]) {
                begin = mid + 1;
            }
        }
        return -1;
    }
    int right_bound(std::vector<int>& nums, int target) {
        int begin = 0;
        int end = nums.size() - 1;
        while (begin <= end) {
            int mid = (begin + end) / 2;
            if (target == nums[mid]) {
                if (mid == nums.size() - 1 || nums[mid + 1] > target) {
                    return mid;
                }
                begin = mid + 1;
            } else if (target < nums[mid]) {
                end = mid - 1;
            } else if (target > nums[mid]) {
                begin = mid + 1;
            }
        }
        return -1;
    }
    std::vector<int> searchRange(std::vector<int>& nums, int target) {
        std::vector<int> result;
        result.push_back(let_bound(nums, target));
        result.push_back(right_bound(nums, target));
        return result;
    }

    // 旋转数组查找
    int searchRotateArray(std::vector<int>& nums, int target) {
        int begin = 0;
        int end = nums.size() - 1;
        while (begin <= end) {
            int mid = (begin + end) / 2;
            if (target == nums[mid]) {
                return mid;
            }
            if (nums[begin] < nums[mid]) {  // 左侧有序
                if (nums[begin] <= target && target < nums[mid]) {
                    end = mid - 1;
                } else {
                    begin = mid + 1;
                }
            } else if (nums[mid] < nums[end]) {  // 右侧有序
                if (nums[mid] < target && target <= nums[end]) {
                    begin = mid + 1;
                } else {
                    end = mid - 1;
                }
            } else {  // 相等情况
                begin = mid + 1;
            }
        }
        return -1;
    }

    /**
     * 二叉查找(排序)树(Binary Search Tree)
     * 1、若左子树不空，则左子树上所有节点的值均小于或等于它的根节点的值
     * 2、若右子树不空，则右子树上所有节点的值均大于或等于它的根节点的值
     * 3、左右子树也分别为二叉查找(排序)树
     * 4、等于的情况只能出现在左子树或右子树的某一侧
     */
    void BST_insert(TreeNode* node, TreeNode* insert_node) {
        if (insert_node->val < node->val) {  // 插入节点小，在左子树插入
            if (node->left) {
                BST_insert(node->left, insert_node);
            } else {
                node->left = insert_node;
            }
        } else {  // 反之(大于等于)，在右子树插入
            if (node->right) {
                BST_insert(node->right, insert_node);
            } else {
                node->right = insert_node;
            }
        }
    }

    bool BST_search(TreeNode* node, int value) {
        if (node->val == value) {
            return true;
        }
        if (value < node->val) {
            if (node->left) {
                return BST_search(node->left, value);
            } else {
                return false;
            }
        } else {
            if (node->right) {
                return BST_search(node->right, value);
            } else {
                return false;
            }
        }
    }

    void BST_preorder(TreeNode* node, std::string& data) {
        if (!node) {
            return;
        }
        std::string str;
        itostr(node->val, str);
        data += str;
        data += '#';
        BST_preorder(node->left, data);
        BST_preorder(node->right, data);
    }
    // 编码(Tree->Vector->String)
    std::string serialize(TreeNode* root) {
        std::string data;
        BST_preorder(root, data);
        return data;
    }
    // 解码(String->Vector->Tree)
    TreeNode* deserialize(std::string data) {
        if (data.length() == 0) {
            return NULL;
        }
        std::vector<TreeNode*> node_vec;
        int val = 0;
        for (int i = 0; i < data.length(); i++) {
            if (data[i] == '#') {
                node_vec.push_back(new TreeNode(val));
                val = 0;
            } else {
                val = val * 10 + data[i] - '0';
            }
        }
        for (int i = 1; i < node_vec.size(); i++) {
            BST_insert(node_vec[0], node_vec[i]);
        }
        return node_vec[0];
    }
    void collect_nodes(TreeNode* node, std::vector<TreeNode*>& node_vec) {
        if (!node) {
            return;
        }
        node_vec.push_back(node);
        collect_nodes(node->left, node_vec);
        collect_nodes(node->right, node_vec);
    }

    void BST_insert2(BSTNode* node, BSTNode* insert_node, int& count_small) {
        if (insert_node->val <= node->val) {
            node->count++;
            if (node->left) {
                BST_insert2(node->left, insert_node, count_small);
            } else {
                node->left = insert_node;
            }
        } else {
            // 左子树个数 + 当前节点
            count_small += node->count + 1;
            if (node->right) {
                BST_insert2(node->right, insert_node, count_small);
            } else {
                node->right = insert_node;
            }
        }
    }
    std::vector<int> countSmaller2(std::vector<int>& nums) {
        std::vector<int> result;
        std::vector<BSTNode*> node_vec;
        std::vector<int> count;
        // 从后往前插入过程中，比当前节点值小的
        for (int i = nums.size() - 1; i >= 0; i--) {
            node_vec.push_back(new BSTNode(nums[i]));
        }
        count.push_back(0);
        for (size_t i = 1; i < node_vec.size(); i++) {
            int count_small = 0;
            BST_insert2(node_vec[0], node_vec[i], count_small);
            count.push_back(count_small);
        }
        for (int i = node_vec.size() - 1; i >= 0; i--) {
            delete node_vec[i];
            result.push_back(count[i]);
        }
        return result;
    }
    /**
     * 哈希表(Hash
     * Table，也叫散列表)，是根据关键字值(key)直接进行访问的数据结构，
     * 它通过把关键字值映射到列表中一个位置(数组下标)来直接访问，以加快查找关键字值的速度。
     * 这个映射函数叫做哈希(散列)函数，存放记录的数组叫做哈希(散列)表。
     */
    int hash_func(int key, int table_len) { return key % table_len; }
    void hashInsert(ListNode* hash_table[], ListNode* node, int table_len) {
        int hash_key = hash_func(node->val, table_len);
        node->next = hash_table[hash_key];
        hash_table[hash_key] = node;
    }
    bool hashSearch(ListNode* hash_table[], int value, int table_len) {
        int hash_key = hash_func(value, table_len);
        ListNode* head = hash_table[hash_key];
        while (head) {
            if (head->val == value) {
                return true;
            }
            head = head->next;
        }
        return false;
    }

    // 已知一个只包含大小写字符的字符串，求用该字符串中的字符可以生成的最长回文字符串长度。
    int longestPalindrome(std::string s) {
        int char_map[128] = {0};
        int max_length = 0;
        int flag = 0;
        for (int i = 0; i < s.length(); i++) {
            char_map[s[i]]++;
        }
        for (int i = 0; i < 128; i++) {
            if (char_map[i] % 2 == 0) {
                max_length += char_map[i];
            } else {
                max_length += char_map[i] - 1;
                flag = 1;
            }
        }
        return max_length + flag;
    }

    // pattern = "abba", str = "dog cat cat dog"
    bool wordPattern(std::string pattern, std::string str) {
        // 单词到pattern字符的映射
        std::map<std::string, char> word_map;
        char used[128] = {0};  // 已经被映射的pattern字符
        std::string word;      // 临时保存拆分出的单词
        int pos = 0;           // 当前指向的pattern字符
        str.push_back(' ');  // str尾部push一个空格，使得遇到空格拆分单词
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == ' ') {
                if (pos == pattern.length()) {
                    return false;
                }
                // 若单词未出现在哈希映射中
                if (word_map.find(word) == word_map.end()) {
                    if (used[pattern[pos]]) {
                        return false;
                    }
                    word_map[word] = pattern[pos];
                    used[pattern[pos]] = 1;
                } else {
                    if (word_map[word] != pattern[pos]) {
                        return false;
                    }
                }
                word = "";
                pos++;
            } else {
                word += str[i];
            }
        }
        // pattern没遍历完
        if (pos != pattern.length()) {
            return false;
        }
        return true;
    }

    // 将所有anagram(由颠倒字母顺序而构成的字)放到一起输出
    std::vector<std::vector<std::string> > groupAnagrams(
        std::vector<std::string>& strs) {
        std::map<std::string, std::vector<std::string> > anagram;
        std::vector<std::vector<std::string> > result;
        for (int i = 0; i < strs.size(); i++) {
            std::string str = strs[i];
            std::sort(str.begin(), str.end());
            if (anagram.find(str) == anagram.end()) {
                std::vector<std::string> item;
                anagram[str] = item;
            }
            anagram[str].push_back(strs[i]);
        }
        std::map<std::string, std::vector<std::string> >::iterator it;
        for (it = anagram.begin(); it != anagram.end(); it++) {
            result.push_back((*it).second);
        }
        return result;
    }

    // 已知一个字符串，求用该字符串的无重复字符的最长子串的长度
    int lengthOfLongestSubstring(std::string s) {
        // 窗口头指针
        int begin = 0;
        int result = 0;
        std::string word = "";
        int char_map[128] = {0};
        for (int i = 0; i < s.length(); i++) {
            char_map[s[i]]++;
            if (char_map[s[i]] == 1) {
                word += s[i];
                if (result < word.length()) {
                    result = word.length();
                }
            } else {
                while (begin < i && char_map[s[i]] > 1) {
                    char_map[s[begin]]--;
                    begin++;
                }
                word = "";
                for (int j = begin; j <= i; j++) {
                    word += s[j];
                }
            }
        }
        return result;
    }

    // 将DNA序列看作是只包含['A', 'C', 'G',
    // 'T']4个字符的字符串，给一个DNA字符串，找到长度为10的且超过1次的子串
    std::vector<std::string> findRepeatedDnaSequences(std::string s) {
        std::vector<std::string> result;
        if (s.length() < 10) {
            return result;
        }
        for (int i = 0; i < 1038576; i++) {
            g_hash_map[i] = 0;
        }
        int char_map[128] = {0};
        char_map['A'] = 0;
        char_map['C'] = 1;
        char_map['G'] = 2;
        char_map['T'] = 3;
        int key = 0;
        for (int i = 9; i >= 0; i--) {
            key = (key << 2) + char_map[s[i]];  // key * 4 + char_map[s[i]]
        }
        g_hash_map[key] = 1;
        for (int i = 10; i < s.length(); i++) {
            key = key >> 2;
            key = key | (char_map[s[i]] << 18);
            g_hash_map[key]++;
        }
        for (int i = 0; i < 1048576; i++) {
            if (g_hash_map[i] > 1) {
                result.push_back(change_int_to_DNA(i));
            }
        }
        return result;
    }
    std::vector<std::string> findRepeatedDnaSequences2(std::string s) {
        std::map<std::string, int> word_map;
        std::vector<std::string> result;
        for (int i = 0; i < s.length(); i++) {
            std::string word = s.substr(i, 10);
            if (word_map.find(word) != word_map.end()) {
                word_map[word]++;
            } else {
                word_map[word] = 1;
            }
        }
        std::map<std::string, int>::iterator it;
        for (it = word_map.begin(); it != word_map.end(); it++) {
            if (it->second > 1) {
                result.push_back(it->first);
            }
        }
        return result;
    }

    // 已知字符串S与字符串T，求在S中的最小窗口(区间)，使得这个区间中包含了字符串T中的所有字符
    bool is_window_ok(int map_s[], int map_t[], std::vector<int>& vec_t) {
        for (int i = 0; i < vec_t.size(); i++) {
            // 如果s出现该字符的数量小于t中出现该字符的数量
            if (map_s[vec_t[i]] < map_t[vec_t[i]]) {
                return false;
            }
        }
        return true;
    }
    std::string minWindow(std::string s, std::string t) {
        const int MAX_ARRAY_LEN = 128;
        int map_t[MAX_ARRAY_LEN] = {0};  // 记录t字符串各字符个数
        int map_s[MAX_ARRAY_LEN] = {0};  // 记录s字符串各字符个数
        std::vector<int> vec_t;          // 记录t字符串中有哪些字符
        for (int i = 0; i < t.length(); i++) {
            map_t[t[i]]++;
        }
        for (int i = 0; i < MAX_ARRAY_LEN; i++) {
            if (map_t[i] > 0) {
                vec_t.push_back(i);
            }
        }
        int window_begin = 0;
        std::string result;
        // i代表窗口的尾指针
        for (int i = 0; i < s.length(); i++) {
            map_s[s[i]]++;
            while (window_begin < i) {
                char begin_ch = s[window_begin];
                if (map_t[begin_ch] == 0) {
                    window_begin++;
                } else if (map_s[begin_ch] > map_t[begin_ch]) {
                    map_s[begin_ch]--;
                    window_begin++;
                } else {
                    break;
                }
            }
            if (is_window_ok(map_s, map_t, vec_t)) {
                int new_window_len = i - window_begin + 1;
                if (result == "" || result.length() > new_window_len) {
                    result = s.substr(window_begin, new_window_len);
                }
            }
        }
        return result;
    }
};

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

void testListNode() {
    ListNode a(1);
    ListNode b(2);
    ListNode c(3);
    ListNode d(4);
    ListNode e(5);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    e.next = NULL;
    ListNode* head = &a;
    Solution s;
    // head = s.reverseList(head);
    head = s.reverseBetween(head, 2, 4);
    while (head) {
        printf("%d\n", head->val);
        head = head->next;
    }
}

/**
 * 贪心法：遵循某种规律，不断贪心的选取当前最优策略的算法设计方法
 */
void payMoney() {
    const int RMB[] = {200, 100, 20, 10, 5, 1};
    const int NUM = 6;
    int X = 628;
    for (size_t i = 0; i < NUM; i++) {
        int k = RMB[i];
        int use = X / k;
        X = X - k * use;
        printf("%d-%d\n", k, use);
    }
}

void testFindChildContent() {
    Solution solve;
    std::vector<int> g;
    std::vector<int> s;
    g.push_back(5);
    g.push_back(10);
    g.push_back(2);
    g.push_back(9);
    g.push_back(15);
    g.push_back(9);
    s.push_back(6);
    s.push_back(1);
    s.push_back(20);
    s.push_back(3);
    s.push_back(8);
    int child = solve.findContentChildren(g, s);
    printf("child = %d\n", child);
}

void testRemoveKdigits() {
    Solution solve;
    std::string result = solve.removeKdigits("1432219", 3);
    printf("%s\n", result.c_str());
    std::string result2 = solve.removeKdigits("100200", 1);
    printf("%s\n", result2.c_str());
}

void testCanJump() {
    std::vector<int> nums;
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(1);
    nums.push_back(1);
    nums.push_back(4);
    Solution sol;
    printf("%d\n", sol.jump(nums));
}

void testMinimumStop() {
    std::vector<std::pair<int, int> > stop;
    int N, L, P, dis, fuel;
    scanf("%d", &N);
    for (size_t i = 0; i < N; i++) {
        scanf("%d %d", &dis, &fuel);
        stop.push_back(std::make_pair(dis, fuel));
    }
    scanf("%d %d", &L, &P);
    Solution sol;
    printf("%d\n", sol.get_minimum_stop(L, P, stop));
}

void testCombinationSum() {
    std::vector<int> nums;
    nums.push_back(10);
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(7);
    nums.push_back(6);
    nums.push_back(1);
    nums.push_back(5);
    std::vector<std::vector<int> > result;
    Solution sol;
    result = sol.combinationSum(nums, 8);
    for (size_t i = 0; i < result.size(); i++) {
        if (result[i].size() == 0) {
            printf("[]");
        }
        for (size_t j = 0; j < result[i].size(); j++) {
            printf("[%d]", result[i][j]);
        }
        printf("\n");
    }
}

void testGenerate3() {
    std::vector<std::string> result;
    Solution sol;
    int n = 3;
    sol.generate3("", n, n, result);
    for (size_t i = 0; i < result.size(); i++) {
        printf("'%s'\n", result[i].c_str());
    }
}

void testSolveNQueens() {
    Solution s;
    std::vector<std::vector<std::string> > result;
    result = s.solveNQueens(4);
    for (size_t i = 0; i < result.size(); i++) {
        for (size_t j = 0; j < result[i].size(); j++) {
            printf("%s\n", result[i][j].c_str());
        }
        printf("\n");
    }
}

void test_merge_sort() {
    std::vector<int> vec1;
    std::vector<int> vec2;
    srand(time(NULL));
    for (size_t i = 0; i < 10000; i++) {
        int num = (rand() * rand()) % 100003;
        vec1.push_back(num);
        vec2.push_back(num);
    }
    Solution sol;
    sol.merge_sort(vec1);
    std::sort(vec2.begin(), vec2.end());
    assert(vec1.size() == vec2.size());
    for (size_t i = 0; i < vec1.size(); i++) {
        assert(vec1[i] == vec2[i]);
    }
}

void testCountSmaller() {
    int test[] = {5, -7, 9, 1, 3, 5, -2, 1};
    std::vector<int> nums;
    for (size_t i = 0; i < 8; i++) {
        nums.push_back(test[i]);
    }
    Solution solve;
    std::vector<int> result = solve.countSmaller(nums);
    for (size_t i = 0; i < 2 * result.size(); i++) {
        if (i < 8) {
            printf("%3d", test[i]);
        } else if (i == 8) {
            printf("\n");
            printf("%3d", result[i - 8]);
        } else {
            printf("%3d", result[i - 8]);
        }
    }
    printf("\n");
}

void testPathSum() {
    TreeNode a(5);
    TreeNode b(4);
    TreeNode c(8);
    TreeNode d(11);
    TreeNode e(13);
    TreeNode f(4);
    TreeNode g(7);
    TreeNode h(2);
    TreeNode x(5);
    TreeNode y(1);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    c.left = &e;
    c.right = &f;
    d.left = &g;
    d.right = &h;
    f.left = &x;
    f.right = &y;
    Solution solve;
    std::vector<std::vector<int> > result = solve.pathSum(&a, 22);
    for (size_t i = 0; i < result.size(); i++) {
        for (size_t j = 0; j < result[i].size(); j++) {
            printf("[%d]", result[i][j]);
        }
        printf("\n");
    }
}

void testFlatten() {
    TreeNode a(1);
    TreeNode b(2);
    TreeNode c(5);
    TreeNode d(3);
    TreeNode e(4);
    TreeNode f(6);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.right = &f;
    TreeNode* root = &a;
    preorder_print1(root, 0);
    Solution solve;
    solve.flatten(&a);
    TreeNode* head = &a;
    while (head) {
        if (head->left) {
            printf("ERROR\n");
        }
        printf("[%d]", head->val);
        head = head->right;
    }
    printf("\n");
}

void testRightSideView() {
    TreeNode a(1);
    TreeNode b(2);
    TreeNode c(5);
    TreeNode d(3);
    TreeNode e(4);
    TreeNode f(6);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.right = &f;
    Solution solve;
    std::vector<int> result = solve.rightSideView(&a);
    for (size_t i = 0; i < result.size(); i++) {
        printf("[%d]\n", result[i]);
    }
}

void testGraphNode() {
    int n = 5;
    GraphNode* graph[n];
    for (size_t i = 0; i < n; i++) {
        graph[i] = new GraphNode(i);
    }
    graph[0]->neighbors.push_back(graph[2]);
    graph[0]->neighbors.push_back(graph[4]);
    graph[1]->neighbors.push_back(graph[0]);
    graph[1]->neighbors.push_back(graph[2]);
    graph[2]->neighbors.push_back(graph[3]);
    graph[3]->neighbors.push_back(graph[4]);
    graph[4]->neighbors.push_back(graph[3]);
    printf("graph:\n");
    for (size_t i = 0; i < n; i++) {
        printf("Label(%lu):", i);
        for (size_t j = 0; j < graph[i]->neighbors.size(); j++) {
            printf("%2d", graph[i]->neighbors[j]->label);
        }
        printf("\n");
    }
    for (size_t i = 0; i < n; i++) {
        delete graph[i];
    }
}

void testGraph() {
    const int n = 5;
    GraphNode* graph[n];
    for (size_t i = 0; i < n; i++) {
        graph[i] = new GraphNode(i);
    }
    graph[0]->neighbors.push_back(graph[4]);
    graph[0]->neighbors.push_back(graph[2]);
    graph[1]->neighbors.push_back(graph[0]);
    graph[1]->neighbors.push_back(graph[2]);
    graph[2]->neighbors.push_back(graph[3]);
    graph[3]->neighbors.push_back(graph[4]);
    graph[4]->neighbors.push_back(graph[3]);
    Solution solve;
    int visit[n] = {0};
    for (size_t i = 0; i < n; i++) {
        if (visit[i] == 0) {
            printf("From label(%d):", graph[i]->label);
            // solve.DFS_graph(graph[i], visit);
            solve.BFS_graph(graph[i], visit);
            printf("\n");
        }
    }
    for (size_t i = 0; i < n; i++) {
        delete graph[i];
    }
}

void testCanFinish() {
    std::vector<std::pair<int, int> > prerequisites;
    prerequisites.push_back(std::make_pair(1, 0));
    prerequisites.push_back(std::make_pair(2, 0));
    prerequisites.push_back(std::make_pair(3, 1));
    prerequisites.push_back(std::make_pair(3, 2));
    Solution solve;
    printf("%d\n", solve.canFinish2(4, prerequisites));
}

void testSearchRange() {
    int test[] = {5, 7, 7, 8, 8, 8, 8, 10};
    std::vector<int> nums;
    Solution solve;
    for (size_t i = 0; i < 8; i++) {
        nums.push_back(test[i]);
    }
    for (size_t i = 0; i < 12; i++) {
        std::vector<int> result = solve.searchRange(nums, i);
        printf("%lu : [%d, %d]\n", i, result[0], result[1]);
    }
}

void testBST_insert() {
    TreeNode root(8);
    std::vector<TreeNode*> node_vec;
    int test[] = {3, 10, 1, 6, 15};
    for (size_t i = 0; i < 5; i++) {
        node_vec.push_back(new TreeNode(test[i]));
    }
    Solution sol;
    for (size_t i = 0; i < node_vec.size(); i++) {
        sol.BST_insert(&root, node_vec[i]);
    }
    preorder_print2(&root, 0);
    for (size_t i = 0; i < node_vec.size(); i++) {
        delete node_vec[i];
    }
}

void testBST_search() {
    TreeNode a(8);
    TreeNode b(3);
    TreeNode c(10);
    TreeNode d(1);
    TreeNode e(6);
    TreeNode f(15);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.left = &e;
    c.left = &f;
    Solution sol;
    for (int i = 0; i < 20; i++) {
        if (sol.BST_search(&a, i)) {
            printf("%d is in the BST.\n", i);
        } else {
            printf("%d is not in the BST.\n", i);
        }
    }
}

void testSerialize() {
    TreeNode a(8);
    TreeNode b(3);
    TreeNode c(10);
    TreeNode d(1);
    TreeNode e(6);
    TreeNode f(15);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.left = &e;
    c.left = &f;
    Solution sol;
    std::string data = sol.serialize(&a);
    printf("%s\n", data.c_str());
    TreeNode* root = sol.deserialize(data);
    preorder_print1(root, 0);
}

void testCountSmaller2() {
    int test[] = {5, -7, 9, 1, 3, 5, -2, 1};
    std::vector<int> nums;
    for (size_t i = 0; i < 8; i++) {
        nums.push_back(test[i]);
    }
    Solution solve;
    std::vector<int> result = solve.countSmaller2(nums);
    for (size_t i = 0; i < 2 * result.size(); i++) {
        if (i < 8) {
            printf("%3d", test[i]);
        } else if (i == 8) {
            printf("\n");
            printf("%3d", result[i - 8]);
        } else {
            printf("%3d", result[i - 8]);
        }
    }
    printf("\n");
}

void testCharCount(std::string str) {
    int char_map[128] = {0};
    for (int i = 0; i < str.length(); i++) {
        char_map[str[i]]++;
    }
    for (int i = 0; i < 128; i++) {
        if (char_map[i] > 0) {
            printf("[%c]: %d\n", i, char_map[i]);
        }
    }
}
void testHashSort() {
    int nums[10] = {999, 1, 444, 7, 20, 9, 1, 3, 7, 7};
    int hash_map[1000] = {0};
    for (int i = 0; i < 10; i++) {
        hash_map[nums[i]]++;
    }
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < hash_map[i]; j++) {
            printf("%d\n", i);
        }
    }
}

void testHash() {
    const int TABLE_LEN = 11;
    ListNode* hash_table[TABLE_LEN] = {0};
    std::vector<ListNode*> hash_node_vec;
    int test[8] = {1, 1, 4, 9, 20, 30, 150, 500};
    Solution solve;
    for (int i = 0; i < 8; i++) {
        hash_node_vec.push_back(new ListNode(test[i]));
    }
    for (int i = 0; i < hash_node_vec.size(); i++) {
        solve.hashInsert(hash_table, hash_node_vec[i], TABLE_LEN);
    }
    printf("Hash table:\n");
    for (int i = 0; i < TABLE_LEN; i++) {
        printf("[%d]:", i);
        ListNode* head = hash_table[i];
        while (head) {
            printf("->%d", head->val);
            head = head->next;
        }
        printf("\n");
    }
    printf("\n");
    printf("Test search:\n");
    for (int i = 0; i < 10; i++) {
        if (solve.hashSearch(hash_table, i, TABLE_LEN)) {
            printf("%d is in the hash table.\n", i);
        } else {
            printf("%d is not in the hash table.\n", i);
        }
    }
    for (int i = 0; i < hash_node_vec.size(); i++) {
        delete hash_node_vec[i];
    }
}

void testFindRepeatedDnaSequences() {
    std::string s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
    Solution solve;
    std::vector<std::string> result = solve.findRepeatedDnaSequences(s);
    for (int i = 0; i < result.size(); i++) {
        printf("%s\n", result[i].c_str());
    }
}

void testMinWindow() {
    Solution solve;
    std::string result = solve.minWindow("ADOBECODEBANC", "ABC");
    printf("%s\n", result.c_str());
    result = solve.minWindow("MADOBCCABEC", "ABCC");
    printf("%s\n", result.c_str());
    result = solve.minWindow("aa", "aa");
    printf("%s\n", result.c_str());
}

int main() {
    // std::string s = "1+121 - (14+(5-6) )";
    Solution solve;
    // printf("%d\n", solve.calculate(s));
    // test_heap();
    // int test[] = {6, 10, 1, 7, 99, 4, 33};
    // std::vector<int> nums;
    // for (size_t i = 0; i < 7; i++)
    // {
    //     nums.push_back(test[i]);
    // }
    // double m = solve.findMedian(nums);
    // printf("find median num = %f", m);
    // testListNode();
    // payMoney();
    // testRemoveKdigits();
    // testCanJump();
    // testMinimumStop();
    testCombinationSum();
    // testGenerate3();
    // testSolveNQueens();
    // test_merge_sort();
    // testCountSmaller();
    // testPathSum();
    // testFlatten();
    // testRightSideView();
    // testGraphNode();
    // testGraph();
    // testCanFinish();
    // testSearchRange();
    // testBST_insert();
    // testBST_search();
    // testSerialize();
    // testCountSmaller2();
    // std::string str = "abcdefgaaxxxyt";
    // solve.charCount(str);
    // solve.hashSort();
    // testHash();
    // std::string s = "abccccddaa";
    // printf("%d\n", solve.longestPalindrome(s));
    // std::string pattern = "abba";
    // std::string str = "dog cat cat dog";
    // printf("%d\n", solve.wordPattern(pattern, str));
    // std::string s = "abcbadab";
    // printf("%d\n", solve.lengthOfLongestSubstring(s));
    // testFindRepeatedDnaSequences();
    // testMinWindow();

    return 0;
}
