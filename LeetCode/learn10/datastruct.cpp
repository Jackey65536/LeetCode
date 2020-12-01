#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <cstring>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>

#define TRIE_MAX_CHAR_NUM 26

struct TrieNode {
    TrieNode* child[TRIE_MAX_CHAR_NUM];
    bool is_end;
    TrieNode() : is_end(false) {
        for (int i = 0; i < TRIE_MAX_CHAR_NUM; i++) {
            child[i] = 0;
        }
    }
};

void preorder_trie(TrieNode* node, int layer) {
    for (int i = 0; i < TRIE_MAX_CHAR_NUM; i++) {
        if (node->child[i]) {
            for (int j = 0; j < layer; j++) {
                printf("---");
            }
            printf("%c", i + 'a');
            if (node->child[i]->is_end) {
                printf("(end)");
            }
            printf("\n");
            preorder_trie(node->child[i], layer + 1);
        }
    }
}

void get_all_word_from_trie(TrieNode* node, std::string& word,
                            std::vector<std::string>& word_list) {
    for (size_t i = 0; i < TRIE_MAX_CHAR_NUM; i++) {
        if (node->child[i]) {
            word.push_back(i + 'a');
            if (node->child[i]->is_end) {
                word_list.push_back(word);
            }
            get_all_word_from_trie(node->child[i], word, word_list);
            word.erase(word.length() - 1, 1);
        }
    }
}

// 字典树
class TrieTree {
   public:
    TrieTree() {}
    ~TrieTree() {
        for (int i = 0; i < _node_vec.size(); i++) {
            delete _node_vec[i];
        }
    }
    // 将word插入至trie
    void insert(const char* word) {
        TrieNode* ptr = &_root;
        while (*word) {
            int pos = *word - 'a';
            if (!ptr->child[pos]) {
                ptr->child[pos] = new_node();
            }
            ptr = ptr->child[pos];
            word++;
        }
        ptr->is_end = true;
    }
    // 搜索trie中是否存在word
    bool search(const char* word) {
        TrieNode* ptr = &_root;
        while (*word) {
            int pos = *word - 'a';
            if (!ptr->child[pos]) {
                return false;
            }
            ptr = ptr->child[pos];
            word++;
        }
        return ptr->is_end;
    }
    // 确认trie中是否有前缀prefix的单词
    bool startsWith(const char* prefix) {
        TrieNode* ptr = &_root;
        while (*prefix) {
            int pos = *prefix - 'a';
            if (!ptr->child[pos]) {
                return false;
            }
            ptr = ptr->child[pos];
            prefix++;
        }
        return true;
    }
    TrieNode* root() { return &_root; }

   private:
    TrieNode* new_node() {
        TrieNode* node = new TrieNode();
        _node_vec.push_back(node);
        return node;
    }
    // 保存所有node，析构时统一销毁
    std::vector<TrieNode*> _node_vec;
    TrieNode _root;
};
/**
 * 设计一个数据结构，支持如下操作：
 * 1、添加单词
 * 2、搜索单词
 * 搜索字符'a'~'z'或'.'
 */
class WordDictionary {
   public:
    WordDictionary(){};
    void addWord(std::string word) { _trie_tree.insert(word.c_str()); }
    bool search(std::string word) {
        return search_trie(_trie_tree.root(), word.c_str());
    }
    bool search_trie(TrieNode* node, const char* word) {
        if (*word == '\0') {
            return node->is_end;
        }
        if (*word == '.') {
            for (int i = 0; i < TRIE_MAX_CHAR_NUM; i++) {
                if (node->child[i] && search_trie(node->child[i], word + 1)) {
                    return true;
                }
            }
        } else {
            int pos = *word - 'a';
            if (node->child[pos] && search_trie(node->child[pos], word + 1)) {
                return true;
            }
        }
        return false;
    }

   private:
    TrieTree _trie_tree;
};

/**
 * 并查集(不相交集合)：它应用于N个元素的集合求并与查询问题，在该应用场景中，
 * 我们通常是在开始时让每个元素构成一个单元素的集合，然后按一定顺序将属于同
 * 一组的元素所在的集合合并，期间要反复查找一个元素在那个集合中。
 */
class DisjointSet {
   public:
    DisjointSet(int n) {
        for (int i = 0; i < n; i++) {
            _id.push_back(i);
            _size.push_back(1);
        }
        _count = n;
    }
    int find(int p) {
        while (p != _id[p]) {
            _id[p] = _id[_id[p]];
            p = _id[p];
        }
        return p;
    }
    void union_(int p, int q) {
        int i = find(p);
        int j = find(q);
        if (i == j) {
            return;
        }
        if (_size[i] < _size[j]) {
            _id[i] = j;
            _size[j] += _size[i];
        } else {
            _id[j] = i;
            _size[i] += _size[j];
        }
        _count--;
    }
    void print_set() {
        printf("元素：");
        for (int i = 0; i < _id.size(); i++) {
            printf("%d ", i);
        }
        printf("\n");
        printf("集合：");
        for (int i = 0; i < _id.size(); i++) {
            printf("%d ", _id[i]);
        }
        printf("\n");
    }
    int count() { return _count; }

   private:
    std::vector<int> _id;
    std::vector<int> _size;  // 集合大小
    int _count;              // 集合个数
};

/**
 * 线段树：一种平衡二叉树(完全二叉树)，它将一个线段区间划分成一些单元区间。
 * 对于线段树中的每一个非叶子节点[a, b]，它的左儿子表示的区间为[a, (a+b)/2]，
 * 右儿子表示的区间为[(a+b)/2+1, b]，最后的叶子节点数目为N，与数组下标对应。
 * 线段树一版包括建立、查询、插入、更新等操作，建立规模为N的时间复杂度是O(NlogN),
 * 其他操作时间复杂度为O(logN)
 */
/**
 * value：区间和数组
 * nums：原始数组
 * pos：当前线段对应下标，即二叉树的层数
 */
void build_segment_tree(std::vector<int>& value, std::vector<int>& nums,
                        int pos, int left, int right) {
    if (left == right) {
        value[pos] = nums[left];
        return;
    }
    int mid = (left + right) / 2;
    build_segment_tree(value, nums, pos * 2 + 1, left, mid);
    build_segment_tree(value, nums, pos * 2 + 2, mid + 1, right);
    // 左孩子区间+右孩子区间
    value[pos] = value[pos * 2 + 1] + value[pos * 2 + 2];
}

void print_segment_tree(std::vector<int>& value, int pos, int left, int right,
                        int layer) {
    for (int i = 0; i < layer; i++) {
        printf("---");
    }
    printf("[%d %d][%d]: %d\n", left, right, pos, value[pos]);
    if (left == right) {
        return;
    }
    int mid = (left + right) / 2;
    print_segment_tree(value, pos * 2 + 1, left, mid, layer + 1);
    print_segment_tree(value, pos * 2 + 2, mid + 1, right, layer);
}

int sum_range_segment_tree(std::vector<int>& value, int pos, int left,
                           int right, int qleft, int qright) {
    if (qleft > right || qright < left) {
        return 0;
    }
    if (qleft <= left && qright >= right) {
        return value[pos];
    }
    int mid = (left + right) / 2;
    return sum_range_segment_tree(value, pos * 2 + 1, left, mid, qleft,
                                  qright) +
           sum_range_segment_tree(value, pos * 2 + 2, mid + 1, right, qleft,
                                  qright);
}

void update_segment_tree(std::vector<int>& value, int pos, int left, int right,
                         int index, int new_value) {
    if (left == right && left == index) {
        value[pos] = new_value;
        return;
    }
    int mid = (left + right) / 2;
    if (index <= mid) {
        update_segment_tree(value, pos * 2 + 1, left, mid, index, new_value);
    } else {
        update_segment_tree(value, pos * 2 + 2, mid + 1, right, index,
                            new_value);
    }
    value[pos] = value[pos * 2 + 1] + value[pos * 2 + 2];
}

/**
 * 给定一个整数数组nums，求这个整数数组中，下标i到下标j之间的数字和(i<=j)，
 * a[i]+a[i+1]+...+a[j]。在求和的过程中，可能需要更新数组的某个元素a[i].
 */
class NumArray {
   public:
    NumArray(std::vector<int> nums) {
        if (nums.size() == 0) {
            return;
        }
        int n = nums.size() * 4;
        for (int i = 0; i < n; i++) {
            _value.push_back(0);
        }
        build_segment_tree(_value, nums, 0, 0, nums.size() - 1);
        _right_end = nums.size() - 1;
    }
    void update(int i, int val) {
        update_segment_tree(_value, 0, 0, _right_end, i, val);
    }
    int sumRange(int i, int j) {
        return sum_range_segment_tree(_value, 0, 0, _right_end, i, j);
    }

   private:
    std::vector<int> _value;
    int _right_end;
};

class Solution {
   public:
    // 求朋友圈数
    int findCircleNum(std::vector<std::vector<int> >& M) {
        std::vector<int> visit(M.size(), 0);
        int count = 0;
        for (int i = 0; i < M.size(); i++) {
            if (!visit[i]) {
                DFS_graph(i, M, visit);
                count++;
            }
        }
        return count;
    }
    // 并查集实现
    int findCircleNum2(std::vector<std::vector<int> >& M) {
        DisjointSet dis(M.size());
        for (int i = 0; i < M.size(); i++) {
            for (int j = i + 1; j < M.size(); j++) {
                if (M[i][j]) {
                    dis.union_(i, j);
                }
            }
        }
        return dis.count();
    }

   private:
    void DFS_graph(int u, std::vector<std::vector<int> >& graph,
                   std::vector<int>& visit) {
        visit[u] = 1;
        for (int i = 0; i < graph[u].size(); i++) {
            if (graph[u][i] && !visit[i]) {
                DFS_graph(i, graph, visit);
            }
        }
    }
};

void testTrieNode() {
    TrieNode root;
    TrieNode n1;
    TrieNode n2;
    TrieNode n3;
    root.child['a' - 'a'] = &n1;
    root.child['b' - 'a'] = &n2;
    root.child['e' - 'a'] = &n3;
    n2.is_end = true;

    TrieNode n4;
    TrieNode n5;
    TrieNode n6;
    n1.child['b' - 'a'] = &n4;
    n2.child['c' - 'a'] = &n5;
    n3.child['f' - 'a'] = &n6;

    TrieNode n7;
    TrieNode n8;
    TrieNode n9;
    TrieNode n10;
    n4.child['c' - 'a'] = &n7;
    n4.child['d' - 'a'] = &n8;
    n5.child['d' - 'a'] = &n9;
    n6.child['g' - 'a'] = &n10;
    n7.is_end = true;
    n8.is_end = true;
    n9.is_end = true;
    n10.is_end = true;

    TrieNode n11;
    n7.child['d' - 'a'] = &n11;
    n11.is_end = true;
    // preorder_trie(&root, 0);
    std::string word;
    std::vector<std::string> word_list;
    get_all_word_from_trie(&root, word, word_list);
    for (int i = 0; i < word_list.size(); i++) {
        printf("%s ", word_list[i].c_str());
    }
}

void testTrieTree() {
    TrieTree tt;
    tt.insert("abcd");
    tt.insert("abc");
    tt.insert("abd");
    tt.insert("b");
    tt.insert("bcd");
    tt.insert("efg");
    printf("preorder_trie:\n");
    preorder_trie(tt.root(), 0);
    printf("\n");
    std::vector<std::string> word_list;
    std::string word;
    printf("All words:\n");
    get_all_word_from_trie(tt.root(), word, word_list);
    for (int i = 0; i < word_list.size(); i++) {
        printf("%s\n", word_list[i].c_str());
    }
    printf("\n");
    printf("Search:\n");
    printf("abc: %d\n", tt.search("abc"));
    printf("abcd: %d\n", tt.search("abcd"));
    printf("bc: %d\n", tt.search("ac"));
    printf("b: %d\n", tt.search("b"));
    printf("\n");
    printf("ab: %d\n", tt.startsWith("ab"));
    printf("abc: %d\n", tt.startsWith("abc"));
    printf("bc: %d\n", tt.startsWith("bc"));
    printf("fg: %d\n", tt.startsWith("fg"));
}

void testWordDictionary() {
    WordDictionary dic;
    dic.addWord("bad");
    dic.addWord("dad");
    dic.addWord("mad");
    printf("%d\n", dic.search("pad"));
    printf("%d\n", dic.search("bad"));
    printf("%d\n", dic.search(".ad"));
    printf("%d\n", dic.search("b.."));
}

void testFindCircleNum() {
    Solution sol;
    int test[][3] = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1},
    };
    std::vector<std::vector<int> > M(3, std::vector<int>(3, 0));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            M[i][j] = test[i][j];
        }
    }
    // printf("%d\n", sol.findCircleNum(M));
    printf("%d\n", sol.findCircleNum2(M));
}

void testDisjointSet() {
    DisjointSet dis(8);
    dis.print_set();
    printf("Union(0, 5)\n");
    dis.union_(0, 5);
    dis.print_set();
    printf("Find(0) = %d, Find(5) = %d\n", dis.find(0), dis.find(5));
    printf("Find(2) = %d, Find(5) = %d\n", dis.find(2), dis.find(5));
    dis.union_(2, 4);
    dis.print_set();
    dis.union_(0, 4);
    dis.print_set();
    printf("Find(2) = %d, Find(5) = %d\n", dis.find(2), dis.find(5));
}

void testSegment() {
    std::vector<int> nums;
    for (int i = 0; i < 6; i++) {
        nums.push_back(i);
    }
    std::vector<int> value(24, 0);
    build_segment_tree(value, nums, 0, 0, nums.size() - 1);
    printf("segment_tree: \n");
    print_segment_tree(value, 0, 0, nums.size() - 1, 0);
    int sum_range = sum_range_segment_tree(value, 0, 0, nums.size() - 1, 2, 4);
    printf("sum_range [2, 4] = %d\n", sum_range);
    update_segment_tree(value, 0, 0, nums.size() - 1, 2, 10);
    printf("segment_tree:\n");
    print_segment_tree(value, 0, 0, nums.size() - 1, 0);
}

void testNumArray() {
    std::vector<int> nums;
    nums.push_back(1);
    nums.push_back(3);
    nums.push_back(5);
    NumArray num_array(nums);
    printf("%d\n", num_array.sumRange(0, 2));
    num_array.update(1, 2);
    printf("%d\n", num_array.sumRange(0, 2));
}

int main() {
    // testTrieNode();
    // testTrieTree();
    // testWordDictionary();
    // testDisjointSet();
    // testFindCircleNum();
    // testSegment();
    testNumArray();
    return 0;
}