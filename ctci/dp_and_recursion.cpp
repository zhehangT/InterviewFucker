/**
* Author: T_Zhehang
* Date: 18-3-16
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
//9.1 楼梯有n阶台阶，小孩一次可以上1阶、2阶、3阶。计算小孩有多少种上楼的方式。
int countWays(int n) {
    // write code here
    int* a = new int[n];
    a[0] = 1;
    a[1] = 2;
    a[2] = 4;
    for(int i = 3; i < n ; i++)
        a[i] = a[i-1] + a[i-2] + a[i-3];
    return a[n-1];
}

//9.2 有一个XxY的网格，一个机器人只能走格点且只能向右或向下走，要从左上角走到右下角，计算机器人有多少种走法。

int f(int x){
    int x_ = 1;
    for(int i = 1; i <= x; i++)
        x_ *= i;
    return x_;

}

int countWays(int x, int y) {
    // write code here
    return f(x-1+y-1) / (f(x-1) * f(y-1));
}

// 有障碍点
int countWays(vector<vector<int> > map, int x, int y) {
    // write code here
    vector<vector<int> > dp(x,vector<int>(y,0));
    for(int i = 0; i < x; i++)
        for(int j = 0; j < y; j++){
            if(map[i][j] != 1)
                continue;
            if(i == 0 && j == 0)
                dp[i][j] = 1;
            else if(i == 0)
                dp[i][j] = dp[i][j-1];
            else if(j == 0)
                dp[i][j] = dp[i-1][j];
            else
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    return dp[x-1][y-1];
}

//9.3 在数组A[0..n-1]中，有所谓的魔术索引，满足条件A[i]=i。给定一个升序数组，元素值各不相同，判断在数组A中是否存在魔术索引
bool find(vector<int>& A, int start, int end){
    if(start > end)
        return false;
    int mid = (start + end) / 2;
    if(A[mid] == mid)
        return true;
    else if(A[mid] > mid)
        return find(A, start, mid - 1);
    else
        return find(A, mid + 1, end);
}

bool findMagicIndex(vector<int> A, int n) {
    // write code here
    return find(A, 0, n);
}

// 有重复
bool find2(vector<int>& A, int start, int end){
    if(start > end)
        return false;
    int mid = (start + end) / 2;
    if(A[mid] == mid)
        return true;

    int leftIndex = min(A[mid], mid-1);
    if(find(A, start, leftIndex))
        return true;

    int rightIndex = max(A[mid], mid+1);
    return find(A, rightIndex, end);
}

bool findMagicIndex2(vector<int> A, int n) {
    // write code here
    return find2(A, 0, n);
}

//9.4 返回某集合的所有非空子集
void sub(vector<vector<int>>& results, vector<int> result, vector<int> a){
    if(a.empty()){
        if(result.empty())
            return;
        results.emplace_back(result);
        return;
    }
    auto iter_last = a.end() - 1;
    vector<int> tmp = result;
    tmp.emplace_back(*iter_last);
    a.erase(iter_last);
    sub(results, tmp, a);
    sub(results, result, a);
}

vector<vector<int> > getSubsets(vector<int> A, int n) {
    // write code here
    vector<vector<int>> results;
    vector<int> result;
    sub(results, result, A);
    return results;
}

//9.5 编写一个方法，确定某字符串的所有排列组合。
void permutation(vector<string>& results, string a, string b){
    if(b == ""){
        results.emplace_back(a);
        return;
    }
    for(int i = b.size()-1; i >= 0; i--){
        string sa = a + b[i];
        string sb;
        for(int j = 0; j < b.size(); j++){
            if(j != i)
                sb.push_back(b[j]);
        }

        permutation(results, sa, sb);
    }
}

vector<string> getPermutation(string A) {
    // write code here
    vector<string> results;
    permutation(results, "", A);
    sort(results.rbegin(), results.rend());
    return results;
}



// 9.9 有数量不限的硬币，币值为25分、10分、5分和1分，请编写代码计算n分有几种表示法。
int countWays2(int n) {
    int coins[4]={1,5,10,25};
    int dp[100001]={0};
    dp[0]=1;
    for(int i=0;i<4;i++)
        for(int j=coins[i];j<=n;j++)
            dp[j] =(dp[j]+dp[j-coins[i]])%1000000007;
    return dp[n];
}

// 9.10 这里的n皇后问题指在一个nxn的棋盘上放置n个棋子，使得每行每列和每条对角线上都只有一个棋子，求其摆放的方法数。
int count_queene = 0;
bool valid(vector<int> result, int row, int col, int n){
    for(int row_ = 0; row_ < row; row_++){
        int col_ = result[row_];
        if(col == col_ || col - col_ == row - row_  || col - col_ == row_ - row)
            return false;
    }
    return true;
}

void placeQueene(int row, vector<int> result, vector<vector<int>>& results, int n){
    if(row == n){
//        results.emplace_back(result);
        count_queene++;
        return;
    }
    for(int col = 0; col < n; col++){
        if(valid(result, row, col, n)){
            result[row] = col;
            placeQueene(row+1, result, results, n);
        }
    }
}

int nQueens(int n) {
    // write code here
    vector<vector<int>> results;
    vector<int> result(n, -1);
    placeQueene(0, result, results, n);
    return count_queene;
}

// 数组版本
bool Place(int *a,int i){
    for(int j=1;j<i;j++)
        if((a[j]==a[i])||(a[j]-a[i]==(j-i))||(a[j]-a[i]==i-j))
            return 0;
    return 1;
}

void Queens1(int a[],int i,int n,int &count){
    if(i>n){
        count++;
        return ;
    }
    for(int j=1;j<=n;j++){
        a[i]=j;
        if(Place(a,i))
            Queens1(a,i+1,n,count);
    }
}


int nQueens_(int n) {
    // write code here
    int count=0;
    int *a=new int[n+1];
    Queens1(a,1,n,count);
    return count;
}



// 每次调用dfs时，会一直递归，计算最小的那个box的高度
int dfs(int bottom, vector<vector<bool>>& a, vector<int>& h, vector<int>& dp){

    if(dp[bottom] > 0)
        return dp[bottom];
    int n = a.size();
    int top = 0;
    // 遍历 box 中可以放在 bottom 上面的
    // 取其中高度的最大值
    for(int i = 0; i < n; i++){
        if(a[bottom][i])
            top = max(top, dfs(i, a, h, dp));
    }
    dp[bottom] = top + h[bottom];
    return dp[bottom];
}

int getHeight(vector<int> w, vector<int> l, vector<int> h, int n) {
    // write code here
    vector<vector<bool>> a(n, vector<bool>(n, false));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(w[i] > w[j] && l[i] > l[j])
                a[i][j] = true;
        }
    }

    vector<int> dp(n, 0);
    int ans = 0;
    // 比较以每个box作为底时的高度，得到其中的最大值
    for(int i = 0; i < n; i++){
        int tmp = dfs(i, a, h, dp);
        ans = max(ans, tmp);
    }
            return ans;
}


int main(){

    cout << nQueens_(12) << endl;
    cout << nQueens(12) << endl;

}