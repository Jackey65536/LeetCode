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
    /**
     * 输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。
     * 假设输入的前序遍历和中寻遍历的结果中都不含有重复的数字。
     * eg：
     *  preorder = [3, 9, 20, 15, 7]
     *  inorder = [9, 3, 15, 20, 7]
    */
    TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
        if (preorder.size() == 0 || inorder.size() == 0) {
            return NULL;
        }
        TreeNode* root = new TreeNode(preorder[0]);
        std::vector<int> leftpre, leftin, rightpre, rightin;
        std::vector<int>::iterator it =
            std::find(inorder.begin(), inorder.end(), preorder[0]);
        int index = &*it - &inorder[0];
        for (int i = 0; i < inorder.size(); i++) {
            if (i < index) {
                leftin.push_back(inorder[i]);
            } else if (i > index) {
                rightin.push_back(inorder[i]);
            }
        }
        if (leftin.size() > 0) {
            for (int i = 1; i < index + 1; i++) {
                leftpre.push_back(preorder[i]);
            }
            root->left = buildTree(leftpre, leftin);
        }
        if (rightin.size() > 0) {
            for (int i = index + 1; i < preorder.size(); i++) {
                rightpre.push_back(preorder[i]);
            }
            root->right = buildTree(rightpre, rightin);
        }
        return root;
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
};

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

void testBuildTree() {
    int preorder[] = {3, 9, 20, 15, 7};
    int inorder[] = {9, 3, 15, 20, 7};
    std::vector<int> prenums;
    std::vector<int> innums;
    for (int i = 0; i < 5; i++)
    {
        prenums.push_back(preorder[i]);
        innums.push_back(inorder[i]);
    }
    Solution sol;
    TreeNode *root = sol.buildTree(prenums, innums);
    preorder_print1(root, 0);
    printf("\n");
    preorder_print2(root, 0);
    printf("\n");
    preorder_print3(root, 0);
}

int main() {
    // testPathSum();
    // testFlatten();
    // testRightSideView();
    // testGraphNode();
    // testGraph();
    // testCanFinish();
    testBuildTree();

    return 0;
}