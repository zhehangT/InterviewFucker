//
// Created by T_Zhehang on 2018/3/17.
//

// 11.2 对一个字符串数组进行排序，将所有变位词合并，保留其字典序最小的一个串。这里的变位词指变换其字母顺序所构成的新的词或短语
vector<string> sortStrings(vector<string> str, int n) {
    // write code here
    map<string, string> m;
    vector<string> results;
    for(auto s: str){
        string sort_s = s;
        sort(sort_s.begin(), sort_s.end());
        if(m.find(sort_s) == m.end()){
            m[sort_s] = s;
        }else if(m[sort_s] > s){
            m[sort_s] = s;
        }
    }
    for(auto iter = m.begin(); iter != m.end(); iter++){
        results.emplace_back(iter->second);
    }
    sort(results.begin(), results.end());
    return results;
}

// 11.3 有一个排过序的数组，包含n个整数，但是这个数组向左进行了一定长度的移位,查找某个元素的位置
int find(vector<int>&A, int start, int end, int x){
    if(start > end)
        return -1;
    int mid = (start + end) / 2;
    if(A[mid] == x)
        return mid;
    if(A[mid] < x) {
        if( A[mid] < A[end] && x > A[end])
            return find(A, start, mid-1, x);
        else
            return find(A, mid+1, end, x);
    }else{
        if( A[mid] > A[start] && x < A[start])
            return find(A, mid+1, end, x);
        else
            return find(A, start, mid-1, x);
    }
}

int findElement(vector<int> A, int n, int x) {
    // write code here
    return find(A, 0, n-1, x);
}

// 11.5 有一个排过序的字符串数组，但是其中有插入了一些空字符串，找出给定字符串的位置
int find(vector<string>& str, int start, int end, string x){
    if(start > end)
        return -1;
    int mid = (start + end) / 2;
    if(str[mid] == x)
        return mid;
    int mid_left = mid - 1;
    int mid_right = mid + 1;
    while(str[mid_left] == "" && mid_left > start)
        mid_left--;
    while(str[mid_right] == "" && mid_right < end)
        mid_right++;
    if(str[mid_left] < x)
        return find(str, mid_right, end, x);
    else
        return find(str, start, mid_left, x);

}

int findString(vector<string> str, int n, string x) {
    // write code here
    return find(str, 0, n-1, x);
}

// 11.6 有一个NxM的整数矩阵，矩阵的行和列都是从小到大有序的，查找矩阵中元素x的位置。
int find(vector<int>& row, int start, int end, int x){

    if(start > end)
        return -1;
    int mid = (start + end) / 2;
    if(row[mid] == x)
        return mid;
    if(row[mid] > x)
        return find(row, start, mid-1, x);
    else
        return find(row, mid+1, end, x);
}

vector<int> findElement(vector<vector<int> > mat, int n, int m, int x) {
    // write code here
    for(int i = 1; i < n; i++){
        if( mat[i][0] <= x && mat[i][m-1] >= x){
            int result = find(mat[i], 0, m-1, x);
            if(result != -1)
                return vector<int>{i, result};
        }
    }
    return vector<int>();
}

// 11.7 叠罗汉是一个著名的游戏，游戏中一个人要站在另一个人的肩膀上。同时我们应该让下面的人比上面的人更高一点。
// 已知参加游戏的每个人的身高，计算最多能叠多少个人。注意这里的人都是先后到的，意味着参加游戏的人的先后顺序与原序列中的顺序应该一致
int people = 0;

void heigh(vector<int>& dp, vector<int>& men, int n){
    if(n == men.size())
        return;

    int tmp = 1;
    for(int i = 0; i < n; i++){
        if(men[i] < men[n]){
            tmp = max(tmp, dp[i]+1);
        }
    }
    dp[n] = tmp;
    if(people < tmp)
        people = tmp;
    heigh(dp, men, n+1);
}


int getHeight(vector<int> men, int n) {
    // write code here
    vector<int> dp(n, 0);
    heigh(dp, men, 0);
    return people;
}