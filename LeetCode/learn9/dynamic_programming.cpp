#include <assert.h>
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

/**
 * 动态规划(dynamic programming)
 * 是运筹学的一个分支，是求解决策过程最优化的数学方法。
 * 它利用个阶段之间的关系，逐个求解，最终求得全局最优解。
 * 1、确认原问题与子问题
 * 2、确认动态规划状态
 * 3、确认边界状态值
 * 4、确定状态转移方程
 */

class Solution {
   public:
    /**
     * 在爬楼梯时，每次可向上走1阶台阶或2阶台阶，问有n阶楼梯有多少种上楼方式。
     */
    int climbStairs(int n) {
        if (n < 3) {
            return n;
        }
        // 创建一个size为n每个值都是0的vector
        std::vector<int> dp(n, 0);
        dp[1] = 1;
        dp[2] = 2;
        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
    // 递归回溯法
    int climbStairs0(int n) {
        if (n == 1 || n == 2) {
            return n;
        }
        return climbStairs0(n - 1) + climbStairs0(n - 2);
    }

    /**
     * 在一条直线上，有n个房屋，每个房屋中有数量不等的财宝，有一个盗贼希望从房屋中盗取财宝，
     * 由于房屋中有报警器，如果同时从相邻的两个房屋中盗取财宝就会触发报警器。
     * 问在不触发报警器的前提下，最多可获取多少财宝？
     */
    int rob(std::vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }
        if (nums.size() == 1) {
            return nums[0];
        }
        std::vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        dp[1] = std::max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); i++) {
            dp[i] = std::max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        return dp[nums.size() - 1];
    }

    /**
     * 给定一个数组，求这个数组的连续子数组中，最大的那一段的和。
     *
     * 思路：求以第i个数字结尾的最大字段和，然后求最大的
     * dp[i] = max(dp[i-1]+nums[i], nums[i])
     */
    int maxSubArray(std::vector<int>& nums) {
        std::vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        int max_res = dp[0];
        for (int i = 1; i < nums.size(); i++) {
            dp[i] = std::max(dp[i - 1] + nums[i], nums[i]);
            if (max_res < dp[i]) {
                max_res = dp[i];
            }
        }
        return max_res;
    }

    /**
     * 已知不同面值的钞票，求如何用最少数量的钞票组成某个金额，求可以使用的最少钞票数量。
     * 如果任意数量的已知面值钞票都无法组成该金额，则返回-1。
     */
    int coinChange(std::vector<int>& coins, int amount) {
        // dp保存钞票张数
        std::vector<int> dp(amount + 1, -1);
        dp[0] = 0;
        for (int i = 1; i <= amount; i++) {
            for (int j = 0; j < coins.size(); j++) {
                // i可以被coins[j]与i-coins[j]组合
                if (i - coins[j] >= 0 && dp[i - coins[j]] != -1) {
                    // 更新dp[i]
                    if (dp[i] == -1 || dp[i] > dp[i - coins[j]] + 1) {
                        dp[i] = dp[i - coins[j]] + 1;
                    }
                }
            }
        }
        return dp[amount];
    }

    /**
     * 给定一个二维数组，其保存了一个数字三角形，求从数字三角形顶端到底端各数字和最小的路径之和，
     * 每次可以向下走相邻的两个位置。
     *
     * 思路：从下往上累加，每次取最小的
     */
    int minimumTotal(std::vector<std::vector<int> >& triangle) {
        if (triangle.size() == 0) {
            return 0;
        }
        std::vector<std::vector<int> > dp;
        for (int i = 0; i < triangle.size(); i++) {
            dp.push_back(std::vector<int>());
            for (int j = 0; j < triangle[i].size(); j++) {
                dp[i].push_back(0);
            }
        }
        for (int i = 0; i < dp.size(); i++) {
            dp[dp.size() - 1][i] = triangle[triangle.size() - 1][i];
        }
        for (int i = dp.size() - 2; i >= 0; i--) {
            for (int j = 0; j < dp[i].size(); j++) {
                dp[i][j] =
                    std::min(dp[i + 1][j], dp[i + 1][j + 1]) + triangle[i][j];
            }
        }
        return dp[0][0];
    }

    /**
     * 已知一个未排序数组，求这个数组最长上升子序列的长度。
     */
    int lengthOfLIS(std::vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }
        // 以第i个元素结尾的上升子序列长度
        std::vector<int> dp(nums.size(), 0);
        dp[0] = 1;
        int LIS = 1;
        for (int i = 1; i < dp.size(); i++) {
            dp[i] = 1;
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i] && dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                }
            }
            if (LIS < dp[i]) {
                LIS = dp[i];
            }
        }
        return LIS;
    }
    int lengthOfLIS2(std::vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }
        std::vector<int> stack;
        stack.push_back(nums[0]);
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > stack.back()) {
                stack.push_back(nums[i]);
            } else {
                for (int j = 0; j < stack.size(); j++) {
                    if (stack[j] >= nums[i]) {
                        stack[j] = nums[i];
                        break;
                    }
                }
            }
        }
        return stack.size();
    }
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
    int lengthOfLIS3(std::vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }
        std::vector<int> stack;
        stack.push_back(nums[0]);
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > stack.back()) {
                stack.push_back(nums[i]);
            } else {
                int pos = searchInsert(stack, nums[i]);
                stack[pos] = nums[i];
            }
        }
        return stack.size();
    }

    /**
     * 已知一个二维数组，其中存储了非负整数，找到从左上角到右下角的一条路径，使得路径上的和最小。
     * 移动过程中只能向下或向右
     */
    int minPathSum(std::vector<std::vector<int> >& grid) {
        if (grid.size() == 0) {
            return 0;
        }
        int row = grid.size();
        int column = grid[0].size();
        std::vector<std::vector<int> > dp(row, std::vector<int>(column, 0));
        dp[0][0] = grid[0][0];
        // 第一行
        for (int i = 1; i < column; i++) {
            dp[0][i] = dp[0][i - 1] + grid[0][i];
        }
        // 遍历剩余所有行
        for (int i = 1; i < row; i++) {
            // 先算第一列
            dp[i][0] = dp[i - 1][0] + grid[i][0];
            // 其他列
            for (int j = 1; j < column; j++) {
                dp[i][j] = std::min(dp[i - 1][j], dp[i][j - 1] + grid[i][j]);
            }
        }
        return dp[row - 1][column - 1];
    }

    /**
     * 已知一个二维数组，左上角代表骑士的位置，右下角代表公主的位置，二维数组中存储整数，
     * 正数可以给骑士增加生命值，负数会减少骑士的生命值，问骑士初始时至少是多少生命值，
     * 才可保证骑士在行走的过程中至少保持生命值为1(骑士只能向下或向右行走)
     */
    int calculateMinimumHP(std::vector<std::vector<int> >& dungeon) {
        if (dungeon.size() == 0) {
            return 0;
        }
        std::vector<std::vector<int> > dp(
            dungeon.size(), std::vector<int>(dungeon[0].size(), 0));
        int row = dungeon.size();
        int column = dungeon[0].size();
        dp[row - 1][column - 1] = std::max(1, 1 - dungeon[row - 1][column - 1]);
        for (int i = column - 2; i >= 0; i--) {
            dp[row - 1][i] =
                std::max(1, dp[row - 1][i + 1] - dungeon[row - 1][i]);
        }
        for (int i = row - 2; i >= 0; i--) {
            dp[i][column - 1] =
                std::max(1, dp[i + 1][column - 1] - dungeon[i][column - 1]);
        }
        for (int i = row - 2; i >= 0; i--) {
            for (int j = column - 2; j >= 0; j--) {
                int dp_min = std::min(dp[i + 1][j], dp[i][j + 1]);
                dp[i][j] = std::max(1, dp_min - dungeon[i][j]);
            }
        }
        return dp[0][0];
    }
};

void testRob() {
    int test[] = {5, 2, 6, 3, 1, 7};
    std::vector<int> nums;
    for (int i = 0; i < 6; i++) {
        nums.push_back(test[i]);
    }
    Solution sol;
    printf("%d\n", sol.rob(nums));
}

void testMaxSubArray() {
    std::vector<int> nums;
    nums.push_back(-2);
    nums.push_back(11);
    nums.push_back(-3);
    nums.push_back(4);
    nums.push_back(-1);
    nums.push_back(2);
    nums.push_back(1);
    nums.push_back(-5);
    nums.push_back(4);
    Solution sol;
    printf("\n%d\n", sol.maxSubArray(nums));
}

void testCoinChange() {
    Solution sol;
    std::vector<int> coins;
    coins.push_back(1);
    coins.push_back(2);
    coins.push_back(5);
    coins.push_back(7);
    coins.push_back(10);
    for (int i = 0; i <= 14; i++) {
        printf("dp[%d] = %d\n", i, sol.coinChange(coins, i));
    }
}

void testMinimumTotal() {
    std::vector<std::vector<int> > triangle;
    int test[][10] = {
        {2},
        {3, 4},
        {6, 5, 7},
        {4, 1, 8, 3},
    };
    for (int i = 0; i < 4; i++) {
        triangle.push_back(std::vector<int>());
        for (int j = 0; j < i + 1; j++) {
            triangle[i].push_back(test[i][j]);
        }
    }
    Solution sol;
    printf("%d\n", sol.minimumTotal(triangle));
}

void testLengthOfLIS() {
    std::vector<int> nums;
    nums.push_back(1);
    nums.push_back(7);
    nums.push_back(8);
    nums.push_back(4);
    nums.push_back(2);
    nums.push_back(1);
    Solution sol;
    printf("%d\n", sol.lengthOfLIS2(nums));
}

void testMinPathSum() {
    int test[][3] = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1},
    };
    std::vector<std::vector<int> > grid;
    for (int i = 0; i < 3; i++) {
        grid.push_back(std::vector<int>());
        for (int j = 0; j < 3; j++) {
            grid[i].push_back(test[i][j]);
        }
    }
    Solution sol;
    printf("%d\n", sol.minPathSum(grid));
}

void testCalculateMinimumHP() {
    int test[][3] = {
        {-2, -3, 3},
        {-5, -10, 1},
        {10, 30, -5},
    };
    std::vector<std::vector<int> > dungeon;
    for (int i = 0; i < 3; i++) {
        dungeon.push_back(std::vector<int>());
        for (int j = 0; j < 3; j++) {
            dungeon[i].push_back(test[i][j]);
        }
    }
    Solution sol;
    printf("%d\n", sol.calculateMinimumHP(dungeon));
}

int main() {
    Solution sol;
    // printf("%d", sol.climbStairs0(3));
    // printf("%d", sol.climbStairs(4));
    // testRob();
    // testMaxSubArray();
    // testCoinChange();
    // testMinimumTotal();
    // testLengthOfLIS();
    // testMinPathSum();
    testCalculateMinimumHP();
    return 0;
}