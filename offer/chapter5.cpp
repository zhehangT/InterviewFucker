/**
* Author: T_Zhehang
* Date: 18-3-21
* 剑指offer第五章
*/
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
            val(x), next(NULL) {
    }
};

//面试题29 数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字
int Partition(vector<int>& numbers, int start, int end){

    int flag = numbers[end];
    int i = start - 1;
    for(int j = start; j <= end; j++){
        if(numbers[j] < flag)
            swap(numbers[++i], numbers[j]);
    }
    swap(numbers[++i], numbers[end]);
    int mid = (start + end)/2;
    if(i == mid)
        return i;
    else if(i > mid)
        return Partition(numbers, start, i-1);
    else
        return Partition(numbers, i+1, end);
}

int MoreThanHalfNum_Solution(vector<int> numbers) {
    int mid = Partition(numbers, 0, numbers.size()-1);
    int count = 0;
    for(int n : numbers){
        if(n == numbers[mid])
            count++;
    }
    if(count > numbers.size()/2)
        return numbers[mid];
    return 0;
}
// 面试题30 输入n个整数，找出其中最小的K个数
// 还可以用最大堆
void Partition(vector<int>& numbers, int start, int end, int k){

    if(start > end)
        return;
    int flag = numbers[end];
    int i = start - 1;
    for(int j = start; j <= end; j++){
        if(numbers[j] < flag)
            swap(numbers[++i], numbers[j]);
    }
    swap(numbers[++i], numbers[end]);
    if(i >= k)
        Partition(numbers, start, i-1, k);
    else{
        Partition(numbers, start, i-1, k);
        Partition(numbers, i+1, end, k);
    }
}

//面试题33 输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个
vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
    if(input.size() < k)
        return vector<int>();

    Partition(input, 0, input.size()-1, k);
    return vector<int>(input.begin(), input.begin()+k);
}


static bool cmp(int a, int b){
    string s_a = to_string(a);
    string s_b = to_string(b);
    return s_a + s_b <= s_b + s_a;
}

string PrintMinNumber(vector<int> numbers) {
    sort(numbers.begin(), numbers.end(), cmp);
    string s="";
    for(int n : numbers)
        s += to_string(n);
    return s;
}

// 面试34题
int GetUglyNumber_Solution(int index) {
    if(index == 0)
        return 0;

    vector<int> uglys(index);
    int index_2 = 0;
    int index_3 = 0;
    int index_5 = 0;
    uglys[0] = 1;
    for(int i = 1; i < index; i++){
        uglys[i] = min(min(2*uglys[index_2], 3*uglys[index_3]), 5*uglys[index_5]);
        while(2*uglys[index_2] <= uglys[i])
            index_2++;
        while(3*uglys[index_3] <= uglys[i])
            index_3++;
        while(5*uglys[index_5] <= uglys[i])
            index_5++;
    }
    return uglys[index-1];
}

// 面试36题：在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组,求出这个数组中的逆序对的总数P
int InversePairsHelp(vector<int>& sorted_data, vector<int>& data, int start, int end){

    if(start == end){
        sorted_data[start] = data[start];
        return 0;
    }

    int mid = (start + end) / 2;
    int left = InversePairsHelp(data, sorted_data, start, mid);
    int right = InversePairsHelp(data, sorted_data, mid+1, end);

    int index_left = mid;
    int index_right = end;
    int index_data = end;
    int count = 0;
    while(index_left >= start && index_right >= mid+1){
        if(data[index_left] > data[index_right]){
            sorted_data[index_data--] = data[index_left--];
            count += index_right - mid;
        }else{
            sorted_data[index_data--] = data[index_right--];
        }
    }

    while(index_left >= start)
        sorted_data[index_data--] = data[index_left--];
    while(index_right >= mid+1)
        sorted_data[index_data--] = data[index_right--];
    return left + right + count;
}

//面试37题 输入两个链表，找出它们的第一个公共结点。
ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
    set<ListNode*> list_set;
    ListNode* node = pHead1;
    while(node != nullptr){
        list_set.insert(node);
        node = node->next;
    }
    node = pHead2;
    while(node != nullptr){
        if(list_set.find(node) != list_set.end())
            return node;
        node = node->next;
    }
    return nullptr;
}

int InversePairs(vector<int> data) {
    vector<int> sorted_data(data.begin(), data.end());
    int result =  InversePairsHelp(sorted_data, data, 0, data.size()-1);
    return result;
}



int main(){
}