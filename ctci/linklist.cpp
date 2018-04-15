/**
* Author: T_Zhehang 
* Date: 18-3-5
*/
#include<iostream>
#include<stack>
using namespace std;

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
    ListNode(int x, ListNode* node) : val(x), next(node) {}

};

void PrintList(ListNode* pListHead){
    ListNode* node = pListHead;
    while(node != NULL){
        cout << node->val;
        node = node->next;
    }
    cout << endl;
}

//2.2 输入一个链表，输出该链表中倒数第k个结点。
ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {

    if(pListHead == NULL || k==0)
        return NULL;


    ListNode* node = pListHead;
    for(int i = 1; i < k; i++){
        if(node->next != NULL)
            node = node->next;
        else
            return NULL;
    }
    ListNode* result = pListHead;
    while(node->next != NULL){

        result = result->next;
        node = node->next;
    }
    return result;
}

//2.3 给定带删除的节点，请执行删除操作，若该节点为尾节点，返回false，否则返回true
bool RemoveNode(ListNode* pNode) {
    // write code here
    if(pNode->next == NULL)
        return false;
    else{
        ListNode* tmp = pNode->next;
        pNode->next = tmp->next;
        pNode->val = tmp->val;
        delete tmp;
        return true;
    }
}

//2.4 以给定值x为基准将链表分割成两部分，所有小于x的结点排在大于或等于x的结点之前
ListNode* Partition(ListNode* pHead, int x) {
    // write code here
    if(pHead == NULL)
        return NULL;
    ListNode* lessHead = NULL;
    ListNode* less = NULL;
    ListNode* bigHead = NULL;
    ListNode* big = NULL;
    while(pHead != NULL){
        if(pHead->val < x){
            if(less == NULL){
                lessHead = pHead;
                less = pHead;
            }else{
                less->next = pHead;
                less = less->next;
            }
        }else{
            if(big == NULL){
                bigHead = pHead;
                big = pHead;
            }else{
                big->next = pHead;
                big = big->next;
            }
        }
        pHead = pHead->next;
    }

    if(lessHead == NULL)
        return bigHead;
    else{
        if(big != NULL)
            big->next = NULL;
        less->next = bigHead;
        return lessHead;
    }
}

//2.5 有两个用链表表示的整数，每个结点包含一个数位。这些数位是反向存放的，也就是个位排在链表的首部。
// 编写函数对这两个整数求和，并用链表形式返回结果。
ListNode* plusAB(ListNode* a, ListNode* b) {
    // write code here
    ListNode* head = nullptr;
    ListNode* node = nullptr;
    ListNode* tmp = nullptr;
    head = node;
    int carry = 0, sum, val1, val2;
    while( a != nullptr || b != nullptr || carry != 0){
        val1 = (a == nullptr ? 0 : a->val);
        val2 = (b == nullptr ? 0 : b->val);
        sum = val1 + val2 + carry;
        carry = sum / 10;
        if( head == nullptr){
            head = new ListNode(sum%10);
            node = head;
        }else{
            tmp = new ListNode(sum%10);
            node->next = tmp;
            node = node->next;
        }
        if(a != nullptr)
            a = a->next;
        if(b != nullptr)
            b = b->next;
    }
    return head;
}

//2.6请编写一个函数，检查链表是否为回文。
bool isPalindrome(ListNode* pHead) {
    // write code here
    ListNode* pSlow = pHead;
    ListNode* pFast = pHead;
    stack<int> s;

    while(pFast != nullptr && pFast->next != nullptr){
        s.push(pSlow->val);
        pSlow = pSlow->next;
        pFast = pFast->next->next;
    }
    if(pFast != nullptr)
        pSlow = pSlow -> next;
    while(pSlow != nullptr){
        if(pSlow->val != s.top())
            return false;
        pSlow = pSlow->next;
        s.pop();
    }
    return true;
}

int main(){

    ListNode* a = new ListNode(4);
    ListNode* b = new ListNode(2, a);
    ListNode* c = new ListNode(5, b);
    ListNode* d = new ListNode(1, c);
    PrintList(d);
    PrintList(Partition(d, 9));

    return 0;
}