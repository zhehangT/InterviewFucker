/**
* Author: T_Zhehang
* Date: 18-3-18
*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// 17.1 不使用任何临时变量，直接交换两个数的值
vector<int> exchangeAB(vector<int> AB) {
    // write code here

    AB[0] = AB[0] + AB[1];
    AB[1] = AB[0] - 2 * AB[1];
    AB[0] = (AB[0] - AB[1]) / 2;
    AB[1] = AB[1] + AB[0];
    return AB;
}

//17.3 计算n的阶乘有多少个尾随零。
int getFactorSuffixZero(int n) {
    // write code here
    int count = 0;
    for(int i = 5; n / i > 0; i*=5 ){
        count += n/i;
    }
    return count;
}

// 17.4 找出两个数字中最大的那个。条件是不得使用if-else等比较和判断运算符。
int getMax(int a, int b) {
    // write code here
    b = a-b;//此时b>>31为1则b小于0即a<b,若b>>31为0 则a>b
    a -= b & (b >> 31); //若a<b a=a-(a-b),若a>b a=a-0
    //注意负数插1，正数插0
    return a;
}


//17.5 有四个槽，每个槽放一个球，颜色可能是红色(R)、黄色(Y)、绿色(G)或蓝色(B)。
// 要是你猜对了某个槽的颜色，则算一次“猜中”。要是只是猜对了颜色但槽位猜错了，则算一次“伪猜中”。注意，“猜中”不能算入“伪猜中”。
vector<int> calcResult(string A, string guess) {
    // write code here
    vector<int> result(2, 0);

    for(int i = 0; i < 4; i++){
        if(A[i] == guess[i]){
            result[0]++;
            A[i] = '0';
            guess[i] = '0';
        }
    }
    for(int i = 0; i < 4; i++){
        if(guess[i] == '0')
            continue;
        for(int j = 0; j < 4; j++){
            if(A[j] == guess[i]){
                result[1]++;
                A[j] = '0';
                break;
            }
        }
    }
    return result;
}

//17.6 有一个整数数组，找出索引m和n，只要将m和n之间的元素排好序，整个数组就是有序的。
vector<int> findSegment(vector<int> A, int n) {
    // write code here
    int left = 0;
    while(A[left] <= A[left+1] && left < n-1)
        left++;
    if(left == n-1)
        return vector<int>{0, 0};
    int right = n-1;
    while(A[right] >= A[right-1] && right > 0)
        right--;
    int middle_min = A[left];
    int middle_max = A[right];
    for(int i = left; i <= right; i++){
        middle_min = min(middle_min, A[i]);
        middle_max = max(middle_max, A[i]);
    }

    while(A[left-1] > middle_min){
        left--;
        if(left == 0)
            break;
    }
    while(A[right+1] < middle_max){
        right++;
        if(right == n-1)
            break;
    }

    return vector<int>{left, right};
}

//17.8 对于一个有正有负的整数数组，请找出总和最大的连续数列
int getMaxSum(vector<int> A, int n) {
    // write code here
    int sum = 0;
    int max_sum = A[0];
    for(int i = 0; i < n; i++){
        if(A[i] > 0){
            sum += A[i];
            max_sum = max(max_sum, sum);
        }else if(A[i] + sum > 0){
            sum += A[i];
        }else{
            sum = 0;
        }
    }
    return max_sum;
}

//17.12 找出数组中两数之和为指定值的所有整数对的个数
int countPairs(vector<int> A, int n, int sum) {
    // write code here
    sort(A.begin(), A.end());
    int i = 0;
    int j = n - 1;
    int count = 0;
    while( i < j){
        if(A[i] + A[j] < sum)
            i++;
        else if(A[i] + A[j] > sum)
            j--;
        else if(A[i] == A[j]){
            count += (j - i + 1) * (i - j) / 2;
            break;
        }else{
            int tmp_i = 1;
            while(A[i] == A[i+1]){
                i++;
                tmp_i++;
            }
            int tmp_j = 1;
            while(A[j] == A[j-1]){
                j--;
                tmp_j++;

            }
            count += tmp_i * tmp_j;
            i++;
            j--;
        }

    }
    return count;
}

int main(){


}
