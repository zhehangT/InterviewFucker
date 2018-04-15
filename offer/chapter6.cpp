/**
* Author: T_Zhehang
* Date: 18-3-21
* 剑指offer第六章
*/
#include <climits>
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

// 面试38题 统计一个数字在排序数组中出现的次数。
int index_start = INT_MAX;
int index_end = INT_MIN;

void findK(vector<int>& data, int start, int end, int k){
    if(start > end){
        return;
    }

    int mid = (start+end)/2;
    if(data[mid] > k)
        findK(data, start, mid-1, k);
    else if(data[mid] < k)
        findK(data, mid+1, end, k);
    else{
        index_start = min(index_start, mid);
        index_end = max(index_end, mid);
        if(data[mid-1] == k)
            findK(data, start, mid-1, k);
        if(data[mid+1] == k)
            findK(data, mid+1, end, k);
    }

}

int GetNumberOfK(vector<int> data ,int k) {
    findK(data, 0, data.size()-1, k);
    if(index_start > data.size())
        return 0;
    return index_end - index_start + 1;
}

//面试39题 输入一棵二叉树，求该树的深度
//int TreeDepthHelp(TreeNode* root){
//    if(root == nullptr)
//        return 0;
//    return max(TreeDepthHelp(root->left), TreeDepthHelp(root->right))+1;
//
//}
//
//int TreeDepth(TreeNode* pRoot)
//{
//    return TreeDepthHelp(pRoot);
//}
//
//// 判断是不是平衡二叉树
//bool IsBalancedHelp(TreeNode* root, int& depth){
//
//    if(root == nullptr){
//        depth = 0;
//        return true;
//    }
//    int left;
//    int right;
//    if(IsBalancedHelp(root->left, left) && IsBalancedHelp(root->right, right)){
//        int diff = left - right;
//        if(diff <= 1 && diff >= -1){
//            depth = 1 + (left > right ? left : right);
//            return true;
//        }
//    }
//    return false;
//}
//
//bool IsBalanced_Solution(TreeNode* pRoot) {
//    int depth = 0;
//    return IsBalancedHelp(pRoot, depth);
//}


//面试40题 一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字。
void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {

    int result = data[0];
    for(int i = 1; i < data.size(); i++){
        result = result ^ data[i];
    }
    int flag = 1;
    while(flag != result & flag){
        flag = flag << 1;
    }

    vector<int> tmp1;
    vector<int> tmp2;
    for(int i = 0; i < data.size(); i++){
        if((data[i] & flag) == flag)
            tmp1.emplace_back(data[i]);
        else
            tmp2.emplace_back(data[i]);
    }

    *num1 = tmp1[0];
    for(int i = 1; i < tmp1.size(); i++){
        *num1 = *num1 ^ tmp1[i];
    }

    *num2 = tmp2[0];
    for(int i = 1; i < tmp2.size(); i++){
        *num2 = *num2 ^ tmp2[i];
    }
}

// 面试题41-1： 输入一个递增排序的数组和一个数字S，输出所有和为S的连续正数序列。序列内按照从小至大的顺序，
vector<vector<int> > FindContinuousSequence(int sum) {

    vector<vector<int>> results;
    vector<int> sums(sum/2 + 2);
    for(int i = 0; i < sums.size(); i++){
        sums[i] = i * (i+1) / 2;
    }
    for(int i = 0, j = 1; j < sums.size();){

        if(sums[j]-sums[i] == sum){
            vector<int> tmp;
            for(int x = i +1; x <= j; x++)
                tmp.emplace_back(x);
            results.emplace_back(tmp);
            i++;
            j++;
        }else if(sums[j] - sums[i] < sum)
            j++;
        else
            i++;
    }
    return results;
}

// 面试41-2 输入一个递增排序的数组和一个数字S，在数组中查找两个数，是的他们的和正好是S，如果有多对数字的和等于S，输出两个数的乘积最小的。
vector<int> FindNumbersWithSum(vector<int> array,int sum) {

    if(array.empty())
        return  vector<int>();
    int i = 0;
    int j = array.size()-1;
    int result_i = 0;
    int result_j = 0;
    int tmp = INT_MAX;
    while(j > i){
        if(array[i] + array[j] == sum && array[i] * array[j] < tmp){
            result_i = array[i];
            result_j = array[j];
            tmp = result_i * result_j;
            i++;
            j--;
        }
        else if(array[i] + array[j] < sum)
            i++;
        else
            j--;
    }
    if( result_i + result_j != sum)
        return vector<int>();
    return vector<int>{result_i, result_j};
}

//面试42-1 输入一个英文句子，翻转句子中单词的顺序，但是单词内字符的顺序不变
void ReverseString(string& str, int start, int end){
    if(start >= end)
        return;
    char tmp;
    for(int i = 0; i <= (end-start)/2; i++){
        tmp = str[start+i];
        str[start+i] = str[end-i];
        str[end-i] = tmp;
    }

}

string ReverseSentence(string str) {

    if(str.empty())
        return str;

    ReverseString(str, 0, str.size()-1);
    int start = 0;
    for(int i = 0; i < str.size();i++){
        if(str[i] == ' '){
            ReverseString(str, start, i-1);
            start = i+1;
        }
    }
    ReverseString(str, start, str.size()-1);

    return str;
}

// 面试42-2 对于一个给定的字符序列S，把其循环左移K位后的序列输出。
// 例如，字符序列S=”abcXYZdef”,要求输出循环左移3位后的结果，即“XYZdefabc”
string LeftRotateString(string str, int n) {
    if(str.size() == 0)
        return str;
    if(n > str.size())
        n = n % str.size();
    char* tmp = new char[n];
    for(int i = 0; i < n; i++)
        tmp[i] = str[i];
    for(int i = n; i < str.size(); i++)
        str[i-n] = str[i];
    for(int i = 0; i < n; i++)
        str[str.size()-1-i] = tmp[n-1-i];
    return str;
}

//面试题43 从扑克牌中随机抽5张牌，判断是不是一个顺子，大小王（0）可以看成任意数字
bool IsContinuous( vector<int> numbers ) {

    if(numbers.size() != 5)
        return false;

    sort(numbers.begin(), numbers.end());
    int count_0 = 0;
    for(int n : numbers){
        if(n == 0)
            count_0++;
        else
            break;
    }
    for(int i = count_0; i < numbers.size()-1; i++){
        int gap = numbers[i+1] - numbers[i];
        if(gap == 1)
            continue;
        if(gap > 1 && count_0 >= gap-1){
            count_0-=(gap-1);
        }else
            return false;
    }
    return true;
}

// 面试题44 约瑟夫环
int LastRemaining_Solution(int n, int m)
{
    vector<int> numbers(n);
    for(int i = 0; i < n; i++)
        numbers[i] = i;
    int count = 0;
    auto iter = numbers.begin();
    while(numbers.size() != 1){

        for(int i = 1; i < m; i++){
            iter++;
            if(iter == numbers.end())
                iter = numbers.begin();
        }
        iter = numbers.erase(iter);
        if(iter == numbers.end())
            iter = numbers.begin();
    }
    return *iter;
}


int main(){


}