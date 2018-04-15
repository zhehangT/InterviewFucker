/**
* Author: T_Zhehang
* Date: 18-3-21
* 剑指offer第八章
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    struct ListNode *next;

    ListNode(int x) :
            val(x), next(NULL) {
    }
};

struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {

    }
};

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};

// 面试题51 在一个长度为n的数组里的所有数字都在0到n-1的范围内。
// 数组中某些数字是重复的，但不知道有几个数字是重复的。也不知道每个数字重复几次。
// 请找出数组中任意一个重复的数字。
bool duplicate(int numbers[], int length, int* duplication) {
    for(int i = 0; i < length;){
        if(i != numbers[i]){
            if(numbers[numbers[i]] == numbers[i]){
                *duplication = numbers[i];
                return true;
            }else{
                int tmp = numbers[numbers[i]];
                numbers[numbers[i]] = numbers[i];
                numbers[i] = tmp;
            }
        }else
            i++;

    }
    return false;
}

// 面试题52 给定一个数组A[0,1,...,n-1],请构建一个数组B[0,1,...,n-1]。
// 其中B中的元素B[i]=A[0]*A[1]*...*A[i-1]*A[i+1]*...*A[n-1]。
// 不能使用除法。
vector<int> multiply(const vector<int>& A) {

    int l = A.size();
    vector<int> a1(l, 1);
    vector<int> a2(l, 1);
    for(int i = 1; i < l; i++){
        a1[i] = a1[i-1] * A[i-1];
        a2[l-i-1] = a2[l-i] * A[l-i];
    }
    vector<int> B(l);
    for(int i = 0; i < l; i++)
        B[i] = a1[i] * a2[i];
    return B;
}

// 面试题53 匹配包括'.'和'*'的正则表达式。模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（包含0次）
bool MatchHelp(char* str, char* pattern){
    if(*str == '\0' && *pattern == '\0')
        return true;
    if(*str != '\0' && *pattern == '\0')
        return false;

    if(*(pattern+1) == '*'){
        if(*pattern == *str|| (*pattern == '.' && *str != '\0')){
            return MatchHelp(str+1, pattern) ||
                   MatchHelp(str+1, pattern+2) ||
                   MatchHelp(str, pattern+2);

        }else{
            return MatchHelp(str, pattern+2);
        }
    }
    if(*str == *pattern || (*pattern == '.' && *str != '\0'))
        return MatchHelp(str+1, pattern+1);
    return false;

}


bool match(char* str, char* pattern)
{
    if(str == nullptr || pattern == nullptr)
        return false;
    else
        return MatchHelp(str, pattern);
}

// 面试题54 判断字符串是否表示数值
bool isExponential(char* s){
    if(*s != 'e' && *s != 'E')
        return false;
    ++s;
    if(*s == '+' || *s == '-')
        ++s;
    if(*s == '\0')
        return false;

    while(*s != '\0' && *s >= '0' && *s <= '9')
        s++;
    return (*s == '\0') ? true : false;

}

bool isNumeric(char* string)
{
    if(string == nullptr)
        return false;
    //判断正负号
    if(*string == '+' || *string == '-')
        string++;
    if(*string == '\0')
        return false;
    while(*string != '\0' && *string >= '0' && *string <= '9')
        string++;
    if(*string != '\0'){
        if(*string == '.'){
            ++string;
            while(*string != '\0' && *string >= '0' && *string <= '9')
                string++;
        }
        if(*string == 'e' || *string == 'E')
            return isExponential(string);
    }
    return *string == '\0';
}

// 面试题57 删除链表中重复的结点
ListNode* deleteDuplication(ListNode* pHead)
{
    if(pHead == nullptr)
        return nullptr;

    ListNode* newHead = new ListNode(-1);
    ListNode* pre = newHead;
    bool flag = true;
    while(pHead != nullptr){
        if(pHead->next == nullptr){
            if(flag){
                pre->next = pHead;
            }else
                pre->next = nullptr;
        }
        else if(pHead->val == pHead->next->val){
            flag = false;
        }
        else if(flag){
            pre->next = pHead;
            pre = pre->next;
        }else{
            flag = true;
        }

        if(!flag){
            ListNode* tmp = pHead;
            pHead = pHead->next;
            delete tmp;
        }else
            pHead = pHead->next;

    }
    return newHead->next;
}

//面试题58 给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点
TreeLinkNode* GetNext(TreeLinkNode* pNode)
{
    if(pNode == nullptr)
        return nullptr;
    //右子树不为空，下一个节点为右子树最左边的节点
    if(pNode->right != nullptr){
        pNode = pNode->right;
        while(pNode->left != nullptr){
            pNode = pNode->left;
        }
        return pNode;
    }

    //右子树为空，且当前节点是父节点的左子树，下一个节点为父节点
    if(pNode->next != nullptr && pNode->next->left == pNode)
        return pNode->next;
        //右子树为空，且当前节点是父节点的右子树
    else{
        while(pNode->next != nullptr){
            if(pNode->next->left == pNode)
                return pNode->next;
            pNode = pNode->next;
        }
        return nullptr;
    }
}

//面试题59 用来判断一颗二叉树是不是对称的
bool isSymmetrical(TreeNode* node1, TreeNode* node2){
    if(node1 == nullptr && node2 == nullptr)
        return true;
    if(node1 == nullptr || node2 == nullptr)
        return false;
    if(node1->val == node2->val)
        return isSymmetrical(node1->left, node2->right) && isSymmetrical(node1->right, node2->left);
    return false;
}

bool isSymmetrical(TreeNode* pRoot)
{
    if(pRoot == nullptr)
        return true;
    return isSymmetrical(pRoot->left, pRoot->right);
}

//面试题60 把二叉树打印成多行
vector<vector<int> > PrintN(TreeNode* pRoot) {
    vector<vector<int>> results;
    if(pRoot == nullptr)
        return results;
    vector<int> tmp;
    queue<TreeNode*> q;
    q.push(pRoot);
    int cur = 1;
    int next = 0;
    while(!q.empty()){
        TreeNode* node = q.front();
        q.pop();
        tmp.emplace_back(node->val);
        if(node->left != nullptr){
            next++;
            q.push(node->left);
        }
        if(node->right != nullptr){
            next++;
            q.push(node->right);
        }
        cur--;
        if(cur == 0){
            results.emplace_back(tmp);
            tmp.clear();
            cur = next;
            next = 0;
        }
    }
    return results;
}

//面试题61 请实现一个函数按照之字形打印二叉树。
//即第一行按照从左到右的顺序打印，第二层按照从右至左的顺序打印，第三行按照从左到右的顺序打印，其他行以此类推。
vector<vector<int> > PrintZ(TreeNode* pRoot) {
    vector<vector<int>> results;
    if(pRoot == nullptr)
        return results;
    vector<int> tmp(1);
    queue<TreeNode*> q;
    q.push(pRoot);
    int cur = 1;
    int next = 0;
    bool flag = true;
    while(!q.empty()){
        TreeNode* node = q.front();
        q.pop();
        if(flag)
            tmp[tmp.size()-cur] = node->val;
        else
            tmp[cur-1] = node->val;

        if(node->left != nullptr){
            next++;
            q.push(node->left);
        }
        if(node->right != nullptr){
            next++;
            q.push(node->right);
        }
        cur--;
        if(cur == 0){
            results.emplace_back(tmp);
            tmp.clear();
            tmp.resize(next);
            cur = next;
            next = 0;
            flag = !flag;
        }
    }
    return results;
}

//面试题63 给定一颗二叉搜索树，请找出其中的第k大的结点
TreeNode* KthNodeHelp(TreeNode* node, int k, int& n){

    if(node == nullptr)
        return nullptr;
    TreeNode* result = KthNodeHelp(node->left, k, n);
    if(result != nullptr)
        return result;
    n++;
    if(n == k)
        return node;
    return KthNodeHelp(node->right, k, n);
}


TreeNode* KthNode(TreeNode* pRoot, int k)
{
    if(pRoot == nullptr || k <= 0)
        return nullptr;
    int i = 0;
    return KthNodeHelp(pRoot, k, i);
}
//面试题64 获取未排序的数据中的中位数
//最大堆
//priority_queue<int, vector<int>, less<int> > q_max;
//最小堆
//priority_queue<int, vector<int>, greater<int> > q_min;
//q_max.top();

//面试题65 对于一个数组，记录滑动窗口内的最大值
vector<int> maxInWindows(const vector<int>& num, unsigned int size)
{
    vector<int> results;
    if( num.size() == 0 || num.size() < size)
        return results;
    deque<int> q_index;
    for(int i = 0; i < size; i++){
        while(!q_index.empty() && num[i] >= num[q_index.back()])
            q_index.pop_back();
        q_index.push_back(i);
    }
    results.emplace_back(num[q_index.front()]);
    for(int i = size; i < num.size(); i++){
        while(!q_index.empty() && num[i] > num[q_index.back()])
            q_index.pop_back();
        if(!q_index.empty() && q_index.front() <= int(i-size))
            q_index.pop_front();
        q_index.push_back(i);
        results.emplace_back(num[q_index.front()]);
    }
    return results;
}

//面试题67 终于踏妈做完了
//计算位置的数值
int getSum(int number)
{
    int sum = 0;
    while(number > 0)
    {
        sum+=number%10;
        number/=10;
    }
    return sum;
}


//检查当前位置是否可以访问
bool check(int threshold,int rows,int cols,int i,int j,bool* flag)
{
    if(i>=0 && i<rows && j>=0 && j<cols
       && getSum(i)+getSum(j)<=threshold
       && flag[i*cols+j] == false)
        return true;
    return false;
}

int movingCountHelp(int threshold, int rows, int cols, int row, int col, bool* visited){
    int count = 0;
    if(check(threshold, rows, cols, row, col, visited)){
        visited[row*cols + col] = true;

        count = 1+movingCountHelp(threshold,rows,cols,row-1,col,visited)
                +movingCountHelp(threshold,rows,cols,row,col-1,visited)
                +movingCountHelp(threshold,rows,cols,row+1,col,visited)
                +movingCountHelp(threshold,rows,cols,row,col+1,visited);
    }
    return count;
}

int movingCount(int threshold, int rows, int cols)
{
    bool *visited = new bool[rows*cols];
    for(int i = 0; i < rows*cols; i++)
        visited[i] = false;
    int count = movingCountHelp(threshold, rows, cols, 0, 0, visited);
    delete[] visited;
    return count;

}







int main(){
    maxInWindows(vector<int>{1,3,-1,-3,5,3,6,7}, 3);
}