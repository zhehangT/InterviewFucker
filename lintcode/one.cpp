/**
* Author: T_Zhehang
* Date: 18-3-26
*/



#include "util.h"
using namespace std;

//7. 二叉树的序列化与反序列化
string serialize(TreeNode * root) {
    // write your code here
    if(root == nullptr)
        return "{}";
    vector<TreeNode*> vector_tree;
    vector_tree.emplace_back(root);
    for(int i = 0; i < vector_tree.size(); i++){
        TreeNode* node = vector_tree[i];
        if(node == nullptr)
            continue;
        else{
            vector_tree.emplace_back(node->left);
            vector_tree.emplace_back(node->right);
        }
    }
    while(vector_tree.size() > 0 && vector_tree[vector_tree.size()-1] == nullptr)
        vector_tree.pop_back();

    stringstream ss;
    ss << "{" << vector_tree[0]->val;
    for(int i = 1; i < vector_tree.size(); i++){
        if(vector_tree[i] == nullptr)
            ss << ",#";
        else
            ss << "," << vector_tree[i]->val;
    }
    ss << "}";
    return ss.str();

}

vector<string> split(string data){

    vector<string> result;
    int start_index=0;
    int end_index;
    while((end_index = data.find(",", start_index)) != string::npos){
        result.emplace_back(data.substr(start_index, end_index - start_index));
        start_index = end_index + 1;
    }
    result.emplace_back(data.substr(start_index, data.size() - start_index));
    return result;

}

TreeNode * deserialize(string &data) {
    // write your code here
    if(data.size() <= 2)
        return nullptr;

    vector<string> vals = split(data.substr(1, data.size() - 2));
    TreeNode* root = new TreeNode(atoi(vals[0].c_str()));
    queue<TreeNode*> q_tree;
    q_tree.push(root);
    bool is_left = true;
    for(int i = 1; i < vals.size(); i++){
        if(vals[i] != "#"){
            TreeNode* node = new TreeNode(atoi(vals[i].c_str()));
            if(is_left)
                q_tree.front()->left = node;
            else
                q_tree.front()->right = node;
            q_tree.push(node);
        }

        if (!is_left) {
            q_tree.pop();
        }

        is_left = !is_left;
    }
    return root;
}

//16 重复字符的全排列
void permuteUnique(vector<vector<int>> results, vector<int> nums, int i){

    if(i == nums.size() -1){
        results.emplace_back(nums);
        return;
    }
    for(int j = i; j < nums.size(); j++){

        bool is_permute = true;
        for(int k = 0; k < j; k++){
            if(nums[k] == nums[j]){
                is_permute = false;
                break;
            }
        }
        if(is_permute) {
            swap(nums[i], nums[j]);
            permuteUnique(results, nums, i + 1);
            swap(nums[i], nums[j]);
        }
    }
}

vector<vector<int>> permuteUnique(vector<int> &nums) {
    // write your code here
    vector<vector<int>> results;
    if(nums.empty()){
        results.emplace_back(nums);
        return results;
    }
    permuteUnique(results, nums, 0);
    return results;
}

//32. 最小子串覆盖
string minWindow(string &source , string &target) {
    // write your code here
    if(source.size() < target.size() || target.size() == 0)
        return "";

    unordered_map<char, int> target_count;
    for(auto c : target){
        target_count[c]++;
    }

    int i = 0;
    int j = 0;
    int min_len = INT_MAX;
    string result = "";
    int target_left = target_count.size();

    for(; i <= source.size()-target.size(); i++){

        while(j < source.size() && target_left != 0){
            target_count[source[j]]--;
            if(target_count[source[j]] == 0){
                target_left--;
            }
            j++;
        }

        if(target_left == 0 && j - i < min_len){
            min_len = j - i;
            result = source.substr(i, min_len);
        }

        if(target_count[source[i]] == 0){
            target_left++;
        }
        target_count[source[i]]++;
    }
    return result;
}

//
int searchMatrix(vector<vector<int>> &matrix, int target) {
    // write your code here
    int row = matrix.size();
    if(row == 0)
        return 0;
    int col = matrix[0].size();

    int j = col-1;
    int i = 0;
    int count = 0;
    while( i != row-1 && j != 0  ){
        if(matrix[i][j] == target){
            count++;
            if(i != row-1)
                i++;
            if(j != 0)
                j--;
        }
        else if(matrix[i][j] < target){
            if(i != row-1)
                i++;
            else
                break;
        }else{
            if(j != 0)
                j--;
            else
                break;
        }
    }

    if(matrix[row-1][0] == target)
        ++count;
    return count;
}

// 39. 恢复旋转排序数组
void recoverRotatedSortedArray(vector<int> &nums) {
    // write your code here
    if(nums.size() <=1 )
        return;
    int offset = 1;
    for(; offset < nums.size()-1; offset++){
        if(nums[offset] < nums[offset-1])
            break;
    }
    if( offset == nums.size()-1 )
        return;

    for(int i = 0; i < offset/2; i++){
        swap(nums[i], nums[offset-i-1]);
    }

    for(int i = 0; i < (nums.size() - offset)/2; i++){
        swap(nums[offset+i], nums[nums.size()-i-1]);
    }

    for(int i = 0; i < nums.size()/2; i++){
        swap(nums[i], nums[nums.size()-i-1]);
    }

}

int maxTwoSubArrays(vector<int> &nums) {
    // write your code here

    vector<int> left_max = vector<int>(nums.size());
    vector<int> right_max = vector<int>(nums.size());

    left_max[0] = nums[0];
    right_max[nums.size()-1] = nums[nums.size()-1];
    for(int i = 1; i < nums.size(); i++){
        left_max[i] = max(left_max[i-1]+nums[i], nums[i]);
        right_max[nums.size()-i-1] = max(nums[nums.size()-i-1],
                                         right_max[nums.size()-i] + nums[nums.size()-i-1]);
    }

    int result = INT_MIN;
    for(int i = 0; i < nums.size(); i++)
        for(int j = i+1; j < nums.size(); j++){
            result = max(result, left_max[i]+right_max[j]);
        }
    return result;
}

//45. 最大子数组差
int maxDiffSubArrays(vector<int> &nums) {
    // write your code here

    vector<int> left_max(nums.size());
    vector<int> left_min(nums.size());
    left_max[0] = left_min[0] = nums[0];

    vector<int> right_max(nums.size());
    vector<int> right_min(nums.size());
    int end_index = nums.size() - 1;
    right_max[end_index] = right_min[end_index] = nums[end_index];

    for(int i = 1; i < nums.size(); i++){
        left_max[i] = max(left_max[i-1]+nums[i], nums[i]);
        left_min[i] = min(left_min[i-1]+nums[i], nums[i]);
        right_max[end_index-i] = max(right_max[end_index-i+1]+nums[end_index-i],
                                     nums[end_index-i]);
        right_min[end_index-i] = min(right_min[end_index-i+1]+nums[end_index-i],
                                     nums[end_index-i]);
    }

    int result = INT_MIN;
    for(int i = 0; i < nums.size(); i++){
        for(int j = i+1; j < nums.size(); j++){
            result = max(result, left_max[i]-right_min[j]);
            result = max(result, right_max[j]-left_min[i]);
        }
    }
    return result > 0 ? result : -result;
}

//48 给定一个整型数组，找到主元素，它在数组中的出现次数严格大于数组元素个数的1/k。
int majorityNumber(vector<int> &nums, int k) {
    // write your code here
    map<int, int> count_map;

    for(int i = 0; i < nums.size(); i++){
        count_map[nums[i]]++;
        if(count_map.size() == k){
            for(auto iter = count_map.begin(); iter != count_map.end();){
                iter->second--;
                if(iter->second == 0)
                    count_map.erase(iter++);
                else
                    iter++;
            }
        }
    }

    for(auto it = count_map.begin(); it != count_map.end(); it++) {
        it->second = 0;
    }

    int maxCount = 0;
    int result;
    for(int i = 0; i < nums.size(); i++) {
        auto it = count_map.find(nums[i]);
        if(it != count_map.end()) {
            it->second++;
            if(maxCount < it->second) {
                maxCount = it->second;
                result = it->first;
            }
        }
    }
    return result;
}

//49. 字符大小写排序
void sortLetters(string &chars) {
    // write your code here

    int i = 0;
    int j = chars.size()-1;
    while(i < j){

        while(i < j && chars[i] > 'a' && chars[i] < 'z')
            i++;
        while(i < j && chars[j] > 'A' && chars[j] < 'Z')
            j--;
        if(i < j){
            swap(chars[i], chars[j]);
            i++;
            j--;
        }
    }
}

// 58. 四数之和
vector<vector<int>> fourSum(vector<int> &numbers, int target) {
    // write your code here
    sort(numbers.begin(), numbers.end());
    vector<vector<int>> results;
    if(numbers.size() < 4)
        return results;
    for(int i = 0; i < numbers.size()-3; i++){
        if(i != 0 && numbers[i] == numbers[i-1])
            continue;
        for(int j = i + 1; j < numbers.size()-2; j++){
            if(j != i+1 && numbers[j] == numbers[j-1])
                continue;
            int target_ = target - numbers[i] - numbers[j];
            int left = j + 1;
            int right = numbers.size() - 1;
            while(left < right){
                if( numbers[left] + numbers[right] == target_){
                    results.emplace_back(vector<int>{numbers[i], numbers[j], numbers[left], numbers[right]});
                    left++;
                    while(left < right && numbers[left] == numbers[left-1])
                        left++;
                    right--;
                    while(left < right && numbers[right] == numbers[right+1])
                        right--;
                }else if(numbers[left] + numbers[right] > target_){
                    right--;
                }else{
                    left++;
                }
            }
        }
    }
    return results;
}

//59. 最接近的三数之和
int threeSumClosest(vector<int> &numbers, int target) {
    // write your code here

    sort(numbers.begin(), numbers.end());
    int result;
    int min_difference = INT_MAX;
    for(int i = 0; i < numbers.size(); i++){
        if(i != 0 && numbers[i] == numbers[i-1])
            continue;
        int target_ = target - numbers[i];
        int left = i + 1;
        int right = numbers.size()-1;
        while(left < right){
            int difference = target_ - numbers[left] - numbers[right];
            if(difference == 0)
                return target;
            if(abs(difference) < min_difference){
                result =  numbers[i] + numbers[left] + numbers[right];
                min_difference = abs(difference);
            }
            if(difference < 0)
                right--;
            else
                left++;

        }
    }
    return result;
}

//60. 搜索插入位置
int find(vector<int>& A,int target, int start, int end){
    if(start == end){
        if(A[start] < target)
            return start+1;
        else
            return start;
    }
    int mid = (start + end) / 2;
    if(A[mid] == target)
        return mid;
    else if(A[mid] > target)
        return find(A, target, start, mid-1);
    else
        return find(A, target, mid+1, end);
}

int searchInsert(vector<int> &A, int target) {
    // write your code here
    if(A.empty())
        return 0;
    return find(A, target, 0, A.size()-1);
}

// 61. 搜索区间
vector<int> searchRange(vector<int> &A, int target) {
    // write your code here
    int i = 0;
    int j = A.size()-1;
    int left_target = -1;
    while(i <= j){

        int mid = (i+j)/2;
        if(A[mid] == target){
            left_target = mid;
            j = mid-1;
        }else if(A[mid] < target)
            i = mid+1;
        else
            j = mid-1;

    }

    i = 0;
    j = A.size()-1;
    int right_target = -1;
    while(i <= j){

        int mid = (i+j)/2;
        if(A[mid] == target){
            right_target = mid;
            i = mid+1;
        }else if(A[mid] < target)
            i = mid+1;
        else
            j = mid-1;
    }

    return vector<int>{left_target, right_target};

}


int search(vector<int> &A, int target) {
    // write your code here
    if(A.empty())
        return -1;
    int i = 0;
    int j = A.size()-1;
    while(i <= j){
        int mid = (i+j)/2;
        if(A[mid] == target){
            return mid;
        }else if(A[mid] > target){
            if(target < A[i])
                i = mid+1;
            else
                j = mid-1;
        }
        else if(target > A[j])
            j = mid - 1;
        else
            i = mid + 1;
    }
    return -1;
}

//62.搜索旋转排序数组
int find2(vector<int>& A, int target, int start, int end){
    if(start > end)
        return -1;

    int mid = (start + end) / 2;
    if(A[mid] == target)
        return mid;

    if(A[mid] > target){
        if(A[start] > A[mid])
            return find(A, target, start, mid-1);
        else{
            int result = find(A, target, start, mid-1);
            if(result != -1)
                return result;
            else
                return find(A, target, mid+1, end);
        }
    }else if(A[end] < A[mid])
        return find(A, target, mid+1, end);
    else{
        int result = find(A, target, start, mid-1);
        if(result != -1)
            return result;
        else
            return find(A, target, mid+1, end);
    }
}

int search2(vector<int> &A, int target) {
    // write your code here
    if(A.empty())
        return -1;
    return find2(A, target, 0, A.size()-1);

}

// 76.给定一个整数序列，找到最长上升子序列（LIS），返回LIS的长度
//假设a = [4, 2, 6, 3, 1, 5], 初始dp=[], 具体算法运行步骤如下:
//a[0]=4 => dp=[4];
//a[1]=2 => dp=[2];
//a[2]=6 => dp=[2, 6];
//a[3]=3 => dp=[2, 3];
//a[4]=1 => dp=[1, 3];
//a[5]=5 => dp=[1, 3, 5];
int longestIncreasingSubsequence(vector<int> &nums) {
    // write your code here

    if(nums.empty())
        return 0;

    vector<int> dp;
    dp[0] = nums[0];

    for(int i = 1; i < nums.size(); i++){
        auto iter = find(dp.begin(), dp.end(), nums[i]);
        if(iter != dp.end()){
            *iter = nums[i];
        }
        else
            dp.emplace_back(nums[i]);
    }

    return dp.size();
}

vector<int> singleNumberIII(vector<int> &A) {
    // write your code here
    vector<int> result;
    if(A.size() < 2)
        return result;

    int tmp = 0;
    for(auto a : A){
        tmp = tmp ^ a;
    }

    int i  = 1;
    while(((tmp >> i) & 1) != 1) {
        i++;
    }

    int result1 = 0;
    int result2 = 0;

    for(auto a : A){
        if(((a >> i) & 1) == 1)
            result1 = result1 ^ a;
        else
            result2 = result2 ^ a;
    }
    result.emplace_back(result1);
    result.emplace_back(result2);
    return result;
}

// 95. 验证二叉查找树
bool isValidBST(TreeNode* node, int low, int high){
    if(node == nullptr)
        return true;
    if(node->val <= low || node->val >= high){
        if(node->val != INT_MAX || node->val != INT_MIN)
            return false;
    }
    return isValidBST(node->left, low, node->val)
           && isValidBST(node->right, node->val, high);
}

bool isValidBST(TreeNode * root) {
    // write your code here
    if(root == nullptr)
        return true;
    return isValidBST(root, INT_MIN, INT_MAX);
}

// 98. 链表排序
ListNode* mergeList(ListNode* node1, ListNode* node2){

    ListNode* head = new ListNode(-1);
    ListNode* node = head;

    while(node1 != nullptr && node2 != nullptr){

        if(node1->val < node2->val){
            node->next = node1;
            node1 = node1->next;
        }else{
            node->next = node2;
            node2 = node2->next;
        }
        node = node->next;
        node->next = nullptr;
    }

    if(node1 != nullptr)
        node->next = node1;
    else
        node->next = node2;
    return head->next;
}

ListNode * sortList(ListNode* head) {
    // write your code here

    if(head == nullptr)
        return nullptr;
    if(head->next == nullptr)
        return head;

    ListNode* head1 = head;
    ListNode* head2 = head->next;
    while(head2 != nullptr && head2->next != nullptr){
        head1 = head1->next;
        head2 = head2->next->next;
    }

    head2 = head1->next;
    head1->next = nullptr;
    head1 = sortList(head);
    head2 = sortList(head2);

    return mergeList(head1, head2);
}


int kSum(vector<int> A, int K, int target) {
    vector<vector<int>> ans(K+1, vector<int>(target+1));
    ans[0][0] = 1;
    for(int i = 0; i < A.size(); ++i)
        for(int j = K; j > 0; j--)
            for(int k = target; k >= A[i]; k--) {
                ans[j][k] += ans[j - 1][k - A[i]];
            }
    return ans[K][target];
}



int main(){



}
