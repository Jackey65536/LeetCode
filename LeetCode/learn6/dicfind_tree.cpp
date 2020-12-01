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

// Binary Tree
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct BSTNode {
    int val;
    int count;  // 记录左子树节点个数
    BSTNode* left;
    BSTNode* right;
    BSTNode(int x) : val(x), left(NULL), right(NULL), count(0) {}
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

class Solution {
   public:
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
    std::vector<int> countSmaller(std::vector<int>& nums) {
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
};

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

int main() {
    Solution solve;
    // testSearchRange();
    // testBST_insert();
    // testBST_search();
    // testSerialize();
    testCountSmaller();

    return 0;
}