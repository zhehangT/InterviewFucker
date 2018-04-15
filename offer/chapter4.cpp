/**
* Author: T_Zhehang
* Date: 18-3-21
* 剑指offer第四章
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};
// 面试题28：输入一个字符串,按字典序打印出该字符串中字符的所有排列
void PermutationHelp(vector<string>& results, string str, int index){
    if(str.size() == 0)
        return;

    if(index == str.size()-1){
        results.emplace_back(str);
        return;
    }
    PermutationHelp(results, str, index+1);
    for(int i = index+1; i < str.size(); i++){
        if(str[index] != str[i]){
            swap(str[index], str[i]);
            PermutationHelp(results, str, index+1);
            swap(str[index], str[i]);
        }
    }
}

vector<string> Permutation(string str) {
    vector<string> results;
    PermutationHelp(results, str, 0);
    sort(results.begin(), results.end());
    return results;
}

// 面试题27：输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表
void ConvertHelp(TreeNode* root, TreeNode** node){
    if(root == nullptr)
        return;

    if(root->left != nullptr)
        ConvertHelp(root->left, node);
    if(*node != nullptr)
        (*node)->right = root;
    root->left = *node;
    *node = root;
    if(root->right != nullptr)
        ConvertHelp(root->right, node);
}


TreeNode* Convert(TreeNode* pRootOfTree)
{
    TreeNode* node = nullptr;
    ConvertHelp(pRootOfTree, &node);
    while( node != nullptr &&  node->left != nullptr)
        node = node->left;
    return node;
}



int main(){


}
