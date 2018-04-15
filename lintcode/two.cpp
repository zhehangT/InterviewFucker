/**
* Author: T_Zhehang 
* Date: 18-4-7
*/
#include <unordered_set>
#include "util.h"
using namespace std;
//104. Merge K Sorted Lists
ListNode *mergeKLists(vector<ListNode*> &lists) {
    // write your code here

    ListNode* head = new ListNode(-1);
    ListNode* node = head;

    vector<bool> flag(lists.size(), true);

    for(int i = 0; i < lists.size();){
        ListNode* minNode = nullptr;
        int min_index = -1;
        for(int j = 0; j < lists.size();j++){
            ListNode* tmpNode = lists[j];
            if(tmpNode == nullptr && flag[j]){
                flag[j] = false;
                i++;
                continue;
            }
            if(minNode == nullptr || tmpNode->val < minNode->val){
                minNode = tmpNode;
                min_index = j;
            }
        }
        node->next = minNode;
        node = node->next;
        lists[min_index] = lists[min_index]->next;
    }
    return head->next;

}

int minCut(string s) {
    int n = s.length();
    int f[n + 1];
    bool isPalin[n][n];

    for (int i = 0; i < n; i++) {
        isPalin[i][i] = true;
        if (i + 1 < n) {
            isPalin[i][i + 1] = (s[i] == s[i + 1]);
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 2; j < n; j++) {
            isPalin[i][j] = isPalin[i + 1][j - 1] && (s[i] == s[j]);
        }
    }

    f[0] = -1;
    for (int i = 1; i <= n; i++) {
        f[i] = i - 1;
        for (int j = 0; j < i; j++) {
            if (isPalin[j][i - 1]) {
                f[i] = min(f[i], f[j] + 1);
            }
        }
    }

    return f[n];
}

//119. 编辑距离
int minDistance(string &word1, string &word2) {
    // write your code here

    if(word1.empty())
        return word2.size();
    if(word2.empty())
        return word1.size();

    vector<vector<int>> dp(word1.size()+1, vector<int>(word2.size()+1));
    for(int i = 0; i <= word1.size(); i++){
        dp[i][0] = i;
    }
    for(int i = 0; i <= word2.size(); i++){
        dp[0][i] = i;
    }

    for(int i = 1; i <= word1.size(); i++){
        for(int j = 1; j <= word2.size(); j++){
            if(word1[i-1] == word2[j-1]){
                dp[i][j] = min(min(dp[i][j-1], dp[i-1][j])+1, dp[i-1][j-1]);
            }else{
                dp[i][j] = min(min(dp[i][j-1], dp[i-1][j])+1, dp[i-1][j-1]+1);
            }
        }
    }

    return dp[word1.size()][word2.size()];

}


int max_ = INT_MAX;

bool isChange(string& word, string& end){

    int count = 0;
    for(int i = 0; i < word.size(); i++){
        if(word[i] != end[i]){
            count++;
            if(count == 2)
                return false;
        }
    }
    return true;
}

void findLadders(vector<vector<string>>& results, vector<string> result, string word, string end,
                 unordered_set<string> dict){

    if(result.size() >= max_)
        return;

    if(isChange(word, end)){
        result.emplace_back(end);
        if(result.size() < max_){
            results.clear();
            results.emplace_back(result);
            max_ = result.size();
        }else if(result.size() == max_){
            results.emplace_back(result);
        }
        return;
    }
    for(auto iter = dict.begin(); iter != dict.end(); iter++){
        string tmp = *iter;
        if(tmp != word && isChange(word, tmp)){
            unordered_set<string> tmp_dict = dict;
            vector<string> tmp_result = result;
            tmp_dict.erase(tmp);
            tmp_result.emplace_back(tmp);
            findLadders(results, tmp_result, tmp, end, tmp_dict);
        }
    }
}



vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
    // write your code here
    vector<vector<string>> results;
    vector<string> result;
    dict.erase(start);
    result.emplace_back(start);
    findLadders(results, result, start, end, dict);
    return results;
}
//141. x的平方根
int findSqrt(int x, int i, int j){

    if(i >= j)
        return j-1;

    int mid = (i+j)/2;
    int tmp = mid*mid;
    if(mid * mid > x)
        return findSqrt(x, i, mid-1);

    if(tmp == x || tmp < x && (mid+1)*(mid+1) > x)
        return mid;

    else
        return findSqrt(x, mid+1, j);

}

int sqrt(int x) {
    // write your code here
    int high = min(46341, x/2);
    return findSqrt(x, 0, high);

}



int main(){

    cout << sqrt(2147483647);
}