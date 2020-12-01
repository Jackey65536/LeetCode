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
#include <numeric>

struct Qitem {
    std::string node;
    int parent_pos;
    int step;
    Qitem(std::string _node, int _parent_pos, int _step)
        : node(_node), parent_pos(_parent_pos), step(_step) {}
};

struct Witem {
    int x;
    int y;
    int h;
    Witem(int _x, int _y, int _h) : x(_x), y(_y), h(_h) {}
};

struct cmp {
    bool operator()(const Witem& a, const Witem& b) { return a.h > b.h; }
};

void testWitem() {
    std::priority_queue<Witem, std::vector<Witem>, cmp> Q;
    Q.push(Witem(0, 0, 5));
    Q.push(Witem(1, 3, 2));
    Q.push(Witem(5, 2, 4));
    Q.push(Witem(0, 1, 8));
    Q.push(Witem(6, 7, 1));
    while (!Q.empty())
    {
        int x = Q.top().x;
        int y = Q.top().y;
        int h = Q.top().h;
        printf("x = %d y = %d h = %d\n", x, y, h);
        Q.pop();
    }
}

void DFS(std::vector<std::vector<int> >& mark,
         std::vector<std::vector<char> >& grid, int x, int y) {
    mark[x][y] = 1;
    static const int dx[] = {-1, 1, 0, 0};
    static const int dy[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; i++) {
        int newx = x + dx[i];
        int newy = y + dy[i];
        if (newx < 0 || newx >= mark.size() || newy < 0 ||
            newy >= mark[newx].size()) {
            continue;
        }
        if (mark[newx][newy] == 0 && grid[newx][newy] == '1') {
            DFS(mark, grid, newx, newy);
        }
    }
}

void BFS(std::vector<std::vector<int> >& mark,
         std::vector<std::vector<char> >& grid, int x, int y) {
    mark[x][y] = 1;
    static const int dx[] = {-1, 1, 0, 0};
    static const int dy[] = {0, 0, -1, 1};
    std::queue<std::pair<int, int> > Q;
    Q.push(std::make_pair(x, y));
    mark[x][y] = 1;
    while (!Q.empty()) {
        x = Q.front().first;
        y = Q.front().second;
        Q.pop();
        for (int i = 0; i < 4; i++) {
            int newx = dx[i] + x;
            int newy = dy[i] + y;
            if (newx < 0 || newx >= mark.size() || newy < 0 ||
                newy >= mark[newx].size()) {
                continue;
            }
            if (mark[newx][newy] == 0 && grid[newx][newy] == '1') {
                Q.push(std::make_pair(newx, newy));
                mark[newx][newy] = 1;
            }
        }
    }
}

class Solution {
public:
    /**
     * 用一个二维数组代表一张地图，这张地图由字符‘0’与字符’1‘组成，其中’0‘字符代表水域，
     * ’1‘字符代表小岛土地，小岛‘1‘被水‘0’所包围，当小岛土地‘1’在水平和垂直方向相连接时，
     * 认为是同一块土地。求这张地图中小岛的数量。
     */
    int numIslands(std::vector<std::vector<char> >& grid) {
        int island_num = 0;
        std::vector<std::vector<int> > mark;
        for (size_t i = 0; i < grid.size(); i++) {
            mark.push_back(std::vector<int>());
            for (size_t j = 0; j < grid[i].size(); j++) {
                mark[i].push_back(0);
            }
        }
        for (size_t i = 0; i < grid.size(); i++) {
            for (size_t j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == '1' && mark[i][j] == 0) {
                    DFS(mark, grid, i, j);
                    island_num++;
                }
            }
        }
        return island_num;
    }

    /**
     * 已知两个单词(分别是起始单词和结束单词)，一个单词词典，
     * 根据转换规则计算从起始单词到结束单词的最短转换步数
     * 1、在转换时，只能转换单词中的1个字符
     * 2、转换得到的新单词，必须在单词词典中
     */
    bool connect(const std::string& word1, const std::string& word2) {
        int cnt = 0;
        for (int i = 0; i < word1.size(); i++) {
            if (word1[i] != word2[i]) {
                cnt++;
            }
        }
        return cnt == 1;
    }
    void construct_graph(
        std::string& beginWord, std::vector<std::string>& wordList,
        std::map<std::string, std::vector<std::string> >& graph) {
        wordList.push_back(beginWord);
        for (int i = 0; i < wordList.size(); i++) {
            graph[wordList[i]] = std::vector<std::string>();
        }
        for (int i = 0; i < wordList.size(); i++) {
            for (int j = i + 1; j < wordList.size(); j++) {
                if (connect(wordList[i], wordList[j])) {
                    graph[wordList[i]].push_back(wordList[j]);
                    graph[wordList[j]].push_back(wordList[i]);
                }
            }
        }
    }
    int BFS_graph(std::string& beginWord, std::string& endWord,
                  std::map<std::string, std::vector<std::string> >& graph) {
        // 搜索队列<顶点，步数>
        std::queue<std::pair<std::string, int> > Q;
        std::set<std::string> visit;  // 记录已访问的顶点
        Q.push(std::make_pair(beginWord, 1));
        visit.insert(beginWord);
        while (!Q.empty()) {
            std::string node = Q.front().first;
            int step = Q.front().second;
            Q.pop();
            if (node == endWord) {
                return step;
            }
            const std::vector<std::string>& neighbors = graph[node];
            for (int i = 0; i < neighbors.size(); i++) {
                if (visit.find(neighbors[i]) == visit.end()) {
                    Q.push(std::make_pair(neighbors[i], step + 1));
                    visit.insert(neighbors[i]);
                }
            }
        }

        return 0;
    }
    int ladderLength(std::string beginWord, std::string endWord,
                     std::vector<std::string>& wordList) {
        std::map<std::string, std::vector<std::string> > graph;
        construct_graph(beginWord, wordList, graph);
        return BFS_graph(beginWord, endWord, graph);
    }

    void construct_graph2(
        std::string& beginWord, std::vector<std::string>& wordList,
        std::map<std::string, std::vector<std::string> >& graph) {
        int has_begin_word = 0;
        for (int i = 0; i < wordList.size(); i++) {
            if (wordList[i] == beginWord) {
                has_begin_word = 1;
            }
            graph[wordList[i]] = std::vector<std::string>();
        }
        for (int i = 0; i < wordList.size(); i++) {
            for (int j = i + 1; j < wordList.size(); j++) {
                if (connect(wordList[i], wordList[j])) {
                    graph[wordList[i]].push_back(wordList[j]);
                    graph[wordList[j]].push_back(wordList[i]);
                }
            }
            if (has_begin_word == 0 && connect(beginWord, wordList[i])) {
                graph[beginWord].push_back(wordList[i]);
            }
        }
    }
    void BFS_graph2(
        std::string& beginWord, std::string& endWord,
        std::map<std::string, std::vector<std::string> >& graph,
        std::vector<Qitem>& Q,  // 使用vector实现队列，可保存所有信息
        std::vector<int>& end_word_pos) {  // 终点endWord所在队列的位置下标
        std::map<std::string, int> visit;  // <单词，步数>
        int min_step = 0;                  // 到达endWord的最小步数
        Q.push_back(Qitem(beginWord, -1, 1));
        visit[beginWord] = 1;
        int front = 0;
        while (front != Q.size()) {
            const std::string& node = Q[front].node;
            int step = Q[front].step;
            // step > min_step时，代表多有到终点的路径都搜索完成
            if (min_step != 0 && step > min_step) {
                break;
            }
            if (node == endWord) {
                // 当搜搜索到结果时，记录到达终点的最小步数
                min_step = step;
                end_word_pos.push_back(front);
            }
            const std::vector<std::string>& neighbors = graph[node];
            for (int i = 0; i < neighbors.size(); i++) {
                // 节点没被访问，或另一条最短路径
                if (visit.find(neighbors[i]) == visit.end() ||
                    visit[neighbors[i]] == step + 1) {
                    Q.push_back(Qitem(neighbors[i], front, step + 1));
                    visit[neighbors[i]] = step + 1;
                }
            }
            front++;
        }
    }

    std::vector<std::vector<std::string> > findLadders(
        std::string beginWord, std::string endWord,
        std::vector<std::string>& wordList) {
        std::map<std::string, std::vector<std::string> > graph;
        construct_graph2(beginWord, wordList, graph);
        std::vector<Qitem> Q;
        std::vector<int> end_word_pos;
        BFS_graph2(beginWord, endWord, graph, Q, end_word_pos);
        std::vector<std::vector<std::string> > result;
        for (int i = 0; i < end_word_pos.size(); i++) {
            int pos = end_word_pos[i];
            std::vector<std::string> path;
            while (pos != -1) {
                path.push_back(Q[pos].node);
                pos = Q[pos].parent_pos;
            }
            result.push_back(std::vector<std::string>());
            for (int j = path.size() - 1; j >= 0; j--) {
                result[i].push_back(path[j]);
            }
        }
        return result;
    }

    /**
     * 已知一个数组，保存了n个(n<=15)个火柴棍，问可否使用这n个火柴棍摆成1个正方形
     */
    bool generate(int i, std::vector<int>& nums, int target, int bucket[]) {
        if (i >= nums.size()) {
            return bucket[0] == target && bucket[1] == target &&
                   bucket[2] == target && bucket[3] == target;
        }
        for (int j = 0; j < 4; j++) { // 在4个桶中分别尝试
            if (bucket[j] + nums[i] > target) {
                continue;
            }
            bucket[j] += nums[i]; // 放入j桶中
            if (generate(i + 1, nums, target, bucket)) {
                return true;
            }
            bucket[j] -= nums[i];
        }
        return false;
    }
    bool makesquare(std::vector<int>& nums) {
        if (nums.size() < 4) {
            return false;
        }
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
        }
        // std::accumulate(nums.begin(), nums.end(), 0);
        if (sum % 4) {
            return false;
        }
        // 从大到小排序
        std::sort(nums.begin(), nums.end());
        int bucket[4] = {0};
        return generate(0, nums, sum / 4, bucket);
    }
    // 位运算解法
    bool makesquare2(std::vector<int>& nums) {
        if (nums.size() < 4) {
            return false;
        }
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
        }
        if (sum % 4) {
            return false;
        }
        int target = sum / 4;
        // 所有满足条件的一个边代表的集合
        std::vector<int> ok_subset;
        // 所有满足条件的两个边代表的集合
        std::vector<int> ok_half;
        int all = 1 << nums.size();
        // 求出所有和为target的排列组合
        for (int i = 0; i < all; i++) {
            int sum = 0;
            for (int j = 0; j < nums.size(); j++) {
                if (i & (1 << j)) {
                    sum += nums[j];
                }
            }
            if (sum == target) {
                ok_subset.push_back(i);
            }
        }
        // 两两组合
        for (int i = 0; i < ok_subset.size(); i++) {
            for (int j = i + 1; j < ok_subset.size(); j++) {
                if ((ok_subset[i] & ok_subset[j]) == 0) {
                    ok_half.push_back(ok_subset[i] | ok_subset[j]);
                }
            }
        }
        // 两两组合
        for (int i = 0; i < ok_half.size(); i++) {
            for (int j = i + 1; j < ok_half.size(); j++) {
                if ((ok_half[i] & ok_half[j]) == 0) {
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * 已知一个m*n的二维数组，数组存储正整数，代表一个个单元的高度（立方体），
     * 将这些立方体想象成水槽，问如果下雨这些立方体中会有多少积水。
    */
    int trapRainWater(std::vector<std::vector<int> >& heightMap) {
        std::priority_queue<Witem, std::vector<Witem>, cmp> Q;
        if (heightMap.size() < 3 || heightMap[0].size() < 3) {
            return 0;
        }
        int row = heightMap.size();
        int column = heightMap[0].size();
        std::vector<std::vector<int> > mark;
        for (int i = 0; i < row; i++) {
            mark.push_back(std::vector<int>());
            for (int j = 0; j < column; j++) {
                mark[i].push_back(0);
            }
        }
        for (int i = 0; i < row; i++) {
            Q.push(Witem(i, 0, heightMap[i][0]));
            mark[i][0] = 1;
            Q.push(Witem(i, column - 1, heightMap[i][column - 1]));
            mark[i][column - 1] = 1;
        }
        for (int i = 1; i < column - 1; i++) {
            Q.push(Witem(0, i, heightMap[0][i]));
            mark[0][i] = 1;
            Q.push(Witem(row - 1, i, heightMap[row - 1][i]));
            mark[row - 1][i] = 1;
        }
        /**
         * 方向数组
         *          (-1,0)
         * (0,-1)   (0, 0)   (0,1)
         *          (1, 0)
         */
        static const int dx[] = {-1, 1, 0, 0};
        static const int dy[] = {0, 0, -1, 1};
        int result = 0;
        while (!Q.empty()) {
            int x = Q.top().x;
            int y = Q.top().y;
            int h = Q.top().h;
            Q.pop();
            for (int i = 0; i < 4; i++) {
                int newx = x + dx[i];
                int newy = y + dy[i];
                if (newx < 0 || newx >= row || newy < 0 || newy >= column ||
                    mark[newx][newy]) {
                    continue;
                }
                if (h > heightMap[newx][newy]) {
                    result += (h - heightMap[newx][newy]);
                    heightMap[newx][newy] = h;
                }
                Q.push(Witem(newx, newy, heightMap[newx][newy]));
                mark[newx][newy] = 1;
            }
        }

        return result;
    }
};

void testNumIslands() {
    std::vector<std::vector<char> > grid;
    char str[10][10] = {"11100", "11000", "00100", "00011"};
    for (size_t i = 0; i < 4; i++) {
        grid.push_back(std::vector<char>());
        for (size_t j = 0; j < 5; j++) {
            grid[i].push_back(str[i][j]);
        }
    }
    Solution solve;
    printf("%d\n", solve.numIslands(grid));
}

void testLadderLength() {
    std::string beginWord = "hit";
    std::string endWord = "cog";
    std::vector<std::string> wordList;
    wordList.push_back("hot");
    wordList.push_back("dot");
    wordList.push_back("dog");
    wordList.push_back("lot");
    wordList.push_back("log");
    wordList.push_back("cog");
    Solution solve;
    int result = solve.ladderLength(beginWord, endWord, wordList);
    printf("result = %d\n", result);
}

void testFindLadders() {
    std::string beginWord = "hit";
    std::string endWord = "cog";
    std::vector<std::string> wordList;
    wordList.push_back("hot");
    wordList.push_back("dot");
    wordList.push_back("dog");
    wordList.push_back("lot");
    wordList.push_back("log");
    wordList.push_back("cog");
    Solution solve;
    std::vector<std::vector<std::string> > result =
        solve.findLadders(beginWord, endWord, wordList);
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            printf("[%s] ", result[i][j].c_str());
        }
        printf("\n");
    }
}

void testMakesquare() {
    std::vector<int> nums;
    nums.push_back(1);
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(4);
    nums.push_back(3);
    nums.push_back(2);
    nums.push_back(3);
    Solution sol;
    printf("%d\n", sol.makesquare(nums));
}

void testTrapRainWater() {
    int test[][10] = {
        {9, 9, 9, 2, 3}, {9, 1, 7, 1, 3}, {9, 9, 9, 3, 3}};
        // {1, 4, 3, 1, 3, 2}, {3, 2, 1, 3, 2, 4}, {2, 3, 3, 2, 3, 1}};
    std::vector<std::vector<int> > heightMap;
    for (int i = 0; i < 3; i++) {
        heightMap.push_back(std::vector<int>());
        for (int j = 0; j < 6; j++) {
            heightMap[i].push_back(test[i][j]);
        }
    }
    Solution sol;
    printf("%d\n", sol.trapRainWater(heightMap));
}

int main() {
    // testNumIslands();
    // testLadderLength();
    // testFindLadders();
    // testMakesquare();
    // testWitem();
    testTrapRainWater();
    return 0;
}