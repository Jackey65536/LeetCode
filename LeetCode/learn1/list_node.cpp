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

bool cmp(const ListNode* a, const ListNode* b) { return a->val < b->val; }

class Solution {
   public:
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

    // 链表逆序(头插法)
    ListNode* reverseList2(ListNode* head) {
        ListNode tmphead(0);
        while (head) {
            ListNode* next = head->next;
            head->next = tmphead.next;
            tmphead.next = head;
            head = next;
        }
        return tmphead.next;
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
        // 连接逆置后的链表尾与逆置段的后一个节点
        modify_list_tail->next = head;
        if (pre_head)  // 如果pre_head不空，说明不是从第一个节点开始逆置的 m > 1
        {
            // 将逆置链表开始的节点前驱与逆置后的头节点连接
            pre_head->next = new_head;
        } else {
            // 如果pre_head为null，说明m==1从第一个节点开始逆置，结果即为逆置后的头结点
            result = new_head;
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
        // 使用vector根据存储几点位置访问地址
        std::vector<RandomListNode*> node_vec;
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
};

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
    head = s.reverseList2(head);
    // head = s.reverseBetween(head, 2, 4);
    while (head) {
        printf("%d\n", head->val);
        head = head->next;
    }
}

int main() {
    testListNode();

    return 0;
}