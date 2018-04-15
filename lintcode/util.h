/**
* Author: T_Zhehang 
* Date: 18-4-7
*/

#ifndef INTERVIEWFUCKER_UTIL_H
#define INTERVIEWFUCKER_UTIL_H

#include <map>
#include <queue>
#include <string>
#include <iostream>
#include <sstream>
#include <climits>
#include <unordered_map>
#include <algorithm>



struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int data) :val(data),left(nullptr),right(nullptr) {}
};

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int data) : val(data), next(nullptr) {}
};


#endif //INTERVIEWFUCKER_UTIL_H
