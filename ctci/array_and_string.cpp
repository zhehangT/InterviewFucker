/**
* Author: T_Zhehang 
* Date: 18-3-2
*/
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

//1.1 判断一个字符串里面的所有字符是否全都不同
bool QuickCheck( string& s, int start, int end )
{

    if ( start < end )
    {
        int i = start - 1;
        int flag = s[end];
        for ( int j = start; j < end; j++ )
        {
            if ( s[j] < flag )
            {
                i++;
                int tmp = s[i];
                s[i] = s[j];
                s[j] = tmp;
            }
            else if( s[j] == flag)
                return false;
        }
        i++;
        s[end] = s[i];
        s[i] = flag;
        return QuickCheck(s, start, i - 1) && QuickCheck(s, i + 1, end);
    }
    return true;
}

//1.2 不利用额外的存储空间，进行字符串反转
string reverseString(string iniString) {
    // write code here
    int i_max = iniString.size()-1;
    for(int i = 0; i < iniString.size()/2; i++){
        iniString[i_max+1] = iniString[i];
        iniString[i] = iniString[i_max-i];
        iniString[i_max-i] = iniString[i_max+1];
    }
    iniString[i_max+1] = '\0';
    return iniString;
}

//1.3 给定两个字符串，请编写程序，确定其中一个字符串的字符重新排列后，能否变成另一个字符串
bool checkSam(string stringA, string stringB) {
    // write code here
    if(stringA.size() != stringB.size())
        return false;
    int a[256] = {0};
    int b[256] = {0};
    for(int i = 0; i < stringA.size(); i++){
        a[stringA[i]]++;
        b[stringB[i]]++;
    }
    for(int i = 0; i < 256; i++){
        if(a[i]!=b[i])
            return false;
    }
    return true;
}

//1.4 将字符串中的空格全部替换为“%20”
string replaceSpace(string iniString, int length) {
    // write code here
    for(int i=0; i<iniString.size();){

        if(iniString[i] == ' '){
            iniString.replace(i, 1, "%20");
            i += 3;
        }
        else
            i++;
    }
    return iniString;
}

string replaceSpace2(string iniString, int length) {

    int num_space = 0;
    for(int i = 0; i < length; i++){
        if(iniString[i] == ' ')
            num_space++;
    }

    int new_length = length + 2*num_space;

    int i = length-1;
    int j = new_length-1;
    iniString[new_length] = '\0';
    while(i >= 0){
        if(iniString[i] == ' '){
            iniString[j--] = '0';
            iniString[j--] = '2';
            iniString[j--] = '%';
            i--;
        }
        else{
            iniString[j--] = iniString[i--];
        }
    }
    return iniString;
}

//1.5 利用字符重复出现的次数，编写一个方法，实现基本的字符串压缩功能。
// 比如，字符串“aabcccccaaa”经压缩会变成“a2b1c5a3”。
// 若压缩后的字符串没有变短，则返回原先的字符串。
int CompressedLength(string s){
    int length = 0;
    int count = 1;
    char c = s[0];
    for(int i=1; i < s.size(); i++){
        if(c != s[i]){
            length += (to_string(count).size()+1);
            c = s[i];
            count = 1;
        }else{
            count++;
        }
    }
    length += (to_string(count).size()+1);
    return length;

}

string zipString(string iniString) {
    // write code here
    int compressedLength = CompressedLength(iniString);
    if(compressedLength >= iniString.size())
        return iniString;
    char s[compressedLength];
    int count = 1;
    int index = 0;
    char c = iniString[0];
    for(int i = 1; i < iniString.size(); i++){

        if( c == iniString[i]){
            count++;
        }else{
            s[index++] = c;
            string s_count = to_string(count);
            for(int j = 0; j < s_count.size(); j++)
                s[index++] = s_count[j];
            c = iniString[i];
            count = 1;
        }
    }
    s[index++] = c;
    string s_count = to_string(count);
    for(int j = 0; j < s_count.size(); j++)
        s[index++] = s_count[j];
    s[compressedLength] = '\0';
    assert(index == compressedLength);
    return s;
}

//1.6 有一副由NxN矩阵表示的图像，在不占用额外内存空间的情况下(即不使用缓存矩阵)，将图像顺时针旋转90度。
vector<vector<int> > transformImage(vector<vector<int> > mat, int n) {
    // write code here
    for(int i = 0; i < n/2; i++){
        for(int j = i; j < n - i - 1; j++){
            int temp = mat[i][j];
            mat[i][j] = mat[n-j-1][i];
            mat[n-j-1][i] = mat[n-i-1][n-j-1];
            mat[n-i-1][n-j-1] = mat[j][n-i-1];
            mat[j][n-i-1] = temp;
        }
    }
    return mat;
}

// 1.7 若N阶方阵中某个元素为0，则将其所在的行与列清零。
vector<vector<int> > clearZero(vector<vector<int> > mat, int n) {
    // write code here
    bool *row = new bool[n]();
    bool *col = new bool[n]();
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            if(mat[i][j] == 0){
                row[i] = true;
                col[j] = true;
            }
        }

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            if(row[i] || col[j]){
                mat[i][j] = 0;
            }
        }
    return mat;
}

// 1.8 给定两个字符串s1和s2，请编写代码检查s2是否为s1旋转而成
bool checkReverseEqual(string s1, string s2) {
    // write code here
    if(s1.size() == s2.size() && s1.size() > 0){
        string s = s1 + s1;
        return s.find(s2) <= s2.size();
    }
    return false;
}

int main(){


    return 0;
}