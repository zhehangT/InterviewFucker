/**
* Author: T_Zhehang
* Date: 18-3-18
*/

#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <algorithm>
#include <queue>

using namespace std;
// 18.1 请编写一个函数，将两个数字相加。不得使用+或其他算数运算符。
int addAB(int A, int B) {
    // write code here
    while(B != 0){
        int A_ = A ^ B;
        int B_ = A & B;
        B = B_ << 1;
        A = A_;
    }
    return A;
}

// 18.4 请编写一个方法，输出0到n(包括n)中数字2出现了几次
int countNumberOf2s(int n) {
    // write code here
    int count = 0;
    int low = 0;
    int high = 0;
    int cur = 0;
    int flag = 1;
    while(n/flag!=0)
    {
        //低位上的数
        low = n-(n/flag)*flag;
        //当前位上的数
        cur = (n/flag)%10;
        //高位上的数
        high = n/(flag*10);
        if(cur == 1 || cur == 0)
            count += high*flag;
        if(cur == 2)
            count += high*flag + low +1;
        if(cur > 2)
            count += (high+1)*flag;
        flag *= 10;
    }
    return count;
}

//18.5 有一篇文章内含多个单词，现给定两个单词，请设计一个高效算法，找出文中这两个单词的最短距离
int getDistance(vector<string> article, int n, string x, string y) {
    // write code here
    int min_distance = INT_MAX;
    int i_x = -1;
    int i_y = -1;
    for(int i = 0; i < n; i++){
        if(article[i] == x){
            i_x = i;
        }else if(article[i] == y){
            i_y = i;
        }
        if(i_x != -1 && i_y != -1){
            min_distance = min(min_distance, abs(i_x - i_y));
        }
    }
    return min_distance;
}

//18.7 有一组单词，在数组中找出由数组中字符串组成的最长的串A，即A是由其它单词组成的(可重复)最长的单词。
static bool cmp(string a, string b){
    return a.size() > b.size();
}

bool isCompose(vector<string>& str, string s, int i){
    if(s.size() == 0)
        return true;
    for(int j = i+1; j < str.size(); j++){
        if(s.find(str[j]) == 0){
            bool tmp = isCompose(str, s.substr(str[j].size()), i);
            if(tmp)
                return true;
        }
    }
    return false;
}

int getLongest(vector<string> str, int n) {
    // write code here
    sort(str.begin(), str.end(), cmp);
    for(int i = 0; i < n; i++){
        if(isCompose(str, str[i], i))
            return str.size();
    }
    return -1;
}

//18.9 现有一些随机生成的数字要将其依次传入，对于每次传入一个数字后，算出当前所有传入数字的中位数
// 利用单个set进行排序和查找
vector<int> getMiddle(vector<int> A, int n) {
    // write code here
    vector<int> result(n);
    multiset<int> s;
    for(int i = 0; i < 2; i++){
        s.insert(A[i]);
        result[i] = *s.begin();
    }
    for(int i = 2; i < n; i++){
        s.insert(A[i]);
        auto begin_ = s.begin();
        auto begin2_ = s.begin();
        while(true){
            if(begin2_ == s.end()){
                result[i] = *(--begin_);
                break;
            }else if((++begin2_) == s.end()){
                result[i] = *(begin_);
                break;
            }
            begin_++;
            begin2_++;
        }
    }
    return result;
}

// 利用两个set进行排序和查找
vector<int> getMiddle2(vector<int> A, int n) {
    // write code here
    vector<int> result(n);
    multiset<int> min_s;
    multiset<int> max_s;
    min_s.insert(A[0]);
    result[0] = A[0];
    for(int i = 1; i < n; i++){
        auto iter = min_s.rbegin();
        auto iter2 = max_s.begin();
        if(min_s.size() == max_s.size()){
            if(*iter > A[i])
                min_s.insert(A[i]);
            else
                max_s.insert(A[i]);
        }else if(min_s.size() > max_s.size()){
            if(*iter > A[i]){
                max_s.insert(*iter);
                min_s.erase(*iter);
                min_s.insert(A[i]);
            }else{
                max_s.insert(A[i]);
            }
        }else{
            if(*iter2 < A[i]){
                min_s.insert(*iter2);
                max_s.erase(*iter2);
                max_s.insert(A[i]);
            }else{
                min_s.insert(A[i]);
            }
        }
        if(min_s.size() >= max_s.size()){
            result[i] = *min_s.rbegin();
        }else{
            result[i] = *max_s.begin();
        }
    }
    return result;
}

// priority_queue版本，速度最快
vector<int> getMiddle3(vector<int> A, int n) {
    // write code here
    vector<int> result(n);
    priority_queue<int, vector<int>, less<int>> less;
    priority_queue<int, vector<int>, greater<int>> big;
    less.push(A[0]);
    result[0] = A[0];
    for(int i = 1; i < n; i++){
        if(less.size() == big.size()){
            if(big.top() > A[i])
                less.push(A[i]);
            else
                big.push(A[i]);
        }else if(less.size() > big.size()){
            if(less.top() > A[i]){
                big.push(less.top());
                less.pop();
                less.push(A[i]);
            }else{
                big.push(A[i]);
            }
        }else{//less.size() < big.size()
            if(big.top() < A[i]){
                less.push(big.top());
                big.pop();
                big.push(A[i]);
            }else{
                less.push(A[i]);
            }
        }
        if(less.size() >= big.size()){
            result[i] = less.top();
        }else{
            result[i] = big.top();
        }
    }
    return result;
}

//["abc","adc","bdc","aaa”],4,”abc","bdc"
bool isNext(const string& s1, const string& s2){
    if(s1.size() != s2.size() || s1 == s2)
        return false;
    int c = 0;
    for(int i = 0; i < s1.size(); i++){
        if(s1[i] != s2[i])
            c++;
        if(c > 1)
            return false;
    }
    return true;
}

int bfs(vector<string>& dic, string s, string t){

    queue<pair<string, int>> q;
    vector<bool> isVisited(dic.size(), false);

    q.push(pair<string, int>(s, 0));
    while(!q.empty()){
        pair<string, int> next = q.front();
        q.pop();
        for(int i = 0; i < dic.size(); i++){
            if(!isVisited[i] && isNext(next.first, dic[i])){
                if(dic[i] == t)
                    return next.second+1;
                else {
                    q.push(pair<string, int>(dic[i], next.second+1));
                    isVisited[i] = true;
                }
            }
        }
    }
    return -1;

}

int countChanges(vector<string> dic, int n, string s, string t) {
    // write code here
    if(s == t)
        return 0;
    return bfs(dic, s, t);
}

// 18.11 有一个方阵，其中每个单元(像素)非黑即白(非0即1)，找到四条边颜色相同的最大子方阵。
// 暴力法
int maxSubMatrix(vector<vector<int> > mat, int n) {
    //选定最大子方阵的边长，选择顶点，判断是合法 
    int maxLength = n;
    while(maxLength){
        for(int i = 0; i <= n - maxLength; ++i){
            for(int j = 0; j <= n - maxLength; ++j){
                int pixel = mat[i][j];
                bool flag = true;
                for(int k = 0; k < maxLength; ++k){
                    int top = mat[i][j + k]; // 上边的线
                    int bottom = mat[i + maxLength - 1][j + k];  // 下边的线
                    int left = mat[i + k][j]; // 左边的线
                    int right = mat[i + k][j + maxLength -1]; // 右边的线
                    if(top != pixel || bottom != pixel || left != pixel || right != pixel){
                        flag = false;
                        break;
                    }
                }
                if(flag)
                return maxLength;
            }
        }
        maxLength--;
    }
    return 0;
}


void processMatrix(vector<vector<int>>& mat, vector<vector<pair<int, int>>>& mat_black, vector<vector<pair<int, int>>>& mat_white){

    for(int i = 0; i < mat.size(); i++){
        for(int j = 0; j < mat.size(); j++){
            if(mat[i][j] == 0){
                mat_white[i][j] = pair<int, int>(0, 0);
                if(i == 0 && j == 0){
                    mat_black[i][j] = pair<int, int>(1, 1);
                }else if(i == 0){
                    mat_black[i][j] = pair<int, int>(mat_black[i][j-1].first+1, 1);
                }else if(j == 0){
                    mat_black[i][j] = pair<int, int>(1, mat_black[i-1][j].second+1);
                }else{
                    mat_black[i][j] = pair<int, int>(mat_black[i][j-1].first+1, mat_black[i-1][j].second+1);
                }
            }else{
                mat_black[i][j] = pair<int, int>(0, 0);
                if(i == 0 && j == 0){
                    mat_white[i][j] = pair<int, int>(1, 1);
                }else if(i == 0){
                    mat_white[i][j] = pair<int, int>(mat_white[i][j-1].first+1, 1);
                }else if(j == 0){
                    mat_white[i][j] = pair<int, int>(1, mat_white[i-1][j].second+1);
                }else{
                    mat_white[i][j] = pair<int, int>(mat_white[i][j-1].first+1, mat_white[i-1][j].second+1);
                }
            }
        }
    }
}

// 通过processMatrix缓存每个位置往左和往上的最长长度
int maxSubMatrix2(vector<vector<int> > mat, int n) {
    // write code here
    vector<vector<pair<int, int>>> mat_black(n, vector<pair<int, int>>(n));
    vector<vector<pair<int, int>>> mat_white(n, vector<pair<int, int>>(n));
    processMatrix(mat, mat_black, mat_white);

    int maxLength = n;
    while(maxLength){
        for(int i = 0; i <= n - maxLength; ++i){
            for(int j = 0; j <= n - maxLength; ++j){
                if(mat_black[i][j+maxLength-1].first >= maxLength
                   && mat_black[i+maxLength-1][j].second >= maxLength
                   && mat_black[i+maxLength-1][j+maxLength-1].first >= maxLength
                   && mat_black[i+maxLength-1][j+maxLength-1].second >= maxLength){
                    return maxLength;
                }else if(mat_white[i][j+maxLength-1].first >= maxLength
                         && mat_white[i+maxLength-1][j].second >= maxLength
                         && mat_white[i+maxLength-1][j+maxLength-1].first >= maxLength
                         && mat_white[i+maxLength-1][j+maxLength-1].second >= maxLength){
                    return maxLength;
                }
            }
        }
        maxLength--;
    }
    return 0;
}

// 18.12 有一个正整数和负整数组成的NxN矩阵，请编写代码找出元素总和最大的子矩阵
int sumOfSubMatrix(vector<vector<int> > mat, int n) {
    // write code here
    int result = INT_MIN;
    for(int i = 0; i < n; i++){
        vector<int> mat_help(n);
        for(int j = i; j < n; j++){
            if(i == j){
                for(int k = 0; k < n; k++){
                    mat_help[k] = mat[j][k];
                }
            }else{
                for(int k = 0; k < n; k++){
                    mat_help[k] = mat_help[k] + mat[j][k];
                }
            }
            vector<int> mat_help_tmp = mat_help;
            int tmp = mat_help_tmp[0];
            for(int k = 1; k < n; k++){
                mat_help_tmp[k] = max(mat_help_tmp[k], mat_help_tmp[k-1]+mat_help_tmp[k]);
                tmp = max(tmp, mat_help_tmp[k]);
            }
            result = max(result, tmp);
        }
    }
    return result;
}

int main(){

    vector<string> dic{"ph","b","ibl","na","a","a","b","a","b","a","b","a","j"};
    cout << countChanges(dic,13,"j","a") << endl;


}