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

/**
 * 哈希表(Hash
 * Table，也叫散列表)，是根据关键字值(key)直接进行访问的数据结构，
 * 它通过把关键字值映射到列表中一个位置(数组下标)来直接访问，以加快查找关键字值的速度。
 * 这个映射函数叫做哈希(散列)函数，存放记录的数组叫做哈希(散列)表。
 */

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
    testMinWindow();
}