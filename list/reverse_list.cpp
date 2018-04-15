/**
* Author: T_Zhehang
* Date: 18-2-10
*/

#include "../util/util.h"

ListNode* reverse_list(ListNode* head){

    if(head == nullptr)
        return nullptr;
    ListNode* pre = head;
    ListNode* cur = head->next;
    ListNode* next;
    pre->next = nullptr;
    while(cur != nullptr){
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    return pre;
}



int main(){

    ListNode* head = getRandomList(10);
    cout << "Before Reverse:" << endl;
    printList(head);

    head = reverse_list(head);
    cout << "After Reverse:" << endl;
    printList(head);
    return 0;
}