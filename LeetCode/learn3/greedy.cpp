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
 * 贪心法：遵循某种规律，不断贪心的选取当前最优策略的算法设计方法
 */

bool cmp2(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return a.first < b.first;
}
bool cmp3(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return a.first > b.first;
}

class Solution {
   public:
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
};

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
    printf("请输入N: ");
    scanf("%d", &N);
    for (size_t i = 0; i < N; i++) {
        scanf("%d %d", &dis, &fuel);
        stop.push_back(std::make_pair(dis, fuel));
    }
    scanf("%d %d", &L, &P);
    Solution sol;
    printf("%d\n", sol.get_minimum_stop(L, P, stop));
}

int main() {
    // payMoney();
    // testRemoveKdigits();
    testCanJump();
    // testMinimumStop();

    return 0;
}