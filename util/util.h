/**
* Author: T_Zhehang 
* Date: 18-1-20
*/

#ifndef INTERVIEWFUCKER_UTIL_H
#define INTERVIEWFUCKER_UTIL_H

#include<iostream>
using namespace std;


struct ListNode{
    int val;
    ListNode* next;
};

ListNode* getRandomList(int num){

    ListNode* head = new ListNode();
    ListNode* node = head;
    head->val = 0;
    for(int i = 1; i < num; i++){
        ListNode* tmp = new ListNode();
        tmp->val = i;
        node->next = tmp;
        node = node->next;
    }
    node->next = NULL;
    return head;
}

void printList(ListNode* head){
    ListNode* node = head;
    while(node != NULL){
        cout << node ->val << endl;
        node = node->next;
    }
}

void printArray(int array[], int length){

    for(int i=0; i<length; i++){

        cout << array[i] << " ";
    }
    cout << endl;

}


#endif //INTERVIEWFUCKER_UTIL_H
