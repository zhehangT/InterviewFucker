/**
* Author: T_Zhehang
* Date: 18-3-14
*/

#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int data) :val(data),left(nullptr),right(nullptr) {}
};

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct UndirectedGraphNode {
    int label;
    vector<struct UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {}
};

// 4.1实现一个函数，检查二叉树是否平衡，平衡的定义如下，对于树中的任意一个结点，其两颗子树的高度差不超过1。
int getHeight(TreeNode* node){

    if(node == nullptr)
        return 0;
    else
        return getHeight(node->left)>getHeight(node->right)?getHeight(node->left)+1:getHeight(node->right)+1;
}

bool isBalance(TreeNode* root) {
    // write code here
    if(root == nullptr)
        return true;
    int diffHeight = getHeight(root->left) - getHeight(root->right);
    if(diffHeight > 1 || diffHeight < -1)
        return false;
    else
        return isBalance(root->left) && isBalance(root->right);

}

int checkHeight(TreeNode* node){
    if(node == nullptr)
        return 0;

    int leftHeight = checkHeight(node->left);
    if(leftHeight == -1){
        return -1;
    }

    int rightHeight = checkHeight(node->right);
    if(rightHeight == -1){
        return -1;
    }

    int diffHeight = leftHeight - rightHeight;
    if(diffHeight > 1 || diffHeight < -1)
        return -1;
    else
        return leftHeight>rightHeight ? leftHeight + 1 : rightHeight + 1;

}

bool isBalance2(TreeNode* root) {
    // write code here
    if(root == nullptr)
        return true;
    if(checkHeight(root) == -1)
        return false;
    else
        return isBalance(root->left) && isBalance(root->right);

}

//4.2 对于一个有向图，请实现一个算法，找出两点之间是否存在一条路径。
struct UndirectedGraphNode {
    int label;
    vector<struct UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {}
};
set<UndirectedGraphNode*> visited;

void DFT(UndirectedGraphNode* a){

    visited.insert(a);
    vector<struct UndirectedGraphNode *> neighbors = a->neighbors;
    for(auto neighbor : neighbors){
        if(visited.find(neighbor) == visited.end()){
            DFT(neighbor);
        }
    }
}

//深度优先搜索，递归版本
bool checkPath(UndirectedGraphNode* a, UndirectedGraphNode* b) {
    // write code here
    DFT(a);
    if(visited.find(b) != visited.end())
        return true;

    visited.clear();
    DFT(b);
    if(visited.find(a) != visited.end())
        return true;
    return false;

}

bool check(UndirectedGraphNode* a, UndirectedGraphNode* b){

    set<UndirectedGraphNode*> visited;
    queue<UndirectedGraphNode*> qa;
    if( a == b)
        return true;
    qa.push(a);
    visited.insert(a);

    while(!qa.empty()){
        UndirectedGraphNode* ptr = qa.front();
        for(auto neighbor : ptr->neighbors){
            if(neighbor == b)
                return true;
            else if(visited.find(neighbor) == visited.end()){
                qa.push(neighbor);
                visited.insert(neighbor);
            }
        }
        qa.pop();
    }
    return false;
}

//广度优先搜索，非递归版本
bool checkPath2(UndirectedGraphNode* a, UndirectedGraphNode* b) {
    // write code here
    return check(a, b) || check(b, a);
}


bool check2(UndirectedGraphNode* a, UndirectedGraphNode* b){

    if( a == b)
        return true;

    set<UndirectedGraphNode*> visited;
    stack<UndirectedGraphNode*> s;
    visited.insert(a);
    s.push(a);

    while(!s.empty()){
        UndirectedGraphNode* ptr = s.top();
        bool has_no_visited = true;
        for(auto neighbor : ptr->neighbors){
            if(neighbor == b)
                return true;
            if(visited.find(neighbor) == visited.end()){
                visited.insert(neighbor);
                s.push(neighbor);
                has_no_visited = false;
                break;
            }
        }
        if(has_no_visited)
            s.pop();
    }
    return false;

}

//深度优先搜索，非递归版本
bool checkPath(UndirectedGraphNode* a, UndirectedGraphNode* b) {
    // write code here
    return check(a, b) || check(b, a);
}

//4.3 对于一个元素各不相同且按升序排列的有序序列，创建一棵高度最小的二叉查找树。
TreeNode* buildBST(vector<int>& vals, int i, int j){

    if(i > j)
        return nullptr;
    int mid = (i + j)/2;
    TreeNode* newNode = new TreeNode(vals[mid]);
    newNode->left = buildBST(vals, i, mid-1);
    newNode->right = buildBST(vals, mid+1, j);
    return newNode;
}

int highBST(TreeNode* root){

    if(root == nullptr)
        return 0;

    int left = highBST(root->left);
    int right = highBST(root->right);

    return left > right ? left + 1 : right +1;
}


int buildMinimalBST(vector<int> vals) {
    // write code here
    if(vals.size() <= 0)
        return 0;

    TreeNode* root = buildBST(vals, 0, vals.size()-1);
    return highBST(root);

}

//4.4 对于一棵二叉树，创建含有某一深度上所有结点的链
vector<vector<ListNode*>> results;
void createAllLevel(TreeNode* root, int level){

    if(root == nullptr)
        return;

    if(results.size() < level){
        vector<ListNode*> result;
        ListNode* node = new ListNode(root->val);
        result.emplace_back(node);
        results.emplace_back(result);
    }
    else{
        ListNode* node = new ListNode(root->val);
        results[level].emplace_back(node);
    }

    createAllLevel(root->left, level+1);
    createAllLevel(root->right, level+1);
}


ListNode* getTreeLevel(TreeNode* root, int dep) {
    // write code here
    createAllLevel(root, 1);

    ListNode* head = nullptr;
    ListNode* tmp = nullptr;
    head = results[dep][0];
    tmp = head;
    for(int i = 1; i < results[dep].size(); i++){
        tmp->next = results[dep][i];
        tmp = tmp->next;
    }
    return head;
}

ListNode* head = new ListNode(-1);
ListNode* node = head;

ListNode* getTreeLevel2(TreeNode* root, int dep) {
    // write code here
    if(root == nullptr || dep <= 0)
        return nullptr;

    if(dep == 1){
        ListNode* tmp = new ListNode(root->val);
        node->next = tmp;
        node = node->next;
    }else{
        getTreeLevel(root->left, dep-1);
        getTreeLevel(root->right, dep-1);
    }

    return head->next;
}


//4.5 检查一棵二叉树是否为二叉查找树。
//通过中序遍历放到一个数组，检查数组是不是排好序的
//vector<int> vals;
//void LDR(TreeNode* root){
//
//    if(root == nullptr)
//        return;
//    LDR(root->left);
//    vals.emplace_back(root->val);
//    LDR(root->right);
//}
//
//bool checkBST(TreeNode* root) {
//    // write code here
//    LDR(root);
//    for(int i = 1; i < vals.size(); i++){
//        if(vals[i] < vals[i-1])
//            return false;
//    }
//    return true;
//}

//一边中序遍历，一边检查当前值是不是比前一个中序遍历得到的值小
int last = INT_MIN;
bool checkBST(TreeNode* root) {

    if (root == nullptr)
        return true;
    if (!checkBST(root->left))
        return false;
    if (last > root->val)
        return false;
    last = root->val;
    if (!checkBST(root->right))
        return false;
    return true;
}

//巧妙的思路
bool checkBST(TreeNode* node, int i, int j){

    if(node == nullptr)
        return true;
    if( node->val < i || node->val > j )
        return false;
    return checkBST(node->left, i, node->val) && checkBST(node->right, node->val, j);

}

bool checkBST2(TreeNode* root) {
    // write code here
    return checkBST(root, INT_MIN, INT_MAX);
}

//4.6 寻找二叉树中指定结点的下一个结点（即中序遍历的后继）
//vector<int> vals;
//void LDR(TreeNode* root){
//
//    if(root == nullptr)
//        return;
//    LDR(root->left);
//    vals.emplace_back(root->val);
//    LDR(root->right);
//}
//int findSucc(TreeNode* root, int p) {
//    // write code here
//    LDR(root);
//    for(int i = 1; i < vals.size(); i++){
//        if(p == vals[i-1])
//            return vals[i];
//    }
//    return -1;
//
//}

int val = -1;
int findSucc(TreeNode* root, int p) {
    // write code here
    if(root == nullptr)
        return -1;
    int tmp = findSucc(root->left, p);
    if(tmp != -1)
        return tmp;
    if(val == p)
        return root->val;
    val = root->val;
    tmp = findSucc(root->right, p);
    if(tmp != -1)
        return tmp;
    return -1;

}

//4.9 输入一颗二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。
vector<vector<int>> results;
void F(TreeNode* root, int sum, int expectNumber, vector<int> result){
    if(root == nullptr)
        return;
    sum = sum + root->val;
    result.emplace_back(root->val);
    if(sum == expectNumber && root->left == nullptr && root->right == nullptr){
        results.emplace_back(result);
    }
    F(root->left, sum, expectNumber, result);
    F(root->right, sum, expectNumber, result);
}

vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
    vector<int> result;
    F(root, 0, expectNumber, result);
    return results;

}