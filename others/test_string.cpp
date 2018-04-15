/**
* Author: T_Zhehang 
* Date: 18-3-2
* 操作string的相关代码
*/
#include <string>
#include <iostream>

using namespace std;

int main(){

    string s = "hello world";
    cout << "string s: " << s << endl;
    cout << "s.length(): " << s.length() << endl;
    cout << "s.size(): " << s.length() << endl;
    cout << (s[11] == '\0') << endl;
    s.replace(5, 1, "%20");
    cout << s << endl;
    return 0;
}