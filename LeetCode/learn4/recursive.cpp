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

/**
 * 回溯法：当探索到某一步时，发现原先选择打不到目标，就退回一步重新选择，
 * 这种走不通就退回再走的技术就是回溯法。
 */

class Solution {
   public:
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

    bool check(int row, int col, const std::vector<int> columns) {
        for (int r = 0; r < row; r++) {
            if (columns[r] == col || row - r == abs(columns[r] - col)) {
                return false;
            }
        }
        return true;
    }
    void backtracking(int n, int row, std::vector<int>& columns, int& count) {
        if (n == row) {
            for (int r = 0; r < n; r++) {
                for (int col = 0; col < n; col++) {
                    printf(columns[r] == col ? "q" : ".");
                }
                printf("\n");
            }
            printf("\n");
            count++;
            return;
        }
        for (int col = 0; col < n; col++) {
            columns[row] = col;
            if (check(row, col, columns)) {
                backtracking(n, row + 1, columns, count);
            }
            columns[row] = -1;
        }
    }
    int solveNQueens2(int n) {
        std::vector<int> columns(n);
        int count = 0;
        backtracking(n, 0, columns, count);
        return count;
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
};

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

int main() {
    Solution sol;
    // testCombinationSum();
    // testGenerate3();
    // testSolveNQueens();
    printf("%d\n", sol.solveNQueens2(4));
    // test_merge_sort();
    // testCountSmaller();

    return 0;
}